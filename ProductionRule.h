#include "SymbolsSet.h"
#include <vector>
using namespace std;

class ProductionRule {
  Symbol name;
  vector<SymbolsSet> RHS;

  public:
  ProductionRule(Symbol);
  void addSymbol(Symbol, bool);
  Symbol getName();
  SymbolsSet getRHS(int);
  unsigned long getRHSSize();
  vector<SymbolsSet>getRHS();
  SymbolsSet* getRHSPointer(int index);
  vector<SymbolsSet>*getAllRHSpointer();
};
