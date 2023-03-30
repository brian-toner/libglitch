/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cluster.cpp
 * Author: brian
 * 
 * Created on September 7, 2017, 6:05 PM
 */

#include "Cluster.h"

namespace glch{    

void save_boundary_data(std::string aSrcFile, std::string aDstFile, std::string aDstAltFile){

    glch::MatT<uchar> lCalibSq;
    glch::load_pgm(aSrcFile,lCalibSq);

    std::vector<glch::Point> lMaskPts = glch::mask_to_pts(lCalibSq);
    glch::BoundaryList lClusters = glch::extract_clusters(lMaskPts,4);

    glch::AString lWrite;
    //lWrite.open("testWrite.csv");
    //lWrite << "ahat,bhat,r2,r,sxx,syy,min,max,SSx,SSy,MeanX,MeanY\n";

    
    
    lWrite << glch::ShapeProperties<int>::header();
    lWrite << "pxArea,pxPerimeter\n";

    glch::AString lAltWrite;
    lAltWrite << glch::Cluster::header();
    lAltWrite << "\n";
    
    for(size_t i = 0; i < lClusters.size(); i++){

        glch::BoundaryList lLargeBoundary = glch::compute_large_boundary(lClusters.at(i));
        std::vector<glch::Point> lTop = lLargeBoundary.front();

        glch::BoundaryList lBoundary = glch::large_to_small_boundary(lLargeBoundary);

        std::vector<glch::Point> lBdy = lBoundary.front();

        
        
        glch::ShapeProperties<int> lTopSP;
        lTopSP.initialize(lTop);

        lWrite << lTopSP.to_string();
        lWrite << lClusters.at(i).size();
        lWrite << lBdy.size();
        lWrite << "\n";
        
        Cluster lClust;
        lClust.compute_parameters(lClusters.at(i));
        lAltWrite << lClust.to_string();
        lAltWrite << "\n";
    }


    glch::save_text_file(aDstFile,lWrite);
    glch::save_text_file(aDstAltFile,lAltWrite);
    
    
    
}
    
Cluster::Cluster() {
}

Cluster::Cluster(const Cluster& orig) :     
                        vArea(orig.vArea),
                        vDiameter(orig.vDiameter),
                        vPerimeter(orig.vPerimeter),
                        vBRArea(orig.vBRArea),
                        vCorners(orig.vCorners),
                        vCirc(orig.vCirc),
                        vFI(orig.vFI),
                        vCER(orig.vCER),
                        vOrientation(orig.vOrientation),
                        vWaviness(orig.vWaviness),
                        vTopArea(orig.vTopArea),
                        vTopCVXArea(orig.vTopCVXArea),
                        vTopPerim(orig.vTopPerim),
                        vTopCVXPerim(orig.vTopCVXPerim),
                        vConvexAreaRatio(orig.vConvexAreaRatio),
                        vMinD(orig.vMinD),
                        vMaxD(orig.vMaxD),
                        vAreaRatio(orig.vAreaRatio),
                        vAspectRatio(orig.vAspectRatio),
                        vMoment(orig.vMoment) {
}

Cluster::~Cluster() {
}

bool cluster_lt(const Cluster& aC1, const Cluster& aC2){
    return aC1.vArea<aC2.vArea;
}

}