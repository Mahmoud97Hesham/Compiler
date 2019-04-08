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
        map<vector<int>, int> allInputsTransitionsNotaccepted;
        checkDuplicates = false;
        for (int i = 0; i < minimizedDFAMap.size(); i++) {
            DFAState currentDFA = minimizedDFAMap.front();
            vector<int> currentStateTransitions;
            for (int j = 0; j < input.size(); j++) {
                currentStateTransitions.push_back(currentDFA.getTransition(input.at(j)));

            }
            if (allInputsTransitions.find(currentStateTransitions) == allInputsTransitions.end() && (currentDFA.isAcceptable())) {
                allInputsTransitions[currentStateTransitions] = currentDFA.getID();
                cout << " ADD TO ACCEPTED MAP " << currentDFA.getID();

            }else if(allInputsTransitionsNotaccepted.find(currentStateTransitions) == allInputsTransitionsNotaccepted.end() &&(!currentDFA.isAcceptable())){
                allInputsTransitionsNotaccepted[currentStateTransitions] = currentDFA.getID();
                cout << " ADD TO NOT ACCEPTED MAP " << currentDFA.getID();
            }else {
                bool isFirstStateAcceptable = currentDFA.isAcceptable();
//                DFAState alternativeState = completeDFAMap.at(allInputsTransitions[currentStateTransitions]);
//                bool isSecondStateAcceptable = alternativeState.isAcceptable();
                cout << " ID " << currentDFA.getID() << " FIRST STATE BOOL " << isFirstStateAcceptable << endl;
//                cout << " ID " << alternativeState.getID()  << " SECOND STATE BOOL " << isSecondStateAcceptable << endl;
                if (isFirstStateAcceptable) {

                    DFAState alternativeState = completeDFAMap.at(allInputsTransitions[currentStateTransitions]);
                    if(alternativeState.getToken() == currentDFA.getToken()){
                        duplicatesMap[currentDFA.getID()] = allInputsTransitions[currentStateTransitions];
                        checkDuplicates = true;
                    }
                    //cout << " ID " << allInputsTransitions[currentStateTransitions] << " ACCEPTED" << endl;
                }else{
                    duplicatesMap[currentDFA.getID()] = allInputsTransitionsNotaccepted[currentStateTransitions];
                    checkDuplicates = true;
                    //cout << " ID " << allInputsTransitions[currentStateTransitions] << " NOT ACCEPTED" << endl;
                }

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
            completeDFAMap[currentDFA.getID()] = currentDFA;
        } else {
            vector<int> dummyVector;
            DFAState dummyState(-1, dummyVector);
            completeDFAMap[currentDFA.getID()] = dummyState;
        }

        iterator++;
    }
}

void MinimizeDFA::printMinimizedDFATable() {
    cout << endl;
    for (int j = 0; j < input.size(); j++) {
        cout << " " << input.at(j);
    }
    cout << endl;
    for (int i = 0; i < completeDFAMap.size(); i++) {
        if (completeDFAMap[i].getID() != -1) {
            cout << completeDFAMap[i].getID() << "  ";
            for (int j = 0; j < input.size(); j++) {
                cout << " " << completeDFAMap[i].getTransition(input.at(j));
            }
            cout << endl;
        }
    }
}