//
// Created by Geek on 3/19/2019.
//

#include "ConversionToDFA.h"
#include <unordered_set>
#include <bits/stdc++.h>
#include <queue>

ConversionToDFA::ConversionToDFA(int state,vector<NFAStatee> nfa,vector<string> inputsVector){
    startState = state;
    nfaMap = nfa;
    inputs = inputsVector;

}

vector<DFAState> ConversionToDFA::convertToDFA(){
    vector<int> startStates = getStartStates();
    map<vector<int>,int> checkDuplicates;
    int id = 1;
    vector<int> dummy;
    DFAState dummyState(0,dummy);
    for(int i = 0;i<inputs.size();i++){
        dummyState.addTransition(0,inputs.at(i));
    }
    dfaMap.push_back(dummyState);
    DFAState startState(id,startStates);
    id++;
    queue<DFAState> dfaStates;
    dfaStates.push(startState);
    while (dfaStates.size() > 0){
        DFAState state = dfaStates.front();
        dfaStates.pop();
        vector<int> equivalentNFA = state.getNFAEquivalent();
        for(int i = 0;i<inputs.size();i++){
            vector<int> nextStates = getInputTransitions(equivalentNFA,inputs.at(i));
            vector<int> finalNextStates = addNestedEquivalentStates(nextStates);
            if(finalNextStates.size() > 0) {
                sort(finalNextStates.begin(), finalNextStates.end());
                if(checkDuplicates.find(finalNextStates) == checkDuplicates.end()){
                    DFAState newState(id, finalNextStates);
                    state.addTransition(id, inputs.at(i));
                    checkDuplicates[finalNextStates] = id;
                    dfaStates.push(newState);
                    id++;
                }else{
                    state.addTransition(checkDuplicates[finalNextStates], inputs.at(i));
                }

            }else{
                state.addTransition(0,inputs.at(i));
            }

        }
        dfaMap.push_back(state);
    }
    return dfaMap;
}
vector<int> ConversionToDFA::getStartStates(){
    vector<int> temp;
    temp.push_back(startState);
    return addNestedEquivalentStates(temp);
}

vector<int> ConversionToDFA::getInputTransitions(vector<int> states , string input){
    unordered_set<int> checkDuplicates;
    vector<int> nextStates;
    for(int i = 0;i < states.size();i++){
        NFAStatee temp = nfaMap[states.at(i) - 1];
        vector<int> inputTransition = temp.getTransition(input);
        for(int j = 0; j < inputTransition.size();j++){
            if(checkDuplicates.find(inputTransition.at(j)) == checkDuplicates.end()) {
                checkDuplicates.insert(inputTransition.at(j));
                nextStates.push_back(inputTransition.at(j));
            }
        }
    }
    return nextStates;
}

vector<int> ConversionToDFA::addNestedEquivalentStates(vector<int> states){
    unordered_set<int> checkDuplicates;
    queue<int> statesQueue;
    vector<int> nfaEpsilonEquivalent;
    for(int i = 0 ; i < states.size();i++){

        if(checkDuplicates.find(states.at(i)) == checkDuplicates.end()){
            checkDuplicates.insert(states.at(i));
            statesQueue.push(states.at(i));
        }
    }
    while(statesQueue.size() > 0){
        int stateID = statesQueue.front();
        nfaEpsilonEquivalent.push_back(stateID);
        statesQueue.pop();
        NFAStatee currentState = nfaMap.at(stateID - 1);
        vector<int> epsilonEquivalent = currentState.getEpsilonEquivalent();
        for(int i = 0;i < epsilonEquivalent.size();i++) {
            if(checkDuplicates.find(epsilonEquivalent.at(i)) == checkDuplicates.end()){
                checkDuplicates.insert(epsilonEquivalent.at(i));
                statesQueue.push(epsilonEquivalent.at(i));
            }

        }
    }
    return nfaEpsilonEquivalent;

}