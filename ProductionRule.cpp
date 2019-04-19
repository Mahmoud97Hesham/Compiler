#include "ProductionRule.h"

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
