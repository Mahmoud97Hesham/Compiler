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
    vector<string> Allkeywords;
    vector<string> Allpunctuations;

public:
    void readLexicalRules(string fileName);

    void handleKeywords(string keywords);

    vector<string> split(string stringToSplit, char delimiter);

    void handlePunctuations(string punctuations);
};

#endif //LEXICALANALYZER_LEXICALRULESPARSER_H
