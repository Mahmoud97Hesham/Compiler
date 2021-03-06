//
// Created by Geek on 3/19/2019.
//

#ifndef LEXICALANALYZER_CONVERSIONTODFA_H
#define LEXICALANALYZER_CONVERSIONTODFA_H

#include "NFAState.h"
#include "DFAState.h"
#include <vector>
#include <unordered_set>

class ConversionToDFA {
    int startState;
    /* table of nfa states and their IDS */
    vector<NFAStatee> nfaMap;
    /* table of dfa states and their IDS */
    vector<DFAState> dfaMap;
    vector<string> inputs;
    unordered_set<int> accept ;
    unordered_set<string> keywords;

public:
    /* Constructor of the class takes Start state ID of NFA and the Table of NFA States */
    ConversionToDFA(int state,vector<NFAStatee> nfa,vector<string> inputsVector,unordered_set<int> acceptingStates,vector<string> allKeywords);
    /* return the start state of the new dfa  */
    vector<DFAState> convertToDFA();
    vector<int> addNestedEquivalentStates(vector<int> states);
    vector<int> getInputTransitions(vector<int> states , string input);
    vector<int> getStartStates();
};


#endif //LEXICALANALYZER_CONVERSIONTODFA_H
