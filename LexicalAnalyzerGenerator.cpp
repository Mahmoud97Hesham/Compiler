#include "LexicalAnaLyzerGenerator.h"

LexicalAnaLyzerGenerator::LexicalAnaLyzerGenerator(vector<DFAState> _minimizedDFA) {
  minimizedDFA = _minimizedDFA;
}

vector<string> LexicalAnaLyzerGenerator::generateLexicalOutput(string filename) {
  ifstream file(filename);
  string line;
  int nextState = 1;
  vector<string> result;
  string token = "";
  bool lastWasSpace = true;
  while(getline(file,line)) {
    int i = 0;
    char c = line[i];
    string cInString(1, c);
    
    while(c != 0) {
      if(c == ' ' || c == '\t') {
        if(!lastWasSpace) {
          token += " >> " + minimizedDFA[nextState].getToken();
          result.push_back(token);
          nextState = 1;
          token = "";
          lastWasSpace = true;
        }
      } else {
        int oldState = nextState;
        nextState = minimizedDFA[nextState].nextState(cInString);
        lastWasSpace = false;
        if(nextState == 0) {
          token += " >> " + minimizedDFA[oldState].getToken();
          result.push_back(token);
          nextState = minimizedDFA[1].nextState(cInString);
          token = c;
        } else {
          token += c;
        }
      }
      c = line[++i];
      cInString = string(1, c);
    }
    lastWasSpace = true;
    if(minimizedDFA[nextState].isAcceptable()) {
      token += " >> " + minimizedDFA[nextState].getToken();
      result.push_back(token);
      nextState = 1;
      token = "";
    }
  }
  return result;
}
