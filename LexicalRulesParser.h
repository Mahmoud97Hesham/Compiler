//
// Created by mahmoud on 3/18/19.
//

#ifndef LEXICALANALYZER_LEXICALRULESPARSER_H
#define LEXICALANALYZER_LEXICALRULESPARSER_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;


class LexicalRulesParser {
    vector<string> allKeywords;
    vector<string> allPunctuations;
    vector<vector<string>> allRegularDefinitions;

public:
    void readLexicalRules(string fileName);

    void handleKeywords(string keywords);

    vector<string> split(string stringToSplit, char delimiter);

    void handlePunctuations(string punctuations);

    void handleRegularDefinition(string regularDefinition);

    string handleFromToChar(string fromToString);
};

#endif //LEXICALANALYZER_LEXICALRULESPARSER_H
