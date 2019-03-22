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
            allKeywords.push_back(splitedString[i]);
        }
        else if(splitedString[i].find('}') != string::npos){
            splitedString[i].erase(remove(splitedString[i].begin(), splitedString[i].end(), '}'), splitedString[i].end());
            allKeywords.push_back(splitedString[i]);
        }
        else{
            allKeywords.push_back(splitedString[i]);
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
            allPunctuations.push_back(splitedString[i]);
        }
        else if(splitedString[i].find(']') != string::npos){
            splitedString[i].erase(remove(splitedString[i].begin(), splitedString[i].end(), ']'), splitedString[i].end());
            allPunctuations.push_back(splitedString[i]);
        }
        else{
            allPunctuations.push_back(splitedString[i]);
        }
    }
}

string LexicalRulesParser::handleFromToChar(string fromToString) {
    vector<string> splitByFromTo = split(fromToString,'-');
    string fromToLogic = "";
    for(int i = int(splitByFromTo[0].at(0)); i <= int(splitByFromTo[1].at(0));i++){
        fromToLogic.push_back(char(i));
        if(i != int(splitByFromTo[1].at(0))){
            fromToLogic += "|";
        }
    }
    return fromToLogic;
}

void LexicalRulesParser::handleRegularDefinition(string regularDefinition) {
    vector<string> singleRegularDefinition;
    regularDefinition.erase(remove(regularDefinition.begin(), regularDefinition.end(), ' '), regularDefinition.end());
    vector<string> splitRegularDefinitionName = split(regularDefinition,'=');
    singleRegularDefinition.push_back(splitRegularDefinitionName[0]);
    string regularDefinitionLogic = "(";
    if(splitRegularDefinitionName[1].find('|') != string::npos){
        vector<string> splitByOr = split(splitRegularDefinitionName[1],'|');
        for(int i = 0;i < splitByOr.size();i++){
            if(splitByOr[i].find('-') != string::npos){
                regularDefinitionLogic += handleFromToChar(splitByOr[i]);
            }
            else{
                bool regularDefinitionFound = false;
                for(int j = 0;j < allRegularDefinitions.size();j++){
                    if(splitByOr[i].find(allRegularDefinitions[j][0]) != std::string::npos){
                        regularDefinitionLogic += allRegularDefinitions[j][1];
                        size_t pos = splitByOr[i].find(allRegularDefinitions[j][1]);
                        if (pos != std::string::npos)
                        {
                            // If found then erase it from string
                            splitByOr[i].erase(pos, allRegularDefinitions[j][1].length());
                        }
                        if(!splitByOr[i].empty()){
                            regularDefinitionLogic += splitByOr[i];
                        }
                        regularDefinitionFound = true;
                        break;
                    }
                    else{
                        continue;
                    }
                }
                if(!regularDefinitionFound){
                    regularDefinitionLogic += splitByOr[i];
                }
            }
            if(i != splitByOr.size() - 1){
                regularDefinitionLogic += "|";
            }
        }
    }
    else if(splitRegularDefinitionName[1].find('-') != string::npos){
        regularDefinitionLogic += handleFromToChar(splitRegularDefinitionName[1]);
    }
    else{
        bool regularDefinitionFound = false;
        for(int j = 0;j < allRegularDefinitions.size();j++){
            if(splitRegularDefinitionName[1].find(allRegularDefinitions[j][0]) != std::string::npos){
                regularDefinitionLogic += allRegularDefinitions[j][1];
                size_t pos = splitRegularDefinitionName[1].find(allRegularDefinitions[j][1]);
                if (pos != std::string::npos)
                {
                    splitRegularDefinitionName[1].erase(pos, allRegularDefinitions[j][1].length());
                }
                if(!splitRegularDefinitionName[1].empty()){
                    regularDefinitionLogic += splitRegularDefinitionName[1];
                }
                regularDefinitionFound = true;
                break;
            }
            else{
                continue;
            }
        }
        if(!regularDefinitionFound){
            regularDefinitionLogic += splitRegularDefinitionName[1];
        }
    }
    regularDefinitionLogic += ")";
    singleRegularDefinition.push_back(regularDefinitionLogic);
    allRegularDefinitions.push_back(singleRegularDefinition);
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
        else if((line.find('=') != string::npos) && !(line.find(':') != string::npos)){
            handleRegularDefinition(line);
        }
    }
}

