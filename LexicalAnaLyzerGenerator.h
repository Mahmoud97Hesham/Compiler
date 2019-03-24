#include <iostream>
#include <string>
#include <fstream>
#include "LexicalRulesParser.h"
#include "MinimizeDFA.h"
#include "DFAState.h"

using namespace std;

class LexicalAnaLyzerGenerator {
  LexicalRulesParser lsp;
  vector<DFAState> minimizedDFA;
  bool isLastPunctuation;
public:
  LexicalAnaLyzerGenerator(LexicalRulesParser, vector<DFAState>);
  void generateLexicalOutput(string);
  bool isPunctuation(string);
};