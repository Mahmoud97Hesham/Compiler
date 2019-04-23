//
// Created by mahmoud on 4/22/19.
//

#include "SyntaxRulesParser.h"

vector<string> SyntaxRulesParser::split(string stringToSplit, char delimiter) {
    vector<string> splitedString;
    stringstream ss(stringToSplit); // Turn the string into a stream.
    string tok;
    while(getline(ss, tok, delimiter)) {
        splitedString.push_back(tok);
    }
    return splitedString;
}

int SyntaxRulesParser::counting(string rule) {
    int countEqual = count(rule.begin(), rule.end(), '=');
    return countEqual;
}

vector<string> SyntaxRulesParser::specialSplit(string stringToSplit, char delimiter) {
    int pos = stringToSplit.find(delimiter);
    vector<string> splittedString;
    splittedString.push_back(stringToSplit.substr(0,pos));
    string right = stringToSplit.substr(pos);
    right.replace(0,1,"");
    splittedString.push_back(right);
    return splittedString;
}

void SyntaxRulesParser::rule(string ruleLine) {
    int countEqual = counting(ruleLine);
    vector<string> splitedRule;
    if(countEqual > 1){
        splitedRule = specialSplit(ruleLine,'=');
    }
    else{
        splitedRule = split(ruleLine,'=');
    }
    splitedRule[0].erase(remove(splitedRule[0].begin(), splitedRule[0].end(), '#'), splitedRule[0].end());
    splitedRule[0].erase(remove(splitedRule[0].begin(), splitedRule[0].end(), ' '), splitedRule[0].end());
    Symbol currentSymbol;
    bool isFound = false;
    for(int i = 0;i < symbols.size();i++){
        bool in = symbols[i].isEqual(splitedRule[0]);
        if(in){
            currentSymbol = symbols[i];
            isFound = true;
            break;
        }
    }
    if(!isFound){
        currentSymbol = Symbol(splitedRule[0]);
        symbols.push_back(currentSymbol);
    }
    ProductionRule currentProductionRule = ProductionRule(currentSymbol);
    if(splitedRule[1].find('|') != string::npos){
        vector<string> splittedByOr = split(splitedRule[1],'|');
        for(int i = 0;i < splittedByOr.size();i++){
            if(i == splittedByOr.size() - 1){
                splittedByOr[i].replace(0,1,"");
            }
            else{
                splittedByOr[i].replace(0,1,"");
                splittedByOr[i].pop_back();
            }
        }
        for(int i = 0;i < splittedByOr.size();i++){
            if(splittedByOr[i].find(' ') != string::npos){
                vector<string> splitBySpace = split(splittedByOr[i],' ');
                for(int j = 0;j < splitBySpace.size();j++){
                    if(splitBySpace[j].at(0) == '\''){
                        splitBySpace[j].erase(remove(splitBySpace[j].begin(), splitBySpace[j].end(), '\''), splitBySpace[j].end());
                        bool found = false;
                        Symbol terminalSymbol;
                        for(int k = 0;k < symbols.size();k++){
                            if(symbols[k].isEqual(splitBySpace[j])){
                                terminalSymbol = symbols[k];
                                found = true;
                                break;
                            }
                        }
                        if(!found){
                            terminalSymbol = Symbol(splitBySpace[j]);
                            terminalSymbol.setTerminal(true);
                            symbols.push_back(terminalSymbol);
                        }
                        if(j == 0){
                            currentProductionRule.addSymbol(terminalSymbol, true);
                        }
                        else{
                            currentProductionRule.addSymbol(terminalSymbol, false);
                        }
                    }
                    else{
                        bool found = false;
                        Symbol nonTerminalSymbol;
                        for(int k = 0;k < symbols.size();k++){
                            if(symbols[k].isEqual(splitBySpace[j])){
                                nonTerminalSymbol = symbols[k];
                                found = true;
                                break;
                            }
                        }
                        if(!found){
                            nonTerminalSymbol = Symbol(splitBySpace[j]);
                            symbols.push_back(nonTerminalSymbol);
                        }
                        if(j == 0){
                            currentProductionRule.addSymbol(nonTerminalSymbol, true);
                        }
                        else{
                            currentProductionRule.addSymbol(nonTerminalSymbol, false);
                        }
                    }
                }
            }
            else{
                if(splittedByOr[i].at(0) == '\''){
                    splittedByOr[i].erase(remove(splittedByOr[i].begin(), splittedByOr[i].end(), '\''), splittedByOr[i].end());
                    bool found = false;
                    Symbol terminalSymbol;
                    for(int j = 0;j < symbols.size();j++){
                        if(symbols[j].isEqual(splittedByOr[i])){
                            terminalSymbol = symbols[j];
                            found = true;
                            break;
                        }
                    }
                    if(!found){
                        terminalSymbol = Symbol(splittedByOr[i]);
                        terminalSymbol.setTerminal(true);
                        symbols.push_back(terminalSymbol);
                    }
                    currentProductionRule.addSymbol(terminalSymbol, true);
                }
                else{
                    bool found = false;
                    Symbol nonTerminalSymbol;
                    for(int j = 0;j < symbols.size();j++){
                        if(symbols[j].isEqual(splittedByOr[i])){
                            nonTerminalSymbol = symbols[j];
                            found = true;
                            break;
                        }
                    }
                    if(!found){
                        nonTerminalSymbol = Symbol(splittedByOr[i]);
                        symbols.push_back(nonTerminalSymbol);
                    }
                    currentProductionRule.addSymbol(nonTerminalSymbol, true);
                }
            }
        }
    }
    else{
        if(splitedRule[1].at(0) == ' '){
            splitedRule[1].replace(0,1,"");
        }
        if(splitedRule[1].find(' ') != string::npos){
            vector<string> splitBySpace = split(splitedRule[1],' ');
            for(int i = 0;i < splitBySpace.size();i++){
                if(splitBySpace[i].at(0) == '\''){
                    splitBySpace[i].erase(remove(splitBySpace[i].begin(), splitBySpace[i].end(), '\''), splitBySpace[i].end());
                    bool found = false;
                    Symbol terminalSymbol;
                    for(int j = 0;j < symbols.size();j++){
                        if(symbols[j].isEqual(splitBySpace[i])){
                            terminalSymbol = symbols[j];
                            found = true;
                            break;
                        }
                    }
                    if(!found){
                        terminalSymbol = Symbol(splitBySpace[i]);
                        terminalSymbol.setTerminal(true);
                        symbols.push_back(terminalSymbol);
                    }
                    if(i == 0){
                        currentProductionRule.addSymbol(terminalSymbol, true);
                    }
                    else{
                        currentProductionRule.addSymbol(terminalSymbol, false);
                    }
                }
                else{
                    bool found = false;
                    Symbol nonTerminalSymbol;
                    for(int j = 0;j < symbols.size();j++){
                        if(symbols[j].isEqual(splitBySpace[i])){
                            nonTerminalSymbol = symbols[j];
                            found = true;
                            break;
                        }
                    }
                    if(!found){
                        nonTerminalSymbol = Symbol(splitBySpace[i]);
                        symbols.push_back(nonTerminalSymbol);
                    }
                    if(i == 0){
                        currentProductionRule.addSymbol(nonTerminalSymbol, true);
                    }
                    else{
                        currentProductionRule.addSymbol(nonTerminalSymbol, false);
                    }
                }
            }
        }
        else{
            if(splitedRule[1].at(0) == '\''){
                splitedRule[1].erase(remove(splitedRule[1].begin(), splitedRule[1].end(), '\''), splitedRule[1].end());
                bool found = false;
                Symbol terminalSymbol;
                for(int j = 0;j < symbols.size();j++){
                    if(symbols[j].isEqual(splitedRule[1])){
                        terminalSymbol = symbols[j];
                        found = true;
                        break;
                    }
                }
                if(!found){
                    terminalSymbol = Symbol(splitedRule[1]);
                    terminalSymbol.setTerminal(true);
                    symbols.push_back(terminalSymbol);
                }
                currentProductionRule.addSymbol(terminalSymbol, true);
            }
            else{
                bool found = false;
                Symbol nonTerminalSymbol;
                for(int j = 0;j < symbols.size();j++){
                    if(symbols[j].isEqual(splitedRule[1])){
                        nonTerminalSymbol = symbols[j];
                        found = true;
                        break;
                    }
                }
                if(!found){
                    nonTerminalSymbol = Symbol(splitedRule[1]);
                    symbols.push_back(nonTerminalSymbol);
                }
                currentProductionRule.addSymbol(nonTerminalSymbol, true);
            }
        }
    }
    productionRules.push_back(currentProductionRule);
}

void SyntaxRulesParser::restOfRule(string restOfRuleLine) {
    restOfRuleLine.replace(0,1,"");
    restOfRuleLine.replace(0,1,"");
    if(restOfRuleLine.find(' ') != string::npos){
        vector<string> splitBySpace = split(restOfRuleLine,' ');
        for(int i = 0;i < splitBySpace.size();i++){
            if(splitBySpace[i].at(0) == '\''){
                splitBySpace[i].erase(remove(splitBySpace[i].begin(), splitBySpace[i].end(), '\''), splitBySpace[i].end());
                bool found = false;
                Symbol terminalSymbol;
                for(int j = 0;j < symbols.size();j++){
                    if(symbols[j].isEqual(splitBySpace[i])){
                        terminalSymbol = symbols[j];
                        found = true;
                        break;
                    }
                }
                if(!found){
                    terminalSymbol = Symbol(splitBySpace[i]);
                    terminalSymbol.setTerminal(true);
                    symbols.push_back(terminalSymbol);
                }
                if(i == 0){
                    productionRules[productionRules.size() - 1].addSymbol(terminalSymbol, true);
                }
                else{
                    productionRules[productionRules.size() - 1].addSymbol(terminalSymbol, false);
                }
            }
            else{
                bool found = false;
                Symbol nonTerminalSymbol;
                for(int j = 0;j < symbols.size();j++){
                    if(symbols[j].isEqual(splitBySpace[i])){
                        nonTerminalSymbol = symbols[j];
                        found = true;
                        break;
                    }
                }
                if(!found){
                    nonTerminalSymbol = Symbol(splitBySpace[i]);
                    symbols.push_back(nonTerminalSymbol);
                }
                if(i == 0){
                    productionRules[productionRules.size() - 1].addSymbol(nonTerminalSymbol, true);
                }
                else{
                    productionRules[productionRules.size() - 1].addSymbol(nonTerminalSymbol, false);
                }
            }
        }
    }
    else{
        if(restOfRuleLine.at(0) == '\''){
            restOfRuleLine.erase(remove(restOfRuleLine.begin(), restOfRuleLine.end(), '\''), restOfRuleLine.end());
            bool found = false;
            Symbol terminalSymbol;
            for(int j = 0;j < symbols.size();j++){
                if(symbols[j].isEqual(restOfRuleLine)){
                    terminalSymbol = symbols[j];
                    found = true;
                    break;
                }
            }
            if(!found){
                terminalSymbol = Symbol(restOfRuleLine);
                terminalSymbol.setTerminal(true);
                symbols.push_back(terminalSymbol);
            }
            productionRules[productionRules.size() - 1].addSymbol(terminalSymbol, true);
        }
        else{
            bool found = false;
            Symbol nonTerminalSymbol;
            for(int j = 0;j < symbols.size();j++){
                if(symbols[j].isEqual(restOfRuleLine)){
                    nonTerminalSymbol = symbols[j];
                    found = true;
                    break;
                }
            }
            if(!found){
                nonTerminalSymbol = Symbol(restOfRuleLine);
                symbols.push_back(nonTerminalSymbol);
            }
            productionRules[productionRules.size() - 1].addSymbol(nonTerminalSymbol, true);
        }
    }
}

vector<ProductionRule> SyntaxRulesParser::readSyntaxRules(string fileName) {
    ifstream file(fileName);
    string line;
    while(getline(file,line)){
        if(line.at(0)  != '#'){
            restOfRule(line);
        }
        else{
            rule(line);
        }
    }
    return productionRules;
}