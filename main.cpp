#include <iostream>
#include <vector>
#include <map>
#include "NFAStatee.h"
#include "ConversionToDFA.h"
using namespace std;

int main() {
    NFAStatee temp1(1);
    NFAStatee temp2(2);
    NFAStatee temp3(3);
    NFAStatee temp4(4);
    NFAStatee temp5(5);
    NFAStatee temp6(6);
    NFAStatee temp7(7);
    temp1.addTransition(2,"epsilon");
    temp1.addTransition(3,"epsilon");
    temp1.addTransition(5,"epsilon");
    temp2.addTransition(4,"0");
    temp2.addTransition(4,"1");
    temp2.addTransition(3,"epsilon");
    temp3.addTransition(4,"0");
    temp3.addTransition(5,"epsilon");
    temp4.addTransition(5,"0");
    temp4.addTransition(6,"1");
    temp4.addTransition(7,"epsilon");
    temp5.addTransition(5,"0");
    temp5.addTransition(2,"epsilon");
    temp6.addTransition(5,"1");
    temp6.addTransition(7,"epsilon");
    vector<NFAStatee> nfa;
    nfa.push_back(temp1);
    nfa.push_back(temp2);
    nfa.push_back(temp3);
    nfa.push_back(temp4);
    nfa.push_back(temp5);
    nfa.push_back(temp6);
    nfa.push_back(temp7);
    vector<string> inputs;
    inputs.push_back("0");
    inputs.push_back("1");
    ConversionToDFA convert(1,nfa,inputs);
    //vector<int> test;
    //test.push_back(3);
    vector<DFAState> v = convert.convertToDFA();
    //cout<< v.size() << endl;
    DFAState one = v.at(0);
    int l = one.getTransition("0");
    DFAState temp = v.at(l);
    vector<int> o = temp.getNFAEquivalent();

    //vector<int> result = convert.getInputTransitions(test,"1");

    //vector<int> result = temp1.getEpsilonEquivalent();
    for(int i=0;i<o.size();i++){
        cout<< o.at(i) << endl;
    }
//   map<vector<int> , int > l ;
//   vector<int> a;
//   a.push_back(1);
//   a.push_back(2);
//   a.push_back(3);
//   l[a] = 8;
//   vector<int > b;
//   b.push_back(1);
//   b.push_back(2);
//
//   cout << l[b] <<endl;
    return 0;
}