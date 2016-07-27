/* 
 * File:   Moments.h
 * Author: brian
 *
 * Created on January 1, 2016, 2:04 PM
 */

#ifndef MOMENTS_H
#define	MOMENTS_H

#include "PointT.h"
#include "MatT.h"

namespace glch{

    template <class T>
    PointF centroid(MatT<T> &aImage){
        PointT<T> lCentroid;

        double m00 = moment(aImage, 0,0);
        double m10 = moment(aImage, 1,0);
        double m01 = moment(aImage, 0,1);
        lCentroid.x = m10/m00;
        lCentroid.y = m01/m00;

        return lCentroid;            
    }
    
    /**
     * Computes the centroid of the polygon through the use of moments.
     * @param aPolygon
     * @return 
     */
    template <class T>
    PointF centroid(std::vector< PointT<T> > &aPolygon){

        PointT<T> lCentroid;

        double m00 = moment(aPolygon, 0,0);
        double m10 = moment(aPolygon, 1,0);
        double m01 = moment(aPolygon, 0,1);
        lCentroid.x = m10/m00;
        lCentroid.y = m01/m00;

        return lCentroid;    
    }

    /**
     * Computes the orientation of a polygon.  The orientation of the object
     * is defined as the angle between the x axis and the axis around which
     * the object can be rotated with minimum inertia.
     * Can be found from Digital Image Processing, Volume 1 p522. Bernd Jahne.
     * @param aPolygon The polygon we are computing the orientation of.
     * @return The orientation angle in radians.
     */
    template <class T>
    double orientation(std::vector<PointT<T> > &aPolygon){
        PointF lCentroid = centroid(aPolygon);
        double mu11 = central_moment(aPolygon, lCentroid, 1,1);
        double mu20 = central_moment(aPolygon, lCentroid, 2,0);
        double mu02 = central_moment(aPolygon, lCentroid, 0,2);
        return (0.5*atan(2.0*mu11/(mu20-mu02)));
    }
    
    template <class T>
    double moment(std::vector< PointT<T> > &aPolygon, size_t p, size_t q){
        double lSum = 0;
        for(size_t i = 0; i < aPolygon.size(); i++){
            lSum += pow(aPolygon.at(i).x,p)*pow(aPolygon.at(i).y,q);
        }

        return lSum;
    }

    template <class T>
    double moment(MatT<T> &aImage, size_t p, size_t q){
        double lSum = 0;
        
        for(size_t r = 0; r < aImage.rows; r++){
            for(size_t c = 0; c < aImage.cols; c++){
                lSum += pow(c,p)*pow(r,q)*aImage.at(c,r);
            }
        }

        return lSum;
    }
    
    template <class T, class U>
    double central_moment(std::vector< PointT<T> > &aPolygon, PointT<U> aCentroid, size_t p, size_t q){
        double lSum = 0;
        for(size_t i = 0; i < aPolygon.size(); i++){
            lSum += pow(aPolygon.at(i).x-aCentroid.x,p)*pow(aPolygon.at(i).y-aCentroid.y,q);
        }

        return lSum;
    }    

    template <class T, class U>
    double central_moment(MatT<T> &aImage, PointT<U> aCentroid, size_t p, size_t q){
        double lSum = 0;
        
        for(size_t r = 0; r < aImage.rows; r++){
            for(size_t c = 0; c < aImage.cols; c++){
                lSum += pow(c-aCentroid.x,p)*pow(r-aCentroid.y,q)*aImage.at(c,r);
            }
        }

        return lSum;
    } 
    
    template <class T, class U>
    double normalized_central_moment(std::vector< PointT<T> > aPolygon, PointT<U> aCentroid, size_t p, size_t q){
        return central_moment(aPolygon,aCentroid,p,q)/(pow(moment(aPolygon,0,0),(double)(p+q)/2.0+1.0) );
    }

    template <class T, class U>
    double normalized_central_moment(MatT<T> &aImage, PointT<U> aCentroid, size_t p, size_t q){
        return central_moment(aImage,aCentroid,p,q)/(pow(moment(aImage,0,0),(double)(p+q)/2.0+1.0) );
    }
    
    template <class T, class U>
    std::vector<double> hu_moments(std::vector< PointT<T> > &aPolygon, PointT<U> aCentroid){
        std::vector<double> lRet(7,0);
        
        double n11 = normalized_central_moment(aPolygon,aCentroid,1,1);

        double n20 = normalized_central_moment(aPolygon,aCentroid,2,0);
        double n02 = normalized_central_moment(aPolygon,aCentroid,0,2);
        
        double n12 = normalized_central_moment(aPolygon,aCentroid,1,2);
        double n21 = normalized_central_moment(aPolygon,aCentroid,2,1);
        
        double n30 = normalized_central_moment(aPolygon,aCentroid,3,0);
        double n03 = normalized_central_moment(aPolygon,aCentroid,0,3);        
        
        lRet[0] = n20+n02;
        
        lRet[1] = pow(n20-n02,2) + 4*pow(n11,2);
        
        lRet[2] = pow(n30-3*n12,2) + pow(3*n21-n03,2);
        
        lRet[3] = pow(n30+n12,2) + pow(n21+n03,2);
        
        lRet[4] = (n30-3*n12)*(n30+n12)*( pow(n30+n12,2) - 3*pow(n21+n03,2) ) +
                  (3*n21-n03)*(n21+n03)*( 3*pow(n30+n12,2)-pow(n21+n03,2) );
        
        lRet[5] = (n20-n02)*( pow(n30+n12,2) - pow(n21+n03,2) ) + 4*n11*(n30+n12)*(n21+n03);
        
        lRet[6] = (3*n21-n03)*(n30+n12)*( pow(n30+n12,2) - 3*pow(n21+n03,2) ) -
                  (n30-3*n12)*(n21+n03)*( 3*pow(n30+n12,2) - pow(n21+n03,2) );
        
        return lRet;
    }  

    template <class T, class U>
    std::vector<double> hu_moments(MatT<T> &aImage, PointT<U> aCentroid){
        std::vector<double> lRet(7,0);
        
        double n11 = normalized_central_moment(aImage,aCentroid,1,1);

        double n20 = normalized_central_moment(aImage,aCentroid,2,0);
        double n02 = normalized_central_moment(aImage,aCentroid,0,2);
        
        double n12 = normalized_central_moment(aImage,aCentroid,1,2);
        double n21 = normalized_central_moment(aImage,aCentroid,2,1);
        
        double n30 = normalized_central_moment(aImage,aCentroid,3,0);
        double n03 = normalized_central_moment(aImage,aCentroid,0,3);        
        
        lRet[0] = n20+n02;
        
        lRet[1] = pow(n20-n02,2) + 4*pow(n11,2);
        
        lRet[2] = pow(n30-3*n12,2) + pow(3*n21-n03,2);
        
        lRet[3] = pow(n30+n12,2) + pow(n21+n03,2);
        
        lRet[4] = (n30-3*n12)*(n30+n12)*( pow(n30+n12,2) - 3*pow(n21+n03,2) ) +
                  (3*n21-n03)*(n21+n03)*( 3*pow(n30+n12,2)-pow(n21+n03,2) );
        
        lRet[5] = (n20-n02)*( pow(n30+n12,2) - pow(n21+n03,2) ) + 4*n11*(n30+n12)*(n21+n03);
        
        lRet[6] = (3*n21-n03)*(n30+n12)*( pow(n30+n12,2) - 3*pow(n21+n03,2) ) -
                  (n30-3*n12)*(n21+n03)*( 3*pow(n30+n12,2) - pow(n21+n03,2) );
        
        return lRet;
    }

    class Moments {
    public:
        Moments(){};
        Moments(const Moments& orig) : vCentroid(orig.vCentroid),
                                             vHu(orig.vHu),
                                             vM(orig.vM),            
                                             vMu(orig.vMu),
                                             vNu(orig.vNu){};
        virtual ~Moments(){};
        
        template <class T>
        Moments(std::vector< PointT<T> > aPoly, size_t aNMoments = 5){
            set_moments(aPoly,aNMoments);
        }

        template <class T>
        Moments(MatT<T> aImage, size_t aNMoments = 5){
            set_moments(aImage,aNMoments);
        }
        
        
        template <class T>
        void set_moments(std::vector< PointT<T> > aPoly, size_t aNMoments){
            vCentroid = centroid(aPoly);
            vM.resize(aNMoments,aNMoments);
            vMu.resize(aNMoments,aNMoments);
            vNu.resize(aNMoments,aNMoments);
            
            for(size_t i = 0; i < aNMoments; i++){
                for(size_t j = 0; j < aNMoments; j++){
                    vM.at(Point(i,j)) = moment(aPoly,i,j);
                    vMu.at(Point(i,j)) = central_moment(aPoly,i,j);
                    vNu.at(Point(i,j)) = normalized_central_moment(aPoly,i,j);
                }
            }

            vHu = hu_moments(aPoly);
        }
        
        template <class T>
        void set_moments(MatT<T> &aImage, size_t aNMoments){
            vCentroid = centroid(aImage);
            vM.resize(aNMoments,aNMoments);
            vMu.resize(aNMoments,aNMoments);
            vNu.resize(aNMoments,aNMoments);
            
            for(size_t i = 0; i < aNMoments; i++){
                for(size_t j = 0; j < aNMoments; j++){
                    vM.at(Point(i,j)) = moment(aImage,i,j);
                    vMu.at(Point(i,j)) = central_moment(aImage,i,j);
                    vNu.at(Point(i,j)) = normalized_central_moment(aImage,i,j);
                }
            }

            vHu = hu_moments(aImage);
        }        
        
        PointF vCentroid;           //Centroid
        std::vector<double> vHu;    //Hu Moments
        MatT<double> vM;            //Moments
        MatT<double> vMu;           //Central moments
        MatT<double> vNu;           //Normalized central moments
        
        template <class T>
        PointF centroid(std::vector< PointT<T> > &aPolygon);

        template <class T>
        PointF centroid(MatT<T> &aImage);
        
        template <class T>
        double moment(std::vector< PointT<T> > &aPolygon, size_t p, size_t q);

        template <class T>
        double moment(MatT<T> &aImage, size_t p, size_t q);
        
        template <class T>
        double central_moment(std::vector< PointT<T> > &aPolygon, size_t p, size_t q);

        template <class T>
        double central_moment(MatT<T> &aImage, size_t p, size_t q);
        
        template <class T>
        double normalized_central_moment(std::vector< PointT<T> > &aPolygon, size_t p, size_t q);

        template <class T>
        double normalized_central_moment(MatT<T> &aImage, size_t p, size_t q);
        
        template <class T>
        std::vector<double> hu_moments(std::vector< PointT<T> > &aPolygon);

        template <class T>
        std::vector<double> hu_moments(MatT<T> &aImage);
        
    private:

    };
    
    template <class T>
    PointF Moments::centroid(std::vector< PointT<T> > &aPolygon){
        vCentroid = glch::centroid(aPolygon);
        return vCentroid;
    }

    template <class T>
    PointF Moments::centroid(MatT<T> &aImage){
        vCentroid = glch::centroid(aImage);
        return vCentroid;
    }
    
    template <class T>
    double Moments::moment(std::vector< PointT<T> > &aPolygon, size_t p, size_t q){
        return glch::moment(aPolygon,p,q);
    }

    template <class T>
    double Moments::moment(MatT<T> &aImage, size_t p, size_t q){
        return glch::moment(aImage,p,q);
    }
    
    template <class T>
    double Moments::central_moment(std::vector< PointT<T> > &aPolygon, size_t p, size_t q){
        return glch::central_moment(aPolygon,vCentroid,p,q);
    }

    template <class T>
    double Moments::central_moment(MatT<T> &aImage, size_t p, size_t q){
        return glch::central_moment(aImage,vCentroid,p,q);
    }
    
    template <class T>
    double Moments::normalized_central_moment(std::vector< PointT<T> > &aPolygon, size_t p, size_t q){
        return glch::normalized_central_moment(aPolygon,vCentroid,p,q);
    }

    template <class T>
    double Moments::normalized_central_moment(MatT<T> &aImage, size_t p, size_t q){
        return glch::normalized_central_moment(aImage,vCentroid,p,q);
    }
    
    template <class T>
    std::vector<double> Moments::hu_moments(std::vector< PointT<T> > &aPolygon){
        return glch::hu_moments(aPolygon,vCentroid);
    }
    
    template <class T>
    std::vector<double> Moments::hu_moments(MatT<T> &aImage){
        return glch::hu_moments(aImage,vCentroid);
    }    
}

#endif	/* MOMENTS_H */

