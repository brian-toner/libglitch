/* 
 * File:   VectorFunctions.h
 * Author: brian
 *
 * Created on July 7, 2015, 8:34 AM
 */

#ifndef VECTORFUNCTIONS_H
#define	VECTORFUNCTIONS_H

#include <vector>
#include <iostream>
#include "RuntimeErrorReport.h"
#include "PointT.h"
#include "miscfunctions.h"

namespace glch{

#define GLCH_MIN_INCLUSIVE 0x01
#define GLCH_MAX_INCLUSIVE 0x02
#define GLCH_ENDPOINT_INCLUSIVE 0x03
#define GLCH_ENDPOINT_EXCLUSIVE 0x00
    
    /**
     * Prints a vector of type T through cout.
     * @param aSrc Source to print.
     * @param aDelim Separation string between printouts.
     */
    template <class T>
    void print_vect(std::vector<T> &aSrc, std::string aDelim = " ", std::ostream& aOutput = std::cout){
        for(size_t i = 0; i < aSrc.size(); i++){
             aOutput << aSrc.at(i) << aDelim;
        }
    }

    /**
     * Prints a vector of type T through cout.
     * @param aSrc Source to print.
     * @param aDelim Separation string between printouts.
     */
    template <class T, class U>
    void print_vect_type(std::vector<T> &aSrc, std::string aDelim = " ", std::ostream& aOutput = std::cout){
        for(size_t i = 0; i < aSrc.size(); i++){
             aOutput << (U)aSrc.at(i) << aDelim;
        }
    }    
    
    template <class T>
    void print_vect_fn(std::vector<T> &aSrc, std::string aDelim = " "){
        for(size_t i = 0; i < aSrc.size(); i++){
            aSrc.at(i).print(aDelim);
        }
    }
        
    /**
     * Copies a 1 dimensional array of size aSize into a vector.
     * @param aSrc The source array
     * @param aSize Size of the array to be copied.
     * @return A vector with the contents of aSrc.
     */
    template <class T>
    std::vector<T> to_vector(T *aSrc, size_t aSize){

        std::vector<T> lRet(aSize);

        for(size_t i = 0; i < aSize; i++){
            lRet.at(i) = aSrc[i];
        }

        return lRet;

    }
    
    /**
     * Copies an array of type T into a string vector.
     * @param aSrc Source to copy
     * @param aSize Size of array.
     * @return A vector containing the values of aSrc converted to a string.
     */
    template <class T>
    std::vector<std::string> to_string_vector(T *aSrc, size_t aSize){

        std::vector<std::string> lRet(aSize);

        for(size_t i = 0; i < aSize; i++){
            lRet.at(i) = to_string(aSrc[i]);
        }

        return lRet;

    }

    /**
     * Sums the values in a vector.
     * @param aVector Vector being summed across.
     * @return The sum of all the elements of the vector.
     */
    template<class T>
    double sum_vector(std::vector<T> &aData){
        double lRet = 0;
        for(size_t i = 0; i < aData.size(); i++){
            lRet += aData.at(i);
        }

        return lRet;
    }

    /**
     * Computes the weighted sum of a vector.  The sum is computed as:
     * \sum_{i=0}^{k}(aData_i*aWeights_i).  If the two vectors are not of the
     * same size then a runtime error will be thrown.
     * @param aData Data to sum.
     * @param aWeights Weight of the corresponding data points.
     * @return Sum of the weighted data.
     */
    template<class T, class U>
    double weighted_sum_vector(std::vector<T> aData, std::vector<U> aWeights){
        double lRet = 0;

        if(aData.size() != aWeights.size()){
            throw RuntimeErrorReport("Error in weighted_sum_vector. Vectors are not of the same size.");
        }
        
        for(size_t i = 0; i < aData.size(); i++){
            lRet += aData.at(i)*aWeights.at(i);
        }

        return lRet;
    }

    /**
     * Computes the weighted mean of the vector. The mean is computed as:
     * \sum_{i=0}^{k}(aData_i*aWeights_i)/\sum_{i=0}^{k}(aData_i).  
     * If the two vectors are not of the same size then a runtime error will be thrown.
     * @param aData Data to average.
     * @param aWeights Weight of the corresponding data points.
     * @return Weighted average.
     */
    template<class T, class U>
    double weighted_mean_vector(std::vector<T> aData, std::vector<U> aWeights){
        if(aData.size() != aWeights.size()){
            throw RuntimeErrorReport("Error in weighted_average_vector. Vectors are not of the same size.");
        }
                
        double lRet = 0;
        double lWeightSum = sum_vector(aWeights);

        for(size_t i = 0; i < aData.size(); i++){
            lRet += (aData.at(i)*aWeights.at(i))/lWeightSum;
        }
        
        return lRet;
    }

    /**
     * Computes the weighted standard deviation of a vector. The weighted standard deviation
     * is computed as: \sum_{i=0}^{k}((aData_i-WM)^2*aWeights_i)/(WS-1) where WM is the weighted mean
     * and WS is the weighted sum.
     * If the two vectors are not of the same size then a runtime error will be thrown.
     * @param aData
     * @param aWeights
     * @return 
     */
    template<class T, class U>
    double weighted_stdev_vector(std::vector<T> aData, std::vector<U> aWeights){
        if(aData.size() != aWeights.size()){
            throw RuntimeErrorReport("Error in weighted_stdev_vector. Vectors are not of the same size.");
        }
                
        double lRet = 0;
        double lWeightedSum = sum_vector(aWeights);
        double lWeightedMean = weighted_mean_vector(aData, aWeights);

        for(size_t i = 0; i < aData.size(); i++){
            lRet += ((aData.at(i)-lWeightedMean)*(aData.at(i)-lWeightedMean))*aWeights.at(i)/(lWeightedSum-1);
        }
        
        return sqrt(lRet);

    }    
    
    /**
     * Searches the vector for the value.  If the value is found then true is reported.
     * Otherwise, false is reported.
     * @param aData Data vector to search.
     * @param aValue Value to search for.
     * @return True if the value is in the vector, false otherwise.
     */
    template<class T>
    bool value_in_vector(std::vector<T> &aData, T aValue){
        bool lFound = false;
        for(size_t i = 0; i < aData.size() && !lFound; i++){
            if(aData.at(i) == aValue){
                lFound = true;
            }
        }
        
        return lFound;
        
    }

    /**
     * Pushes a value into a vector, only if the value is not already present.
     * This is done using the value_in_vector function.
     * @param aData Data vector we are pushing into.
     * @param aValue Value we are attempting to push into the vector.
     */
    template<class T>
    void push_check(std::vector<T> &aData, T aValue){
        if(!value_in_vector(aData,aValue)){
            aData.push_back(aValue);
        }
    }
    
    /**
     * Finds the maximum value in a vector of type T.
     * @param aData vector to scan for the max.
     * @return Maximum value from the vector.
     */    
    template <class T>
    T max(std::vector<T> &aData){
        T lValue = aData.at(0);
        for(size_t i = 0; i < aData.size(); i++){
            if(lValue < aData.at(i)){
                lValue = aData.at(i);
            }
        }

        return lValue;
    }

    /**
     * Finds the minimum value in a vector of type T.
     * @param aData vector to scan for the min.
     * @return Minimum value from the vector.
     */
    template <class T>
    T min(std::vector<T> &aData){
        T lValue = aData.at(0);
        
        for(size_t i = 1; i < aData.size(); i++){
            
            if(lValue > aData.at(i)){
                lValue = aData.at(i);
            }
        }

        return lValue;
    }
    
    /**
     * Maps a vector of data from one range into another range.
     * @param aSrc Source data.
     * @param aDst Destination data.
     * @param aMin Min value to map into.
     * @param aMax Max value to map into.
     */
    template <class T, class U>
    void map_vector(std::vector<T> &aSrc, std::vector<U> &aDst, double aMin, double aMax){
        double lMin = min(aSrc);
        double lMax = max(aSrc);
        double lSrcRange = lMax-lMin;
        double lDstRange = aMax-aMin;
        aDst.resize(aSrc.size());

        std::cout << lMin << " : " << lMax << std::endl;
        
        for(size_t i = 0; i < aSrc.size(); i++){
            
            double lVal = map_point(aSrc.at(i),lDstRange,aMin,lSrcRange,lMin,false);
            //std::cout << lMin << " : " << lMax << " : " << aSrc.at(i) << " : " << lVal << std::endl;
            aDst.at(i) = lVal;
        }
        
    }
    
    /**
     * Maps a vector of data from one range into another range.
     * @param aSrc Source data.
     * @param aDst Destination data.
     * @param aSrcMin Min value to map from.
     * @param aSrcMax Max value to map from.
     * @param aDstMin Min value to map into.
     * @param aDstMax Max value to map into.
     */
    template <class T, class U>
    void map_vector(std::vector<T> &aSrc, std::vector<U> &aDst, double aSrcMin, double aSrcMax, double aDstMin, double aDstMax){
        double lSrcRange = aSrcMax-aSrcMin;
        double lDstRange = aDstMax-aDstMin;
        aDst.resize(aSrc.size());
        
        for(size_t i = 0; i < aSrc.size(); i++){
            aDst.at(i) = map_point(aSrc.at(i),lDstRange,aDstMin,lSrcRange,aSrcMin,false);       
        }
        
    }
    
    template <class T>
    std::vector<PointT<T> > zip_pairs(std::vector<T> aXValues, std::vector<T> aYValues){
        std::vector<PointT<T> > lRet(aXValues.size());
        
        for(size_t i = 0; i < aXValues.size(); i++){
            lRet.at(i) = PointT<T>(aXValues.at(i),aYValues.at(i));
        }
        
        return lRet;
    }
    
    template <class T>
    std::vector< std::vector<PointT<T> > > zip_array(std::vector< std::vector<T> > aXValues, std::vector< std::vector<T> > aYValues){
        std::vector< std::vector<PointT<T> > > lRet(aXValues.size());
        
        for(size_t i = 0; i < aXValues.size(); i++){
            lRet.at(i) = zip_pairs(aXValues.at(i),aYValues.at(i));
        }
        
        return lRet;
    }
    
    /**
     * Finds the first index of the vector where the search value occurs.
     * @param aValues Vector of values being searched.
     * @param aSearchValue Value being searched for in vector.
     * @return The index where the search value was located.  (size_t)-1 if
     * the value was not located in the vector.
     */
    template <class T, class U>
    size_t index_of(std::vector<T> aValues, U aSearchValue){

        for(size_t i = 0; i < aValues.size(); i++){
            if(aValues.at(i) == (T)aSearchValue){
                return i;
            }
        }
        
        return (size_t)-1;
    }

    /**
     * Finds the first index of the vector where the search value occurs.
     * @param aValues Vector of values being searched.
     * @param aSearchValue Value being searched for in vector.
     * @return The index where the search value was located.  (size_t)-1 if
     * the value was not located in the vector.
     */
    template <class T, class U>
    bool search_index_list(std::vector<T> &aValues, std::vector<size_t> &aIndexList, U aSearchValue){

        for(size_t i = 0; i < aValues.size(); i++){
            if(aValues.at(i) == (T)aSearchValue){
                aIndexList.push_back(i);
            }
        }
        
        return (bool)aIndexList.size();
    }
    
    template <class T, class U>
    void convert_vector(std::vector<T> &aSrc, std::vector<U> &aDst){
        aDst.resize(aSrc.size());
        
        for(size_t i = 0; i < aSrc.size(); i++){
            aDst.at(i) = (U)aSrc.at(i);
        }
        
        
    }
    
    template <class T>
    std::vector<T> range(T aStart, T aEnd, T aStep = 1, int aEndpointFlags = GLCH_ENDPOINT_INCLUSIVE){
        std::vector<T> lRet;
        
        if( !(aEndpointFlags & GLCH_MIN_INCLUSIVE) ){
            aStart ++;
        }
        
        if( aEndpointFlags & GLCH_MAX_INCLUSIVE){
            aEnd ++;
        }        
        
        for(T i = aStart; i < aEnd; i += aStep){
            lRet.push_back(i);
        }
        
        return lRet;
    }
    
    
}
    
#endif	/* VECTORFUNCTIONS_H */

