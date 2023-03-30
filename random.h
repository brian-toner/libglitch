/* 
 * File:   random.h
 * Author: brian
 *
 * Created on April 18, 2015, 9:03 AM
 */

#ifndef GLCH_RANDOM_H
#define	GLCH_RANDOM_H

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
//    inline int randint(int aMin, int aMax){
//        return rand()%(aMax+1)+aMin;
//    }
    
    inline int randint(int aMin, int aMax){
        return randf()*( (aMax+1)-aMin) + aMin;
    }
    
    /**
     * Produces a random integer between min (inclusive) and max (exclusive), e.g. domain of [min,max).
     * @param aMin Minimum value.
     * @param aMax Maximum value.
     * @return Random integer between min and max inclusive.
     */
    inline int randint_ub(int aMin, int aMax){
        return randf()*(aMax-aMin) + aMin;
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
     * Produces a vector of random numbers of type T between min and max (exclusive end points).
     * @param aMin aMin Minimum value
     * @param aMax aMax Maximum value
     * @param aNumb Number of elements
     * @return Vector of random number of type T between min and max exclusive.
     */
    template <class T>
    inline std::vector<T> randt_vector(T aMin, T aMax, size_t aNumb){
        std::vector<T> lRet(aNumb);
        
        for(size_t i = 0; i < aNumb; i++){
            lRet.at(i) = randt(aMin,aMax);
        }
        
        return lRet;
    }
    
    /**
     * Generates a random float between min and max values (exclusive end points). e.g. domain of (min,max)
     * @param aMin Minimum value.
     * @param aMax Maximum value.
     * @return Random floating point between min and max exclusive.
     */
    float randf(float aMin, float aMax);

    /**
     * Randomly samples a vector of type T without replacement.  Further, aList 
     * will be updated to yield a new list with the samples from the return list
     * removed.
     * @param aList Input vector being sampled.
     * @param aNumb Number of samples.
     * @return A vector of size Numb, with a random selection from aList.
     */
    template <class T>
    std::vector<T> sample_slice(std::vector<T> &aList, size_t aNumb){
        std::vector<T> lList = aList;

        size_t lListLen = lList.size();
        if(lListLen < aNumb ){
            aNumb = lListLen;
        }
        std::vector<T> lReturn(aNumb);

        for(size_t i = 0; i < aNumb; i++){
            
            int tElement = randint(0,lListLen-1);

            lReturn.at(i) = lList.at(tElement);

            lList.erase(lList.begin()+tElement);
            lListLen--;

        }

        aList = lList;
        return lReturn;
    }
    
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
        int tElement = randint(0,lListLen-1);

        lReturn.at(i) = lList.at(tElement);

        if(!aReplace){
          lList.erase(lList.begin()+tElement);
          lListLen--;
        }
      }

      return lReturn;
    }

    /**
     * Randomly samples a vector of type T.
     * @param aList Input vector being sampled.
     * @return A value will be pulled from the list.
     */
    template <class T>
    T sample_one(const std::vector<T> &aList){

        int lElement = randint(0,aList.size()-1);
        return aList.at(lElement);
    }    
    
    /**
     * Generates a random string.
     * @param aLen The length of the random string.
     * @return The random string.
     */
    string random_string(int aLen);
    
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
        aOut.resize(aMax+1,aMax+1);
        
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

            if(aOut.at(lPoint) != aMapMax){
                aOut.at(lPoint) += 1;
            }

            
        }
        
        map_vector(aOut.data,aOut.data,aMapMin,aMapMax);
        
    }    
    
    
    template <class T>
    void str_to_mat(AString aInput, MatT<T> &aDst){
        AStringList lList = aInput.split("|");
        int lW = lList.at(0).csv(0,0);
        int lH = lList.at(0).csv(0,1);
        
        aDst.resize(lH, lW);
        int lSize = aDst.size();
        int k = 0;
        
        for(int r = 0; r < lH; r++){
            for(int c = 0; c < lW; c++, k++){
                aDst.at(Point(c,r)) = lList.at(1).csv(0,k);
            }
        }
        
//        for(int r = 0; r < lSize; r++){
//            //std::cout << i << std::endl;
//            aDst.at(r) = lList.at(1).csv(0,r);
//        }
        
    }
    
    /**
     * Creates a vector of points containing Brownian motion.  Stores this vector in argOut 
     * @param aMax T-final
     * @param aMin T-start
     * @param aTimeSteps Number of time steps the divide the interval
     * @param aOut Vector where we are storing the generated Brownian motion.
     */
    template <class T>
    void brownian2(size_t aWidth, size_t aHeight, double aStepXMin, double aStepXMax, double aStepYMin, double aStepYMax, double aInc, double aMapMin, double aMapMax, size_t aTimeSteps, MatT<T> &aOut, bool aScale){
        std::vector<double> lPointsX;
        std::vector<double> lPointsY;
        aOut.resize(aHeight,aWidth);
        
        lPointsX = glch::randt_vector<double>(aStepXMin,aStepXMax,aTimeSteps-1);
        lPointsY = glch::randt_vector<double>(aStepYMin,aStepYMax,aTimeSteps-1);
        
        double lStartX = glch::randint(0,aWidth);
        double lStartY = glch::randint(0,aHeight);
        
        //std::cout << lStartX << " : " << lStartY << std::endl;
        
        lPointsX.insert(lPointsX.begin(),lStartX);
        lPointsY.insert(lPointsY.begin(),lStartY);
        
        
        cumulative_sum(lPointsX,lPointsX);
        cumulative_sum(lPointsY,lPointsY);


        for(size_t i = 0; i < lPointsX.size(); i++){

            long lTrunckX = modf(lPointsX.at(i),aWidth);
            long lTrunckY = modf(lPointsY.at(i),aHeight);
            
            if(lTrunckX < 0){
                lTrunckX += aWidth;
            }
            
            if(lTrunckY < 0){
                lTrunckY += aHeight;
            }
            
            //std::cout << AString("(%1,%2)").arg(lTrunckX).arg(lTrunckY) << " | " << AString("(%1,%2)").arg(lPointsX.at(i)).arg(lPointsY.at(i)) << std::endl;
//            if(lTrunckX > aWidth){
//                lTrunckX = (lTrunckX)%aWidth;
//            }
//            
//            if(lTrunckY > aHeight){
//                lTrunckY = (lTrunckY)%aHeight;
//            }
//            
//            while(lTrunckX < 0){
//                lTrunckX += aWidth;
//            }
//            
//            while(lTrunckY < 0){
//                lTrunckY += aHeight;
//            }
            //std::cout << lPointsX.at(i) << " : " << lPointsY.at(i) << std::endl;
            
            //Point lPoint = Point(lMappedX,lMappedY);
            Point lPoint = Point(lTrunckX,lTrunckY);
            double lIncVal = aOut.at(lPoint)+aInc;
            
            if(lIncVal >= aMapMax){
                aOut.at(lPoint) = aMapMax;
            } else {
                aOut.at(lPoint) = lIncVal;
            }

            
        }
        
        if(aScale){
            map_vector(aOut.data,aOut.data,aMapMin,aMapMax);
        }
    }    
    
/*
    template <class T>
    void random_noise(MatT<T> &aOut, double aMin, double aMax){
        MatT<double> lMat(aOut.rows,aOut.cols);
        
        for(size_t i = 0; i < lMat.size(); i++){
            lMat.at(i) = randf();
        }
        
        
        map_vector(lMat.data,aOut.data,0.0,1.0,aMin,aMax);
        
    }
    */
    
    
    /**
     * Alters a value by some random value in the normal distribution.
     * @param aX The value to alter
     * @param aMutationLower The lower mutation range (correlated to the standard deviation)
     * @param aMutationUpper The upper mutation range (correlated to the standard deviation)
     * @param aMin The max value the new value can take
     * @param aMax The min value the new value can take
     * @return Returns the modified value
     */
    double mutate_norm(double aX, double aMutationLower, double aMutationUpper, double aMin, double aMax);
  
    /**
     * Alters a value by some random value in the normal distribution.
     * @param aX The value to alter
     * @param aMutationLower The lower mutation range (correlated to the standard deviation)
     * Default is -10, which is 20 standard deviations away from the mean.
     * @param aMutationUpper The upper mutation range (correlated to the standard deviation)
     * Default is 10, which is 20 standard deviations away from the mean.
     * @return Returns the modified value
     */
    double mutate_norm(double aX, double aMutationLower = -20, double aMutationUpper = 20);
    
    
    double mutate_norm(double aX, double aMutationLower, double aMutationUpper, double aMean, double aStdev, bool aHasMin, bool aHasMax, double aMin, double aMax);
       
}

#endif	/* GLCH_RANDOM_H */

