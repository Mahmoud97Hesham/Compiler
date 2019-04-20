#include "SymbolsSet.h"

void SymbolsSet::addSymbol(Symbol s) {
  symbols.push_back(s);
}

void SymbolsSet::addSymbolWithoutRepetition(Symbol s) {
  for(int i = 0; i < symbols.size(); ++i) {
    if(symbols[i].isEqual(s.getName())) return;
  }
  symbols.push_back(s);
}

Symbol SymbolsSet::getFirst() {
  return symbols.front();
}

vector<Symbol> SymbolsSet::getSymbolsVector() {
  return symbols;
}
