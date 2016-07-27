/* 
 * File:   Boundary.h
 * Author: brian
 *
 * Created on February 2, 2016, 7:14 PM
 */

#ifndef BOUNDARY_H
#define	BOUNDARY_H

#include <vector>
#include "PointT.h"
#include "MatT.h"
#include "TopNeighbor.h"
#include "MatTFunctions.h"
#include "ScalarT.h"
#include "PolygonFunctions.h"

namespace glch{

    typedef std::vector< Point > Boundary;
    typedef std::vector< std::vector<Point> > BoundaryList;

    int get_offset(std::vector<Point> &aDst, int aExcludeCol, int aExcludeRow, bool aEightNeighbors);
    void get_topology(Point aPixel, std::vector<TopNeighbor> &aTopology);
    std::vector<Point> get_neighbors(Point aElement, Rect aBoundary, bool aEightNeighbors);
    std::vector<Point> boundary_to_topboundary(std::vector<Point> &aBoundary);
    bool point_in_boundary(Point aPoint, std::vector<Point> &aBoundary, std::vector<Point> &aTopBoundary);
    void filter_internal_boundaries(BoundaryList &aBoundary, BoundaryList &aTopBoundary);
    bool point_in_top_boundary(Point aPoint, std::vector<Point> &aBoundary);
    std::vector<Point> filter_points(std::vector<Point> aPts);
    void draw_boundary(std::vector<Point> &aSrc, MatT<uchar> &aDst);
    void draw_boundary(MatT<uchar> &aSrc, MatT<uchar> &aDst, bool aEightNeighbors = false);
    
    template <class T>
    std::vector<Point> find_boundary(MatT<T> &aInput, bool aEightNeighbors){

        std::vector<Point> lRet;

        std::vector<Point> lOffset;

        std::vector<Point> lOffsetC;
        std::vector<Point> lOffsetL;
        std::vector<Point> lOffsetR;
        std::vector<Point> lOffsetT;
        std::vector<Point> lOffsetB;

        std::vector<Point> lOffsetTL;
        std::vector<Point> lOffsetTR;
        std::vector<Point> lOffsetBL;
        std::vector<Point> lOffsetBR;

        //int lNumbNeighbors = 4;
        int lCount = 0;

        //lNumbNeighbors = get_offset(lOffsetC, -2, -2, aEightNeighbors);
        get_offset(lOffsetC, -2, -2, aEightNeighbors);
        get_offset(lOffsetTL, -1, -1, aEightNeighbors);
        get_offset(lOffsetTR, 1, -1, aEightNeighbors);
        get_offset(lOffsetBL, -1, 1, aEightNeighbors);
        get_offset(lOffsetBR, 1, 1, aEightNeighbors);

        get_offset(lOffsetT, -2, -1, aEightNeighbors);
        get_offset(lOffsetB, -2, 1, aEightNeighbors);
        get_offset(lOffsetL, -1, -2, aEightNeighbors);
        get_offset(lOffsetR, 1, -2, aEightNeighbors);



        for(size_t r = 0; r < aInput.rows; r++){
            for(size_t c = 0; c < aInput.cols; c++){

                lCount = 0;

                if(aInput.at(c, r) == 0){
                    continue;
                }

                if( (r == 0) && (c == 0) ){
                    lOffset = lOffsetTL;
                } else if ( (r == 0) && (c == aInput.cols-1) ){
                    lOffset = lOffsetTR;
                } else if ( (r == aInput.rows-1) && (c == 0) ){
                    lOffset = lOffsetBL;
                } else if ( (r == aInput.rows-1) && (c == aInput.cols-1) ){ 
                    lOffset = lOffsetBR;
                } else if ( (r == 0) ){
                    lOffset = lOffsetT;
                } else if ( (r == aInput.rows-1) ){
                    lOffset = lOffsetB;
                } else if ( (c == 0) ){
                    lOffset = lOffsetL;
                } else if ( (c == aInput.cols-1) ){
                    lOffset = lOffsetR;
                } else {
                    lOffset = lOffsetC;
                }

                //lNumbNeighbors = lOffset.size();

                for(std::vector<Point>::iterator it = lOffset.begin(); it < lOffset.end(); it++){

                    if( aInput.at(c + (*it).x, r + (*it).y) == 0){
                        lCount++;
                    }

                }

                if( (lCount > 0) ){    
                    lRet.push_back( Point(c,r) );
                }

            }
        }

        return lRet;
    }

    
    
    template <class T>
    std::vector< std::vector<Point> > find_split_boundary(MatT<T> &aInput, bool aEightNeighbors){
        std::vector< std::vector<Point> > lRet;
        MatT<T> lDrawn;
        draw_boundary(aInput, lDrawn, true);
        glch::save_pgm("./lDrawn.pgm",lDrawn);
        
        for(size_t r = 0; r < lDrawn.rows; r++){
            for(size_t c = 0; c < lDrawn.cols; c++){

                uchar &lPt = lDrawn.at(c,r);

                if(lPt == 0){
                    continue;
                } else {
                    //cout << Point(c,r) << endl;
                    std::vector<Point> lBoundary = trace_boundary(lDrawn, Point(c,r), aEightNeighbors);
                    lRet.push_back(lBoundary);
                } 
            }
        }

        return lRet;

    }

    template <class T>
    std::vector<Point> trace_boundary(MatT<T> &aInput, Point aStart, bool aEightNeighbors){

        //Rect lBoundary = Rect(0,0,aInput.cols,aInput.rows);
        std::vector<Point> lNeighbors = get_nonempty_neighbors(aInput, aStart, aEightNeighbors);
        std::vector<Point> lRet;
        lRet.push_back(aStart);

        Point lPt = aStart;

        while(lNeighbors.size() > 0){
            //Find the nearest non empty neighbor

            aInput.at(lPt) = 0;
            int i = 0;
            std::vector<float> lDist = find_distances(lPt, lNeighbors);
            int lLeastElement = 0;
            float lDistance = 0;
            if(lDist.size() > 0){
                lDistance = lDist.at(0);
            } else {
                break;
            }

            for(std::vector<float>::iterator it = lDist.begin(); it != lDist.end(); it++, i++){
                if( (*it) < lDistance){
                    lDistance = (*it);
                    lLeastElement = i;
                }
            }

            lPt = lNeighbors.at(lLeastElement);

            lNeighbors = get_nonempty_neighbors(aInput, lPt, aEightNeighbors);
            lRet.push_back(lPt);
        }

        aInput.at(lPt) = 0;

        return lRet;

    }
    
    
    template <class T>
    std::vector<Point> get_nonempty_neighbors(MatT<T> &aInput, Point aElement, bool aEightNeighbors){
        Rect lBoundary = Rect(0,0,aInput.cols,aInput.rows);
        std::vector<Point> lNeighbors = get_neighbors(aElement, lBoundary, aEightNeighbors);
        remove_empty_neighbors(aInput,lNeighbors);


        return lNeighbors;
    }

    template <class T>
    void remove_empty_neighbors(MatT<T> &aBoundary, std::vector<Point> &aNeighbors){
        std::vector<Point> lRet;

        for(std::vector<Point>::iterator it = aNeighbors.begin(); it != aNeighbors.end(); it++){
            if( aBoundary.at( (*it) ) == 255){
                lRet.push_back( (*it) );
            }
        }

        aNeighbors = lRet;

    }
    

    template <class T>
    void compute_all_boundaries(MatT<T> aInput, std::vector< std::vector<Point> > &aBoundary, std::vector< std::vector<Point> > &aTopBoundary){

        //Resize the image to be 3 times as large, so we can use the digital plane topology
        MatT<T> lInputLg;
        MatT<uchar> lTypes;
        MatT<double> lElements(aInput.rows*3, aInput.cols*3 );

        glch::scale_mat_size(aInput,lInputLg,3,3);
        //om::save_pgm("./resized.pgm",lInputLg);
        lTypes = lInputLg;

        lElements.zero();
        
        std::vector< std::vector<Point> > lTopBoundarys;
        lTopBoundarys = find_split_boundary(lInputLg, true);
        std::vector< std::vector<Point> > lBoundarys;
        lBoundarys.resize( lTopBoundarys.size() );

        int lCols = aInput.cols;

        int lRowsLg = lInputLg.rows;
        int lColsLg = lInputLg.cols;

        std::vector<TopNeighbor> lNeighbors;
        int index = 0;

        //Moving through all the elements and finding the topology
        for(int r = 1; r < lRowsLg; r += 3){
            for(int c = 1; c < lColsLg; c += 3, index++){

                get_topology(Point(c,r), lNeighbors);

                for(std::vector<TopNeighbor>::iterator it = lNeighbors.begin(); it != lNeighbors.end(); it++){
                    lElements.at( (*it).vPt ) = (double)index;
                    lTypes.at( (*it).vPt ) = (*it).vType;

                }
            }  
        }  

        //Mapping the topological boundary back to the pixels.
        for(size_t i = 0; i < lTopBoundarys.size(); i++){

            for(std::vector<Point>::iterator it = lTopBoundarys.at(i).begin(); it != lTopBoundarys.at(i).end(); it++){
                int lIndex = lElements.at( (*it) );
                int lYCoord = lIndex/lCols;
                int lXCoord = lIndex%lCols;

                Point lPixel = Point( lXCoord, lYCoord );

                lBoundarys.at(i).push_back(lPixel);
            }

        }

        //Removing duplicates from the list
        for(std::vector< std::vector<Point> >::iterator it = lBoundarys.begin(); it != lBoundarys.end(); it++){

            std::vector<Point>::iterator itj = (*it).begin();
            while(itj != (*it).end()-1){

                if( (*itj) == (*(itj+1) ) ){
                    (*it).erase( (itj+1) );      
                } else {
                    itj++;
                }

            }

            if( (*it).front() == (*it).back() ){
                (*it).erase( (*it).end()-1 );
            }
        }

        aTopBoundary = lTopBoundarys;
        aBoundary = lBoundarys;

    }

     
    

    template <class T>
    void erode_edge(MatT<T> &aSrc, MatT<T> &aDst, bool aEightNeighbors){

        std::vector<Point> lEdge = find_boundary(aSrc, aEightNeighbors);
        aDst = aSrc;

        for(std::vector<Point>::iterator it = lEdge.begin(); it < lEdge.end(); it++){
            aDst.at((*it)) = 0;
        }

    }
     
    
    template <class T>
    std::vector<Point> find_edge(MatT<T> &aInput, bool aEightNeighbors){

        std::vector<Point> lRet;
        std::vector<Point> lOffset;

        lOffset.push_back( Point(-1,0) );
        lOffset.push_back( Point(0,-1) );
        lOffset.push_back( Point(0,1) );
        lOffset.push_back( Point(1,0) );

        if(aEightNeighbors){
            lOffset.push_back( Point(-1,-1) );
            lOffset.push_back( Point(-1,1) );
            lOffset.push_back( Point(1,-1) );
            lOffset.push_back( Point(1, 1) );
        }

        for(int r = 0; r < aInput.rows; r++){
            for(int c = 0; c < aInput.cols; c++){

                for(std::vector<Point>::iterator it = lOffset.begin(); it < lOffset.end(); it++){
                    int lCount = 0;

                    if( aInput.at(c + (*it).x, r + (*it).y) == 0){
                        lRet.push_back( Point(c,r) );
                        break;
                    }
                }

            }
        }

        return lRet;
    }


    template <class T>
    void count_nonzero_3c(MatT<T> &aSrc, std::vector<int> &aDst){
        aDst.clear();
        aDst.resize(3,0);

        for(int r = 0; r < aSrc.rows; r++){
            for(int c = 0; c < aSrc.cols; c++){
                for(int i = 0; i < 3; i++){
                    if(aSrc.at(c,r)[i] != 0){
                        aDst.at(i) ++;
                    };
                }
            }
        }

    }


    
}



#endif	/* BOUNDARY_H */

