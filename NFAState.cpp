//
// Created by Geek on 3/19/2019.
//

#include "NFAState.h"

#include <vector>
#include <map>
#include <string>
#include <utility>
#include <iostream>

using namespace std;


bool NFAStatee::isAcceptable(){
    return acceptableState;
}

NFAStatee::NFAStatee(int idValue ){
   id = idValue;
}

void NFAStatee::addTransition(int newStateID,string input){
    vector<int> inputStatesIDs = inputMap[input];
    inputStatesIDs.push_back(newStateID);
    inputMap[input] = inputStatesIDs;

    cout <<this->getId()<<" "<< newStateID <<" "<<input<<endl ;
    cout << inputMap[input].size()<<endl ;
}
string NFAStatee::getToken(){
   return token;
}

vector<int> NFAStatee::getTransition(string input){
    return inputMap[input];
}
vector<int> NFAStatee::getEpsilonEquivalent(){
    return inputMap["epsilon"];
}
int NFAStatee ::getId() {
    return  this->id;
}

void NFAStatee::setAcceptable(string token, bool state) {

    this->token = token;
    this->acceptableState = state;
}
