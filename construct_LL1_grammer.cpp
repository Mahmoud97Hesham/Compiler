//
// Created by ahmed on 22/04/19.
//

#include "construct_LL1_grammer.h"
#include <string>
#include <iostream>
using namespace std;

void construct_LL1_grammer::setproduction(vector<ProductionRule> prVec) {

    this->prVec = prVec;
    leftRecursion();
    leftFactoring();
}

void construct_LL1_grammer::leftRecursion() {

   for(int i=0;i<this->prVec.size();i++){

       for (int j = 0; j <prVec.at(i).getRHSSize() ; j++) {

           if (prVec.at(i).getName().getName()==prVec.at(i).getRHS(j).getFirst().getName()) {

               int k=0;
               if(j==0){
                   k=1;
               }

               string newSymbolName = prVec.at(i).getName().getName()+"'";

               Symbol S = Symbol(newSymbolName);
            while ( k<prVec.at(i).getRHSSize()){


            /*   vector<Symbol> temp = prVec.at(i).getRHSPointer(k)->getSymbolsVector();
                temp.push_back(S);
*/

                vector<Symbol>* pointer = prVec.at(i).getRHSPointer(k)->getPointerofSymbolSet();
                 pointer->push_back(S);
                /*cout<<prVec.at(i).getRHS(k).getSymbolsVector().back().getName()<<endl;
                cout<<S.getName()<<endl;*/
                k++;
                if(k==j){
                    k++;
                }

            }


               ProductionRule pr = ProductionRule(S);
            // extract B from AB to start the RHS  in the new production
            vector<Symbol> *myvector = prVec.at(i).getRHSPointer(j)->getPointerofSymbolSet();
               myvector->erase(myvector->begin());

               //vector<Symbol> B = prVec.at(i).getRHS().at(j).getSymbolsVector();

               pr.addSymbol(myvector->at(0),true);
               for(int y=1;y<myvector->size();y++){
                   pr.addSymbol(myvector->at(y), false);
               }

               pr.addSymbol(S,false);

               Symbol eps = Symbol("epsilon");

                pr.addSymbol(eps, true);


               prVec.at(i).getAllRHSpointer()->erase(prVec.at(i).getAllRHSpointer()->begin()+j);

           prVec.push_back(pr);
           }
       }


   }

}

vector<ProductionRule> construct_LL1_grammer::leftFactoring() {




    for(int i=0;i<this->prVec.size();i++){

        for (int j = 0; j <prVec.at(i).getRHSSize()-1 ; j++) {

            vector<int> indexes ;
            bool their_is_factoring = false;
            for(int k=j+1;k<prVec.at(i).getRHSSize();k++){

                if(prVec.at(i).getRHS(j).getFirst().getName()==prVec.at(i).getRHS(k).getFirst().getName()){
                    indexes.push_back(k-1);
                    their_is_factoring= true;
                }

            }

            if(their_is_factoring) {




                Symbol factor1 = Symbol(prVec.at(i).getRHS(j).getFirst().getName());
                SymbolsSet factorSet ;
                factorSet.addSymbol(factor1);
                Symbol factor2 = Symbol(prVec.at(i).getRHS(j).getFirst().getName() +prVec.at(i).getRHS(j).getFirst().getName()+"'");
                factorSet.addSymbol(factor2);
                ProductionRule pr = ProductionRule(factor2);

                vector<SymbolsSet> *SetPointer = prVec.at(i).getAllRHSpointer();

                SetPointer->push_back(factorSet);

                vector<Symbol> *myvector = prVec.at(i).getRHSPointer(j)->getPointerofSymbolSet();

                myvector->erase(myvector->begin());




                pr.addSymbol(myvector->at(0),true);

                for(int y=1;y<myvector->size();y++){
                    pr.addSymbol(myvector->at(y), false);
                }

                prVec.at(i).getAllRHSpointer()->erase(prVec.at(i).getAllRHSpointer()->begin()+j);

                int decreaser = 0;
                for (int k = 0; k < indexes.size(); k++) {

                    cout<<indexes.at(k)<<endl;

                    vector<Symbol> *myvect = prVec.at(i).getRHSPointer(indexes.at(k)-decreaser)->getPointerofSymbolSet();

                    myvect->erase(myvect->begin());

                    pr.addSymbol(myvect->at(0),true);
                    for(int y=1;y<myvect->size();y++){
                        pr.addSymbol(myvect->at(y), false);
                    }

                    prVec.at(i).getAllRHSpointer()->erase(prVec.at(i).getAllRHSpointer()->begin()+indexes.at(k)-decreaser);

                decreaser++;
                }
                prVec.push_back(pr);

            }


        }
    }




    return vector<ProductionRule>();
}

vector<ProductionRule> construct_LL1_grammer::prVecgetproduction() {



                return this->prVec;
}

