#include "LexicalAnaLyzerGenerator.h"

LexicalAnaLyzerGenerator::LexicalAnaLyzerGenerator(vector<DFAState> _minimizedDFA) {
  minimizedDFA = _minimizedDFA;
}

vector<string> LexicalAnaLyzerGenerator::generateLexicalOutput(string filename) {
  ifstream file(filename);
  string line;
  int nextState = 1;
  vector<string> result;
  while(getline(file,line)) {
    int i = 0;
    char c = line[i];
    string cInString(1, c);
    
    while(c != 0) {
      if(c == ' ' || c == '\t') {
        string token;
        result.push_back(token);
        nextState = 1;
      } else {
        nextState = minimizedDFA[nextState].nextState(cInString);
        if(nextState == 0) {
          string token;
          result.push_back(token);
          nextState = 1;
        }
      }
      c = line[++i];
      cInString = string(1, c);
    }
  }
  return result;
}
