#include <iostream>
#include <string>
#include <fstream>
#include "LexicalRulesParser.h"
#include "MinimizeDFA.h"
#include "DFAState.h"

using namespace std;

class LexicalAnaLyzerGenerator {
  vector<DFAState> minimizedDFA;
public:
  LexicalAnaLyzerGenerator(vector<DFAState>);
  vector<string> generateLexicalOutput(string);
};