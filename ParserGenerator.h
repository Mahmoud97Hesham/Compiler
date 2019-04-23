#include "ParsingTableRow.h"

using namespace std;
class ParserGenerator {
  unsigned long prSize;
  vector<ProductionRule> productionRules;
  vector<SymbolsSet> first;
  vector<SymbolsSet> follow;
  vector<bool> firstFollowEvaluated;
  vector<ParsingTableRow> parsingTable;
  public:
  ParserGenerator(vector<ProductionRule>);
  vector<SymbolsSet> getFirst();
  vector<SymbolsSet> getFollow();
  vector<Symbol> getCorrespondingSymbols(Symbol, Symbol);
  private:
  void generateFirst(int);
  void firstLeftRecursive(int, SymbolsSet, int);
  int getNTSymbolProductionRuleIndex(Symbol);
  Symbol getNextSymbol(SymbolsSet, Symbol);
  void generateFollow(int);
  void copyFollow(int, int);
  void copyFirstToFollow(int, int, SymbolsSet, int);
  void addProductionRuleToParsingTable(int, SymbolsSet, Symbol);
  void continueParsingTable();
};
