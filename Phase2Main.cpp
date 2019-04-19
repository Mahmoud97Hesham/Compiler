#include <iostream>
#include "ProductionRule.h"
using namespace std;

int main() {
  vector<ProductionRule> prVec;

  string s = "METHOD_BODY";
  Symbol s1 = Symbol(s);
  ProductionRule pr1 = ProductionRule(s1);
  Symbol s2 = Symbol("STATEMENT_LIST");
  pr1.addSymbol(s2, true);

  prVec.push_back(pr1);

  
  cout << s2.isEqual("STATEMENT_LIST") << endl;   // should print true
  
  ProductionRule pr2 = ProductionRule(s2);
  Symbol s3 = Symbol("STATEMENT");
  pr2.addSymbol(s3, true);
  pr2.addSymbol(s2, true);
  pr2.addSymbol(s3, false);

  prVec.push_back(pr2);
  return 0;
}
