/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Gene.cpp
 * Author: brian
 * 
 * Created on August 28, 2018, 4:16 PM
 */

#include "Gene.h"

namespace glch{

Gene::Gene() {
}

Gene::Gene(const Gene& orig) : 
    vName(orig.vName),
    vValue(orig.vValue),
    vMin(orig.vMin),
    vMax(orig.vMax),
    vHasMin(orig.vHasMin),
    vHasMax(orig.vHasMax),
    vMutateLower(orig.vMutateLower),
    vMutateUpper(orig.vMutateUpper),
    vMean(orig.vMean),
    vStdev(orig.vStdev) {
}

Gene::~Gene() {
}

Gene::Gene(std::string aName,
        double aValue,
        double aMin,
        double aMax,
        bool aHasMin,
        bool aHasMax,
        double aMutateLower,
        double aMutateUpper,
        double aMean,
        double aStdev){
    
    vName = aName;
    vValue = aValue;
    vMin = aMin;
    vMax = aMax;
    vHasMin = aHasMin;
    vHasMax = aHasMax;
    vMutateLower = aMutateLower;
    vMutateUpper = aMutateUpper;
    vMean = aMean;
    vStdev = aStdev;
    
    
}


void Gene::mutate(){
        
        vValue = glch::mutate_norm(vValue, 
                vMutateLower, 
                vMutateUpper, 
                vMean, 
                vStdev, 
                vHasMin, 
                vHasMax, 
                vMin, 
                vMax);
       
    }


}