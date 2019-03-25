#include <iostream>
#include <vector>
#include <map>
#include "NFAState.h"
#include "ConversionToDFA.h"
#include "MinimizeDFA.h"
#include "NfaAlgorithm.h"
#include "LexicalRulesParser.h"
#include "LexicalAnaLyzerGenerator.h"
#include <unordered_set>
#include <iterator>

using namespace std;

int main() {
   /* NFAStatee temp1(0);
    NFAStatee temp2(1);
    NFAStatee temp3(2);
    NFAStatee temp4(3);
    NFAStatee temp5(4);
    NFAStatee temp6(5);
    NFAStatee temp7(6);
    temp1.addTransition(1,"epsilon");
    temp1.addTransition(2,"epsilon");
    temp1.addTransition(4,"epsilon");
    temp2.addTransition(3,"0");
    temp2.addTransition(3,"1");
    temp2.addTransition(2,"epsilon");
    temp3.addTransition(3,"0");
    temp3.addTransition(4,"epsilon");
    temp4.addTransition(4,"0");
    temp4.addTransition(5,"1");
    temp4.addTransition(6,"epsilon");
    temp5.addTransition(4,"0");
    temp5.addTransition(1,"epsilon");
    temp6.addTransition(4,"1");
    temp6.addTransition(6,"epsilon");
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
    ConversionToDFA convert(0,nfa,inputs);
    //vector<int> test;
    //test.push_back(3);
    vector<DFAState> v = convert.convertToDFA();
    //cout<< v.size() << endl;
//    DFAState l = v.at(1);
//    vector<int> o = l.getNFAEquivalent();
    MinimizeDFA minimize(v,inputs);
    vector<DFAState> minimized = minimize.minimize();
    DFAState one = minimized.at(4);
    int l = one.getTransition("0");

    DFAState temp = minimized.at(l);
    vector<int> o = temp.getNFAEquivalent();
    //vector<int> result = convert.getInputTransitions(test,"1");

    //vector<int> result = temp1.getEpsilonEquivalent();
//    for(int i=0;i<o.size();i++){
//        cout<< o.at(i) << endl;
//    }
    minimize.printMinimizedDFATable();
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
*/

  // LexicalRulesParser lexical;
//    lexical.readLexicalRules("LexicalRules");




NfaAlgorithm testNfa;

//testNfa.Algorithm("letter","(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)((a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z))*");
//testNfa.Algorithm("digit","(0|1|2|3|4|5|6|7|8|9)");
//testNfa.Algorithm("digits","(0|1|2|3|4|5|6|7|8|9)+");
//testNfa.Algorithm("p1","(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)((a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)|(0|1|2|3|4|5|6|7|8|9))*");
testNfa.Algorithm("p1","(a|b)((c|d)|(0|1))*");
vector<string> tttt = testNfa.get_All_inputs();
  vector<NFAStatee> states = testNfa.getNfaStates();
  int size = testNfa.get_All_inputs().size();
  for (int  i = 0;  i <size ; ++ i) {


    cout << tttt.back()<<endl;

    tttt.pop_back();
  }

  unordered_set<int> s =testNfa.getAcceptedStates();

    std::copy(s.begin(),
              s.end(),
              std::ostream_iterator<int>(std::cout, " "));

    vector<NFAStatee> temp;
    for(int i = 0 ; i < states.size();i++){
        NFAStatee dummy(-1);
        temp.push_back(dummy);
    }
    for(int i = 0 ; i < temp.size();i++){
        temp[states.at(i).getId()] = states.at(i);
    }
    unordered_set<int> accept = testNfa.getAcceptedStates();
    ConversionToDFA convert(0,temp,testNfa.get_All_inputs(),accept);
    //vector<int> test;
    //test.push_back(3);
    vector<DFAState> v = convert.convertToDFA();
    //cout<< v.size() << endl;
//    DFAState l = v.at(1);
//    vector<int> o = l.getNFAEquivalent();
    MinimizeDFA minimize(v,testNfa.get_All_inputs());
    vector<DFAState> minimized = minimize.minimize();
//    minimize.printMinimizedDFATable();
//    cout << "ACCEPT " << minimized.at(2).getToken() << endl;

    LexicalAnaLyzerGenerator lag(minimized);
    cout << endl << endl;
    vector<string> test = lag.generateLexicalOutput("test.txt");
    cout << test.size() << endl;
    ofstream outputFile("output.txt");
    for(int i = 0; i < test.size(); ++i) {
        outputFile << test[i] << endl;
    }




  return 0;
}