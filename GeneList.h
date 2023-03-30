/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GeneList.h
 * Author: brian
 *
 * Created on August 28, 2018, 6:18 PM
 */

#ifndef GLCH_GENELIST_H
#define GLCH_GENELIST_H

#include "Gene.h"

namespace glch{

class GeneList {
public:
    GeneList();
    GeneList(const GeneList& orig);
    virtual ~GeneList();
    
    GeneList(size_t vSize){
        vGenes.resize(vSize);
    }
    
    std::vector<Gene> vGenes;
    
    void insert_gene(Gene vGene){
        vGenes.push_back(vGene);
    }
    
    void mutate(){
        for(size_t i = 0; i < vGenes.size(); i++){
            vGenes.at(i).mutate();
        }
    }
    
    size_t size(){
        return vGenes.size();
    }
    
    Gene& at(size_t aIndex){
        return vGenes.at(aIndex);
    }
    
    
    
    Gene& at(std::string aGene){
        
        for(size_t i = 0; i < vGenes.size(); i++){
            if(vGenes.at(i).vName == aGene){
                return vGenes.at(i);
            }
        }
        
        throw glch::RuntimeErrorReport("Error, Gene" + aGene + " not found.");
        
    }
    
    void print(){
        
        for(size_t i = 0; i < vGenes.size(); i++){
            vGenes.at(i).print();
        }
        
    }
    
    static GeneList breed(GeneList& aV1, GeneList& aV2){

        GeneList lRet(aV1.size());

        std::vector<size_t> lP1 = glch::range<size_t>(0,(aV1.size()-1));
        std::vector<size_t> lP2 = glch::sample_slice(lP1,aV1.size()/2);            

        for(std::vector<size_t>::iterator it = lP1.begin(); it != lP1.end(); it++){
            lRet.at((*it)) = aV1.at((*it));
        }            

        for(std::vector<size_t>::iterator it = lP2.begin(); it != lP2.end(); it++){
            lRet.at((*it)) = aV2.at((*it));
        }                 

        return lRet;

    }
    
private:

};

}
#endif /* GLCH_GENELIST_H */

