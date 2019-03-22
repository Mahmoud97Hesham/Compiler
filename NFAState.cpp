//
// Created by Geek on 3/17/2019.
//

#include "NFAState.h"
#include <vector>
#include <map>
#include <string>
#include <utility>

using namespace std;

void NFAState::setAcceptable(){
    acceptableState = true;
}
bool NFAState::isAcceptable(){
    return acceptableState;
}

void NFAState::addNextState(NFAState newState,string input){
    nextStates.push_back(newState);
    //inputMap[newState] = input;
}
vector<NFAState>NFAState ::getNextStates(){
    return  this->nextStates;

}




