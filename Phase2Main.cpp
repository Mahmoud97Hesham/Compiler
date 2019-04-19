#include <iostream>
#include "ParserGenerator.h"
using namespace std;

int main() {
  vector<ProductionRule> prVec;

  Symbol S = Symbol("S");
  Symbol A = Symbol("A");
  Symbol B = Symbol("B");
  Symbol C = Symbol("C");
  Symbol D = Symbol("D");
  Symbol E = Symbol("E");
  Symbol a = Symbol("a");
  Symbol b = Symbol("b");
  Symbol c = Symbol("c");
  Symbol d = Symbol("d");
  Symbol e = Symbol("e");
  Symbol epsilon = Symbol("epsilon");
  
  ProductionRule pr1 = ProductionRule(S);
  pr1.addSymbol(A, true);
  pr1.addSymbol(B, false);
  pr1.addSymbol(C, false);
  pr1.addSymbol(D, false);
  pr1.addSymbol(E, false);
  prVec.push_back(pr1);

  cout << A.isEqual("a") << endl;   // should print true
  
  ProductionRule pr2 = ProductionRule(A);
  pr2.addSymbol(a, true);
  pr2.addSymbol(epsilon, true);
  prVec.push_back(pr2);
  
  ProductionRule pr3 = ProductionRule(B);
  pr3.addSymbol(b, true);
  pr3.addSymbol(epsilon, true);
  prVec.push_back(pr3);
  
  ProductionRule pr4 = ProductionRule(C);
  pr4.addSymbol(c, true);
  prVec.push_back(pr4);
  
  ProductionRule pr5 = ProductionRule(D);
  pr5.addSymbol(d, true);
  pr5.addSymbol(epsilon, true);
  prVec.push_back(pr5);
  
  ProductionRule pr6 = ProductionRule(E);
  pr6.addSymbol(e, true);
  pr6.addSymbol(epsilon, true);
  prVec.push_back(pr6);
  
  ParserGenerator pg = ParserGenerator(prVec);
  return 0;
}
