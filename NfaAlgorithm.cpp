//
// Created by ahmed on 18/03/19.
//

#include "NfaAlgorithm.h"
#include "NFAState.h"


void NfaAlgorithm::Algorithm(string regularExpression) {


    int parenthesisCounter = 0;
    string epsilon = "epsilon";
    NFAState StartingState;
    NfaStates.push_back(StartingState);
    StartState.push_back(StartingState);

    for (int i = 0; i < regularExpression.length(); i++) {

        if (regularExpression[i] == '(') {
            parenthesisCounter++;
            if (NfaStates.size() != 0) {

                StartState.push_back(NfaStates.back());
                NFAState dummyState;
                NfaStates.back().addNextState(dummyState, epsilon);
                NfaStates.push_back(dummyState);
                StartState.push_back(dummyState);
            } else {

                NFAState dummyState0;
                NfaStates.push_back(dummyState0);
                StartState.push_back(dummyState0);


                NFAState dummyState;
                NfaStates.back().addNextState(dummyState, epsilon);
                NfaStates.push_back(dummyState);
                StartState.push_back(dummyState);
            }

        } else if (regularExpression[i] == ')') {

            if (parenthesisCounter > 0) {
                parenthesisCounter--;

                NFAState dummyState;
                NfaStates.back().addNextState(dummyState, epsilon);
                NfaStates.push_back(dummyState);

                if (i + 1 < regularExpression.length() && regularExpression[i + 1] == '*') {

                    i++;
                    NfaStates.back().addNextState(StartState.back(), epsilon);
                    StartState.pop_back();
                    StartState.back().addNextState(dummyState, epsilon);
                    StartState.pop_back();
                } else if (i + 1 < regularExpression.length() && regularExpression[i + 1] == '+') {

                    NfaStates.back().addNextState(StartState.back(), epsilon);
                    StartState.pop_back();
                    StartState.pop_back();
                }

            } else {
                //error
            }

        } else if (regularExpression[i] == '|') {

            NFAState dummyState;
            StartState.back().addNextState(dummyState, epsilon);
            NfaStates.push_back(dummyState);

        } else if (regularExpression[i] == '\\') {

            i++;
            NFAState dummyState;
            string temp = "";
            temp += regularExpression[i];
            NfaStates.back().addNextState(dummyState, temp);
            NfaStates.push_back(dummyState);

        } else if (regularExpression[i] == '/') {

            /* THIS CONDITION IS FOR REGULAR DEFINITIONS */

        } else if(regularExpression[i]=='*' || regularExpression[i]=='+'){

              //error

        } else {

            if (i+1<regularExpression.length() && regularExpression[i + 1] != '*'
                && regularExpression[i + 1] != '+') {

                NFAState dummyState;
                string temp = "";
                temp += regularExpression[i];
                NfaStates.back().addNextState(dummyState, temp);
                NfaStates.push_back(dummyState);

            } else if (i+1<regularExpression.length() && regularExpression[i + 1] == '+') {
                NFAState dummyState;
                string temp = "";
                temp += regularExpression[i];
                NfaStates.back().addNextState(dummyState, temp);
                NfaStates.push_back(dummyState);
                NfaStates.back().addNextState(NfaStates.back(), temp);
                i++;
            } else if (i+1<regularExpression.length() && regularExpression[i + 1] == '*') {

                NFAState dummyState;
                string temp = "";
                temp += regularExpression[i];
                NfaStates.back().addNextState(dummyState, temp);

                NFAState dummyState1;
                NfaStates.back().addNextState(dummyState1, epsilon);
                dummyState.addNextState(dummyState1, epsilon);
                dummyState.addNextState(dummyState, temp);
                NfaStates.push_back(dummyState);
                NfaStates.push_back(dummyState1);
                i++;


            }


        }


    }
}