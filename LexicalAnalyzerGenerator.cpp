#include "LexicalAnaLyzerGenerator.h"

LexicalAnaLyzerGenerator::LexicalAnaLyzerGenerator(LexicalRulesParser _lsp, vector<DFAState> _minimizedDFA) {
  lsp = _lsp;
  minimizedDFA = _minimizedDFA;
  isLastPunctuation = false;
}

void LexicalAnaLyzerGenerator::generateLexicalOutput(string filename) {
  ifstream file(filename);
  string line;
  while(getline(file,line)) {
    int i = 0;
    char c = line[i];
    string cInString(1, c);
    
    while(c != 0) {
      if(c == ' ' || c == '\t' || isPunctuation(cInString)) {
        // see the last state and save it to the output result
        if(isLastPunctuation) {
          // save the punctuation to the output result
          isLastPunctuation = false;
        }
        // reset the dfa
      } else {
        // input the char to the dfa
      }
      c = line[++i];
      cInString = string(1, c);
    }
  }
}

bool LexicalAnaLyzerGenerator::isPunctuation(string input) {
// check if the input is a punctuation
}