/* 
 * File:   TopNeighbor.cpp
 * Author: brian
 * 
 * Created on August 4, 2015, 9:16 AM
 */

#include "TopNeighbor.h"

namespace glch{

    TopNeighbor::TopNeighbor(){
    
    }
    
    TopNeighbor::TopNeighbor(const TopNeighbor& orig) : vType(orig.vType), vPt(orig.vPt){
    
    }
    
    TopNeighbor::TopNeighbor(Point aPt, uchar aType){
        vType = aType;
        vPt = aPt;
    }

}