/* 
 * File:   Boundary.cpp
 * Author: brian
 * 
 * Created on February 2, 2016, 7:14 PM
 */

#include <set>

#include "Boundary.h"


namespace glch{


    int get_offset(std::vector<Point> &aDst, int aExcludeCol, int aExcludeRow, bool aEightNeighbors){
        aDst.clear();

        std::vector<Point> lOffset;
        int lNumbNeighbors = 4;

        //lOffset.push_back( Point(-1,0) );
        //lOffset.push_back( Point(0,-1) );
        //lOffset.push_back( Point(0,1) );
        //lOffset.push_back( Point(1,0) );

        if(aEightNeighbors){
            lNumbNeighbors = 8;
            //lOffset.push_back( Point(-1,-1) );
            //lOffset.push_back( Point(-1,1) );
            //lOffset.push_back( Point(1,-1) );
            //lOffset.push_back( Point(1, 1) );
        }

        lOffset = get_neighbors(Point(0,0),lNumbNeighbors,false);
        
        
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
    
    
    
    
    //===================================================//
    // Revised
    //===================================================//
    
    
    std::vector<Point> get_boundary_points(MatT<uchar>& aMask){
        
        std::vector<Point> lRet;
        
        for(size_t r = 0; r < aMask.rows; r++){
            for(size_t c = 0; c < aMask.cols; c++){
                Point lTemp = Point(c,r);
                
                if(is_boundary_point(lTemp, aMask)){
                    lRet.push_back(lTemp);
                }
                
            }
        }
        
        return lRet;
    }
    
    std::vector<Point> get_boundary_points(std::vector<Point>& aPoints){
        
        std::vector<Point> lRet;
        Rect lROI = glch::bounding_rect(aPoints);
  
        for(size_t i = 0; i < aPoints.size(); i++){
            
            Point lTemp = aPoints.at(i);

            if(is_boundary_point(lTemp, aPoints,lROI)){
                lRet.push_back(lTemp);
            }
                            
            
        }
        
        return lRet;
    }    
    
    
    std::vector<TopNeighbor> get_pixel_topology(Point aPixel){
        
        std::vector<TopNeighbor> lRet(9);
        
        for(size_t i = 0; i < 9; i++){
            lRet.at(i) = TopNeighbor(Point(aPixel.x+GLCH_NEIGHBOR_X[i],aPixel.y+GLCH_NEIGHBOR_Y[i]), GLCH_TOP_NEIGHBOR[i]);
        }
        
        return lRet;
    }    
    
    size_t get_next_point(Point aPt, std::vector<Point>& aPts){
        
        bool lContinue = true;
        size_t lRet = GLCH_NOT_FOUND;
        
        for(size_t i = 0; lContinue && i < 4; i++){
            Point lPoint = Point(aPt.x + GLCH_CW_FOUR_NEIGHBOR_X[i], aPt.y + GLCH_CW_FOUR_NEIGHBOR_Y[i]);
            size_t lTmpIndex = glch::index_of(aPts,lPoint);

            if(lTmpIndex != GLCH_NOT_FOUND){
                lRet = lTmpIndex;
                lContinue = false;
            }
        }
            
        return lRet;
    }
    
    Point fix_parent_point(Point aPt){     
        return Point((aPt.x-1)/3,(aPt.y-1)/3);   
    }
    
    Point find_parent_point(Point aSearch){
        
        int lMap[3] = { 1, 0,-1};
        
        int lOrigCol = aSearch.x%3;
        int lOrigRow = aSearch.y%3;
        
        Point lRet;
        
        lRet.x = aSearch.x+lMap[lOrigCol];
        lRet.y = aSearch.y+lMap[lOrigRow];
        
        return lRet;
    }

    std::vector<Point> find_children_point(Point aSearch){
        return get_neighbors(Point(aSearch.x*3+1,aSearch.y*3+1),8,true);
        
    }
    
    std::vector<Point> find_top_children(Point aSearch){
        return get_neighbors(Point(aSearch.x*2+1,aSearch.y*2+1),8,true);
    }
    
    

    
    Point extract_boundary_points(Point aSearch, Boundary& aBoundary){
        
        Point lRet = find_parent_point(aSearch);
        std::vector<Point> lNeighbors = get_neighbors(lRet,8,true);
        
        for(size_t i = 0; i < lNeighbors.size(); i++){
            size_t lIndex = glch::index_of(aBoundary,lNeighbors.at(i));
            
            if(lIndex != GLCH_NOT_FOUND){
                aBoundary.erase(aBoundary.begin()+lIndex);
            }
            
        }
        
        lRet = fix_parent_point(lRet);
        
        return lRet;
        
    }

    
    Boundary small_to_large_boundary(Boundary& aSmBoundary){
        
        Boundary lPixels = pts_to_lgpts(aSmBoundary);
        //Boundary lBoundaryPts = get_boundary_points(lPixels);
        BoundaryList lBoundaries = compute_boundary(lPixels); //trace_boundary(lBoundaryPts);
        
        size_t lMaxSize = 0;
        size_t lMaxIndex = 0;

        if(lBoundaries.size() > 1){
            lMaxSize = lBoundaries.front().size();
            lMaxIndex = 0;
            
            for(size_t i = 1; i < lBoundaries.size(); i++){
                if(lBoundaries.at(i).size() > lMaxSize){
                    lMaxSize = lBoundaries.at(i).size();
                    lMaxIndex = 1;
                }
            }
            
        }
        
        return lBoundaries.at(lMaxIndex);
        
    }
    
    BoundaryList large_to_small_boundary(BoundaryList& aLgBoundary){
        
        BoundaryList lRet(aLgBoundary.size());
        
        for(size_t i = 0; i < aLgBoundary.size(); i++){
            
            while(aLgBoundary.at(i).size() > 0){
                Point lPt = aLgBoundary.at(i).front();
                Point lNewPt = extract_boundary_points(lPt,aLgBoundary.at(i));
                
                lRet.at(i).push_back(lNewPt);
            }
            
        }
        
        return lRet;
        
        
    }

    
    BoundaryList compute_small_boundary(MatT<uchar>& aMask){
        
        BoundaryList lLgBoundary = compute_large_boundary(aMask);
        return large_to_small_boundary(lLgBoundary);
        
    }

    BoundaryList compute_small_boundary(std::vector<Point>& aMaskSet){
        
        std::vector<Point> lBP = get_boundary_points(aMaskSet);
        BoundaryList lLgBoundary = compute_large_boundary(lBP);
        return large_to_small_boundary(lLgBoundary);
        
    }
    
    /**
     * Converts a mask into a set of points.  This is done by scanning over the
     * rows and columns of the mask and finding any non-zero points.  These points
     * are then pushed into the vector.
     * @param aMask The mask to convert.
     * @return A list of the non-zero pixels in the mask.
     */
    std::vector<Point> mask_to_pts(MatT<uchar>& aMask){
        
        std::vector<Point> lRet;
        
        for(size_t r = 0; r < aMask.rows; r++){
            for(size_t c = 0; c < aMask.cols; c++){
                Point lPt = Point(c,r);
                
                if( aMask.at(lPt) ){
                    lRet.push_back(lPt);
                }
            }
        }
        
        return lRet;        
    }
    
    std::vector<Point> pts_to_toppts(std::vector<Point>& aPts){
        std::vector<Point> lPixels;
        
        for(size_t i = 0; i < aPts.size(); i++){
            Boundary lNewPts = find_top_children(aPts.at(i));
            for(size_t j = 0; j < lNewPts.size(); j++){
                size_t lIndex = glch::index_of(lPixels,lNewPts.at(j));
                
                if(lIndex == GLCH_NOT_FOUND){
                    lPixels.push_back(lNewPts.at(j));
                }
            }

        }
              
        return lPixels;        
    }
    
    std::vector<Point> pts_to_lgpts(std::vector<Point>& aPts){
        std::vector<Point> lPixels;
        
        for(size_t i = 0; i < aPts.size(); i++){
            Boundary lNewPts = find_children_point(aPts.at(i));
            lPixels.insert(lPixels.end(),lNewPts.begin(),lNewPts.end());
        }
              
        return lPixels;
    }
    
    BoundaryList compute_boundary(glch::MatT<unsigned char> aMask){
        
        glch::MatT<unsigned char> lMaskLG(aMask.rows*3,aMask.cols*3);

        glch::scale_mat_size(aMask,lMaskLG,3,3);

        //Get the boundary points on the Mat.
        glch::MatT<unsigned char> lMaskLGBdr = lMaskLG;
        for(int r = 1; r < lMaskLG.rows-1; r++){
            for(int c = 1; c < lMaskLG.cols-1; c++){

                bool lInterior = ((lMaskLG.at_no_wrap(c-1,r-1)>0)+
                                 (lMaskLG.at_no_wrap(c-1,r)>0)+
                                 (lMaskLG.at_no_wrap(c-1,r+1)>0)+
                                 (lMaskLG.at_no_wrap(c,r-1)>0)+
                                 (lMaskLG.at_no_wrap(c,r+1)>0)+
                                 (lMaskLG.at_no_wrap(c+1,r-1)>0)+
                                 (lMaskLG.at_no_wrap(c+1,r)>0)+
                                 (lMaskLG.at_no_wrap(c+1,r+1)>0))==8;
                if(lInterior){
                    lMaskLGBdr.at(glch::Point(c,r)) = 0;
                }

            }
        }

        //Extract the boundary points from the image.
        std::vector<glch::Point> lBoundary;
        for(int r = 0; r < lMaskLGBdr.rows; r++){
            for(int c = 0; c < lMaskLGBdr.cols; c++){
                glch::Point lPt(c,r);
                if(lMaskLGBdr.at(lPt)>0){
                    lBoundary.push_back(lPt);
                }
            }
        }
        
        glch::BoundaryList lBoundaries = trace_boundary(lBoundary,lMaskLG.cols);
        glch::BoundaryList lSmBoundaries = glch::large_to_small_boundary(lBoundaries);
        
        return lSmBoundaries;
    }
    
    /**
     * Computes the boundary of the list of points.  This is done by finding
     * the boundary points and then tracing the boundary.
     * @param aPts The points to find the boundary(s) of.
     * @return A list of points in an acceptable format to trace the boundary of.
     */
    BoundaryList compute_boundary(std::vector<Point>& aPts){
        //std::cout << "Test" << 611 << std::endl;
        std::vector<Point> lBoundary = get_boundary_points(aPts);
        //std::cout << "Test" << 613 << std::endl;
        return trace_boundary(lBoundary);        
    }
    
    /**
     * 
     * @param aMaskSet
     * @return 
     */
    BoundaryList compute_large_boundary(std::vector<Point>& aMaskSet){
        
        std::vector<Point> lPixels = pts_to_lgpts(aMaskSet);
        return compute_boundary(lPixels);
    }

    /**
     * Extracts the clusters from a mask image.  This is done by first turning
     * the mask into a vector of points (mask_to_pts) and then extracting the
     * clusters from this vector.
     * @param aSrc The mask to locate and extract the clusters from.
     * @return A set of clusters.
     */
    BoundaryList extract_clusters(MatT<uchar> aSrc, size_t aNumbNeighbors = 4){
        
        std::vector<Point> lMaskPts = mask_to_pts(aSrc);
        return extract_clusters(lMaskPts, aNumbNeighbors);
        
    }
    
    /**
     * Groups the list of points in aPts into their associated cluster groups.
     * Here we take a list of points and we find out which points are associated
     * with which mask.  These mask points then can be analyzed as desired. 
     * @param aPts The list of ungrouped points.
     * @return A set of clusters.
     */
    BoundaryList extract_clusters(std::vector<Point>& aPts, size_t aNumbNeighbors = 4){
        
        std::vector<Point> lPts = aPts;
        BoundaryList lRet;
        
        while(lPts.size() > 0){
            
            std::vector<Point> lDst;
            Point lPt = lPts.front();
            recurse_group_pts(lPt,lPts,lDst,aNumbNeighbors);
            
            lRet.push_back(lDst);
            
        }
        
        return lRet;
    }
    
    /**
     * This function recursively finds all of the points associated with a mask.
     * This is essentially a rudimentary flood fill algorithm that only finds
     * the nearest 4 neighbors.  Those 4 neighbors are then used to make the next
     * recursive call until automagically all the points associated with the mask
     * are located and placed in the dst vector.
     * @param aStPt The starting point to search for neighbors.
     * @param aSrc The source list of points (Will be altered!)
     * @param aDst The destination list of points (Will also be altered!)
     */
    void recurse_group_pts(Point aStPt, std::vector<Point>& aSrc, std::vector<Point>& aDst, size_t aNumbNeighbors){
        
        size_t lSrcIndex = glch::index_of(aSrc,aStPt);

        if( (lSrcIndex != GLCH_NOT_FOUND) ){
            size_t lDstIndex = glch::index_of(aDst,aStPt);

            if( (lDstIndex == GLCH_NOT_FOUND) ){
                aDst.push_back(aStPt);
                aSrc.erase(aSrc.begin()+lSrcIndex);
                
                std::vector<Point> lNeighbors = get_neighbors(aStPt,aNumbNeighbors,false);
            
                for(size_t i = 0; i < lNeighbors.size(); i++){
                    recurse_group_pts(lNeighbors.at(i), aSrc, aDst,aNumbNeighbors);
                }
                
            }
            
        }
        
        
    }
    
    BoundaryList compute_large_boundary(MatT<uchar>& aMask){
    
        std::vector<Point> lMaskPts = mask_to_pts(aMask);
        return compute_large_boundary(lMaskPts);
        
    }

    Boundary get_largest_area_boundary(MatT<uchar>& aMask){
        BoundaryList lBoundaries = glch::compute_boundary(aMask);
        //BoundaryList lBoundaries = glch::compute_small_boundary(aMask);
        double lLargestArea = 0;
        int lLargestIndex = 0;

        for(long unsigned int i = 0; i < lBoundaries.size(); i++){
            double lArea = glch::area(lBoundaries.at(i));
            if(lArea > lLargestArea){
                lLargestIndex = i;
                lLargestArea = lArea;
            } 
        }
        
        return lBoundaries.at(lLargestIndex);
    }
    
    
    /**
     * Computes the digital plane topological boundary of a set of points and places these
     * boundaries into their own vector.
     * 
     *  .-.-.-.
     *  |P|P|P|
     *  .-.-.-.
     *  |P|P|P|
     *  .-.-.-.
     * 
     * The digital plane topological boundary is illustrated as above, where
     * each pixel has a 4 corners and 4 edges which are shared with adjacent
     * pixels.
     * 
     * @param aMaskSet The set of mask points to analyze.
     * @return A list of boundaries.
     */    
    BoundaryList compute_top_boundary(std::vector<Point>& aMaskSet){
        
        //std::vector<Point> lBP = get_boundary_points(aMaskSet);
        std::vector<Point> lPixels = pts_to_toppts(aMaskSet);
        return compute_boundary(lPixels);
        
    }

    /**
     * Computes the digital plane topological boundary of a mask and places these
     * boundaries into their own vector.
     * 
     *  .-.-.-.
     *  |P|P|P|
     *  .-.-.-.
     *  |P|P|P|
     *  .-.-.-.
     * 
     * The digital plane topological boundary is illustrated as above, where
     * each pixel has a 4 corners and 4 edges which are shared with adjacent
     * pixels.
     * 
     * @param aMask The mask to analyze.
     * @return A list of boundaries.
     */
    BoundaryList compute_top_boundary(MatT<uchar>& aMask){

        std::vector<Point> lMaskPts = mask_to_pts(aMask);
        return compute_top_boundary(lMaskPts);
        
    }
    
    /**
     * Computes the topological features of digital plane topological boundary.
     * @param aBoundary The digital plane topological boundary to analyze.
     * @param aEdges The number of edges. (Return Value)
     * @param aCorners The number of corners. (Return Value)
     */
    void count_top_features(Boundary aBoundary, double& aEdges, double& aCorners){
        
        double lEdges = 0;
        double lCorners = 0;
        
        for(size_t i = 0; i < aBoundary.size(); i++){

            Point lPt = aBoundary.at(i);
            size_t lCol = lPt.x%2;
            size_t lRow = lPt.y%2;

            if( !lCol && !lRow ){
                
                std::vector<Point> lNeighbors = get_neighbors(lPt,4,false);
                size_t lAdjSide1 = 0;
                size_t lAdjSide2 = 0;
                
                lAdjSide1 += (glch::index_of(aBoundary,lNeighbors.at(0)) != GLCH_NOT_FOUND);
                lAdjSide1 += (glch::index_of(aBoundary,lNeighbors.at(1)) != GLCH_NOT_FOUND);
                
                lAdjSide2 += (glch::index_of(aBoundary,lNeighbors.at(2)) != GLCH_NOT_FOUND);
                lAdjSide2 += (glch::index_of(aBoundary,lNeighbors.at(3)) != GLCH_NOT_FOUND);
                
                if( (lAdjSide1 != 2) && (lAdjSide2 != 2) ){
                    lCorners ++;
                }
                
            } else {
                lEdges++;
                
            }
            
        }
        
        aEdges = lEdges;
        aCorners = lCorners;
        
    }

    double count_top_corners(Boundary aBoundary){

        double lEdges;
        double lCorners;
        count_top_features(aBoundary,lEdges,lCorners);
        
        return lCorners;
    }
    
    double count_top_edges(Boundary aBoundary){

        double lEdges;
        double lCorners;
        count_top_features(aBoundary,lEdges,lCorners);
        
        return lEdges;
    }
    
    std::map<size_t,Point>::iterator get_next_point_it(Point aPt, std::map<size_t,Point> &aBoundaryMap, size_t aColumns){
        
        std::map<size_t,Point>::iterator lRet = aBoundaryMap.end();
        
        for(size_t i = 0; i < 4; i++){
            Point lPoint = Point(aPt.x + GLCH_CW_FOUR_NEIGHBOR_X[i], aPt.y + GLCH_CW_FOUR_NEIGHBOR_Y[i]);
            size_t lTmpIndex = lPoint.y*aColumns+lPoint.x; //glch::index_of(aPts,lPoint);
            if(aBoundaryMap.find(lTmpIndex) != aBoundaryMap.end()){
                lRet = aBoundaryMap.find(lTmpIndex);
                break;
            }
            
        }
            
        return lRet;
    }
    
    BoundaryList trace_boundary(std::vector<Point>& aBoundaryPoints, size_t aColumns){
        BoundaryList lRet;
        std::map<size_t,Point> aBoundaryMap;
        
        for(size_t i = 0; i < aBoundaryPoints.size(); i++){
            size_t lIndex = aBoundaryPoints.at(i).y*(aColumns+1)+aBoundaryPoints.at(i).x;
            //aBoundaryMap[lIndex] = aBoundaryPoints.at(i);
            aBoundaryMap.insert(std::pair<size_t,Point>(lIndex,aBoundaryPoints.at(i)));
        }
        
        while(aBoundaryMap.size() > 0){
            std::map<size_t,Point>::iterator lNextPoint = (aBoundaryMap.begin());
            std::vector<Point> lCurrentBoundary;
            while(lNextPoint != aBoundaryMap.end()){
                Point lPt = (*lNextPoint).second;
                //std::cout << lPts.size() << " : " << lNextPoint << std::endl;
                //lPt.print();
                
                lCurrentBoundary.push_back(lPt);
                aBoundaryMap.erase(lNextPoint);
                lNextPoint = get_next_point_it(lPt,aBoundaryMap,(aColumns+1));
                //std::cout << "Test" << 775 << std::endl;
            }
            //std::cout << "Test" << 777 << std::endl;
            lRet.push_back(lCurrentBoundary);
            
        }
        //std::cout << "Test" << 781 << std::endl;
        return lRet;
        
    }
    
    BoundaryList trace_boundary(std::vector<Point>& aBoundaryPoints){
        
        BoundaryList lRet;
        std::vector<Point> lPts = aBoundaryPoints;
        
        while(lPts.size() > 0){

            size_t lNextPoint = 0;
            std::vector<Point> lCurrentBoundary;
            
            while(lNextPoint != GLCH_NOT_FOUND){
                Point lPt = lPts.at(lNextPoint);
                //std::cout << lPts.size() << " : " << lNextPoint << std::endl;
                //lPt.print();
                
                lCurrentBoundary.push_back(lPt);
                lPts.erase(lPts.begin()+lNextPoint);
                lNextPoint = get_next_point(lPt,lPts);
                //std::cout << "Test" << 775 << std::endl;
            }
            //std::cout << "Test" << 777 << std::endl;
            lRet.push_back(lCurrentBoundary);
            
        }
        //std::cout << "Test" << 781 << std::endl;
        return lRet;
    }
    
    
    bool is_boundary_point(Point aElement, std::vector<Point>& aElements, Rect aROI){
        
        std::vector<Point> lNeighbors = get_valid_neighbors(aElement,8,false,aROI);
        size_t lCount = 0;
        bool lRet = true;
        
        // If the point is not in the masked area, then it can not be in the boundary.
        size_t lIndex = glch::index_of(aElements,aElement);
        //std::cout << "Index: " << lIndex << std::endl;
        //glch::print_vect_fn(lNeighbors);
        
        if(lIndex == GLCH_NOT_FOUND){
            return false;
        }
        
        // If the point is in the mask and at the edge of the image, then it is
        // considered in the boundary.
        if(lNeighbors.size() < 8){
            return true;
        }
        
        
        
        //Check if the element has all of its neighbors in the mask.
        for(size_t i = 0; i < lNeighbors.size(); i++){
            lIndex = glch::index_of(aElements,lNeighbors.at(i));
            
            //std::cout << lIndex << " ";
            
            if(lIndex != GLCH_NOT_FOUND){
                lCount ++;
            }
            
        }
        
        if(lCount == lNeighbors.size()){
            lRet = false;
        }
        
        //std::cout << "\nNumbNeighbors: " << lNeighbors.size() << " : " << lCount << std::endl;
        
        return lRet;
        
    }
    
    /**
     * Checks if a point is considered in the boundary of a mask.
     * This is done by checking if all of the point's neighbors are in the
     * mask.  If the element is 'surrounded' (all 8-neighbors) by points then
     * it is in the interior.  Otherwise it is in the boundary. 
     * @param aElement The point to check.
     * @param aMask The mask to check in.
     * @return True if the element is in the boundary.  False otherwise.
     */
    bool is_boundary_point(Point &aElement, MatT<uchar>& aMask){
 
        std::vector<Point> lNeighbors = get_valid_neighbors(aElement,8,false,Rect(0,0,aMask.cols,aMask.rows));
        size_t lCount = 0;
        bool lRet = true;
        
        // If the point is not in the masked area, then it can not be in the boundary.
        if(!aMask.at(aElement)){
            return false;
        }
        
        // If the point is in the mask and at the edge of the image, then it is
        // considered in the boundary.
        if(lNeighbors.size() < 8){
            return true;
        }
        
        //Check if the element has all of its neighbors in the mask.
        for(size_t i = 0; i < lNeighbors.size(); i++){
            
            if(aMask.at(lNeighbors.at(i))){
                lCount ++;
            }
            
        }
        
        if(lCount == lNeighbors.size()){
            lRet = false;
        }
        
        
        return lRet;
    }
    
    /**
     * Locates all neighbors which are inside of the specified region.
     * @param aElement The element to find the neighbors of.
     * @param aCount The number of neighbors to locate (max 8);
     * @param aIncludeSelf Include the point in the return vector (index 0);
     * @param aRegion The specified region.
     * @return A list of points inside of the region which are also the neighbors
     * of the specified element.
     */
    std::vector<Point> get_valid_neighbors(Point aElement, size_t aCount, bool aIncludeSelf, Rect aRegion){
        
        std::vector<Point> lRet;
        
        for(size_t i = aIncludeSelf?0:1 ; i < aCount+1; i++ ){
            Point lPt = Point(aElement.x+GLCH_NEIGHBOR_X[i],aElement.y+GLCH_NEIGHBOR_Y[i]);
            if(aRegion.contains(lPt)){
                lRet.push_back(lPt);
            }
        }

        
        return lRet;
        
    }
    
    std::vector<Point> get_neighbors(Point aElement, size_t aCount, bool aIncludeSelf){
        
        size_t lOffset = aIncludeSelf?0:1;
        std::vector<Point> lRet(!lOffset+aCount);
        
        for(size_t i = lOffset; i < aCount+1; i++ ){
            lRet.at(i-lOffset) = Point(aElement.x+GLCH_NEIGHBOR_X[i],aElement.y+GLCH_NEIGHBOR_Y[i]);
        }

        
        return lRet;
    }
    
}