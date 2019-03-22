//
// Created by ahmed on 18/03/19.
//

#include <algorithm>
#include "NfaAlgorithm.h"
#include "NFAStatee.h"


void NfaAlgorithm::Algorithm(string token,string regularExpression) {


    int parenthesisCounter = 0;
    string epsilon = "epsilon";
    if(NfaStates.size()==0){
    stateIdCounter ++;
    NFAStatee StartingState(0);
    StartingState.setAcceptable(token, true);
    NfaStates.push_back(StartingState);
    //this->starState=StartingState;
    StartStateTrack.push_back(StartingState);}

    vector<NFAStatee> parenthesisEndStates;
    for (int i = 0; i < regularExpression.length(); i++) {

        if (regularExpression[i] == '(') {
            parenthesisCounter++;

            stateIdCounter++;
            NFAStatee end_this_Parenthes(stateIdCounter);
            parenthesisEndStates.push_back(end_this_Parenthes);

            StartStateTrack.push_back(NfaStates.back());
            stateIdCounter++;
            NFAStatee dummyState(stateIdCounter);
            dummyState.setAcceptable(token, true);
            NfaStates.back().addTransition(stateIdCounter,epsilon);
            NfaStates.back().setAcceptable(token, false);
            NfaStates.push_back(dummyState);
            StartStateTrack.push_back(dummyState);

        } else if (regularExpression[i] == ')') {

            if (parenthesisCounter > 0) {
                parenthesisCounter--;


                NfaStates.back().addTransition(parenthesisEndStates.back().getId(),epsilon);
                NfaStates.back().setAcceptable(token, false);
                NfaStates.push_back(parenthesisEndStates.back());
                parenthesisEndStates.pop_back();

                stateIdCounter++;

                NFAStatee dummyState(stateIdCounter);
                dummyState.setAcceptable(token, true);
                NfaStates.back().addTransition(stateIdCounter, epsilon);
                NfaStates.back().setAcceptable(token, false);
                if (i + 1 < regularExpression.length() && regularExpression[i + 1] == '*') {

                    i++;
                    NfaStates.back().addTransition(StartStateTrack.back().getId(), epsilon);
                    NfaStates.back().setAcceptable(token, false);
                    StartStateTrack.pop_back();
                    StartStateTrack.back().addTransition(stateIdCounter, epsilon);
                    StartStateTrack.back().setAcceptable(token, false);
                    StartStateTrack.pop_back();

                } else if (i + 1 < regularExpression.length() && regularExpression[i + 1] == '+') {

                    NfaStates.back().addTransition(StartStateTrack.back().getId(), epsilon);
                    NfaStates.back().setAcceptable(token, false);
                    StartStateTrack.pop_back();
                    StartStateTrack.pop_back();
                }
                NfaStates.push_back(dummyState);


            } else {
                //error
            }

        } else if (regularExpression[i] == '|') {

            if(parenthesisCounter>0){
                NfaStates.back().addTransition(parenthesisEndStates.back().getId(),epsilon);
                NfaStates.back().setAcceptable(token, false);
            }
            stateIdCounter++;
            NFAStatee dummyState(stateIdCounter);
            dummyState.setAcceptable(token, true);
            StartStateTrack.back().addTransition(stateIdCounter, epsilon);
            StartStateTrack.back().setAcceptable(token, false);
            NfaStates.push_back(dummyState);

        } else if (regularExpression[i] == '\\') {

            i++;
            stateIdCounter++;
            NFAStatee dummyState(stateIdCounter);
            dummyState.setAcceptable(token, true);
            string temp = "";
            temp += regularExpression[i];

            // check if inputs vector contains that input ,if not add it
            if(!(std::find(All_inputs.begin(), All_inputs.end(), temp) != All_inputs.end())) {
                All_inputs.push_back(temp);
            }


            NfaStates.back().addTransition(stateIdCounter, temp);
            NfaStates.back().setAcceptable(token, false);
            NfaStates.push_back(dummyState);

        }
        else if(regularExpression[i]=='*' || regularExpression[i]=='+'){

              //error

        } else {

            if ((i+1<regularExpression.length() && regularExpression[i + 1] != '*'
                && regularExpression[i + 1] != '+') ||i+1==regularExpression.length() ) {
                stateIdCounter++;

                NFAStatee dummyState(stateIdCounter);
                dummyState.setAcceptable(token, true);
                string temp = "";
                temp += regularExpression[i];

                // check if inputs vector contains that input ,if not add it
                if(!(std::find(All_inputs.begin(), All_inputs.end(), temp) != All_inputs.end())) {
                    All_inputs.push_back(temp);
                }

                NfaStates.back().addTransition(stateIdCounter, temp);
                NfaStates.back().setAcceptable(token, false);
                NfaStates.push_back(dummyState);

            } else if (i+1<regularExpression.length() && regularExpression[i + 1] == '+') {
                stateIdCounter++;
                NFAStatee dummyState(stateIdCounter);
                dummyState.setAcceptable(token, true);
                string temp = "";
                temp += regularExpression[i];

                // check if inputs vector contains that input ,if not add it
                if(!(std::find(All_inputs.begin(), All_inputs.end(), temp) != All_inputs.end())) {
                    All_inputs.push_back(temp);
                }

                NfaStates.back().addTransition(stateIdCounter, temp);
                NfaStates.back().setAcceptable(token, false);
                NfaStates.push_back(dummyState);
                NfaStates.back().addTransition(NfaStates.back().getId(), temp);
                NfaStates.back().setAcceptable(token, false);
                i++;
            } else if (i+1<regularExpression.length() && regularExpression[i + 1] == '*') {
                stateIdCounter++;
                NFAStatee dummyState(stateIdCounter);
                dummyState.setAcceptable(token, true);
                string temp = "";
                temp += regularExpression[i];

                // check if inputs vector contains that input ,if not add it
                if(!(std::find(All_inputs.begin(), All_inputs.end(), temp) != All_inputs.end())) {
                    All_inputs.push_back(temp);
                }

                NfaStates.back().addTransition(stateIdCounter,epsilon);
                NfaStates.back().setAcceptable(token, false);
                dummyState.addTransition(stateIdCounter,temp);
                dummyState.setAcceptable(token, false);

                /*NfaStates.back().addTransition(stateIdCounter, temp);
                stateIdCounter++;

                NFAStatee dummyState1(stateIdCounter);
                NfaStates.back().addTransition(stateIdCounter, epsilon);
                dummyState.addTransition(stateIdCounter, epsilon);
                dummyState.addTransition(stateIdCounter-1, temp);*/
                NfaStates.push_back(dummyState);
                //NfaStates.push_back(dummyState1);
                i++;


            }


        }


    }
}
vector <string> NfaAlgorithm :: get_All_inputs(){

    return this->All_inputs;

};

/*
NFAStatee NfaAlgorithm ::getStarState() {


    return this->starState;
}
*/


