/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ImgClusters.h
 * Author: brian
 *
 * Created on September 8, 2017, 9:16 AM
 */

#ifndef GLCH_IMG_CLUSTERS_H
#define GLCH_IMG_CLUSTERS_H

#include <vector>
#include <bits/algorithmfwd.h>
#include "Cluster.h"

namespace glch{

class ImgClusters {
public:
    ImgClusters();
    ImgClusters(const ImgClusters& orig);
    virtual ~ImgClusters();

    std::vector<Cluster> vClusters;
    
    void analyze_image(MatT<uchar> aMask, size_t aNumbNeighbors = 8){
        
        BoundaryList lClusters = glch::extract_clusters(aMask,aNumbNeighbors);
        vClusters.resize(lClusters.size());
        
        for(size_t i = 0; i < lClusters.size(); i++){
            vClusters.at(i).compute_parameters(lClusters.at(i));
        }
        
        std::sort(vClusters.begin(),vClusters.end(),cluster_lt);
        
    }
    
    void print(){
        
        for(size_t i = 0; i < vClusters.size(); i++){
            std::cout << vClusters.at(i).to_string() << std::endl;
        }
    }
    
private:

};

}

#endif /* GLCH_IMG_CLUSTERS_H */

