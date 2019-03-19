//
// Created by mahmoud on 3/18/19.
//

#include "LexicalRulesParser.h"


vector<string> LexicalRulesParser::split(string stringToSplit,char delimiter){
    vector<string> splitedString;
    stringstream ss(stringToSplit); // Turn the string into a stream.
    string tok;
    while(getline(ss, tok, delimiter)) {
        splitedString.push_back(tok);
    }
    return splitedString;
}

void LexicalRulesParser::handleKeywords(string keywords){
    vector<string>splitedString = split(keywords,' ');
    for(int i = 0;i < splitedString.size();i++){
        if(splitedString[i] == "{" || splitedString[i] == "}"){
            continue;
        }
        else if(splitedString[i].find('{') != string::npos){
            splitedString[i].erase(remove(splitedString[i].begin(), splitedString[i].end(), '{'), splitedString[i].end());
            Allkeywords.push_back(splitedString[i]);
        }
        else if(splitedString[i].find('}') != string::npos){
            splitedString[i].erase(remove(splitedString[i].begin(), splitedString[i].end(), '}'), splitedString[i].end());
            Allkeywords.push_back(splitedString[i]);
        }
        else{
            Allkeywords.push_back(splitedString[i]);
        }
    }
}

void LexicalRulesParser::handlePunctuations(string punctuations){
    vector<string> splitedString = split(punctuations,' ');
    for(int i = 0;i < splitedString.size();i++){
        if(splitedString[i] == "[" || splitedString[i] == "]"){
            continue;
        }
        else if(splitedString[i].find('[') != string::npos){
            splitedString[i].erase(remove(splitedString[i].begin(), splitedString[i].end(), '['), splitedString[i].end());
            Allpunctuations.push_back(splitedString[i]);
        }
        else if(splitedString[i].find(']') != string::npos){
            splitedString[i].erase(remove(splitedString[i].begin(), splitedString[i].end(), ']'), splitedString[i].end());
            Allpunctuations.push_back(splitedString[i]);
        }
        else{
            Allpunctuations.push_back(splitedString[i]);
        }
    }
}

void LexicalRulesParser::readLexicalRules(string fileName){
    ifstream file(fileName);
    string line;
    while(getline(file,line)){
        if(line.at(0) == '{'){
            handleKeywords(line);
        }
        else if(line.at(0) == '['){
            handlePunctuations(line);
        }
    }
}

