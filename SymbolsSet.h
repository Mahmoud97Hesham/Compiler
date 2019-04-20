#include "Symbol.h"
#include <vector>
using namespace std;

class SymbolsSet {
  vector<Symbol> symbols;
  public:
  void addSymbol(Symbol);
  void addSymbolWithoutRepetition(Symbol);
  Symbol getFirst();
  vector<Symbol> getSymbolsVector();
};
