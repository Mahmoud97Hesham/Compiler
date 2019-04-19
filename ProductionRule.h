#include <vector>
#include "SymbolsSet.h"
using namespace std;

class ProductionRule {
  Symbol name;
  vector<SymbolsSet> RHS;
  public:
  ProductionRule(Symbol);
  void addSymbol(Symbol, bool);
};