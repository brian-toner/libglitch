/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GeneBuilder.h
 * Author: brian
 *
 * Created on August 24, 2017, 10:02 AM
 */

#ifndef GENEBUILDER_H
#define GENEBUILDER_H

#include <vector>
#include "random.h"
#include <limits>
#include "miscfunctions.h"

namespace glch{

    
    /**
     * Randomly selects 50% of genes  from two vectors and merges them into a new vector.
     * @param aV1 The first set of genes
     * @param aV2 The second set of genes
     * @return A new set of genes.
     */
    std::vector<double> breed_vects(std::vector<double>& aV1, std::vector<double>& aV2);
    
    
    
    
    class GeneBuilder {
    public:
        GeneBuilder();
        GeneBuilder(const GeneBuilder& orig);
        virtual ~GeneBuilder();

        std::vector<std::string> vName;
        
        std::vector<double> vCoef;
        std::vector<double> vExp;

        std::vector<double> vLowerBound;
        std::vector<double> vUpperBound;
        
        double vMutationLower;
        double vMutationUpper;
        
        void insert_gene(std::string aName, double aCoef, double aExp, double aLowerBound, double aUpperBound){
            vName.push_back(aName);
            vCoef.push_back(aCoef);
            vExp.push_back(aExp);
            vLowerBound.push_back(aLowerBound);
            vUpperBound.push_back(aUpperBound);
            
        }
        
        void insert_gene(std::string aName, double aCoef, double aExp){
            
            double lMin = -1*std::numeric_limits<double>::max();
            double lMax = std::numeric_limits<double>::max();

            insert_gene(aName,aCoef,aExp,lMin,lMax);
        }

        void insert_gene_min(std::string aName, double aCoef, double aExp, double aLowerBound){
            double lMax = std::numeric_limits<double>::max();

            insert_gene(aName,aCoef,aExp,aLowerBound,lMax);
        }
        
        void insert_gene_max(std::string aName, double aCoef, double aExp, double aUpperBound){
            
            double lMin = -1*std::numeric_limits<double>::max();
            insert_gene(aName,aCoef,aExp,lMin,aUpperBound);
        }
        
        double compute_gene(double aXVal, size_t aIndex){
            //This generates a number from a normal distribution to alter a gene.
            //Most of the time this will produce a value which is near zero (with default L/U)
            //However, on the occasion it will cause some kind of mutation.
            double lRandVal = (rand()%2?-1:1)*glch::normal_dist(glch::randf(vMutationLower,vMutationUpper),0,1);
            //std::cout << aXVal << " : " << lRandVal << endl;
            
            
            
            return aXVal + lRandVal;
            //return pow(aXVal*vCoef.at(aIndex),vExp.at(aIndex));
        }

        double compute(std::vector<double> aXVals){
            
            double lRet = 0;
            for(size_t i = 0; i < aXVals.size(); i++){
                lRet += compute_gene(aXVals.at(i), i);
            }

            return lRet;
        }

        double check_bounds(std::vector<double> aXVals){
            bool lRet = true;

            for(size_t i = 0; i < aXVals.size(); i++){
                lRet &= (aXVals.at(i) > vLowerBound.at(i)) && (aXVals.at(i) < vUpperBound.at(i));
            }

            return (double)lRet;
        }

        GeneBuilder breed(GeneBuilder &aPartner){

            GeneBuilder lRet;
            
            lRet.vCoef = breed_vects(vCoef, aPartner.vCoef);
            lRet.vExp = breed_vects(vExp, aPartner.vExp);
            lRet.vLowerBound = breed_vects(vLowerBound, aPartner.vLowerBound);
            lRet.vUpperBound = breed_vects(vUpperBound, aPartner.vUpperBound);
            
            return lRet;
        }

        double mutate_all(){
            
            mutate_vector(vCoef,1);
            mutate_vector(vExp,1);
            mutate_vector(vLowerBound,1);
            mutate_vector(vUpperBound,1);
            
            return 0;
        }
        
        static void mutate_vector(std::vector<double>& aVect, double aRate){
            
            for(size_t i = 0; i < aVect.size(); i++){
                
                if(glch::randf() < aRate){
                    aVect.at(i) = glch::normal(aVect.at(i),.1);
                }
                
            }
            
        }
        
        static void mutate_vector(std::vector<double>& aVect, std::vector<double>& aSigma, double aRate){
            
            for(size_t i = 0; i < aVect.size(); i++){
                
                if(glch::randf() < aRate){
                    aVect.at(i) = glch::normal(aVect.at(i),aSigma.at(i));
                }
                
            }
            
        }
        
        
        void print(){
            
            std::cout << std::endl << "Coef: ";
            glch::print_vect(vCoef);
            std::cout << std::endl << "Exp: ";
            glch::print_vect(vExp);
            std::cout << std::endl << "Lower: ";
            glch::print_vect(vLowerBound);
            std::cout << std::endl << "Upper: ";
            glch::print_vect(vUpperBound);
            std::cout << std::endl;
        }

    private:

    };


    
}

#endif /* GENEBUILDER_H */

