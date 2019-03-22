#include <utility>

#include "MinimizeDFA.h"
#include <map>
#include <iostream>

map<int, int> duplicatesMap;

MinimizeDFA::MinimizeDFA(vector<DFAState> dfaMap, vector<string> inputs) {
    completeDFAMap = std::move(dfaMap);
    input = std::move(inputs);
}

vector<DFAState> MinimizeDFA::minimize() {
    bool checkDuplicates;
    for (int i = 0; i < completeDFAMap.size(); i++) {
        minimizedDFAMap.push(completeDFAMap.at(i));
    }
    do {
        map<vector<int>, int> allInputsTransitions;
        checkDuplicates = false;
        for (int i = 0; i < minimizedDFAMap.size(); i++) {
            DFAState currentDFA = minimizedDFAMap.front();
            vector<int> currentStateTransitions;
            for (int j = 0; j < input.size(); j++) {
                currentStateTransitions.push_back(currentDFA.getTransition(input.at(j)));
                cout << currentDFA.getTransition(input.at(j)) << " ";
            }
            cout << endl;
            if (allInputsTransitions.find(currentStateTransitions) == allInputsTransitions.end()) {
                allInputsTransitions[currentStateTransitions] = currentDFA.getID();

            } else {
                checkDuplicates = true;
                duplicatesMap[currentDFA.getID()] = allInputsTransitions[currentStateTransitions];
            }
            minimizedDFAMap.pop();
            minimizedDFAMap.push(currentDFA);
        }
        updateDFA();
    } while (checkDuplicates);
    return completeDFAMap;

}

void MinimizeDFA::updateDFA() {
    int iterator = 0;
    while (iterator < minimizedDFAMap.size()) {
        DFAState currentDFA = minimizedDFAMap.front();
        minimizedDFAMap.pop();
        if (duplicatesMap.find(currentDFA.getID()) == duplicatesMap.end()) {
            for (int j = 0; j < input.size(); j++) {
                if (duplicatesMap.find(currentDFA.getTransition(input.at(j))) != duplicatesMap.end()) {
                    currentDFA.addTransition(duplicatesMap[currentDFA.getTransition(input.at(j))], input.at(j));
                }
            }
            minimizedDFAMap.push(currentDFA);
        } else {
            vector<int> dummyVector;
            DFAState dummyState(-1, dummyVector);
        }
        completeDFAMap[currentDFA.getID()] = currentDFA;
        iterator++;
    }
}