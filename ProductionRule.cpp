#include "ProductionRule.h"
#include <iostream>

ProductionRule::ProductionRule(Symbol _name) {
  name = _name;
}

void ProductionRule::addSymbol(Symbol s, bool newSet) {
  if(newSet) {
    SymbolsSet symbolsSet;
    symbolsSet.addSymbol(s);
    RHS.push_back(symbolsSet);
  } else {
    if (!RHS.empty())
      RHS.back().addSymbol(s);
  }
}

Symbol ProductionRule::getName() {
  return name;
}

SymbolsSet ProductionRule::getRHS(int index) {
  return RHS[index];
}

unsigned long ProductionRule::getRHSSize() {
  return RHS.size();
}

vector<SymbolsSet> ProductionRule::getRHS() {
  return this->RHS;
}
vector<SymbolsSet> *ProductionRule::getAllRHSpointer() {
  return &this->RHS;
}
SymbolsSet* ProductionRule::getRHSPointer(int index) {
    return &RHS[index];
}

