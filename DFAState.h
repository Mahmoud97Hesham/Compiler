//
// Created by Geek on 3/17/2019.
//

#ifndef LEXICALANALYZER_DFASTATE_H
#define LEXICALANALYZER_DFASTATE_H
#include <map>
#include <vector>
#include <string>
#include "NFAState.h"
using namespace std;
class DFAState {
    int id;
    bool acceptableState = false;
    map<string,int> inputMap;
    vector<int> nfaEquivalent;
    string token = "";
public:
    DFAState(int idValue,vector<int> nfaVector);
    int nextState(string input);
    void setAcceptable();
    bool isAcceptable();
    vector<int> getNFAEquivalent();
    void addTransition(int newState,string input);
    int getID();
    int getTransition(string input);
    string getToken();
    void setToken(string tokenName);

};


#endif //LEXICALANALYZER_DFASTATE_H
