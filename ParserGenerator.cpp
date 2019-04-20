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
}

vector<SymbolsSet> ParserGenerator::getFisrt() {
  return first;
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
