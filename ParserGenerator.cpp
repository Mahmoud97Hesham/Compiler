#include "ParserGenerator.h"
#include <iostream>

ParserGenerator::ParserGenerator(vector<ProductionRule> _productionRules) {
  productionRules = _productionRules;
  prSize = productionRules.size();
  first.resize(prSize);
  follow.resize(prSize);
  firstFollowEvaluated.resize(prSize*2);
  for(int i = 0; i < prSize; ++i) {
    if(!firstFollowEvaluated[i]) generateFirst(i);
  }
  Symbol end = Symbol("$");
  end.setTerminal(true);
  follow[0].addSymbol(end);
  for(int i = 0; i < prSize; ++i) {
    if(!firstFollowEvaluated[i+prSize]) generateFollow(i);
  }
}

vector<SymbolsSet> ParserGenerator::getFirst() {
  return first;
}

vector<SymbolsSet> ParserGenerator::getFollow() {
  return follow;
}

void ParserGenerator::generateFirst(int index) {
  ProductionRule pr = productionRules[index];
  for(int i = 0; i < pr.getRHSSize(); ++i) {
    SymbolsSet ss_i = pr.getRHS(i);
    Symbol firstSymbol_i = ss_i.getFirst();
    if(firstSymbol_i.isTerminal()) {
      first[index].addSymbolWithoutRepetition(firstSymbol_i);
    } else {
      firstLeftRecursive(index, ss_i, getNTSymbolProductionRuleIndex(firstSymbol_i));
    }
  }
  firstFollowEvaluated[index] = true;
}

void ParserGenerator::firstLeftRecursive(int first_i, SymbolsSet ss, int recursive) {
  if(!firstFollowEvaluated[recursive]) generateFirst(recursive);
  vector<Symbol> recursiveSymbols = first[recursive].getSymbolsVector();
  for(int i = 0; i < recursiveSymbols.size(); ++i) {
    Symbol symbol = recursiveSymbols[i];
    if(symbol.isEpsilon()) {
      Symbol nextSymbol = getNextSymbol(ss, productionRules[recursive].getName());
      if(nextSymbol.isEqual("")) first[first_i].addSymbolWithoutRepetition(symbol);
      else if(nextSymbol.isTerminal()) first[first_i].addSymbolWithoutRepetition(nextSymbol);
      else firstLeftRecursive(first_i, ss, getNTSymbolProductionRuleIndex(nextSymbol));
    }
    else if(symbol.isTerminal()) first[first_i].addSymbolWithoutRepetition(symbol);
    else firstLeftRecursive(first_i, ss, getNTSymbolProductionRuleIndex(symbol));
  }
}

int ParserGenerator::getNTSymbolProductionRuleIndex(Symbol symbol) {
  for(int i = 0; i < prSize; ++i) {
    if (productionRules[i].getName().isEqual(symbol.getName())) return i;
  }
  return -1;
}

Symbol ParserGenerator::getNextSymbol(SymbolsSet ss, Symbol symbol) {
  vector<Symbol> symbolsVector = ss.getSymbolsVector();
  for(int i = 0; i < symbolsVector.size(); ++i) {
    if(symbolsVector[i].isEqual(symbol.getName()) && (i == symbolsVector.size()-1 || !symbolsVector[i+1].isEqual(symbol.getName()))) return symbolsVector[i+1];
  }
  return Symbol();
}

void ParserGenerator::generateFollow(int index) {
  Symbol symbol = productionRules[index].getName();
  for(int i = 0; i < prSize; ++i) {
    if(index == i) continue;
    for(int j = 0; j < productionRules[i].getRHSSize(); ++j) {
      SymbolsSet ss_j = productionRules[i].getRHS(j);
      vector<Symbol> ssVec_j = ss_j.getSymbolsVector();
      for(int k = 0; k < ssVec_j.size(); ++k) {
        if(ssVec_j[k].isEqual(symbol.getName())) {
          if(k == ssVec_j.size() - 1) {
            copyFollow(index, i);
          } else if(ssVec_j[k+1].isTerminal()) {
            follow[index].addSymbolWithoutRepetition(ssVec_j[k+1]);
          } else {
            copyFirstToFollow(index, i, ss_j, getNTSymbolProductionRuleIndex(ssVec_j[k+1]));
          }
        }
      }
    }
  }
  firstFollowEvaluated[index+prSize] = true;
}

void ParserGenerator::copyFollow(int follow_i, int copy_i) {
  if(!firstFollowEvaluated[copy_i+prSize]) generateFollow(copy_i);
  vector<Symbol> copyFollowSymbols = follow[copy_i].getSymbolsVector();
  for(int i = 0; i < copyFollowSymbols.size(); ++i) {
    follow[follow_i].addSymbolWithoutRepetition(copyFollowSymbols[i]);
  }
}

void ParserGenerator::copyFirstToFollow(int follow_i, int followPR_i, SymbolsSet currentSS, int copy_i) {
  vector<Symbol> copyFirstSymbols = first[copy_i].getSymbolsVector();
  for(int i = 0; i < copyFirstSymbols.size(); ++i) {
    if(copyFirstSymbols[i].isEpsilon()) {
      Symbol nextSymbol = getNextSymbol(currentSS, productionRules[copy_i].getName());
      if(nextSymbol.isEqual("")) copyFollow(follow_i, followPR_i);
      else if(nextSymbol.isTerminal()) follow[follow_i].addSymbolWithoutRepetition(nextSymbol);
      else copyFirstToFollow(follow_i, followPR_i, currentSS, getNTSymbolProductionRuleIndex(nextSymbol));
    } else {
      follow[follow_i].addSymbolWithoutRepetition(copyFirstSymbols[i]);
    }
  }
}
