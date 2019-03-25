//
// Created by ahmed on 18/03/19.
//

#ifndef LEXICALANALYZER_NFAALGORITHM_H
#define LEXICALANALYZER_NFAALGORITHM_H

#include "NFAState.h"
#include <unordered_set>
class NfaAlgorithm {

    vector<NFAStatee> NfaStates;
    vector <long int>StartStateTrack;
    vector <string> All_inputs;

private:
    int stateIdCounter=0;
    unordered_set<int> acceptedStates;
public:
    unordered_set<int> getAcceptedStates();
    void setAcceptedStates(int order);

public:


public:


    void Algorithm(string token,string regularExpression);
    vector <string> get_All_inputs();
   // NFAStatee getStarState();
    vector<NFAStatee> getNfaStates();
};


#endif //LEXICALANALYZER_NFAALGORITHM_H
