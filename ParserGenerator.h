#include "ProductionRule.h"
using namespace std;

class ParserGenerator {
  vector<ProductionRule> productionRules;
  vector<SymbolsSet> first;
  vector<SymbolsSet> follow;
  public:
  ParserGenerator(vector<ProductionRule>);
  void generateFirst();
};