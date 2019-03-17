#include <iostream>
#include <vector>
#include <unordered_map>
#include "NFAState.h"
using namespace std;

int main() {
    NFAState startState;
    NFAState secondState;
    NFAState thirdState;
    NFAState fourthState;
    NFAState fifthState;
    NFAState sixthState;
//    startState.addNextState(secondState,"epsilon");
//    startState.addNextState(thirdState,"epsilon");
//    startState.addNextState(fourthState,"epsilon");
//    secondState.addNextState(fifthState,"0");
//    thirdState.addNextState(sixthState,"1");
    fourthState.setAcceptable();
    fifthState.setAcceptable();
    sixthState.setAcceptable();
    return 0;
}