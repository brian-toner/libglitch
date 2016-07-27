/* 
 * File:   PolygonT.h
 * Author: brian
 *
 * Created on December 31, 2015, 8:59 AM
 */

#ifndef POLYGONT_H
#define	POLYGONT_H


#include <vector>
#include <math.h>
#include <limits>

#include "Boundary.h"
#include "PointT.h"
#include "RectT.h"
#include "Moments.h"
#include "ShapeProperties.h"
#include "miscfunctions.h"
#include "PairT.h"
#include "PolygonFunctions.h"
#include "MatT.h"

namespace glch{
    
    template <class T>
    class PolyT {
          
    public:
        PolyT(){};
        PolyT(std::vector< PointT<T> > aPolyPoints){
            set_polygon(aPolyPoints);
        };

        template <class U>
        PolyT(MatT<U> &aImage){
            set_polygon(aImage);
        }
        
        PolyT(const PolyT& orig) : vData(orig.vData),
                                    vBoundingRect(orig.vBoundingRect){};
        virtual ~PolyT(){};
        
        

        template <class U>
        void set_polygon(MatT<U> &aImage, bool aTopBoundary = false){
            BoundaryList lBoundaries;
            BoundaryList lTopBoundaries;
    
            compute_all_boundaries(aImage,lBoundaries,lTopBoundaries);
            if(lBoundaries.size() == 0){
                std::cout << "No boundaries to detect." <<std::endl;
                return;
            }
            size_t lMaxSize = glch::area(lBoundaries.front());
            size_t lIndex = 0;
            
            for(size_t i = 1; i < lBoundaries.size(); i++){
                size_t lTempSize = glch::area(lBoundaries.at(i));
                
                if(lTempSize > lMaxSize){
                    lMaxSize = lTempSize;
                    lIndex = i;
                }
            }
            
            if(aTopBoundary){
                set_polygon(lTopBoundaries.at(lIndex));
            } else {
                set_polygon(lBoundaries.at(lIndex));
            }
            
        }
        
        void set_polygon(std::vector< PointT<T> > aPolyPoints){
            vData = aPolyPoints;
            init_polygon();
        }

        void init_polygon(){
            vBoundingRect = bounding_rect(vData);
            vMinimalBoundingRect = glch::minimal_bounding_rect(vData);
            compute_moments();
        }
        
        void push_back(PointT<T> aPoint){
            vData.push_back(aPoint);
            vBoundingRect = set_bounding_rect();
            compute_moments();
        }
        
        size_t size(){
            return vData.size();
        }
        
        PointT<T> &front(){
            return vData.front();
        }
        
        PointT<T> &back(){
            return vData.back();
        }    
        
        PointT<T> &at(size_t aElement){
            return vData.at(aElement);
        }
        
        void print(std::string aDelim = " "){
            for(size_t i = 0; i < size(); i++){
                at(i).print(aDelim);
            }
        }
        
        size_t lowest_point(){
            return glch::lowest_point(vData);
        }
        
        size_t furthest_from(PointT<T> aPt){
            return glch::furthest_from(vData,aPt);            
        }
        
        void convex(){
            glch::convex_hull(vData);
            init_polygon();
        }
        
        void charge_starting_element(size_t aNewStart);
        void subdivide_vertex(size_t aVertex, bool aForward = false);
        void subdivide_polygon();
        RectT<T> set_bounding_rect();
        RectT<T> get_bounding_rect();
        bool contains(PointT<T> aPoint);
        
        /**
         * Simplifies the polygon using the Douglas-Peucker algorithm.
         * @param aEpsilon Minimum distance between nodes of the simplified polygon.
         */
        void simplify(double aDelta);
        
        double perimeter();
        double area();
        PointT<T> centroid();
        double moment(size_t p, size_t q);
        double central_moment(size_t p, size_t q);
        double normalized_central_moment(size_t p, size_t q);
        
        std::vector<size_t> diameter_points();

        std::vector< PointT<T> > vData;
        RectT<T> vBoundingRect;
        Moments vMoments;
        std::vector< PointF > vMinimalBoundingRect;
        
        void compute_moments(){
            vMoments.set_moments(vData, 5); 
        }
        
    private:

    };

    /**
     * Subdivides the vertex indexed by aVertex.  This will split the polygon 
     * between aPolyVertex and aPolyvertex-1 (looping back to the lase element if necessary).  
     * @param aPolygon Polygon to subdivide.
     * @param aPolyVertex Index of the vertex to subdivide.
     */
    template<class T>
    void PolyT<T>::subdivide_vertex(size_t aVertex, bool aForward){
        glch::subdivide_vertex(vData,aVertex,aForward);
        init_polygon();
    }
    
    
    /**
     * Shifts the polygon's vertices so that aNewStart is element 0. This will
     * not disrupt the structure of the polygon.  If the first and last elements
     * in the polygon are the same then the last element will be deleted before
     * the shift and the new first element will be added to the end of the polygon.
     * @param aNewStart Polygon index which will become zero.
     */
    template<class T>
    void PolyT<T>::charge_starting_element(size_t aNewStart){
        glch::change_starting_element(vData, aNewStart);   
        init_polygon();
        
    }    
    
    /**
     * Subdivides all the vertices of the polygon.
     */
    template<class T>
    void PolyT<T>::subdivide_polygon(){
        std::vector< PointT<T> > lData = vData;
        glch::subdivide_polygon(lData);
        set_polygon(lData);
   
    }
    
    template<class T>
    RectT<T> PolyT<T>::set_bounding_rect(){
        return bounding_rect(vData);
    }
    
    template <class T>
    RectT<T> PolyT<T>::get_bounding_rect(){
        return vBoundingRect;
    }
    
    /**
     * Computes if a point falls along or inside of the boundary of a non self
     * intersecting polygon.
     * @param aPoint The point we are checking for.
     * @return True if the point is within the polygon.  False otherwise.
     */    
    template <class T>
    bool PolyT<T>::contains(PointT<T> aPoint){
        return glch::contains(vData,aPoint);
    }
    
    /**
     * Simplifies the polygon using the Douglas-Peucker algorithm.
     * @param aEpsilon Minimum distance between nodes of the simplified polygon.
     */
    template <class T>
    void PolyT<T>::simplify(double aEpsilon){
        std::vector< PointT<T> > lData = vData;
        glch::simplify(lData,aEpsilon);
        set_polygon(lData);
    }    
    
    
    template <class T>
    PointT<T> PolyT<T>::centroid(){
        return vMoments.vCentroid; 
    }
    
    template <class T>
    double PolyT<T>::moment(size_t p, size_t q){
        return vMoments.vM.at(Point(p,q));
    }
    
    template <class T>
    double PolyT<T>::central_moment(size_t p, size_t q){
        return vMoments.vMu.at(Point(p,q));
    }    
    
    template <class T>
    double PolyT<T>::normalized_central_moment(size_t p, size_t q){
        return vMoments.vNu.at(Point(p,q));
    }    
    
    template <class T>
    std::vector<size_t> PolyT<T>::diameter_points(){
        std::vector<size_t> lRet = glch::diameter_points(vData);
        
        return lRet;
        
    }    
    
    
    
    
#if false
    /**
 * Finds a point which is opposite of aPoint which passes through the centroid of aPolygon.
 * @param aPolygon
 * @param aPoint
 * @param aCentroid
 * @param aIndex Index of the opposite point.
 * @return 
 */
cv::Point2d find_opposite_point(std::vector<cv::Point2d> &aPolygon, cv::Point2d aPoint, size_t &aIndex){
    
    double      lError = DBL_MAX;
    cv::Point2d lReturn;
    cv::Point2d lCentroid = calc_centroid(aPolygon);

    lReturn = aPolygon.at(0);
    
    
    for(std::vector<cv::Point2d>::iterator it = aPolygon.begin(); it != aPolygon.end(); it++){
        
        if((*it).x == aPoint.x && (*it).y == aPoint.y){
            continue;
        }
        double tempError;
        
        if((*it).x != aPoint.x){
            tempError = ((*it).y-aPoint.y)/((*it).x-aPoint.x)*(lCentroid.x-(*it).x)-lCentroid.y+(*it).y;
        } else {
            tempError = (-1)*(lCentroid.x+aPoint.x);
        }
        tempError = fabs(tempError);            

        if(tempError < lError ){
            lError = tempError;
            lReturn = (*it);
            aIndex = it - aPolygon.begin();
        }
        

    }

    return lReturn;
}

void get_max_min_diameter(std::vector<cv::Point2d> &aPolygon, double &aMaxDist, double &aMinDist){
    
    double lMax;
    double lMin;
    size_t lIndex;

    cv::Point2d lInitPt = find_opposite_point(aPolygon, aPolygon.at(0), lIndex);
    //Point2d locInitPt = find_opposite_position(argPoly, argPoly->at(0), argCentroid);
    double lInitDist = calc_dist(aPolygon.at(0), lInitPt);
    
    
    lMax = lInitDist;
    lMin = lInitDist;
    
    //std::cout << "Centroid: " << lCentroid.x << " : " << lCentroid.y << std::endl;
    //std::cout << "Size: " << aPolygon.size() << std::endl;
    //std::cout << lMax << " : " << lMin << " : " << lIndex << std::endl;;
    
    for(std::vector<cv::Point2d>::iterator it = aPolygon.begin(); it != aPolygon.end(); it++){
        
        lIndex = it-aPolygon.begin();
        //calc_dist
        cv::Point2d tempPoint = find_opposite_point(aPolygon, (*it), lIndex);
        //Point2d tempPoint = find_opposite_position(argPoly, (*it), argCentroid, it-argPoly->begin());
        //cv::Point2d tempPoint2;
        //tempPoint2.x = tempPoint.x;
        //tempPoint2.y = tempPoint.y;
        
        double tempDist = calc_dist((*it), tempPoint);
        
        //std::cout << "Point: " << (*it).x << " : " << (*it).y << " | Opposite: " << tempPoint.x << " : " << tempPoint.y << " | Dist: " << tempDist << std::endl;
        
        //cout << tempDist << endl;
        //cout << it - argPoly->begin() << endl;
        
        if(tempDist < lMin){
            lMin = tempDist;
        }
        
        if(tempDist > lMax){
            lMax = tempDist;
        }
        
    }
    
    aMaxDist = lMax;
    aMinDist = lMin;
    
}

cv::Point2d calc_centroid(std::vector<cv::Point2d> &aPolygon){

    double lSumX = 0;
    double lSumY = 0;
    double lSum = 0;
    cv::Point2d lCentroid;

    for(std::vector<cv::Point2d>::iterator it = aPolygon.begin(); it != aPolygon.end(); it++){
        double tempSum = 0;
        double tempX = (*it).x+1;
        double tempY = (*it).y+1;
        
        tempSum += 1;
        
        lSumX += tempSum*tempX;
        lSumY += tempSum*tempY;

        lSum += tempSum;
        
    }

    lCentroid.x = lSumX/lSum -1;
    lCentroid.y = lSumY/lSum -1;
    
    return lCentroid;    
}

#endif

}   

#endif	/* POLYGONT_H */

