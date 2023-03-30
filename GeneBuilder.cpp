/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GeneBuilder.cpp
 * Author: brian
 * 
 * Created on August 24, 2017, 10:02 AM
 */

#include "GeneBuilder.h"


namespace glch{

    GeneBuilder::GeneBuilder() {
        vMutationLower = -10;
        vMutationUpper = 10;
    }

    GeneBuilder::GeneBuilder(const GeneBuilder& orig) {
    }

    GeneBuilder::~GeneBuilder() {
    }

    
    std::vector<double> breed_vects(std::vector<double>& aV1, std::vector<double>& aV2){

        std::vector<double> lRet(aV1.size());

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
}