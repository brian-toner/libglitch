/* 
 * File:   Boundary.cpp
 * Author: brian
 * 
 * Created on February 2, 2016, 7:14 PM
 */

#include "Boundary.h"


namespace glch{


    int get_offset(std::vector<Point> &aDst, int aExcludeCol, int aExcludeRow, bool aEightNeighbors){
        aDst.clear();

        std::vector<Point> lOffset;
        int lNumbNeighbors = 4;

        lOffset.push_back( Point(-1,0) );
        lOffset.push_back( Point(0,-1) );
        lOffset.push_back( Point(0,1) );
        lOffset.push_back( Point(1,0) );

        if(aEightNeighbors){
            lNumbNeighbors = 8;
            lOffset.push_back( Point(-1,-1) );
            lOffset.push_back( Point(-1,1) );
            lOffset.push_back( Point(1,-1) );
            lOffset.push_back( Point(1, 1) );
        }


        for(std::vector<Point>::iterator it = lOffset.begin(); it < lOffset.end(); it++){
            bool lCopy = true;
            if( ((*it).x == aExcludeCol) || ((*it).y == aExcludeRow) ){
                lNumbNeighbors --;
                lCopy = false;
            }


            if(lCopy){
                aDst.push_back( (*it) );
            }

        }

        return lNumbNeighbors;
    }


    

    

    void get_topology(Point aPixel, std::vector<TopNeighbor> &aTopology){
        if(aTopology.size() < 9){
            aTopology.resize(9);
        }

        aTopology.at(0) = TopNeighbor(Point(aPixel.x-1, aPixel.y-1), 'C');
        aTopology.at(1) = TopNeighbor(Point(aPixel.x, aPixel.y-1), 'E');
        aTopology.at(2) = TopNeighbor(Point(aPixel.x+1, aPixel.y-1), 'C');

        aTopology.at(3) = TopNeighbor(Point(aPixel.x-1, aPixel.y), 'E');
        aTopology.at(4) = TopNeighbor(Point(aPixel.x, aPixel.y), 'P');
        aTopology.at(5) = TopNeighbor(Point(aPixel.x+1, aPixel.y), 'E');

        aTopology.at(6) = TopNeighbor(Point(aPixel.x-1, aPixel.y+1), 'C');
        aTopology.at(7) = TopNeighbor(Point(aPixel.x, aPixel.y+1), 'E');
        aTopology.at(8) = TopNeighbor(Point(aPixel.x+1, aPixel.y+1), 'C');

    }

    std::vector<Point> get_neighbors(Point aElement, Rect aBoundary, bool aEightNeighbors){
        int r = aElement.y;
        int c = aElement.x;
        std::vector<Point> lOffset;

        int lLeft = aBoundary.x;
        int lRight = aBoundary.width-1;
        int lTop = aBoundary.y;
        int lBottom = aBoundary.height-1;

        if( (r == lTop) && (c == lLeft) ){
            get_offset(lOffset, -1, -1, aEightNeighbors);
        } else if ( (r == lTop) && (c == lRight) ){
            get_offset(lOffset, 1, -1, aEightNeighbors);
        } else if ( (r == lBottom) && (c == lLeft) ){
            get_offset(lOffset, -1, 1, aEightNeighbors);
        } else if ( (r == lBottom) && (c == lRight) ){ 
            get_offset(lOffset, 1, 1, aEightNeighbors);
        } else if ( (r == lTop) ){
            get_offset(lOffset, -2, -1, aEightNeighbors);
        } else if ( (r == lBottom) ){
            get_offset(lOffset, -2, 1, aEightNeighbors);
        } else if ( (c == lLeft) ){
            get_offset(lOffset, -1, -2, aEightNeighbors);
        } else if ( (c == lRight) ){
            get_offset(lOffset, 1, -2, aEightNeighbors);
        } else {
            get_offset(lOffset, -2, -2, aEightNeighbors);
        }

        for(std::vector<Point>::iterator it = lOffset.begin(); it != lOffset.end(); it++){

            (*it).x += c;
            (*it).y += r;
        }

        return lOffset;
    }

    std::vector<Point> boundary_to_topboundary(std::vector<Point> &aBoundary){

        MatT<uchar> lSrc;
        int lMaxX = 0;
        int lMaxY = 0;
        std::vector< std::vector<Point> > lBoundary;
        std::vector< std::vector<Point> > lTopBoundary;

        for(std::vector<Point>::iterator it = aBoundary.begin(); it != aBoundary.end(); it++){
            if( (*it).x > lMaxX){
                lMaxX = (*it).x;
            }

            if( (*it).y > lMaxY){
                lMaxY = (*it).y;
            }
        }

        lSrc = MatT<uchar>(lMaxY+2,lMaxX+2,  1); //Type uchar
        lSrc.zero();
        MatT<uchar> lImTopBoundary = MatT<uchar>( (lMaxY+1)*3, (lMaxX+1)*3,  1); //Type uchar
        lImTopBoundary.zero();

        draw_boundary(aBoundary,lSrc);

        compute_all_boundaries(lSrc,lBoundary,lTopBoundary);

        return lTopBoundary.at(0);

    }      
    
    bool point_in_boundary(Point aPoint, std::vector<Point> &aBoundary, std::vector<Point> &aTopBoundary){

        if(aTopBoundary.size() > 0){
            Point lPoint;
            if(aBoundary.size() == aTopBoundary.size()){
                lPoint = aPoint;
            } else {
                lPoint = Point(aPoint.x*3,aPoint.y*3);
            }
            
            return point_in_top_boundary(lPoint, aTopBoundary);
        }

        aTopBoundary = boundary_to_topboundary(aBoundary);

        return point_in_top_boundary(Point(aPoint.x*3,aPoint.y*3), aTopBoundary);

    }

    void filter_internal_boundaries(BoundaryList &aBoundary, BoundaryList &aTopBoundary){
        BoundaryList lBoundary;
        BoundaryList lTopBoundary;

        for(BoundaryList::iterator it = aTopBoundary.begin(); it != aTopBoundary.end(); it++){
            bool lInternalBoundary = false;
            size_t lIndex = (it - aTopBoundary.begin());

            for(BoundaryList::iterator itj = aTopBoundary.begin(); itj != aTopBoundary.end(); itj++){
                if(it == itj){
                    break;
                }

                lInternalBoundary = point_in_top_boundary( (*itj).front() , (*it));

                if(lInternalBoundary){
                    break;
                }
            }

            if(!lInternalBoundary){
                lBoundary.push_back( aBoundary.at(lIndex) );
                lTopBoundary.push_back( aTopBoundary.at(lIndex) );
            }  
        }

        aBoundary = lBoundary;
        aTopBoundary = lTopBoundary;    

    }


    bool point_in_top_boundary(Point aPoint, std::vector<Point> &aBoundary){

        std::vector<Point> lLeftRay;

        for(std::vector<Point>::iterator it = aBoundary.begin(); it != aBoundary.end(); it++){

            //We can specify if 
            //if( (*it).x == aPoint.x && (*it).y == aPoint.y ){
            //    return true;
            //}

            if( (*it).y == aPoint.y ){
                if( (*it).x < aPoint.x ){

                    std::vector<Point>::iterator lSlopeBeginIt = (it);
                    std::vector<Point>::iterator lSlopeEndIt = (it);

                    bool lExitCalc = false;  //Lets us know when we went past the last element


                    //we may start on a flat bit, in which case we have to trace backwards
                    while( (*lSlopeBeginIt).y == (*it).y ){
                        //get_last(lSlopeBeginIt,aBoundary);

                        if(lSlopeBeginIt == aBoundary.begin()){
                            lSlopeBeginIt = aBoundary.end()-1;
                            //lExitCalc = true;
                        } else{
                            lSlopeBeginIt--;
                        }
                    }

                    float lSlope1 = ((*(lSlopeBeginIt+1) ).y - (*lSlopeBeginIt).y);

                    //Tracing forward to find the slope at the end
                    while( (*lSlopeEndIt).y == (*it).y ){
                        //lExitCalc = get_next(lSlopeEndIt,aBoundary);

                        if(lSlopeEndIt+1 == aBoundary.end()){
                            lSlopeEndIt = aBoundary.begin();
                            lExitCalc = true;
                        } else{
                            lSlopeEndIt++;
                        }
                    }

                    float lSlope2 = ((*lSlopeEndIt).y - (*(lSlopeEndIt-1)).y);


                    if( (lSlope2 > 0 && lSlope1 > 0) || (lSlope2 < 0 && lSlope1 < 0) ){
                        lLeftRay.push_back( (*it) );

                    }

                    if(lExitCalc){
                        it = aBoundary.end()-1;
                    } else {
                        it = lSlopeEndIt;
                    }
                }
            }      
        }

        if( lLeftRay.size() == 0){
            return false;
        }

        if( lLeftRay.size() == 1){
            return true;
        }

        lLeftRay = filter_points(lLeftRay);

        if( lLeftRay.size() % 2 == 0){
            return false;
        } else {
            return true;
        }


    }

    std::vector<Point> filter_points(std::vector<Point> aPts){

        std::vector<bool> lCopyPts;
        std::vector<Point> lNewPts;
        lCopyPts.resize( aPts.size(), true );

        for(std::vector<Point>::iterator iti = aPts.begin(); iti != aPts.end()-1; iti++){
            size_t lIndex = (iti - aPts.begin() ) + 1;

            std::vector<Point>::iterator lNext = (iti+1);
            for(std::vector<Point>::iterator itj = lNext; itj != aPts.end(); itj++, lIndex++){

                if( (*iti).x == (*itj).x+1 || (*iti).x == (*itj).x-1){
                    lCopyPts.at(lIndex) = false;
                }

            }

        }

        for(size_t i = 0; i < lCopyPts.size(); i++){
            if( lCopyPts.at(i) ){
                lNewPts.push_back( aPts.at(i) );
            }
        }

        return lNewPts;
    }

    void draw_boundary(std::vector<Point> &aSrc, MatT<uchar> &aDst){

        draw_points(aDst,aSrc,255);

    }
    
    void draw_boundary(MatT<uchar> &aSrc, MatT<uchar> &aDst, bool aEightNeighbors){

        aDst = aSrc;
        aDst.zero();

        std::vector<Point> lBoundary = find_boundary(aSrc, aEightNeighbors);
        draw_points(aDst,lBoundary,255);
  
    }
}