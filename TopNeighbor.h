/* 
 * File:   TopNeighbor.h
 * Author: brian
 *
 * Created on August 4, 2015, 9:16 AM
 */

#ifndef GLCH_TOPNEIGHBOR_H
#define	GLCH_TOPNEIGHBOR_H

#include "PointT.h"
#include "defines.h"

namespace glch{

    static const int GLCH_NEIGHBOR_X[9] = { 0 ,0, 0,-1, 1,-1, 1,-1, 1};
    static const int GLCH_NEIGHBOR_Y[9] = { 0,-1, 1, 0, 0, 1,-1,-1, 1};
    static const char GLCH_TOP_NEIGHBOR[9] = { 'P', 'E', 'E', 'E', 'E', 'C', 'C', 'C', 'C'};
    static const int GLCH_CW_FOUR_NEIGHBOR_X[4] = { 0, 1, 0,-1};
    static const int GLCH_CW_FOUR_NEIGHBOR_Y[4] = {-1, 0, 1, 0};
    
    struct TopNeighbor{
        uchar  vType;     //What is the component of the digital topology, pixel P, edge E, corner C.
        Point  vPt;  //Where in the topology is this located

        TopNeighbor();
        TopNeighbor(const TopNeighbor& orig);
        TopNeighbor(Point aPt, uchar aType);

        void print(std::string aDelim = ""){
            vPt.print(" | ");
            std::cout << vType << std::endl;
            
        }
        
    };

}

#endif	/* GLCH_TOPNEIGHBOR_H */

