/* 
 * File:   PointT.h
 * Author: brian
 *
 * Created on July 4, 2015, 10:16 PM
 */

#ifndef POINTT_H
#define	POINTT_H

#include <vector>
#include <iostream>
#include <math.h>

namespace glch{

    template <class T>
    class PointT{
        public:
        T x;    //x coordinate
        T y;    //y coordinate

        /**
         * Default constructor.  Sets x and y to zero.
         */
        PointT(){
            x = 0;
            y = 0;
        }

        /**
         * Assigns x and y to aX and aY respectively.
         * @param aX Value to set the x-coordinate to.
         * @param aY Value to set the y-coordinate to.
         */
        PointT(T aX, T aY){
            x = aX;
            y = aY;
        }

        PointT(const PointT<T> &orig) : x(orig.x), y(orig.y){};

        /**
         * Compares the distance between this point and another.
         * @param aPt comparison point.
         * @return distance between the two points.
         */
        double distance(PointT<T> aPt);
        double perpindicular_distance(PointT<T> aEndPt, PointT<T> aPt);
        
        bool operator==(PointT<T> aPt);
        bool operator!=(PointT<T> aPt);

        /**
         * Calculates the slope between this and another point.
         * @param aPt Second point.
         * @return Slope of the two points.
         */
        double slope(PointT<T> aPt);

        /**
         * Computes if the slope between this and another point is undefined (e.g. same x values)
         * @param aPt Second point.
         * @return True if the slope is undefined, false otherwise.
         */
        bool slope_undef(PointT<T> aPt);
        
        /**
         * Computes the y intercept between this an another point.
         * @param aPt Second point.
         * @return The y intercept of the two points.
         */
        double y_intercept(PointT<T> aPt);
        
        template <class U>
        operator PointT<U>(){
            return PointT<U>(U(x),U(y));
        }
        
        void print(std::string aDelim = "\n"){
            std::cout << "[" << x << "," << y << "]" << aDelim;
        }
        
        double dot(PointT<T> aPt){
            return x*aPt.x+y*aPt.y;
        }
        
        double cross(PointT<T> aPt){
            return x*aPt.y-y*aPt.x;
        }
        
    };


    template <class T>
    double PointT<T>::distance(PointT<T> aPt){
        return sqrt( (x - aPt.x)*(x - aPt.x) + (y - aPt.y)*(y - aPt.y) );
    }
    
    template <class T>
    double PointT<T>::perpindicular_distance(PointT<T> aEndPt, PointT<T> aPt){
        return fabs((aEndPt.y-y)*aPt.x - (aEndPt.x-x)*aPt.y + aEndPt.x*y - aEndPt.y*x) / distance(aEndPt);
    }    

    template <class T>
    double perpendicular_distance(PointT<T> aPt1, PointT<T> aPt2, PointT<T> aPt){
        return fabs((aPt2.y-aPt1.y)*aPt.x - (aPt2.x-aPt1.x)*aPt.y + aPt2.x*aPt1.y - aPt2.y*aPt1.x) / sqrt((aPt2.y-aPt1.y)*(aPt2.y-aPt1.y) + (aPt2.x-aPt1.x)*(aPt2.x-aPt1.x) );
    }    
    
    template <class T>
    double parallel_distance(PointT<T> aPt1, PointT<T> aPt2, PointT<T> aPt){
        double lPerpDistance = perpendicular_distance(aPt1,aPt2,aPt);
        double lDistance = aPt1.distance(aPt2);
        return sqrt( lDistance*lDistance - lPerpDistance*lPerpDistance );
    }      
    
    template <class T>
    bool PointT<T>::operator==(PointT<T> aPt){
        return ((x == aPt.x) && (y == aPt.y));
    }
  
    template <class T>
    bool PointT<T>::operator!=(PointT<T> aPt){
        return ((x != aPt.x) || (y != aPt.y));
    }
    
    /**
     * Calculates the slope between this and another point.
     * @param aPt Second point.
     * @return Slope of the two points.
     */
    template <class T>
    double PointT<T>::slope(PointT<T> aPt){
        double lSlope = 0;

        if((x - aPt.x) != 0){
            lSlope = (double)(aPt.y - y)/(double)(aPt.x - x);
        }

        return lSlope;
    }

    /**
     * Computes if the slope between this and another point is undefined (e.g. same x values)
     * @param aPt Second point.
     * @return True if the slope is undefined, false otherwise.
     */
    template <class T>
    bool PointT<T>::slope_undef(PointT<T> aPt){
        bool lReturn = false;

        if((x - aPt.x) == 0)
            lReturn = true;

        return lReturn;
    }

    /**
     * Computes the y intercept between this an another point.
     * @param aPt Second point.
     * @return The y intercept of the two points.
     */
    template <class T>
    double PointT<T>::y_intercept(PointT<T> aPt){
        double lRet;
        double lSlope;
        lSlope = slope(aPt);

        lRet = y - x*lSlope;
        return lRet;
    }    
    
    typedef PointT<double> PointF;
    typedef PointT<int> Point;
    typedef std::vector<PointF> MatPoints;           //Relabeling a vector of real x,y coordinates
    typedef std::vector<MatPoints> MatPointsList;    //List of MatPoints
    
    /**
     * Converts a set of points of one type into a list of PointF
     * @param aSrc Source we are converting
     * @return A list of points converted to matpoints.
     */
    template <class T>
    MatPoints to_matpoints(std::vector<PointT<T> > aSrc){
        MatPoints lRet(aSrc.size());
        
        for(size_t i = 0; i < aSrc.size(); i++){
            lRet.at(i) = aSrc.at(i);
        }
        
        return lRet;
    }
    
    template <class T>
    MatPointsList to_matpointslist(std::vector< std::vector< PointT<T> > > aSrc){
        MatPointsList lRet(aSrc.size());
        
        for(size_t i = 0; i < aSrc.size(); i++){
            lRet.at(i) = to_matpoints(aSrc.at(i));
        }        
        
        return lRet;
    }
    
    
}

#endif	/* POINTT_H */

