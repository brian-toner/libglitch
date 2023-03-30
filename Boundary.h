/* 
 * File:   Boundary.h
 * Author: brian
 *
 * Created on February 2, 2016, 7:14 PM
 */

#ifndef GLCH_BOUNDARY_H
#define	GLCH_BOUNDARY_H

#include <vector>
#include "PointT.h"
#include "MatT.h"
#include "TopNeighbor.h"
#include "MatTFunctions.h"
#include "ScalarT.h"
#include "PolygonFunctions.h"
#include <set>
#include <map>

namespace glch{

    typedef std::vector< Point > Boundary;
    typedef std::vector< Boundary > BoundaryList;


    /////////////////////////////////////////////////////////////////
    // Revised
    /////////////////////////////////////////////////////////////////
    
    BoundaryList trace_boundary(std::vector<Point>& aBoundaryPoints);
    size_t get_next_point(Point aPt, std::vector<Point>& aPts);
    
    std::map<size_t,Point>::iterator get_next_point_it(Point aPt, std::map<size_t,Point> &aBoundaryMap, size_t aColumns);
    BoundaryList trace_boundary(std::vector<Point>& aBoundaryPoints, size_t aColumns);
    
    std::vector<Point> get_boundary_points(std::vector<Point>& aPoints);
    
    /**
     * Searches a mask for all boundary points.  This list is unordered and does
     * not contain information about the polygons.
     * @param aMask The mask to search for boundary points.
     * @return A list of all boundary points in the image.
     */
    std::vector<Point> get_boundary_points(MatT<uchar>& aMask);
    
    
    
    std::vector<TopNeighbor> get_pixel_topology(Point aPixel);
    std::vector<Point> get_neighbors(Point aElement, size_t aCount, bool aIncludeSelf);
    
    
    bool is_boundary_point(Point aElement, std::vector<Point>& aElements, Rect aROI);
    
    /**
     * Checks if a point is considered in the boundary of a mask.
     * This is done by checking if all of the point's neighbors are in the
     * mask.  If the element is 'surrounded' (all 8-neighbors) by points then
     * it is in the interior.  Otherwise it is in the boundary. 
     * @param aElement The point to check.
     * @param aMask The mask to check in.
     * @return True if the element is in the boundary.  False otherwise.
     */
    bool is_boundary_point(Point &aElement, MatT<uchar>& aMask);
    
    /**
     * Locates all neighbors which are inside of the specified region.
     * @param aElement The element to find the neighbors of.
     * @param aCount The number of neighbors to locate (max 8);
     * @param aIncludeSelf Include the point in the return vector (index 0);
     * @param aRegion The specified region.
     * @return A list of points inside of the region which are also the neighbors
     * of the specified element.
     */    
    std::vector<Point> get_valid_neighbors(Point aElement, size_t aCount, bool aIncludeSelf, Rect aImageDim);    
    
    Point fix_parent_point(Point aPt);
    Point find_parent_point(Point aSearch);
    Point extract_boundary_points(Point aSearch, Boundary& aBoundary);
    BoundaryList compute_small_boundary(MatT<uchar>& aMask);
    BoundaryList compute_small_boundary(std::vector<Point>& aMaskSet);
    
    BoundaryList compute_large_boundary(std::vector<Point>& aMaskSet);
    
    BoundaryList compute_large_boundary(MatT<uchar>& aMask);
    
    Boundary get_largest_area_boundary(MatT<uchar>& aMask);
    
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
    BoundaryList compute_top_boundary(MatT<uchar>& aMask);
    
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
    BoundaryList compute_top_boundary(std::vector<Point>& aMaskSet);
    BoundaryList compute_boundary(glch::MatT<unsigned char> aMask);
    
    
    double count_top_corners(Boundary aBoundary);
    double count_top_edges(Boundary aBoundary);
    
    /**
     * Computes the topological features of digital plane topological boundary.
     * @param aBoundary The digital plane topological boundary to analyze.
     * @param aEdges The number of edges. (Return Value)
     * @param aCorners The number of corners. (Return Value)
     */
    void count_top_features(Boundary aBoundary, double& aEdges, double& aCorners);
    
    std::vector<Point> pts_to_toppts(std::vector<Point>& aPts);
        
    std::vector<Point> pts_to_lgpts(std::vector<Point>& aPts);
    
    /**
     * Converts a mask into a set of points.  This is done by scanning over the
     * rows and columns of the mask and finding any non-zero points.  These points
     * are then pushed into the vector.
     * @param aMask The mask to convert.
     * @return A list of the non-zero pixels in the mask.
     */    
    std::vector<Point> mask_to_pts(MatT<uchar>& aMask);
    
    /* Computes the boundary of the list of points.  This is done by finding
     * the boundary points and then tracing the boundary.
     * @param aPts The points to find the boundary(s) of.
     * @return A list of points in an acceptable format to trace the boundary of.
     */
    BoundaryList compute_boundary(std::vector<Point>& aPts);
    
    
    
    
    /**
     * Extracts the clusters from a mask image.  This is done by first turning
     * the mask into a vector of points (mask_to_pts) and then extracting the
     * clusters from this vector.
     * @param aSrc The mask to locate and extract the clusters from.
     * @return A set of clusters.
     */
    BoundaryList extract_clusters(MatT<uchar> aSrc, size_t aNumbNeighbors);
    
    /**
     * Groups the list of points in aPts into their associated cluster groups.
     * Here we take a list of points and we find out which points are associated
     * with which mask.  These mask points then can be analyzed as desired. 
     * @param aPts The list of ungrouped points.
     * @return A set of clusters.
     */    
    BoundaryList extract_clusters(std::vector<Point>& aPts, size_t aNumbNeighbors);
    
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
    void recurse_group_pts(Point aStPt, std::vector<Point>& aSrc, std::vector<Point>& aDst, size_t aNumbNeighbors = 4);
       
    

    
    Boundary small_to_large_boundary(Boundary& aSmBoundary);
    
    /**
     * Converts a large boundary (x3 size) into a small boundary.
     * @param aLgBoundary The boundary to convert.
     * @return The boundary converted back into a small boundary.
     */
    BoundaryList large_to_small_boundary(BoundaryList& aLgBoundary);
    
    /////////////////////////////////////////////////////////////////
    // Old
    /////////////////////////////////////////////////////////////////
    
    int get_offset(std::vector<Point> &aDst, int aExcludeCol, int aExcludeRow, bool aEightNeighbors);
    void get_topology(Point aPixel, std::vector<TopNeighbor> &aTopology);
    

    
    std::vector<Point> get_neighbors(Point aElement, Rect aBoundary, bool aEightNeighbors);
    std::vector<Point> boundary_to_topboundary(std::vector<Point> &aBoundary);
    bool point_in_boundary(Point aPoint, Boundary &aBoundary, Boundary &aTopBoundary);
    void filter_internal_boundaries(BoundaryList &aBoundary, BoundaryList &aTopBoundary);
    bool point_in_top_boundary(Point aPoint, Boundary &aBoundary);
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

                uchar &lPt = lDrawn.at(Point(c,r) );

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
    void compute_all_boundaries(MatT<T> aInput, BoundaryList &aBoundary, BoundaryList &aTopBoundary){
        
        MatT<T> lInput;
        MatT<T> lTemp;
        glch::resize_mat_pad(aInput,lTemp,aInput.rows+2,aInput.cols+2);
        //glch::save_pgm("./resized-boundary.pgm",lTemp);
        glch::shift_matrix(lTemp,lInput,1,1);
        //glch::save_pgm("./resized-boundary-shift.pgm",lInput);
        //Resize the image to be 3 times as large, so we can use the digital plane topology
        MatT<T> lInputLg;
        MatT<uchar> lTypes;
        MatT<size_t> lElements(lInput.rows*3, lInput.cols*3 );

        glch::scale_mat_size(lInput,lInputLg,3,3);
        glch::save_pgm("./resized.pgm",lInputLg);
        lTypes = lInputLg;

        lElements.zero();
        
        std::vector< std::vector<Point> > lTopBoundarys;
        lTopBoundarys = find_split_boundary(lInputLg, true);
        std::vector< std::vector<Point> > lBoundarys;
        lBoundarys.resize( lTopBoundarys.size() );

        int lCols = lInput.cols;

        int lRowsLg = lInputLg.rows;
        int lColsLg = lInputLg.cols;

        std::vector<TopNeighbor> lNeighbors;
        int index = 0;

        //Moving through all the elements and finding the topology
        for(int r = 1; r < lRowsLg; r += 3){
            for(int c = 1; c < lColsLg; c += 3, index++){
                std::cout << r << " : " << c << " : " << lRowsLg << " : " << lColsLg << std::endl;
                get_topology(Point(c,r), lNeighbors);
                
                for(std::vector<TopNeighbor>::iterator it = lNeighbors.begin(); it != lNeighbors.end(); it++){
                    std::cout << it - lNeighbors.begin() << std::endl;
                    (*it).vPt.print();
                    try{
                        lElements.at( (*it).vPt ) = index;
                        lTypes.at( (*it).vPt ) = (*it).vType;
                    } catch (const std::out_of_range& lError) {
                        
                    } catch (const glch::RuntimeErrorReport& lError){
                        
                    }
                    
                }
            }  
        }  

        //Mapping the topological boundary back to the pixels.
        for(size_t i = 0; i < lTopBoundarys.size(); i++){

            for(std::vector<Point>::iterator it = lTopBoundarys.at(i).begin(); it != lTopBoundarys.at(i).end(); it++){
                int lIndex = lElements.at_no_wrap( (*it) );
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
    double count_thresh(MatT<T> &aSrc, double aThresh){
        double lRet = 0;

        for(int i = 0; i < aSrc.size(); i++){
            if(aThresh < aSrc.at(i)){
                lRet++;
            }
        }
        
        return lRet;
    }
    
    template <class T>
    double count_nonzero(MatT<T> &aSrc){
        double lRet = 0;

        for(int r = 0; r < aSrc.rows; r++){
            for(int c = 0; c < aSrc.cols; c++){
                if(aSrc.at(c,r) != 0){
                    lRet++;
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



#endif	/* GLCH_BOUNDARY_H */

