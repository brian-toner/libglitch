/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Gene.h
 * Author: brian
 *
 * Created on August 28, 2018, 4:16 PM
 */

#ifndef GLCH_GENE_H
#define GLCH_GENE_H

#include <iostream>
#include "random.h"

namespace glch{

class Gene {
public:
    Gene();
    Gene(const Gene& orig);
    virtual ~Gene();
    
    Gene(std::string aName,
        double aValue,
        double aMin,
        double aMax,
        bool aHasMin,
        bool aHasMax,
        double aMutateLower,
        double aMutateUpper,
        double aMean,
        double aStdev);
    
    std::string vName;
    double vValue;
    double vMin;
    double vMax;
    bool vHasMin;
    bool vHasMax;
    
    double vMutateLower;
    double vMutateUpper;
    
    double vMean;
    double vStdev;
    
    void mutate();
    
    void print(){
        std::cout << vName << ": ";
        std::cout << vValue << " ";
        std::cout << vMin << " ";
        std::cout << vMax << " ";
        std::cout << vHasMin << " ";
        std::cout << vHasMax << " ";
    
        std::cout << vMutateLower << " ";
        std::cout << vMutateUpper << " ";
    
        std::cout << vMean << " ";
        std::cout << vStdev << "\n";
    }
    
private:

};

}

#endif /* GLCH_GENE_H */

