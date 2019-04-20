#include "ProductionRule.h"
using namespace std;

class ParserGenerator {
  unsigned long prSize;
  vector<ProductionRule> productionRules;
  vector<SymbolsSet> first;
  vector<SymbolsSet> follow;
  vector<bool> firstFollowEvaluated;
  public:
  ParserGenerator(vector<ProductionRule>);
  vector<SymbolsSet> getFisrt();
  private:
  void generateFirst(int);
  void firstLeftRecursive(int, SymbolsSet, int);
  int getNTSymbolProductionRuleIndex(Symbol);
  Symbol getNextSymbol(SymbolsSet, Symbol);
};
