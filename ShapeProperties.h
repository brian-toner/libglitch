/* 
 * File:   ShapeProperties.h
 * Author: brian
 *
 * Created on January 2, 2016, 2:30 PM
 */

#ifndef GLCH_SHAPEPROPERTIES_H
#define	GLCH_SHAPEPROPERTIES_H

#include "PointT.h"
#include "Moments.h"
#include <limits>
#include "RectT.h"
#include "PolyT.h"
#include "PolygonFunctions.h"
#include <math.h>

namespace glch{

    template <class T>
    class ShapeProperties {
    public:
        ShapeProperties(){}; 
        
        
        ShapeProperties(std::vector< PointT<T> > &aPoly, size_t aNMoments = 5){
            initialize(aPoly,aNMoments);  
        };
        
        ShapeProperties(const ShapeProperties& orig) : vArea(orig.vArea),
                                                        vPerimeter(orig.vPerimeter),
                                                        vDiameter(orig.vDiameter),
                                                        vCvxArea(orig.vCvxArea),
                                                        vCvxPerimeter(orig.vCvxPerimeter),
                                                        vDMin(orig.vDMin),
                                                        vDMax(orig.vDMax),
                                                        vWaviness(orig.vWaviness),
                                                        vAspectRatio(orig.vAspectRatio),
                                                        vFilamentRatio(orig.vFilamentRatio),
                                                        vCircularRatio(orig.vCircularRatio),
                                                        vMCpt(orig.vMCpt),
                                                        vMEct(orig.vMEct),
                                                        vMoments(orig.vMoments),
                                                        vOrientation(orig.vOrientation),
                                                        vBoundingRect(orig.vBoundingRect),   
                                                        vCvxHull(orig.vCvxHull),
                                                        vMinimalBoundingRect(orig.vMinimalBoundingRect){};
        virtual ~ShapeProperties(){};

        static std::string header(){
            glch::AString lRet;
            
            lRet << "Centroid_X";
            lRet << "Centroid_Y";
            lRet << "Area";
            lRet << "Perimeter";
            lRet << "Diameter";
            lRet << "CvxArea";
            lRet << "CvxPerimeter";
            lRet << "DMin";
            lRet << "DMax";
            lRet << "Waviness";
            lRet << "AspectRatio";
            lRet << "FilamentRatio";
            lRet << "CircularRatio";
            lRet << "MCpt";
            lRet << "MEct";
            lRet << "Orientation";
            
            return lRet;
        }
        
        std::string to_string(){
            glch::AString lRet;
            
            lRet << vBoundingRect.centroid().x;
            lRet << vBoundingRect.centroid().y;
            lRet << vArea;
            lRet << vPerimeter;
            lRet << vDiameter;
            lRet << vCvxArea;
            lRet << vCvxPerimeter;
            lRet << vDMin;
            lRet << vDMax;
            lRet << vWaviness;
            lRet << vAspectRatio;
            lRet << vFilamentRatio;
            lRet << vCircularRatio;
            lRet << vMCpt;
            lRet << vMEct;
            lRet << vOrientation;
            
            return lRet;
        }
        
        void initialize(std::vector< PointT<T> > &aPoly, size_t aNMoments = 5){
            moments(aPoly,aNMoments);
            vArea = area(aPoly);
            vPerimeter = perimeter(aPoly);
            vDiameter = diameter(aPoly);
            min_max_distances(aPoly,vDMin,vDMax);
            
            vMinimalBoundingRect = minimal_bounding_rect(aPoly);
            vBoundingRect = bounding_rect(aPoly);
            vCvxHull = convex_hull(aPoly);
            vCvxArea = area(vCvxHull);
            vCvxPerimeter = perimeter(vCvxHull);
            vOrientation = orientation(aPoly);
            
            vFilamentRatio = (4.0*vArea)/(vPerimeter*vDiameter);
            vCircularRatio = (4*M_PI*vArea)/(vPerimeter*vPerimeter);
            vAspectRatio = vDMin/vDMax;
            vWaviness = vCvxPerimeter/vPerimeter;

            double m00 = vMoments.vM.at(Point(0,0));
            double mup20 = vMoments.vMu.at(Point(2,0))/m00;
            double mup02 = vMoments.vMu.at(Point(0,2))/m00;
            double mup11 = vMoments.vMu.at(Point(1,1))/m00;
            
            vMCpt = 1.0/(2.0*M_PI)*m00/(mup20+mup02);
            vMEct = sqrt((mup20-mup02)*(mup20-mup02) + 4.0*mup11*mup11 )/(mup20+mup02);
        }
        
        double      vArea;
        double      vPerimeter;
        double      vDiameter;
        double      vCvxArea;
        double      vCvxPerimeter;
        double      vDMin;
        double      vDMax;
        double      vWaviness;
        double      vAspectRatio;
        double      vFilamentRatio;
        double      vCircularRatio;
        double      vMCpt;
        double      vMEct;
        Moments     vMoments;
        double      vOrientation;
        RectF       vBoundingRect;
        
        std::vector< PointT<T> > vCvxHull;
        std::vector< PointF > vMinimalBoundingRect;
        
    private:

        void moments(std::vector< PointT<T> > &aPoly, size_t aNMoments);
        
        PointF centriod(){
            return vMoments.vCentroid;
        }
        
    };

    /**
     * Computes the moments up to n-moments
     * @param aPoly The polygon whose moments are being computed.
     * @param aNMoments Order of moments being computed 
     * i.e. nmoments = 5 => M_55, Mu_55, and Nu_55 will be computed.
     */
    template <class T>
    void ShapeProperties<T>::moments(std::vector< PointT<T> > &aPoly, size_t aNMoments){ 
        vMoments.set_moments(aPoly,aNMoments);  
    }
    

    
    
    
}

#endif	/* GLCH_SHAPEPROPERTIES_H */

