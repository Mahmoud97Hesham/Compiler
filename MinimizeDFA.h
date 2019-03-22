#ifndef LEXICALANALYZER_MINIMIZEDFA_H
#define LEXICALANALYZER_MINIMIZEDFA_H

#include <vector>
#include <queue>
#include "DFAState.h"
using namespace std;
class MinimizeDFA {
    vector<DFAState> completeDFAMap;
    queue<DFAState> minimizedDFAMap;
    vector<string> input;
public:
    MinimizeDFA(vector<DFAState> dfaMap,vector<string> inputs);
    vector<DFAState> minimize();
    void updateDFA();
};


#endif //LEXICALANALYZER_MINIMIZEDFA_H
