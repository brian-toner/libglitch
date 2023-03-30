/* 
 * File:   PolygonFunctions.h
 * Author: brian
 *
 * Created on January 7, 2016, 1:11 PM
 */

#ifndef GLCH_POLYGONFUNCTIONS_H
#define	GLCH_POLYGONFUNCTIONS_H

#include <cfloat>
#include <math.h>
#include <limits>
#include <vector>
#include <algorithm>
//#include <values.h>

#include "PointT.h"
#include "RectT.h"
#include "PairT.h"
#include "VectorFunctions.h"
#include "Moments.h"


namespace glch{
    
    /**
     * Flips a polygon horizontally inside of an area with a width of aWidth.
     * @param aSrc Polygon to flip.
     * @param aDst Output flipped polygon.
     * @param aWidth Width of area the polygon is inside of.
     */
    template <class T>
    void flip_polygon_horizontal(std::vector< PointT<T> > &aSrc, std::vector< PointT<T> > &aDst, int aWidth){

        aDst = aSrc;

        for(size_t i = 0; i < aDst.size(); i++){
            aDst.at(i).x = aWidth - aDst.at(i).x;
        }

        return;

    }

    template <class T>
    size_t lowest_point(std::vector< PointT<T> > &aSrc){
        PointT<T> lPt = aSrc.at(0);
        size_t lIndex = 0;

        for(size_t i = 1; i < aSrc.size(); i++){
            if(lPt.y == aSrc.at(i).y){
                if(lPt.x > aSrc.at(i).x){
                    lPt = aSrc.at(i);
                    lIndex = i;
                }
            } else if (lPt.y > aSrc.at(i).y){
                lPt = aSrc.at(i);
                lIndex = i;
            }

        }

        return lIndex;
    }

    template <class T>
    size_t furthest_from(std::vector< PointT<T> > &aSrc, PointT<T> aPt){
        double lDistance = aPt.distance(aSrc.front());
        size_t lIndex = 0;

        for(size_t i = 1; i < aSrc.size(); i++){
            if(aPt.distance(aSrc.at(i)) > lDistance){
                lIndex = i;
                lDistance = aPt.distance(aSrc.at(i));
            }

        }            

        return lIndex;

    }

    template <class T>
    void angle_sort(std::vector< PointT<T> > &aSrc){
        PointT<T> lPt1 = aSrc.at(lowest_point(aSrc));
        std::vector<PairT<double> > lDistances(aSrc.size());

        for(size_t i = 0; i < aSrc.size(); i++){
            lDistances.at(i).first = i;
            PointT<T> lPt2 = aSrc.at(i);
            double lAngle;

            if(lPt1.slope_undef(lPt2)){
                if(lPt1 == lPt2){
                    lAngle = -M_PI/2.0;
                } else {
                    lAngle = M_PI/2.0;
                }

            } else {
                lAngle = acos((lPt2.x-lPt1.x)/lPt1.distance(lPt2) );
            }
            lDistances.at(i).second = lAngle;
        }


        std::sort(lDistances.begin(), lDistances.end());

        std::vector<PointT<T> > lSorted(aSrc.size());
        for(size_t i = 0; i < aSrc.size(); i++){
            lSorted.at(i) = aSrc.at(lDistances.at(i).first);
        }
        aSrc = lSorted;

    }
    
    /**
     * Subdivides the vertex indexed by aVertex.  This will split the polygon 
     * between aPolyVertex and aPolyvertex-1 (looping back to the lase element if necessary).  
     * @param aPolygon Polygon to subdivide.
     * @param aPolyVertex Index of the vertex to subdivide.
     */
    template<class T>
    void subdivide_vertex(std::vector< PointT<T> > &aSrc, size_t aVertex, bool aForward){

        size_t lVertex = aVertex-1;
        size_t lOffset = 0;
        
        if(aForward){
            lVertex = aVertex+1;
            lOffset = 1;
        }

        if(lVertex < 0){
            lVertex = aSrc.size()-1;
        }

        if(lVertex >= aSrc.size()){
            lVertex = 0;
        }
        
        double lX1 =  aSrc.at(aVertex).x;
        double lX2 =  aSrc.at(lVertex).x;
        double lY1 =  aSrc.at(aVertex).y;
        double lY2 =  aSrc.at(lVertex).y;

        PointT<T> locInsert;
        locInsert.x = lX2 + (lX1-lX2)/2;
        locInsert.y = lY2 + (lY1-lY2)/2;

        aSrc.insert(aSrc.begin() + aVertex+lOffset,locInsert);

    }
    
    /**
     * Shifts the polygon's vertices so that aNewStart is element 0. This will
     * not disrupt the structure of the polygon.  If the first and last elements
     * in the polygon are the same then the last element will be deleted before
     * the shift and the new first element will be added to the end of the polygon.
     * @param aNewStart Polygon index which will become zero.
     */
    template<class T>
    void change_starting_element(std::vector< PointT<T> > &aSrc, size_t aNewStart){
        bool lSameStartEnd = false;
        if(aSrc.front() == aSrc.back()){
            aSrc.erase(aSrc.end()-1);
            lSameStartEnd = true;
        }
        
        for(size_t i = 0; i < aNewStart; i++){
            aSrc.push_back(aSrc.at(i));
        }
        
        aSrc.erase(aSrc.begin(),aSrc.begin()+aNewStart );
        
        if( (aSrc.front() != aSrc.back()) && lSameStartEnd){
            aSrc.push_back(aSrc.front());
        }
        
    }    
    
    /**
     * Subdivides all the vertices of the polygon through linear approximation.  
     * If the first and last elements of the polygon are not the same then a new 
     * element which is linearly between the first and last element 
     * will be added to the end of the vector.
     */
    template<class T>
    void subdivide_polygon(std::vector< PointT<T> > &aSrc){
        
        for(size_t i = 1; i < aSrc.size(); i+=2){
            subdivide_vertex(aSrc,i,false);
        }
        
        if(aSrc.front() != aSrc.back() ){
            subdivide_vertex(aSrc,aSrc.size()-1,true);
        }
        
        
        
    }
    
    /**
     * Computes the perimeter of the polygon using Euclidean distance formula.
     * @param aPoly The polygon we are finding the perimeter of.
     * @return The perimeter of the polygon.
     */
    template <class T>
    double perimeter(std::vector< PointT<T> > &aPoly){
        double lRet = aPoly.front().distance(aPoly.back());
  
        for(size_t i = 0; i < aPoly.size()-1; i++){
            lRet += aPoly.at(i).distance(aPoly.at(i+1));
        }
        
        return lRet;
    }
    
    template <class T>
    double poly_moment(std::vector<PointT<T> >& aPoly, size_t p, size_t q, bool aClosed = false){
        
        double lArea1 = area(aPoly,aClosed);
        double lArea2 = moment(aPoly,0,0);
        double lARatio = lArea1/lArea2;
        
        return moment(aPoly,p,q)*lARatio;
        
    }
    
    /**
     * Computes the area of the polygon using cross product of points.
     * @param aPoly The polygon to find the area of
     * @param aClosed If the polygon front pt = back pt.
     * @return The polygon area.
     */
    template <class T>
    double area(std::vector<PointT<T> >& aPoly, bool aClosed = false){
        double lRet = 0;
        
        if(!aClosed){
            lRet += aPoly.back().cross(aPoly.front());
        }
        
        for(size_t i = 0; i < aPoly.size()-1; i++){
            lRet += aPoly.at(i).cross(aPoly.at(i+1));
        }
        
        //Traversal direction alters sign.
        return fabs(lRet/2.0);
    }
    
    template <class T, class U>
    void rotate_polygon(std::vector<PointT<T> > &aPoly, PointT<U> aCenter, double aTheta){

        for(size_t i = 0; i < aPoly.size(); i++){
            double xprime = aCenter.x + (aPoly.at(i).x-aCenter.x)*cos(aTheta)-(aPoly.at(i).y-aCenter.y)*sin(aTheta);
            double yprime = aCenter.y + (aPoly.at(i).x-aCenter.x)*sin(aTheta)+(aPoly.at(i).y-aCenter.y)*cos(aTheta);
            aPoly.at(i) = PointT<T>(xprime,yprime);
        }
        
    }
    
    /**
     * Finds the bounding rectangle around the polygon.  This is done by finding
     * the largest and smallest of the x and y coordinates.  This is not the tightest
     * fitting bounding rectangle.  In other words this is not the rectangle for which
     * the area inside of it is nearest in value to that of the polygon's area.
     * @param aPoly The polygon for which we are finding the bounding rectangle.
     * @return The bounding rectangle of the polygon.
     */
    template<class T>
    RectT<T> bounding_rect(std::vector< PointT<T> > &aPoly){

        RectT<T> lReturn;   //The final rectangle.

        double lMinX = aPoly.front().x;   //Smallest x of all the vertices 
        double lMinY = aPoly.front().y;   //Smallest y of all the vertices 
        double lMaxX = aPoly.front().x;   //Largest x of all the vertices 
        double lMaxY = aPoly.front().y;   //Largest y of all the vertices 

        if(aPoly.size() > 1){

            lMinX = aPoly.at(0).x;
            lMinY = aPoly.at(0).y;

            for(long unsigned int i = 0; i < aPoly.size(); i++){
                if(lMinX > aPoly.at(i).x){
                    lMinX = aPoly.at(i).x;
                }

                if(lMinY > aPoly.at(i).y){
                    lMinY = aPoly.at(i).y;
                }

                if(lMaxX < aPoly.at(i).x){
                    lMaxX = aPoly.at(i).x;
                }

                if(lMaxY < aPoly.at(i).y){
                    lMaxY = aPoly.at(i).y;
                }        
            }

        }

        lReturn.x = lMinX;
        lReturn.y = lMinY;
        lReturn.width = lMaxX-lMinX+1;
        lReturn.height = lMaxY-lMinY+1;

        return lReturn;

    }
    
    /**
     * Finds the minimum bounding rectangle of a polygon.  This is done by finding
     * the orientation of the polygon and rotating it so that it's orientation
     * is zero.  The bounding rectangle of this rotated polygon is found and then
     * rotated by the negative angle for which the polygon was rotated.
     * @param aPoly The polygon to find the minimum bounding rectangle of.
     * @return A polygon which represents the minimum bounding rectangle of the
     * polygon.
     */
    template<class T>
    std::vector<PointF > minimal_bounding_rect(std::vector< PointT<T> > &aPoly){

        //Rotate the polygon so it's orientation is 0
        PointF lCent = centroid(aPoly);
        double lTheta = orientation(aPoly);
        rotate_polygon(aPoly,lCent,-lTheta);

        //Find the bounding rectangle of this rotated polygon, and rotate it back 
        //about the polygons centroid.
        RectF lBounding = bounding_rect(aPoly);
        std::vector<PointF> lBoundingPoly = lBounding.polygon();
        rotate_polygon(lBoundingPoly,lCent,lTheta);

        return lBoundingPoly;
    }
    
    /**
     * Computes the minimum and maximum distances across the minimum bounding rectangle.
     * @param aPoly The polygon to find the distances of.
     * @param aMinDistance Minimum distance will be copied to this variable.
     * @param aMaxDistance Maximum distance will be copied to this variable.
     */
    template<class T>
    void min_max_distances(std::vector< PointT<T> > aPoly, double &aMinDistance, double &aMaxDistance){
        
        //Rotate the polygon so it's orientation is 0
        PointF lCent = centroid(aPoly);
        double lTheta = orientation(aPoly);
        rotate_polygon(aPoly,lCent,-lTheta);

        //Find the bounding rectangle of this rotated polygon.
        RectF lBounding = bounding_rect(aPoly);
        aMinDistance = std::min((double)lBounding.width,(double)lBounding.height);
        aMaxDistance = std::max((double)lBounding.width,(double)lBounding.height);
        
    }    
    
    template <class T>
    bool on_line(PointT<T> lPt1, PointT<T> lPt2, PointT<T> aSearchPt, double aTolerance = .1){
        
        double lError;
        double y2 = lPt2.y;
        double y1 = lPt1.y;
        double x2 = lPt2.x;
        double x1 = lPt1.x;
        double x = aSearchPt.x;
        double y = aSearchPt.y;
        
        if(lPt2.x == lPt1.x){
            return (y > (std::min(y1,y2)-aTolerance) && y < (std::max(y1,y2)+aTolerance) );
        } else if (lPt2.y == lPt1.y) {
            return (x > (std::min(x1,x2)-aTolerance) && x < (std::max(x1,x2)+aTolerance) );
        } else {
            lError = (y2-y1)/(x2-x1)*(x-x1)-y+y1;
        }
        

        if(fabs(lError) < aTolerance){
            return true;
        }
        
        return false;
    }
    
    template <class T>
    bool on_boundary(std::vector< PointT<T> >& aPoly, PointT<T> aPt){
        
        bool lOnLine = on_line(aPoly.front(),aPoly.back(),aPt);
        
        for(size_t i = 0; i < aPoly.size()-1; i++){
            lOnLine |= on_line(aPoly.at(i),aPoly.at(i+1),aPt);
        }
        
        return lOnLine;
    }
    
    /**
     * Computes if a point falls along or inside of the boundary of a non self
     * intersecting polygon.
     * @param aPoly The polygon we are searching within.
     * @param aPoint The point we are checking for.
     * @return True if the point is within the polygon.  False otherwise.
     */
    template <class T>
    bool contains(std::vector< PointT<T> > &aPoly, PointT<T> aPt){
        int i, j, c = false;
        double y = aPt.y;
        double x = aPt.x;
        int nvert = aPoly.size();

        for (i = 0, j = nvert-1; i < nvert; j = i++) {
            double yi = aPoly.at(i).y;
            double yj = aPoly.at(j).y;
            double xi = aPoly.at(i).x;
            double xj = aPoly.at(j).x;
            

            if ( ((yi>=y) != (yj>=y)) && (x <= (xj-xi) * (y-yi) / (yj-yi) + xi) ){
                c = !c;
            }
        }
        return c;
    }
    
    /**
     * Recursively simplifies polygon using the Douglas-Peucker algorithm.
     * This slightly modified version of Douglas-Peucker finds the largest diameter
     * before the first recursive call.
     * @param aPolygon The polygon being simplified.
     * @param aResults An unordered list of the elements which make up the new simplified polygon.
     * @param aStart The starting node for the simplification.
     * @param aEnd The ending node for the simplification.
     * @param epsilon Minimum distance between nodes of the simplified polygon.
     */
    template <class T>
    void douglas_peucker(std::vector< PointT<T> > &aPolygon, std::vector< size_t > &aResults, size_t aStart, size_t aEnd, double epsilon){
        // Find the point with the maximum distance
        double dmax = 0;
        size_t index = 0;

        if(aStart == 0 && aEnd == (aPolygon.size()-1) ){
            std::vector<size_t> lSplitPts = diameter_points(aPolygon);
            aResults.push_back(lSplitPts.at(0));
            aResults.push_back(lSplitPts.at(1));
            
            douglas_peucker(aPolygon, aResults, aStart, lSplitPts.at(1), epsilon);
            douglas_peucker(aPolygon, aResults, lSplitPts.at(1), aEnd, epsilon);
            
        } else {

            for(size_t i = aStart+1; i < aEnd; i++){
                double d = perpendicular_distance(aPolygon.at(aStart), aPolygon.at(aEnd), aPolygon.at(i));
                if ( d > dmax ) {
                    index = i;
                    dmax = d;
                }
            }

            // If max distance is greater than epsilon, recursively simplify
            if ( dmax > epsilon ) {
                // Recursive call
                douglas_peucker(aPolygon, aResults, aStart, index, epsilon);
                douglas_peucker(aPolygon, aResults, index, aEnd, epsilon);

            } else {
                bool lPushStart = true;
                bool lPushEnd = true;

                for(size_t i = 0; i < aResults.size(); i++){

                    if(aResults.at(i) == aStart){
                        lPushStart = false;
                    }

                    if(aResults.at(i) == aEnd){
                        lPushEnd = false;
                    }
                }

                if(lPushStart){
                    aResults.push_back(aStart);
                }
                if(lPushEnd){
                    aResults.push_back(aEnd);
                }

            }
        }
        
    }    
    
    /**
     * Simplifies the polygon using the Douglas-Peucker algorithm.
     * @param aSrc Polygon we are simplifying.
     * @param aDst New simplified polygon.
     * @param aEpsilon Minimum distance between nodes of the simplified polygon.
     */
    template <class T>
    void simplify(std::vector< PointT<T> > &aSrc, double aEpsilon){

        //Find if the polygon has the same start and end points.
        bool lSameStartEnd = false;
        if(aSrc.front() == aSrc.back()){
            aSrc.erase(aSrc.end()-1);
            lSameStartEnd = true;
        }
        
        std::vector<size_t> lSplitPts = diameter_points(aSrc);
        std::vector<size_t> lSimplifedPts;
        std::vector<PointT<float> > lResults;
        std::vector<PointT<float> > lSimp;
        glch::convert_vector(aSrc,lSimp);
        
        change_starting_element(lSimp,lSplitPts.at(0));
        lSimp.push_back(lSimp.front());
        
        douglas_peucker(lSimp,lSimplifedPts,0,lSimp.size()-1,aEpsilon);

        lResults.resize(lSimplifedPts.size());
        std::sort(lSimplifedPts.begin(), lSimplifedPts.end());
        
        //Copying the found elements into the results.
        for(size_t i = 0; i < lSimplifedPts.size(); i++){
            lResults.at(i) = lSimp.at(lSimplifedPts.at(i));
        }
        
        //If the original polygon had the same start and end, but the new one does not
        //add the starting point to the end.
        if( (lResults.front() != lResults.back()) && lSameStartEnd){
            lResults.push_back(lResults.front());
        }

        //If the original polygon did not have the same start and end, but the new
        //one does, removed the end.
        if( (lResults.front() == lResults.back()) && !lSameStartEnd){
            lResults.erase(lResults.end()-1);
        }
        
        //aSrc = lResults;
        
        glch::convert_vector(lResults,aSrc);
        
    }    

    
    /**
     * Finds the location of the element which is furthest perpendicularly in the
     * polygon from P1 and P2.
     * @param aPolygon The polygon we are finding the furthest point from.
     * @param aMask The elements we are ignoring during the search.
     * @param aP1 First endpoint.
     * @param aP2 Second endpoint.
     * @return The index of the element which is furthest perpendicularly from
     * P1 and P2.  
     */
    template <class T>
    size_t furtherst_from(std::vector<PointT<T> > &aPolygon, std::vector<bool> &aMask, PointT<T> aP1, PointT<T> aP2){
        size_t lIndex = 0;
        double lDist = 0;
        
        for(size_t i = 0; i < aPolygon.size(); i++){
            if(aMask.at(i)){
                double lTempDist = perpendicular_distance(aP1,aP2,aPolygon.at(i));
                if(lTempDist > lDist ){
                    lDist = lTempDist;
                    lIndex = i;
                }
            }
        }
        
        return lIndex;
    }

    template <class T>
    size_t furtherst_from(std::vector<PointT<T> > &aPolygon, PointT<T> aP1, PointT<T> aP2){
        size_t lIndex = 0;
        double lDist = perpendicular_distance(aP1,aP2,aPolygon.front());
        
        for(size_t i = 1; i < aPolygon.size(); i++){

            double lTempDist = perpendicular_distance(aP1,aP2,aPolygon.at(i));
            if(lTempDist > lDist ){
                lDist = lTempDist;
                lIndex = i;
            }
            
        }
        
        return lIndex;
    }
    
    /**
     * Finds the convex hull of the polygon.  This is done by finding the lowest
     * point in the polygon, then finding the point furthest away from this point.
     * Next the point which has the greatest perpendicular distance from these two
     * points is found.  All the points which fall within this triangle are removed
     * from consideration.  The next furthest point away from the two starting points
     * is found and any points which fall within the polygon are removed.  This process
     * is repeated until the convex polygon is found.
     * @param aPolygon The polygon we are finding the convex hull of.
     * @return The convex polygon.
     */
    template <class T>
    std::vector<PointT<T> > convex_hull(std::vector<PointT<T> > &aPolygon){
        
        size_t lCount = aPolygon.size()-2;              //Number of points left to sort through.
        std::vector<PointT<T> > lCvxPoly;                              //The convex polygon.                            
        std::vector<bool> lMask(aPolygon.size(),true);  //Masking off points during search so we don't compute more than we need to
        size_t lIndex;                                  //Index of current point.
        size_t lP1Index = lowest_point(aPolygon);      //Index of the starting point of the convex polygon.
        PointT<T> lP1 = aPolygon.at(lP1Index);          //Starting point of the convex polygon.
        
        size_t lP2Index = furthest_from(aPolygon,lP1);  //Index of the point furthest away from the starting point.
        PointT<T> lP2 = aPolygon.at(lP2Index);          //Point furthest away from the starting point.

        //We no longer need to look at points which are already in the polygon.
        lMask.at(lP1Index) = false;
        lMask.at(lP2Index) = false;
        lCvxPoly.push_back(lP1);
        lCvxPoly.push_back(lP2);
        
        //Scan through the list of points and find the point with the greatest
        //perpendicular distance from p1 and p2.  This point is then removed from the
        //list of points to consider.
        while(lCount > 0){
            lIndex = furtherst_from(aPolygon, lMask, lP1, lP2);
            lCvxPoly.push_back(aPolygon.at(lIndex));
            angle_sort(lCvxPoly);
            lMask.at(lIndex) = false;
            lCount --;
            
            //Finding any points which fall inside of convex polygon.  If a point
            //is found to lie within the boundary, then it is masked off and the
            //counter is decremented.
            for(size_t i = 0; i < aPolygon.size(); i++){
                if(lMask.at(i) && contains(lCvxPoly, aPolygon.at(i) )){
                    lMask.at(i) = false;
                    lCount --;
                }                
            }

        }

        return lCvxPoly;
        
    }    

    template <class T>
    std::vector<PointT<T> > convex_hull_new(std::vector<PointT<T> > &aPolygon){
        
        std::vector<PointT<T> > lSearch = aPolygon;     //The points we are searching through.
        std::vector<PointT<T> > lCvxPoly;               //The convex polygon.                            
        size_t lIndex;                                  //Index of current point.

        lIndex = lowest_point(lSearch);                //Index of the starting point of the convex polygon.
        PointT<T> lP1 = lSearch.at(lIndex);            //Starting point of the convex polygon.
        lCvxPoly.push_back(lP1);
        lSearch.erase(lSearch.begin()+lIndex);
        
        
        lIndex = furthest_from(lSearch,lP1);            //Index of the point furthest away from the starting point.
        PointT<T> lP2 = lSearch.at(lIndex);          //Point furthest away from the starting point.
        lCvxPoly.push_back(lP2);
        lSearch.erase(lSearch.begin()+lIndex);
        
        //Scan through the list of points and find the point with the greatest
        //perpendicular distance from p1 and p2.  This point is then removed from the
        //list of points to consider.
        while(lSearch.size() > 0){
            lIndex = furtherst_from(lSearch, lP1, lP2);
            
            lCvxPoly.push_back(lSearch.at(lIndex));
            lSearch.erase(lSearch.begin()+lIndex);

            angle_sort(lCvxPoly);

            //Finding any points which fall inside of convex polygon.  If a point
            //is found to lie within the boundary, then it is masked off and the
            //counter is decremented.

            for(size_t i = 0; i < lSearch.size(); i++){
                PointT<T> lPt = lSearch.at(i);
                
                if( contains(lCvxPoly, lPt) ){
                    lSearch.erase(lSearch.begin()+i);
                    i--;
                }                
            }
         
            
        }

        return lCvxPoly;
        
    }        
    
    /**
     * Finds the two vertices which are furthest away from each other in a polygon.
     * @param aPoly The polygon we are finding the diameter points of.
     * @return A vector of two elements with the location of the two points which
     * are furthest from each other.
     */
    template <class T>
    std::vector<size_t> diameter_points(std::vector< PointT<T> > &aPoly){
        
        double lDist = 0;
        size_t lP1Index = -1, lP2Index = -1;
        double lTempDist = 0;
        std::vector<size_t> lRet(2);
        
        for(size_t i = 0; i < aPoly.size(); i++){
            for(size_t j = 0; j < aPoly.size(); j++){
                if(aPoly.at(i) == aPoly.at(j) ){continue;}
                
                lTempDist = aPoly.at(i).distance(aPoly.at(j));
                
                if(lTempDist > lDist){
                    lDist = lTempDist;
                    lP1Index = i;
                    lP2Index = j;
                }
                
            }
            
        }
        
        lRet.at(0) = lP1Index;
        lRet.at(1) = lP2Index;
        
        return lRet;
        
    }    

    template <class T>
    double diameter_taxicab(std::vector< PointT<T> > &aPoly){
        
        if(aPoly.size() < 2){
            if(aPoly.size() > 0){
                return 1.0;
            }
            return 0.0;
        }
        
        std::vector<size_t> lElements = diameter_points(aPoly);
        PointT<T> lPoint1 = aPoly.at(lElements.at(0));
        PointT<T> lPoint2 = aPoly.at(lElements.at(1));
        
        return lPoint1.taxicab(lPoint2);
        
    }
    
    /**
     * Computes the diameter of a polygon.  The diameter is computed as the distance
     * between the two points which are furthest from each other in a polygon.
     * @param aPoly The polygon we are trying to find the diameter of.
     * @return The diameter of the polygon.
     */
    template <class T>
    double diameter(std::vector< PointT<T> > &aPoly){
        if(aPoly.size() < 2){
            if(aPoly.size() > 0){
                return 1.0;
            }
            return 0.0;
        }
        
        std::vector<size_t> lElements = diameter_points(aPoly);
        PointT<T> lPoint1 = aPoly.at(lElements.at(0));
        PointT<T> lPoint2 = aPoly.at(lElements.at(1));
        
        return lPoint1.distance(lPoint2);
    }
    
    /**
     * Finds a point which is opposite of aPoint which passes through the centroid of aPolygon.
     * @param aPolygon
     * @param aPoint
     * @param aCentroid
     * @param aIndex Index of the opposite point.
     * @return 
     */
    template <class T>
    size_t find_opposite_point(std::vector<PointT<T> > &aPolygon, PointT<T> aPoint, PointT<T> lCentroid){

        double      lError = DBL_MAX;
        size_t lIndex = 0;
        
        for(size_t i = 0; i < aPolygon.size(); i++){
            if(aPolygon.at(i) == aPoint){continue;}
            
            double tempError;

            if(aPolygon.at(i).x != aPoint.x){
                tempError = (aPolygon.at(i).y-aPoint.y)/(aPolygon.at(i).x-aPoint.x)*(lCentroid.x-aPolygon.at(i).x)-lCentroid.y+aPolygon.at(i).y;
            } else {
                tempError = (-1)*(lCentroid.x+aPoint.x);
            }
            tempError = fabs(tempError);            

            if(tempError < lError ){
                lError = tempError;
                lIndex = i;
            }
            
        }

        return lIndex;
    }

    template <class T>
    void get_max_min_diameter(std::vector<PointT<T> > &aPolygon, double &aMaxDist, double &aMinDist){

        double lMax;
        double lMin;

        PointT<T> lCentroid = centroid(aPolygon);
        PointT<T> lInitPt = aPolygon.at(find_opposite_point(aPolygon, aPolygon.at(0), lCentroid));
        double lInitDist = lInitPt.distance(aPolygon.at(0));

        lMax = lInitDist;
        lMin = lInitDist;

        for(size_t i = 0; i < aPolygon.size(); i++){

            PointT<T> tempPoint = aPolygon.at(find_opposite_point(aPolygon, aPolygon.at(i), lCentroid));

            double tempDist = aPolygon.at(i).distance(tempPoint);

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

    template <class T>
    std::vector<float> find_distances(PointT<T> aRefPt, std::vector<PointT<T> > aCompPts){
        std::vector<float> lRet;
        lRet.resize(aCompPts.size());

        for(size_t i = 0; i < lRet.size(); i++){
            lRet.at(i) = aRefPt.distance(aCompPts.at(i));
        }
        
        return lRet;

    }
}

#endif	/* GLCH_POLYGONFUNCTIONS_H */

