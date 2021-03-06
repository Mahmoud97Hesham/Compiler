//
// Created by mahmoud on 3/18/19.
//

#include "LexicalRulesParser.h"
#include "NfaAlgorithm.h"
#include "DFAState.h"
#include "ConversionToDFA.h"
#include "LexicalAnaLyzerGenerator.h"
#include "MinimizeDFA.h"
#include "iostream"

NfaAlgorithm nfaAlg;


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
            nfaAlg.Algorithm(splitedString[i],splitedString[i]);
        }
        else if(splitedString[i].find('}') != string::npos){
            splitedString[i].erase(remove(splitedString[i].begin(), splitedString[i].end(), '}'), splitedString[i].end());
            allKeywords.push_back(splitedString[i]);
            nfaAlg.Algorithm(splitedString[i],splitedString[i]);
        }
        else{
            allKeywords.push_back(splitedString[i]);
            nfaAlg.Algorithm(splitedString[i],splitedString[i]);
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
            nfaAlg.Algorithm(splitedString[i],splitedString[i]);
        }
        else if(splitedString[i].find(']') != string::npos){
            splitedString[i].erase(remove(splitedString[i].begin(), splitedString[i].end(), ']'), splitedString[i].end());
            allPunctuations.push_back(splitedString[i]);
            nfaAlg.Algorithm(splitedString[i],splitedString[i]);
        }
        else{
            allPunctuations.push_back(splitedString[i]);
            nfaAlg.Algorithm(splitedString[i],splitedString[i]);
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

bool isLetter(char c) {
    if((c >= 97 && c <= 122)) return true;
    return false;
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
                for(int j = allRegularDefinitions.size() - 1;j <= 0;j--){
                    if(splitByOr[i].find(allRegularDefinitions[j][0]) != std::string::npos){
                        regularDefinitionLogic += allRegularDefinitions[j][1];
                        size_t pos = splitByOr[i].find(allRegularDefinitions[j][0]);
                        if (pos != std::string::npos)
                        {
                            // If found then erase it from string
                            splitByOr[i].erase(pos, allRegularDefinitions[j][0].length());
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
        for(int j = allRegularDefinitions.size() - 1;j >= 0;j--){
            size_t start_pos = 0;
            if((start_pos = splitRegularDefinitionName[1].find(allRegularDefinitions[j][0],start_pos)) != std::string::npos ){
                if(start_pos != 0){
                    if(isLetter(splitRegularDefinitionName[1].at(start_pos - 1)) || isLetter(splitRegularDefinitionName[1].at(start_pos + allRegularDefinitions[j][0].length()))){
                        continue;
                    }
                }
                else{
                    if(isLetter(splitRegularDefinitionName[1].at(start_pos + allRegularDefinitions[j][0].length()))){
                        continue;
                    }
                }
                regularDefinitionLogic += allRegularDefinitions[j][1];
                size_t pos = splitRegularDefinitionName[1].find(allRegularDefinitions[j][0]);
                if (pos != std::string::npos)
                {
                    splitRegularDefinitionName[1].erase(pos, allRegularDefinitions[j][0].length());
                }
                if(!splitRegularDefinitionName[1].empty()){
                    regularDefinitionLogic += splitRegularDefinitionName[1];
                }
                regularDefinitionFound = true;
                break;
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

void LexicalRulesParser::handleRegularExpressions(string regularExpression) {
    vector<string> singleRegularExpression;
    regularExpression.erase(remove(regularExpression.begin(), regularExpression.end(), ' '), regularExpression.end());
    vector<string> splitRegularExpressionName = split(regularExpression,':');
    singleRegularExpression.push_back(splitRegularExpressionName[0]);

    for(int i = allRegularDefinitions.size() - 1;i >= 0;i--){
        size_t start_pos = 0;
        while((start_pos = splitRegularExpressionName[1].find(allRegularDefinitions[i][0], start_pos)) != std::string::npos) {
            if(start_pos != 0){
                if(isLetter(splitRegularExpressionName[1].at(start_pos - 1)) || isLetter(splitRegularExpressionName[1].at(start_pos + allRegularDefinitions[i][0].length()))){
                    break;
                }
            }
            else{
                if(isLetter(splitRegularExpressionName[1].at(start_pos + allRegularDefinitions[i][0].length()))){
                    break;
                }
            }
            splitRegularExpressionName[1].replace(start_pos, allRegularDefinitions[i][0].length(), allRegularDefinitions[i][1]);
            start_pos += allRegularDefinitions[i][1].length();
        }
    }
    for(int i = allRegularExpressions.size() - 1;i >= 0;i--){
        size_t start_pos = 0;
        while((start_pos = splitRegularExpressionName[1].find(allRegularExpressions[i][0], start_pos)) != std::string::npos) {
            if(start_pos != 0){
                if(isLetter(splitRegularExpressionName[1].at(start_pos - 1)) || isLetter(splitRegularExpressionName[1].at(start_pos + allRegularExpressions[i][0].length()))){
                    break;
                }
            }
            else{
                if(isLetter(splitRegularExpressionName[1].at(start_pos + allRegularExpressions[i][0].length()))){
                    break;
                }
            }
            splitRegularExpressionName[1].replace(start_pos, allRegularExpressions[i][0].length(), allRegularExpressions[i][1]);
            start_pos += allRegularExpressions[i][1].length();
        }
    }
    singleRegularExpression.push_back(splitRegularExpressionName[1]);
    nfaAlg.Algorithm(singleRegularExpression[0],singleRegularExpression[1]);
   // cout<<singleRegularExpression[1]<<endl;
    allRegularExpressions.push_back(singleRegularExpression);
}

void LexicalRulesParser::readLexicalRules(string fileName){
    ifstream file(fileName);
    string line;
    int errorInLineNumber = 0;
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
        else if(line.find(':') != string::npos){
            handleRegularExpressions(line);
        }
        else{
            errorInLine.push_back(errorInLineNumber);
        }
        errorInLineNumber++;
    }
    /*for(int i = 0; i < allKeywords.size(); i++){
        nfaAlg.Algorithm(allKeywords[i],allKeywords[i]);
    }

    for(int i = 0; i < allPunctuations.size(); i++){
        nfaAlg.Algorithm(allPunctuations[i],allPunctuations[i]);
    }*/
    cout << "KEYWORDS " << endl;
    for(int i = 0;i<allKeywords.size();i++){
        cout << allKeywords[i] << endl;
    }
    vector<NFAStatee> nfa = nfaAlg.getNfaStates();
    vector<NFAStatee> temp;
    for(int i = 0 ; i < nfa.size();i++){
        NFAStatee dummy(-1);
        temp.push_back(dummy);
    }
    for(int i = 0 ; i < temp.size();i++){
        temp[nfa.at(i).getId()] = nfa.at(i);
    }
    unordered_set<int> accept = nfaAlg.getAcceptedStates();
    ConversionToDFA convert(0,temp,nfaAlg.get_All_inputs(),accept,allKeywords);
    vector<DFAState> v = convert.convertToDFA();
//    //cout<< v.size() << endl;
    vector<string> input = nfaAlg.get_All_inputs();
    cout << endl;
    for (int j = 0; j < input.size(); j++) {
        cout << " " << input.at(j);
    }
    cout << endl;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].getID() != -1) {
            cout << v[i].getID() << "  ";
            for (int j = 0; j < input.size(); j++) {
                cout << " " << v[i].getTransition(input.at(j));
            }
            cout << endl;
        }
    }
    MinimizeDFA minimize(v,nfaAlg.get_All_inputs());
    vector<DFAState> minimized = minimize.minimize();
    minimize.printMinimizedDFATable();
    LexicalAnaLyzerGenerator lag(minimized);
   // cout << endl << endl;
    vector<string> test = lag.generateLexicalOutput("test.txt");
    //cout << test.size() << endl;
    ofstream outputFile("output.txt");
    for(int i = 0; i < test.size(); ++i) {
        outputFile << test[i] << endl;
    }

}


