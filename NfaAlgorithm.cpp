//
// Created by ahmed on 18/03/19.
//

#include <algorithm>
#include "NfaAlgorithm.h"
#include "NFAState.h"
#include <unordered_set>
#include <iostream>


void NfaAlgorithm::Algorithm(string token,string regularExpression) {


    cout<< token<<" "<<"&"<<regularExpression<<"&"<<endl;
    int parenthesisCounter = 0;
    string epsilon = "epsilon";
    if(NfaStates.size()==0){
    NFAStatee StartingState(0);
    StartingState.setAcceptable(token, true);
    NfaStates.push_back(StartingState);
    acceptedStates.insert(NfaStates.back().getId());
    //this->starState=StartingState;
    StartStateTrack.push_back(0);}

    vector<NFAStatee> parenthesisEndStates;
    for (int i = 0; i < regularExpression.length(); i++) {

        if (regularExpression[i] == '(') {


            parenthesisCounter++;

            stateIdCounter++;
            NFAStatee end_this_Parenthes(stateIdCounter);
            parenthesisEndStates.push_back(end_this_Parenthes);

            int index = NfaStates.size()-1;
            StartStateTrack.push_back(index);
            stateIdCounter++;
            NFAStatee dummyState(stateIdCounter);
            dummyState.setAcceptable(token, true);
            if(i==0){
                NfaStates.at(0).addTransition(stateIdCounter, epsilon);
                acceptedStates.erase(NfaStates.at(0).getId());

            } else {
                NfaStates.back().addTransition(stateIdCounter, epsilon);
                acceptedStates.erase(NfaStates.back().getId());
                NfaStates.back().setAcceptable(token, false);
            }
            NfaStates.push_back(dummyState);
            acceptedStates.insert(NfaStates.back().getId());
             index = NfaStates.size()-1;
            StartStateTrack.push_back(index);
        } else if (regularExpression[i] == ')') {

            if (parenthesisCounter > 0) {
                parenthesisCounter--;

              //  cout<<NfaStates.at(StartStateTrack.back()).getId()<<endl;
                NfaStates.back().addTransition(parenthesisEndStates.back().getId(),epsilon);
                NfaStates.back().setAcceptable(token, false);
                acceptedStates.erase(NfaStates.back().getId());
                NfaStates.push_back(parenthesisEndStates.back());
                acceptedStates.insert(NfaStates.back().getId());
                parenthesisEndStates.pop_back();

                stateIdCounter++;

                NFAStatee dummyState(stateIdCounter);
                dummyState.setAcceptable(token, true);
                NfaStates.back().addTransition(stateIdCounter, epsilon);
                NfaStates.back().setAcceptable(token, false);
                acceptedStates.erase(NfaStates.back().getId());
                if (i + 1 < regularExpression.length() && regularExpression[i + 1] == '*') {


                    i++;
                    NfaStates.back().addTransition(NfaStates.at(StartStateTrack.back()).getId(), epsilon);
                    NfaStates.back().setAcceptable(token, false);
                    acceptedStates.erase(NfaStates.back().getId());
                    StartStateTrack.pop_back();
                    NfaStates.at(StartStateTrack.back()).addTransition(stateIdCounter, epsilon);
                    NfaStates.at(StartStateTrack.back()).setAcceptable(token, false);
                    acceptedStates.erase(NfaStates.at(StartStateTrack.back()).getId());

                    StartStateTrack.pop_back();

                } else if (i + 1 < regularExpression.length() && regularExpression[i + 1] == '+') {

                    NfaStates.back().addTransition(NfaStates.at(StartStateTrack.back()).getId(), epsilon);
                    NfaStates.back().setAcceptable(token, false);
                    acceptedStates.erase(NfaStates.back().getId());
                    StartStateTrack.pop_back();
                    StartStateTrack.pop_back();
                } else{
                    StartStateTrack.pop_back();
                    StartStateTrack.pop_back();

                }
                NfaStates.push_back(dummyState);
                acceptedStates.insert(NfaStates.back().getId());


            } else {
                //error
            }

        } else if (regularExpression[i] == '|') {

            if(parenthesisCounter>0){
                NfaStates.back().addTransition(parenthesisEndStates.back().getId(),epsilon);
              //  cout << parenthesisEndStates.back().getId()<<" "<<endl;
                NfaStates.back().setAcceptable(token, false);
                acceptedStates.erase(NfaStates.back().getId());
            }
            stateIdCounter++;
            NFAStatee dummyState(stateIdCounter);
            dummyState.setAcceptable(token, true);
            NfaStates.at(StartStateTrack.back()).addTransition(stateIdCounter, epsilon);
            NfaStates.at(StartStateTrack.back()).setAcceptable(token, false);
            acceptedStates.erase(NfaStates.at(StartStateTrack.back()).getId());
            NfaStates.push_back(dummyState);
            acceptedStates.insert(NfaStates.back().getId());
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

            if(i==1){


                if(temp=="L"){

                    NfaStates.at(0).addTransition(stateIdCounter, epsilon);
                    acceptedStates.erase(NfaStates.at(0).getId());
                } else {
                    NfaStates.at(0).addTransition(stateIdCounter, temp);
                    acceptedStates.erase(NfaStates.at(0).getId());
                }


            } else{


                if(temp=="L"){
                    NfaStates.back().addTransition(stateIdCounter, epsilon);
                    NfaStates.back().setAcceptable(token, false);

                } else{
            NfaStates.back().addTransition(stateIdCounter, temp);
            NfaStates.back().setAcceptable(token, false);
                }

                acceptedStates.erase(NfaStates.back().getId());
            }
            NfaStates.push_back(dummyState);

            acceptedStates.insert(NfaStates.back().getId());

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

                if(i==0){
                    NfaStates.at(0).addTransition(stateIdCounter, temp);
                    acceptedStates.erase(NfaStates.at(0).getId());
                } else{
                NfaStates.back().addTransition(stateIdCounter, temp);
                NfaStates.back().setAcceptable(token, false);
                    acceptedStates.erase(NfaStates.back().getId());
                }
                NfaStates.push_back(dummyState);
                acceptedStates.insert(NfaStates.back().getId());


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
                if(i==0){
                    NfaStates.at(0).addTransition(stateIdCounter, temp);
                    acceptedStates.erase(NfaStates.at(0).getId());

                } else{
                NfaStates.back().addTransition(stateIdCounter, temp);
                NfaStates.back().setAcceptable(token, false);
                    acceptedStates.erase(NfaStates.back().getId());
                }
                NfaStates.push_back(dummyState);
                acceptedStates.insert(NfaStates.back().getId());
                NfaStates.back().addTransition(NfaStates.back().getId(), temp);
                NfaStates.back().setAcceptable(token, false);
                acceptedStates.erase(NfaStates.back().getId());

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
                if(i==0){
                    NfaStates.at(0).addTransition(stateIdCounter, epsilon);
                    acceptedStates.erase(NfaStates.at(0).getId());


                } else{
                NfaStates.back().addTransition(stateIdCounter,epsilon);
                NfaStates.back().setAcceptable(token, false);
                    acceptedStates.erase(NfaStates.back().getId());
                }
                dummyState.addTransition(stateIdCounter,temp);
                dummyState.setAcceptable(token, false);
                acceptedStates.erase(NfaStates.back().getId());

                /*NfaStates.back().addTransition(stateIdCounter, temp);
                stateIdCounter++;

                NFAStatee dummyState1(stateIdCounter);
                NfaStates.back().addTransition(stateIdCounter, epsilon);
                dummyState.addTransition(stateIdCounter, epsilon);
                dummyState.addTransition(stateIdCounter-1, temp);*/
                NfaStates.push_back(dummyState);
                acceptedStates.insert(NfaStates.back().getId());
                //NfaStates.push_back(dummyState1);
                i++;


            }


        }


    }
}
vector <string> NfaAlgorithm :: get_All_inputs(){

    return this->All_inputs;

}

vector<NFAStatee> NfaAlgorithm::getNfaStates() {
    return this->NfaStates;
}

unordered_set<int> NfaAlgorithm::getAcceptedStates()  {
    return acceptedStates;
}

void NfaAlgorithm::setAcceptedStates(int order) {
    this->acceptedStates.insert(order);
}



/*
NFAStatee NfaAlgorithm ::getStarState() {


    return this->starState;
}
*/


