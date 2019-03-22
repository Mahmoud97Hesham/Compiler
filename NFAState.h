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
    map<NFAState,string> inputMap;
private:
    vector<NFAState> nextStates;
public:
    void setAcceptable();
    bool isAcceptable();
    void addNextState(NFAState newState,string input);
    vector<NFAState> getNextStates();
    bool operator<(const NFAState& src)const
    {
        return false;
    }
};


#endif //LEXICALANALYZER_NFASTATE_H
