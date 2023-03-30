/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cluster.h
 * Author: brian
 *
 * Created on September 7, 2017, 6:05 PM
 */

#ifndef GLCH_CLUSTER_H
#define GLCH_CLUSTER_H

#include "Moments.h"
#include "PointT.h"
#include "Boundary.h"
#include "ShapeProperties.h"

namespace glch{

void save_boundary_data(std::string aSrcFile, std::string aDstFile, std::string aDstAltFile);

class Cluster {
public:
    Cluster();
    Cluster(const Cluster& orig);
    virtual ~Cluster();
    
    double vArea;
    double vDiameter;
    double vPerimeter;
    double vBRArea;
    double vCorners;
    double vCirc;
    double vFI;
    double vCER;
    double vOrientation;
    double vWaviness;
    double vTopArea;
    double vTopCVXArea;
    double vTopPerim;
    double vTopCVXPerim;
    double vConvexAreaRatio;
    double vMinD;
    double vMaxD;
    double vAreaRatio;
    double vAspectRatio;
    
    Moments vMoment;
    
    std::vector<double> to_vector(){
        return to_string().to_vector<double>();
    }
    
    static AString header(){
        
        AString lRet;
        lRet << "Area";
        lRet << "Minimal_Bounding_Rect_Area";
        lRet << "Diameter";
        lRet << "Perimeter";
        lRet << "Corners";
        lRet << "Circularity_Ratio";
        lRet << "Filament_Ratio";
        lRet << "Corners_Perimeter_Ratio";
        lRet << "Waviness";
        lRet << "Aspect_Ratio";
        lRet << "Minimal_Bounding_Rect_Area_Ratio";
        lRet << "Convex_Area_Ratio";
        lRet << "Orientation";
        lRet << "Centroid_x";
        lRet << "Centroid_y";
        
        for(int i = 0; i < 7; i++){
            lRet << glch::AString("HU%1").arg(i+1);
        }
        
        return lRet;        
        
    }
    
    AString to_string(){
        
        AString lRet;
        
        lRet << vArea;
        lRet << vBRArea;
        lRet << vDiameter;
        lRet << vPerimeter;
        lRet << vCorners;
        lRet << vCirc;
        lRet << vFI;
        lRet << vCER;
        lRet << vWaviness;
        lRet << vAspectRatio;
        lRet << vAreaRatio;
        lRet << vConvexAreaRatio;
        lRet << vOrientation;
        lRet << vMoment.vCentroid.x;
        lRet << vMoment.vCentroid.y;    
        
        for(int i = 0; i < 7; i++){
            lRet << vMoment.vHu.at(i);
        }
        
        return lRet;
    }
    
    void compute_parameters(std::vector<Point>& aCluster){

        
        std::vector<Point> lTP1 = pts_to_toppts(aCluster);
        BoundaryList lTopBound = compute_top_boundary(lTP1);
        Boundary lBL = get_boundary_points(lTP1);

        Boundary lTop = lTopBound.at(0);
        simplify(lTop,1);
        Boundary lCVX = convex_hull_new(lTop);

        vMoment.set_moments(aCluster,10);

        vArea = glch::moment(aCluster,0,0);
        vDiameter = glch::diameter_taxicab(aCluster);
        vPerimeter = 0;
        std::vector<PointF> lBoundingRect = minimal_bounding_rect(aCluster);
        vBRArea = area(lBoundingRect);

        count_top_features(lBL,vPerimeter,vCorners);    

        vCirc = (4*3.14*vArea)/(vPerimeter*vPerimeter);
        vFI = (4*vArea)/(vPerimeter*vDiameter);
        vCER = vCorners/vPerimeter;
        vOrientation = orientation(aCluster);
        vWaviness = perimeter(lTop)/perimeter(lCVX);
        vConvexAreaRatio = area(lTop)/area(lCVX);
        glch::min_max_distances(lCVX,vMinD,vMaxD);
        vAspectRatio = vMinD/vMaxD;
        vAreaRatio = vArea/vBRArea;

        //std::cout << lArea << " : "  << lBRArea << " : " << lDiameter << " : " << lPerimeter << " : " << lCorners << " : " << lCirc << " : " << lFI << " : " << lCER << " : " << lWaviness << " : " << lAspectRatio << " : " << lAreaRatio << " : " << lConvexAreaRatio << " : " << lOrientation << " : " << lMoment.vCentroid.x << " : " << lMoment.vCentroid.y << " : ";    
        //print_vect(lMoment.vHu, " : ");

        //std::cout << std::endl;
    }
    
    bool operator <(Cluster& aCluster){
        return vArea<aCluster.vArea;
    }

    bool operator >(Cluster& aCluster){
        return vArea>aCluster.vArea;
    }

    bool operator ==(Cluster& aCluster){
        return vArea==aCluster.vArea;
    }
    
private:

};

bool cluster_lt(const Cluster& aC1, const Cluster& aC2);

}
#endif /* GLCH_CLUSTER_H */

