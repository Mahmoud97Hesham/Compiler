#include "construct_LL1_grammer.h"
using namespace std;

class ParsingTableRow {
  Symbol nonTerminal;
  vector<Symbol> terminals;
  vector<SymbolsSet> row;
  public:
  ParsingTableRow(Symbol);
  void addEntry(SymbolsSet, Symbol);
  bool equals(Symbol);
  vector<Symbol> getCorrespondingSymbols(Symbol);
};
