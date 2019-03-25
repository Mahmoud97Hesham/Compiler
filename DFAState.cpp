//
// Created by Geek on 3/17/2019.
//

#include "DFAState.h"

DFAState::DFAState(int idValue, vector<int> nfaVector) {
    id = idValue;
    nfaEquivalent = nfaVector;
}
void DFAState::setToken(string tokenName){
    token = tokenName;
}
string DFAState::getToken(){
    return token;
}

void DFAState::setAcceptable() {
    acceptableState = true;
}

bool DFAState::isAcceptable() {
    return acceptableState;
}
int DFAState::getID(){
    return  id;
}
void DFAState::addTransition(int newState, string input) {
    inputMap[input] = newState;
}

int DFAState::nextState(string input) {
    return inputMap[input];
}

vector<int> DFAState::getNFAEquivalent() {
    return nfaEquivalent;
}

int DFAState::getTransition(string input){
    return inputMap[input];
}