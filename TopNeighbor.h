/* 
 * File:   TopNeighbor.h
 * Author: brian
 *
 * Created on August 4, 2015, 9:16 AM
 */

#ifndef TOPNEIGHBOR_H
#define	TOPNEIGHBOR_H

#include "PointT.h"
#include "defines.h"

namespace glch{

    struct TopNeighbor{
        uchar       vType;     //What is the component of the digital topology, pixel P, edge E, corner C.
        Point               vPt;  //Where in the topology is this located

                                TopNeighbor();
                                TopNeighbor(const TopNeighbor& orig);
                                TopNeighbor(Point aPt, uchar aType);

    };

}

#endif	/* TOPNEIGHBOR_H */

