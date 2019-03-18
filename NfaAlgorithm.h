//
// Created by ahmed on 18/03/19.
//

#ifndef LEXICALANALYZER_NFAALGORITHM_H
#define LEXICALANALYZER_NFAALGORITHM_H

#include "NFAState.h"

class NfaAlgorithm {

    vector<NFAState> NfaStates;
    vector <NFAState>StartState;

public:

    void Algorithm(string regularExpression);


};


#endif //LEXICALANALYZER_NFAALGORITHM_H
