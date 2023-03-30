/* 
 * File:   RectT.h
 * Author: brian
 *
 * Created on July 4, 2015, 10:30 PM
 */

#ifndef GLCH_RECTT_H
#define	GLCH_RECTT_H

#include "PointT.h"
#include <iostream>
#include <cstdlib>

namespace glch {

    template <class T>
    struct RectT{
        T x;        //x position of rectangle.
        T y;        //y position of rectangle.
        T width;    //width of rectangle.
        T height;   //height of rectangle.

        /**
         * Checks if two rectangles have the same x, y, width, and height.
         * @param aInput Second rectangle we are checking against.
         * @return True if the rectangles have the same x, y, width, and height.
         * False otherwise.
         */
        bool operator==(RectT aInput){
            return x == aInput.x && y == aInput.y && width == aInput.width && height == aInput.height;
        }

        template <class U>
        operator RectT<U>(){
            return RectT<U>((U)x, (U)y, (U)width, (U)height);
        }

        /**
         * Returns the area of the rectangle (width*height);
         * @return Area
         */
        T area(){return width*height;};

        /**
         * Left x-coordinate of the rectangle.
         * @return Left x-coordinate of the rectangle.
         */
        T left(){return x;};
        
        /**
         * Right x-coordinate of the rectangle.
         * @return Right x-coordinate of the rectangle.
         */
        T right(){return x+width-1;};
        
        /**
         * Top y-coordinate of the rectangle.
         * @return Top y-coordinate of the rectangle.
         */        
        T top(){return y;};
        
        /**
         * Bottom y-coordinate of the rectangle.
         * @return Bottom y-coordinate of the rectangle.
         */        
        T bottom(){return y+height-1;};

        /**
         * Prints off the rectangle information.
         */
        void print(std::string aDelim = ""){
            std::cout << "[" << x << ", " << y << ", " << width << ", " << height << "]" << std::endl;
        }
        
        /**
         * Converts the rectangle into its polygon equivalent.
         * @return A vector of points representing the polygon.
         */
        std::vector<PointT<T> > polygon(){
            std::vector<PointT<T> > lRet(4);
            
            lRet.at(0) = PointT<T>(top_left());
            lRet.at(1) = PointT<T>(top_right(true));
            lRet.at(2) = PointT<T>(bottom_right(true));
            lRet.at(3) = PointT<T>(bottom_left(true));
            
            return lRet;
        }
        
        /**
         * Returns the floating point centroid of the rectangle.
         * @return The centroid of the rectangle.
         */
        PointF centroidf(){return PointF(x+width/2.0,y+height/2.0);};

        /**
         * Returns the centroid of the rectangle.
         * @return The centroid of the rectangle.
         */
        PointT<T> centroid(){return PointT<T>(x+width/2.0,y+height/2.0);};

        /**
         * Returns the top left coordinate of the rectangle.
         * @return Top left coordinate.
         */
        PointT<T> top_left(){return PointT<T>(x,y);};

        /**
         * Returns the top right coordinate of the rectangle.
         * @return Top right coordinate.
         */
        PointT<T> top_right(bool aExtend = false){return PointT<T>(right()+(aExtend?1:0),y);};

        
        /**
         * Returns the bottom left coordinate of the rectangle.
         * @return Bottom left coordinate.
         */
        PointT<T> bottom_left(bool aExtend = false){return PointT<T>(x,bottom()+(aExtend?1:0));};
        
        /**
         * Returns the bottom right coordinate of the rectangle.
         * @return Bottom right coordinate.
         */
        PointT<T> bottom_right(bool aExtend = false){return PointT<T>(right()+(aExtend?1:0),bottom()+(aExtend?1:0));};


        /**
         * Floating point Distance between the centroid of this rectangle and another rectangle.
         * @param aRect Rectangle we are comparing against.
         * @return Distance between the centroids of the the two rectangles.
         */
        double distancef(RectT<T> aRect){
            return centroidf().distance(aRect.centroidf());
        }

        /**
         * Returns the floating point distance between the centroid of this rectangle and a point.
         * @param aPoint Point we are comparing against.
         * @return Distance between the centroid of the rectangle and the point.
         */
        double distancef(PointF aPoint){
            return centroidf().distance(aPoint);
        }

        /**
         * Distance between the centroid of this rectangle and another rectangle.
         * @param aRect Rectangle we are comparing against.
         * @return Distance between the centroids of the the two rectangles.
         */
        double distance(RectT<T> aRect){
            return centroid().distance(aRect.centroid());
        }

        /**
         * Returns the distance between the centroid of this rectangle and a point.
         * @param aPoint Point we are comparing against.
         * @return Distance between the centroid of the rectangle and the point.
         */
        double distance(PointT<T> aPoint){
            return centroid().distance(aPoint);
        }

        /**
         * Default constructor for the rectangle.  Initializes x, y, width, and height to 0.
         */
        RectT(){x = 0;y = 0;width = 0;height = 0;};

        /**
         * Initializes the rectangle based on two points.
         * @param argPt1 Top left coordinate of rectangle.
         * @param argPt2 Bottom right coordinate of rectangle.
         */
        RectT(PointT<T> argPt1, PointT<T> argPt2);

        /**
         * Initializes the rectangle based on input parameters.
         * @param argX x position
         * @param argY y position
         * @param argWidth rectangle width
         * @param argHeight rectangle height
         */
        RectT(T argX, T argY, T argWidth, T argHeight);

        /**
         * Returns the intersecting rectangle between two rectangles.  If the two rectangles
         * do not intersect then either the width or height of the return rectangle
         * will be negative values.
         * @param aRect Rectangle comparing against.
         * @return A new rectangle with the coordinates of the intersecting rectangle.
         * The width and height of this new rectangle will be negative if the two
         * rectangles do not intersect.
         */
        RectT get_intersection(RectT<T> aRect);

        /**
         * Checks if two rectangles intersect.
         * @param aRect Rectangle comparing against.
         * @return True if the two rectangles intersect.  False otherwise.
         */    
        bool check_intersection(RectT<T> aRect);

        double overlap_ratio(RectT<T> argRect2);
        
        /**
         * Computes if two rectangles are similar based on the percent they overlap.  This means
         * that if one rectangle is entirely contained in another then they will be considered
         * similar.
         * @param aRect aRect The rectangle being compared against.
         * @param aOverlap aOverlap The overlap threshold
         * @return True if the two rectangles are similar.
         */
        bool similar(RectT<T> aRect, double aOverlap);
        
        /**
         * Computes if two rectangles are similar based on the percent overland and distance
         * between centroids.  If two rectangles overlap greater than the overlap threshold
         * and their centroid are nearer than the distance threshold then they are similar.
         * @param aRect The rectangle being compared against.
         * @param aOverlap The overlap threshold
         * @param aDistance The distance threshold
         * @return True if the two rectangles are similar.
         */
        bool similar(RectT<T> aRect, double aOverlap, double aDistance);
        /**
         * Returns the smallest possible rectangle where both original rectangles 
         * fall inside the boundary of the new rectangle.
         * @param aRect1 First rectangle
         * @param aRect2 Second rectangle.
         * @return 
         */
        RectT get_merged_rect(RectT<T> aRect);


        /**
         * Resizes the rectangle around the center of mass.
         * @param aRatio The ratio to change the size of the rectangle by.
         * @return A rectangle with the new size based on the old rectangle.
         */
        void resize(double aReduceSizeRatio);
        
        /**
         * Resizes the rectangle so that it has a minimum size of aMinSize and a
         * max size of aMaxSize (based on area).  If the rectangle falls within the two sizes
         * then it will not be resized.
         * @param aMinSize Minimum size the rectangle can be.
         * @param aMaxSize Maximum size the rectangle can be.
         */
        void resize(RectT<T> aMinSize, RectT<T> aMaxSize);
        
        /**
         * Checks if another rectangle is inside of the rectangle.
         * @param aRect
         * @return 
         */
        bool contains(RectT<T> aRect);
        
        /**
         * Checks if a point is inside of the rectangle.
         * @param aPoint Point we are checking.
         * @return 
         */
        bool contains(PointT<T> aPoint);
        
        void to_square();
        
        
        
    };


    /**
     * Initializes the rectangle based on two points.
     * @param argPt1 Top left coordinate of rectangle.
     * @param argPt2 Bottom right coordinate of rectangle.
     */
    template<class T>
    RectT<T>::RectT(PointT<T> argPt1, PointT<T> argPt2){
        x = argPt1.x;
        y = argPt1.y;
        
        width = argPt2.x - argPt1.x;
        height = argPt2.y - argPt1.y;
    }

    
    /**
     * Initializes the rectangle based on input parameters.
     * @param argX x position
     * @param argY y position
     * @param argWidth rectangle width
     * @param argHeight rectangle height
     */
    template<class T>
    RectT<T>::RectT(T argX, T argY, T argWidth, T argHeight){
        x = argX;
        y = argY;
        width = argWidth;
        height = argHeight;
        
    }
    
    
    /**
     * Returns the intersecting rectangle between two rectangles.  If the two rectangles
     * do not intersect then either the width or height of the return rectangle
     * will be negative values.
     * @param aRect Rectangle comparing against.
     * @return A new rectangle with the coordinates of the intersecting rectangle.
     * The width and height of this new rectangle will be negative if the two
     * rectangles do not intersect.
     */
    template<class T>
    RectT<T> RectT<T>::get_intersection(RectT<T> aRect){
        RectT lReturn;
        lReturn.x = std::max(x,aRect.x);
        lReturn.y = std::max(y,aRect.y);
        lReturn.width = std::min(x+width, aRect.x+aRect.width) - lReturn.x;
        lReturn.height = std::min(y+height, aRect.y+aRect.height) - lReturn.y;
        
        return lReturn;
        
    }
    
    
    /**
     * Checks if two rectangles intersect.
     * @param aRect Rectangle comparing against.
     * @return True if the two rectangles intersect.  False otherwise.
     */
    template<class T>
    bool RectT<T>::check_intersection(RectT<T> aRect){
        RectT<T> lIntersectRect = this->get_intersection(aRect);
        
        if(lIntersectRect.height < 0 || lIntersectRect.width < 0){
            return false;
        }
        
        return true;
    }
   
    /**
     * Computes the ratio for which the two rectangles overlapped.  First intersection
     * area is computed.  This is then divided by the area of this rectangle.
     * @param aRect The second rectangle we are comparing to.
     * @return The ratio of the overlap are to this rectangles area.
     */
    template<class T>
    double RectT<T>::overlap_ratio(RectT<T> aRect){

        if(check_intersection(aRect)){            
            return (double)(get_intersection(aRect).area())/(double)area();
        }
        return 0;
    }    
    
    /**
     * Computes if two rectangles are similar.  Meaning they have a high ratio of overlap.
     * This means that if this rectangle is entirely contained in another rectangle
     * then it will be similar to the other rectangle.
     * @param aRect The rectangle this rectangle is being compared to.
     * @param aOverlap The overlap threshold.
     * @return True if they are similar.  False otherwise.
     */
    template<class T>
    bool RectT<T>::similar(RectT<T> aRect, double aOverlap){
        bool lRet = false;
        
        if(*this == aRect){
            lRet = true;
        }

        if(overlap_ratio(aRect) >= aOverlap || aRect.overlap_ratio(*this) >= aOverlap){
            lRet = true;
        }
        
        return lRet;
    }
    
    /**
     * Computes if two rectangles are similar.  Meaning they have a high ratio of overlap
     * and their centroids are within a certain distance of each other.
     * This means that if this rectangle is entirely contained in another rectangle
     * and its centroid is close to the other rectangle's centroid then it will be 
     * similar to the other rectangle.
     * @param aRect The rectangle this rectangle is being compared to.
     * @param aOverlap The overlap threshold.
     * @param aDistance The distance threshold.
     * @return True if they are similar.  False otherwise.
     */
    template<class T>
    bool RectT<T>::similar(RectT<T> aRect, double aOverlap, double aDistance){
        
        if(!similar(aRect,aOverlap)){
            return false;
        }
        
        if(aDistance > distance(aRect)){
            return false;
        }
        
        return true;
        
    }    
    
    /**
     * Returns the smallest possible rectangle where both original rectangles 
     * fall inside the boundary of the new rectangle.
     * @param aRect The rectangle this rectangle is being compared to.
     * @return The smallest possible rectangle where both original rectangles 
     * fall inside the boundary of the new rectangle.
     */
    template<class T>
    RectT<T> RectT<T>::get_merged_rect(RectT<T> aRect){
        RectT<T> lReturn;
        lReturn.x = std::min(x,aRect.x);
        lReturn.y = std::min(y,aRect.y);
        lReturn.width = std::max(x+width, aRect.x+aRect.width) - lReturn.x;
        lReturn.height = std::max(y+height, aRect.y+aRect.height) - lReturn.y;
        
        return lReturn;        
    }
    
    /**
     * Resizes the rectangle around the center of mass.
     * @param aRatio The ratio to change the size of the rectangle by.
     * @return A rectangle with the new size based on the old rectangle.
     */
    template<class T>
    void RectT<T>::resize(double aRatio){
        
        T lOffsetX;
        T lOffsetY;
        if(aRatio < 1){

            lOffsetX = (width - aRatio*width)/2.0;
            lOffsetY = (height - aRatio*height)/2.0;
            width = aRatio*width;
            height = aRatio*height;
            x += lOffsetX;
            y += lOffsetY;

        } else {

            lOffsetX = (aRatio*width - width)/2.0;
            lOffsetY = (aRatio*height - height)/2.0;
            width = aRatio*width;
            height = aRatio*height;
            x -= lOffsetX;
            y -= lOffsetY;

        }
    }

    /**
     * Resizes the rectangle so that it has a minimum size of aMinSize and a
     * max size of aMaxSize (based on area).  If the rectangle falls within the two sizes
     * then it will not be resized.
     * @param aMinSize Minimum size the rectangle can be.
     * @param aMaxSize Maximum size the rectangle can be.
     */
    template<class T>
    void RectT<T>::resize(RectT<T> aMinRect, RectT<T> aMaxRect){
        T lOffsetX = 0;
        T lOffsetY = 0;
        if(area() > aMaxRect.area()){

            lOffsetX = (width - aMaxRect.width)/2;
            lOffsetY = (height - aMaxRect.height)/2;
            width = aMaxRect.width;
            height = aMaxRect.height;
            x += lOffsetX;
            y += lOffsetY;

        } else if(area() < aMinRect.area()){
            lOffsetX = (aMinRect.width - width)/2;
            lOffsetY = (aMinRect.height - height)/2;
            width = aMinRect.width;
            height = aMinRect.height;
            x -= lOffsetX;
            y -= lOffsetY;
        }  
        
    }
    
    /**
     * Checks if another rectangle is inside of this rectangle.
     * @param aRect Rectangle we are checking against.
     * @return True if the other rectangle is inside of this one.  False otherwise.
     */
    template<class T>
    bool RectT<T>::contains(RectT<T> aRect){
        return (left() < aRect.left() && 
                aRect.right() <= right() && 
                top() <= aRect.top() && 
                aRect.bottom() <= bottom());

    }
    
    /**
     * Checks if a point is within this rectangle.
     * @param aPoint Point we are checking against.
     * @return True if this point is inside the rectangle, false otherwise.
     */
    template<class T>
    bool RectT<T>::contains(PointT<T> aPoint){        
        return (left() <= aPoint.x && 
                aPoint.x <= right() && 
                top() <= aPoint.y && 
                aPoint.y <= bottom());
    }
    
    /**
     * Changes this rectangle into a square.
     */
    template<class T>
    void RectT<T>::to_square(){
        T lOffset = 0;

        if(height > width){
            lOffset = (height - width)/2;
            width = height;
            x -= lOffset;
        } else if(height < width){
            lOffset = (width - height)/2;
            height = width;
            y -= lOffset;
        }

    }
    
    typedef RectT<double> RectF;
    typedef RectT<int> Rect;


}

#endif	/* GLCH_RECTT_H */

