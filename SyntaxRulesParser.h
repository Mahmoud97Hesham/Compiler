//
// Created by mahmoud on 4/22/19.
//

#ifndef LEXICALANALYZER_SYNTAXRULESPARSER_H
#define LEXICALANALYZER_SYNTAXRULESPARSER_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "ProductionRule.h"
#include <algorithm>


using namespace std;

class SyntaxRulesParser{
    vector<Symbol> symbols;
    vector<ProductionRule> productionRules;

public:
    vector<ProductionRule> readSyntaxRules(string fileName);
    vector<string> split(string stringToSplit,char delimiter);
    vector<string> specialSplit(string stringToSplit,char delimiter);
    void rule(string ruleLine);
    void restOfRule(string restOfRuleLine);
    int counting(string rule);
};

#endif //LEXICALANALYZER_SYNTAXRULESPARSER_H