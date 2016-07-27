/* 
 * File:   random.h
 * Author: brian
 *
 * Created on April 18, 2015, 9:03 AM
 */

#ifndef RANDOM_H
#define	RANDOM_H

#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <math.h>

#include "PointT.h"
#include "MatT.h"
#include "VectorFunctions.h"
#include "miscfunctions.h"

namespace glch{
    
    /**
     * Produces a random floating point number between 0 and 1.
     * @return A random number between 0 and 1.
     */
    inline float randf(){
        return (float)rand()/(float)RAND_MAX;
    }

    /**
     * Produces a random integer between min and max (inclusive end points), e.g. domain of [min,max].
     * @param aMin Minimum value.
     * @param aMax Maximum value.
     * @return Random integer between min and max inclusive.
     */
    inline int randint(int aMin, int aMax){
        return randf()*( (aMax+1)-aMin) + aMin;
    }

    /**
     * Produces a random number of type T between min and max (exclusive end points), e.g. domain of (min,max).
     * @param aMin Minimum value.
     * @param aMax Maximum value.
     * @return Random number of type T between min and max exclusive.
     */
    template <class T>
    inline T randt(T aMin, T aMax){
        return randf()*( (aMax)-aMin) + aMin;
    }    
    
    /**
     * Generates a random float between min and max values (exclusive end points). e.g. domain of (min,max)
     * @param aMin Minimum value.
     * @param aMax Maximum value.
     * @return Random floating point between min and max exclusive.
     */
    float randf(float aMin, float aMax);

    /**
     * Randomly samples a vector of type T.  If the number of requested samples exceeds the input list size
     * and sample with replacement is disabled, then a vector with the size of of the
     * input will be produced instead.
     * @param aList Input vector being sampled.
     * @param aNumb Number of samples.
     * @param aReplace Sample with replacement. (True to sample and replace, false otherwise)
     * @return A vector of size Numb, with a random selection from aList.
     */
    template <class T>
    std::vector<T> sample(const std::vector<T> &aList, size_t aNumb, bool aReplace = false){
      std::vector<T> lList = aList;

      size_t lListLen = lList.size();
      if(!aReplace && lListLen < aNumb ){
        aNumb = lListLen;
      }
      std::vector<T> lReturn(aNumb);
      
      for(size_t i = 0; i < aNumb; i++){
        int tElement = randint(0,lListLen);

        lReturn[i] = lList[tElement];

        if(!aReplace){
          lList.erase(lList.begin()+tElement);
          lListLen--;
        }
      }

      return lReturn;
    }

    /**
     * Seeds the RNG with the current time.  This can not be performed more 
     * than once every second.
     * @return The random seed used.
     */
    size_t seed_rand(); 
    
    /**
     * Uses the box-muller transformation to produce a 1d normal random distribution.
     * @param aMu Mean.
     * @param aSigma Standard deviation.
     * @return 1d point in the random distribution.
     */
    double normal(double aMu = 0, double aSigma = 1);

    /**
     * Uses the box-mull transformation to produce 2d normal random distribution.
     * @param aMu Mean.
     * @param aSigma Standard deviation.
     * @return 2d point in the random distribution.
     */
    PointF normal_2d(double aMu = 0, double aSigma = 1);
    
    /**
     * Generates a vector of size aSize, with a normal distribution.
     * @param aSize Size of the vector.
     * @param aMu Mean.
     * @param aSigma Standard deviation.
     * @return A normal distribution of size aSize.
     */
    std::vector<double> normal_vector(size_t aSize, double aMu, double aSigma);
    
    /**
     * Creates a vector of points containing Brownian motion.  Stores this vector in argOut 
     * @param aMin T-start
     * @param aMax T-final
     * @param aTimeSteps Number of time steps the divide the interval
     * @param aOut Vector where we are storing the generated Brownian motion.
     */
    void brownian(double argMin, double argMax, size_t argTimeSteps, std::vector<PointF> & argOut);

    /**
     * Creates a vector of points containing Brownian motion.  Stores this vector in argOut 
     * @param aMin T-start
     * @param aMax T-final
     * @param aTimeSteps Number of time steps the divide the interval
     * @param aOut Vector where we are storing the generated Brownian motion.
     */
    void brownian(double aMin, double aMax, size_t aTimeSteps, std::vector<double> & aOut)  ;  
    
    /**
     * Creates a vector of points containing Brownian motion.  Stores this vector in argOut 
     * @param aMax T-final
     * @param aMin T-start
     * @param aTimeSteps Number of time steps the divide the interval
     * @param aOut Vector where we are storing the generated Brownian motion.
     */
    template <class T>
    void brownian(double aMax, double aBoarder, double aMapMin, double aMapMax, size_t aTimeSteps, MatT<T> &aOut){
        std::vector<double> lPointsX;
        std::vector<double> lPointsY;
        aOut.resize(aMax,aMax);
        
        brownian(0,1,aTimeSteps,lPointsX);
        brownian(0,1,aTimeSteps,lPointsY);
        
        double lMaxX = max(lPointsX);
        double lMinX = min(lPointsX);
        double lMaxY = max(lPointsY);
        double lMinY = min(lPointsY);        
        double lRangeX = lMaxX-lMinX;
        double lRangeY = lMaxY-lMinY;
        
        double lAdjMin = -aBoarder;
        double lAdjMax = aMax+aBoarder;
        double lAdjRange = lAdjMax-lAdjMin;
        
        for(size_t i = 0; i < lPointsX.size(); i++){
            double lMappedX = map_point(lPointsX.at(i), lAdjRange, lAdjMin, lRangeX, lMinX, false);
            double lMappedY = map_point(lPointsY.at(i), lAdjRange, lAdjMin, lRangeY, lMinY, false);
            Point lPoint = Point(lMappedX,lMappedY);

            if(lMappedX >= 0 && lMappedX < aMax && lMappedY >= 0 && lMappedY < aMax){
                aOut.at(lPoint) += 1;
            }
            
        }
        
        map_vector(aOut.data,aOut.data,aMapMin,aMapMax);
        
    }    
    
    template <class T>
    void random_noise(MatT<T> &aOut, double aMin, double aMax){
        MatT<double> lMat(aOut.rows,aOut.cols);
        
        for(size_t i = 0; i < lMat.size(); i++){
            lMat.at(i) = randf();
        }
        
        
        map_vector(lMat.data,aOut.data,0.0,1.0,aMin,aMax);
        
    }
    
}

#endif	/* RANDOM_H */

