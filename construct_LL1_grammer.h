//
// Created by ahmed on 22/04/19.
//

#include "ParserGenerator.h"
using namespace std;


class construct_LL1_grammer {
    vector<ProductionRule> prVec;
private:
    void leftRecursion();
    vector<ProductionRule> leftFactoring();
public:
    void setproduction( vector<ProductionRule> prVec);
    vector<ProductionRule> prVecgetproduction( );


};


