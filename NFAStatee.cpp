//
// Created by Geek on 3/19/2019.
//

#include "NFAStatee.h"

#include <vector>
#include <map>
#include <string>
#include <utility>

using namespace std;

void NFAStatee::setAcceptable(){
    acceptableState = true;
}
bool NFAStatee::isAcceptable(){
    return acceptableState;
}

NFAStatee::NFAStatee(int idValue){
   id = idValue;
}

void NFAStatee::addTransition(int newStateID,string input){
    vector<int> inputStatesIDs = inputMap[input];
    inputStatesIDs.push_back(newStateID);
    inputMap[input] = inputStatesIDs;

}

vector<int> NFAStatee::getTransition(string input){
    return inputMap[input];
}
vector<int> NFAStatee::getEpsilonEquivalent(){
    return inputMap["epsilon"];
}
