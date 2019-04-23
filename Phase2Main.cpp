#include <iostream>
#include "SyntaxRulesParser.h"

using namespace std;

/*void example1();
void example2();
void example3();
void example4();
void example5();
void example6();
void example7();
void example8();
void printSymbolsSetVector(vector<SymbolsSet>);*/

int main() {
  /*example1();
  example2();
  example3();
  example4();
  example5();
  example6();
  example7();
  example8();*/
  SyntaxRulesParser syntax;
  syntax.readSyntaxRules("SyntaxRules");

  return 0;
}

/*void example1() {
  vector<ProductionRule> prVec;
  
  Symbol S = Symbol("S");
  Symbol A = Symbol("A");
  Symbol B = Symbol("B");
  Symbol C = Symbol("C");
  Symbol D = Symbol("D");
  Symbol E = Symbol("E");
  Symbol a = Symbol("a");
  a.setTerminal(true);
  Symbol b = Symbol("b");
  b.setTerminal(true);
  Symbol c = Symbol("c");
  c.setTerminal(true);
  Symbol d = Symbol("d");
  d.setTerminal(true);
  Symbol e = Symbol("e");
  e.setTerminal(true);
  Symbol epsilon = Symbol("epsilon");
  epsilon.setTerminal(true);
  
  ProductionRule pr1 = ProductionRule(S);
  pr1.addSymbol(A, true);
  pr1.addSymbol(B, false);
  pr1.addSymbol(C, false);
  pr1.addSymbol(D, false);
  pr1.addSymbol(E, false);
  prVec.push_back(pr1);
  
  //  cout << A.isEqual("a") << endl;   // should print false
  
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
  vector<SymbolsSet> pgFirst = pg.getFirst();
  printSymbolsSetVector(pgFirst);
  printSymbolsSetVector(pg.getFollow());
}

void example2() {
  vector<ProductionRule> prVec;
  
  Symbol S = Symbol("S");
  Symbol B = Symbol("B");
  Symbol C = Symbol("C");
  Symbol a = Symbol("a");
  a.setTerminal(true);
  Symbol b = Symbol("b");
  b.setTerminal(true);
  Symbol c = Symbol("c");
  c.setTerminal(true);
  Symbol d = Symbol("d");
  d.setTerminal(true);
  Symbol epsilon = Symbol("epsilon");
  epsilon.setTerminal(true);
  
  ProductionRule pr1 = ProductionRule(S);
  pr1.addSymbol(B, true);
  pr1.addSymbol(b, false);
  pr1.addSymbol(C, true);
  pr1.addSymbol(d, false);
  prVec.push_back(pr1);
  
  ProductionRule pr2 = ProductionRule(B);
  pr2.addSymbol(a, true);
  pr2.addSymbol(B, false);
  pr2.addSymbol(epsilon, true);
  prVec.push_back(pr2);
  
  ProductionRule pr3 = ProductionRule(C);
  pr3.addSymbol(c, true);
  pr3.addSymbol(C, false);
  pr3.addSymbol(epsilon, true);
  prVec.push_back(pr3);
  
  ParserGenerator pg = ParserGenerator(prVec);
  vector<SymbolsSet> pgFirst = pg.getFirst();
  printSymbolsSetVector(pgFirst);
  printSymbolsSetVector(pg.getFollow());
}

void example3() {
  vector<ProductionRule> prVec;
  
  Symbol E = Symbol("E");
  Symbol T = Symbol("T");
  Symbol EDash = Symbol("E'");
  Symbol TDash = Symbol("T'");
  Symbol F = Symbol("F");
  Symbol plus = Symbol("+");
  plus.setTerminal(true);
  Symbol multiply = Symbol("*");
  multiply.setTerminal(true);
  Symbol id = Symbol("id");
  id.setTerminal(true);
  Symbol openedParenthesis = Symbol("(");
  openedParenthesis.setTerminal(true);
  Symbol closedParenthesis = Symbol(")");
  closedParenthesis.setTerminal(true);
  Symbol epsilon = Symbol("epsilon");
  epsilon.setTerminal(true);
  
  ProductionRule pr1 = ProductionRule(E);
  pr1.addSymbol(T, true);
  pr1.addSymbol(EDash, false);
  prVec.push_back(pr1);

  ProductionRule pr2 = ProductionRule(EDash);
  pr2.addSymbol(plus, true);
  pr2.addSymbol(T, false);
  pr2.addSymbol(EDash, false);
  pr2.addSymbol(epsilon, true);
  prVec.push_back(pr2);

  ProductionRule pr3 = ProductionRule(T);
  pr3.addSymbol(F, true);
  pr3.addSymbol(TDash, false);
  prVec.push_back(pr3);
  
  ProductionRule pr4 = ProductionRule(TDash);
  pr4.addSymbol(multiply, true);
  pr4.addSymbol(F, false);
  pr4.addSymbol(TDash, false);
  pr4.addSymbol(epsilon, true);
  prVec.push_back(pr4);
  
  ProductionRule pr5 = ProductionRule(F);
  pr5.addSymbol(id, true);
  pr5.addSymbol(openedParenthesis, true);
  pr5.addSymbol(E, false);
  pr5.addSymbol(closedParenthesis, false);
  prVec.push_back(pr5);
  
  ParserGenerator pg = ParserGenerator(prVec);
  vector<SymbolsSet> pgFirst = pg.getFirst();
  printSymbolsSetVector(pgFirst);
  printSymbolsSetVector(pg.getFollow());
}

void example4() {
  vector<ProductionRule> prVec;
  
  Symbol S = Symbol("S");
  Symbol A = Symbol("A");
  Symbol B = Symbol("B");
  Symbol C = Symbol("C");
  Symbol a = Symbol("a");
  a.setTerminal(true);
  Symbol b = Symbol("b");
  b.setTerminal(true);
  Symbol c = Symbol("c");
  c.setTerminal(true);
  Symbol d = Symbol("d");
  d.setTerminal(true);
  Symbol g = Symbol("g");
  g.setTerminal(true);
  Symbol h = Symbol("h");
  h.setTerminal(true);
  Symbol epsilon = Symbol("epsilon");
  epsilon.setTerminal(true);
  
  ProductionRule pr1 = ProductionRule(S);
  pr1.addSymbol(A, true);
  pr1.addSymbol(C, false);
  pr1.addSymbol(B, false);
  pr1.addSymbol(C, true);
  pr1.addSymbol(b, false);
  pr1.addSymbol(B, false);
  pr1.addSymbol(B, true);
  pr1.addSymbol(a, false);
  prVec.push_back(pr1);
  
  ProductionRule pr2 = ProductionRule(A);
  pr2.addSymbol(d, true);
  pr2.addSymbol(a, false);
  pr2.addSymbol(B, true);
  pr2.addSymbol(C, false);
  prVec.push_back(pr2);
  
  ProductionRule pr3 = ProductionRule(B);
  pr3.addSymbol(g, true);
  pr3.addSymbol(epsilon, true);
  prVec.push_back(pr3);
  
  ProductionRule pr4 = ProductionRule(C);
  pr4.addSymbol(h, true);
  pr4.addSymbol(epsilon, true);
  prVec.push_back(pr4);
  
  ParserGenerator pg = ParserGenerator(prVec);
  vector<SymbolsSet> pgFirst = pg.getFirst();
  printSymbolsSetVector(pgFirst);
  printSymbolsSetVector(pg.getFollow());
}

void example5() {
  vector<ProductionRule> prVec;
  
  Symbol S = Symbol("S");
  Symbol A = Symbol("A");
  Symbol B = Symbol("B");
  Symbol a = Symbol("a");
  a.setTerminal(true);
  Symbol b = Symbol("b");
  b.setTerminal(true);
  Symbol c = Symbol("c");
  c.setTerminal(true);
  Symbol d = Symbol("d");
  d.setTerminal(true);
  Symbol epsilon = Symbol("epsilon");
  epsilon.setTerminal(true);
  
  ProductionRule pr1 = ProductionRule(S);
  pr1.addSymbol(a, true);
  pr1.addSymbol(A, false);
  pr1.addSymbol(B, false);
  pr1.addSymbol(b, false);
  prVec.push_back(pr1);
  
  ProductionRule pr2 = ProductionRule(A);
  pr2.addSymbol(c, true);
  pr2.addSymbol(epsilon, true);
  prVec.push_back(pr2);
  
  ProductionRule pr3 = ProductionRule(B);
  pr3.addSymbol(d, true);
  pr3.addSymbol(epsilon, true);
  prVec.push_back(pr3);
  
  ParserGenerator pg = ParserGenerator(prVec);
  vector<SymbolsSet> pgFirst = pg.getFirst();
  printSymbolsSetVector(pgFirst);
  printSymbolsSetVector(pg.getFollow());
}

void example6() {
  vector<ProductionRule> prVec;
  
  Symbol S = Symbol("S");
  Symbol B = Symbol("B");
  Symbol C = Symbol("C");
  Symbol D = Symbol("D");
  Symbol E = Symbol("E");
  Symbol F = Symbol("F");
  Symbol a = Symbol("a");
  a.setTerminal(true);
  Symbol b = Symbol("b");
  b.setTerminal(true);
  Symbol c = Symbol("c");
  c.setTerminal(true);
  Symbol h = Symbol("h");
  h.setTerminal(true);
  Symbol g = Symbol("g");
  g.setTerminal(true);
  Symbol f = Symbol("f");
  f.setTerminal(true);
  Symbol epsilon = Symbol("epsilon");
  epsilon.setTerminal(true);
  
  ProductionRule pr1 = ProductionRule(S);
  pr1.addSymbol(a, true);
  pr1.addSymbol(B, false);
  pr1.addSymbol(D, false);
  pr1.addSymbol(h, false);
  prVec.push_back(pr1);
  
  ProductionRule pr2 = ProductionRule(B);
  pr2.addSymbol(c, true);
  pr2.addSymbol(C, false);
  prVec.push_back(pr2);
  
  ProductionRule pr3 = ProductionRule(C);
  pr3.addSymbol(b, true);
  pr3.addSymbol(C, false);
  pr3.addSymbol(epsilon, true);
  prVec.push_back(pr3);
  
  ProductionRule pr4 = ProductionRule(D);
  pr4.addSymbol(E, true);
  pr4.addSymbol(F, false);
  prVec.push_back(pr4);
  
  ProductionRule pr5 = ProductionRule(E);
  pr5.addSymbol(g, true);
  pr5.addSymbol(epsilon, true);
  prVec.push_back(pr5);
  
  ProductionRule pr6 = ProductionRule(F);
  pr6.addSymbol(f, true);
  pr6.addSymbol(epsilon, true);
  prVec.push_back(pr6);
  
  ParserGenerator pg = ParserGenerator(prVec);
  vector<SymbolsSet> pgFirst = pg.getFirst();
  printSymbolsSetVector(pgFirst);
  printSymbolsSetVector(pg.getFollow());
}

void example7() {
  vector<ProductionRule> prVec;
  
  Symbol S = Symbol("S");
  Symbol B = Symbol("B");
  Symbol C = Symbol("C");
  Symbol a = Symbol("a");
  a.setTerminal(true);
  Symbol b = Symbol("b");
  b.setTerminal(true);
  Symbol c = Symbol("c");
  c.setTerminal(true);
  Symbol epsilon = Symbol("epsilon");
  epsilon.setTerminal(true);
  
  ProductionRule pr1 = ProductionRule(S);
  pr1.addSymbol(a, true);
  pr1.addSymbol(B, false);
  pr1.addSymbol(epsilon, true);
  prVec.push_back(pr1);
  
  ProductionRule pr2 = ProductionRule(B);
  pr2.addSymbol(b, true);
  pr2.addSymbol(C, false);
  pr2.addSymbol(epsilon, true);
  prVec.push_back(pr2);
  
  ProductionRule pr3 = ProductionRule(C);
  pr3.addSymbol(c, true);
  pr3.addSymbol(S, false);
  pr3.addSymbol(epsilon, true);
  prVec.push_back(pr3);
  
  ParserGenerator pg = ParserGenerator(prVec);
  vector<SymbolsSet> pgFirst = pg.getFirst();
  printSymbolsSetVector(pgFirst);
  printSymbolsSetVector(pg.getFollow());
}

void example8() {
  vector<ProductionRule> prVec;
  
  Symbol E = Symbol("E");
  Symbol T = Symbol("T");
  Symbol EDash = Symbol("E'");
  Symbol TDash = Symbol("T'");
  Symbol F = Symbol("F");
  Symbol FDash = Symbol("F'");
  Symbol P = Symbol("P");
  Symbol a = Symbol("a");
  a.setTerminal(true);
  Symbol b = Symbol("b");
  b.setTerminal(true);
  Symbol Em = Symbol("Em");
  Em.setTerminal(true);
  Symbol plus = Symbol("+");
  plus.setTerminal(true);
  Symbol multiply = Symbol("*");
  multiply.setTerminal(true);
  Symbol epsilon = Symbol("epsilon");
  epsilon.setTerminal(true);
  Symbol openedParenthesis = Symbol("(");
  openedParenthesis.setTerminal(true);
  Symbol closedParenthesis = Symbol(")");
  closedParenthesis.setTerminal(true);
  
  ProductionRule pr1 = ProductionRule(E);
  pr1.addSymbol(T, true);
  pr1.addSymbol(EDash, false);
  prVec.push_back(pr1);
  
  ProductionRule pr2 = ProductionRule(EDash);
  pr2.addSymbol(plus, true);
  pr2.addSymbol(E, false);
  pr2.addSymbol(epsilon, true);
  prVec.push_back(pr2);
  
  ProductionRule pr3 = ProductionRule(T);
  pr3.addSymbol(F, true);
  pr3.addSymbol(TDash, false);
  prVec.push_back(pr3);
  
  ProductionRule pr4 = ProductionRule(TDash);
  pr4.addSymbol(T, true);
  pr4.addSymbol(epsilon, true);
  prVec.push_back(pr4);
  
  ProductionRule pr5 = ProductionRule(F);
  pr5.addSymbol(P, true);
  pr5.addSymbol(FDash, false);
  prVec.push_back(pr5);
  
  ProductionRule pr6 = ProductionRule(FDash);
  pr6.addSymbol(multiply, true);
  pr6.addSymbol(F, false);
  pr6.addSymbol(epsilon, true);
  prVec.push_back(pr6);
  
  ProductionRule pr7 = ProductionRule(P);
  pr7.addSymbol(openedParenthesis, true);
  pr7.addSymbol(E, false);
  pr7.addSymbol(closedParenthesis, false);
  pr7.addSymbol(a, true);
  pr7.addSymbol(b, true);
  pr7.addSymbol(Em, true);
  prVec.push_back(pr7);

  ParserGenerator pg = ParserGenerator(prVec);
  vector<SymbolsSet> pgFirst = pg.getFirst();
  printSymbolsSetVector(pgFirst);
  printSymbolsSetVector(pg.getFollow());
}

void printSymbolsSetVector(vector<SymbolsSet> ssVec) {
  for(int i = 0; i < ssVec.size(); ++i) {
    vector<Symbol> symbols_i = ssVec[i].getSymbolsVector();
    for(int j = 0; j < symbols_i.size(); ++j) {
      cout << symbols_i[j].getName();
      if(j < symbols_i.size()-1) cout << ", ";
    }
    cout << endl;
  }
  cout << endl;
}*/
