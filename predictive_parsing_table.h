//
// Created by ahmed on 22/04/19.
//

#ifndef LEXICALANALYZER_PREDICTIVE_PARSING_TABLE_H
#define LEXICALANALYZER_PREDICTIVE_PARSING_TABLE_H
#include <vector>
#include <map>
#include <string>
#include "ProductionRule.h"

using namespace std;

class predictive_parsing_table {
    vector<ProductionRule> productionRules;
    vector<Symbol>nonTerminals;
    vector<Symbol>Terminals;

public:
    void set_Productions(vector<ProductionRule> productionRules);
    int **set_Relation(int non_Terminal_Symbol_order ,int  Terminal_Symbol_order,int production_num, int production_index );
    void set_predictive_Table();

};


#endif //LEXICALANALYZER_PREDICTIVE_PARSING_TABLE_H
