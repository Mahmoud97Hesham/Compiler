//
// Created by Geek on 3/17/2019.
//

#ifndef LEXICALANALYZER_NFASTATE_H
#define LEXICALANALYZER_NFASTATE_H

#include <vector>
#include <map>
#include <string>

using namespace std;

class NFAState {
    bool acceptableState = false;
    vector<NFAState> nextStates;
    map<NFAState,string> inputMap;
public:
    void setAcceptable();
    bool isAcceptable();
    void addNextState(NFAState newState,string input);
    bool operator<(const NFAState& src)const
    {
        return false;
    }
};


#endif //LEXICALANALYZER_NFASTATE_H
