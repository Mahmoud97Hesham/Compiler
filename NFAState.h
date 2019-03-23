//
// Created by Geek on 3/19/2019.
//

#ifndef LEXICALANALYZER_NFASTATEE_H
#define LEXICALANALYZER_NFASTATEE_H
#include <vector>
#include <map>
#include <string>

using namespace std;


class NFAStatee {
    bool acceptableState = true;
    map<string,vector<int>> inputMap;
    int id;
    string token;
public:
    NFAStatee(int idValue);
    void setAcceptable(string token , bool state);
    bool isAcceptable();
    void addTransition(int newStateID,string input);
    vector<int> getTransition(string input);
    vector<int> getEpsilonEquivalent();
    int getId();
};


#endif //LEXICALANALYZER_NFASTATEE_H
