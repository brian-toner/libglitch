/* 
 * File:   GridFunctions.h
 * Author: brian
 *
 * Created on January 7, 2016, 1:33 PM
 */

#ifndef GRIDFUNCTIONS_H
#define	GRIDFUNCTIONS_H

#include <vector>
#include "RectT.h"


namespace glch{

    /**
     * Computes the dimension of a grid based on the dimensions of a grid.
     * @param aImageDim
     * @param aBigDim
     * @param aSmallDim
     * @return 
     */
    template <class T>
    int calc_grid_dim(T aImageDim, T aBigDim, T aSmallDim){

        T lBoarder = aBigDim-aSmallDim;
        T lWorkingDim = aImageDim-lBoarder;

        T lReturn = lWorkingDim/aSmallDim;

        return lReturn;
    }
    
    template <class T>
    void build_grid(std::vector<RectT<T> > &argGrid, 
            int aImageWidth, int aImageHeight, int aLgWidth, int aSmWidth){
        int lCols, lRows;
        build_grid(argGrid,aImageWidth,aImageHeight,aLgWidth,aSmWidth, lCols, lRows);
    }

    template <class T>
    void build_grid(std::vector<RectT<T> > &argGrid, 
            int aImageWidth, int aImageHeight, int aLgWidth, int aSmWidth, int &aCols, int &aRows){
        argGrid.clear();

        int locStX = (aLgWidth-aSmWidth)/2;
        int locTempX = (aLgWidth-aSmWidth)/2;
        int locTempY = (aLgWidth-aSmWidth)/2;
        int locIndex = 0;

        int locCols = calc_grid_dim(aImageWidth, aLgWidth, aSmWidth);
        int locRows = calc_grid_dim(aImageHeight, aLgWidth, aSmWidth);  
        aCols = locCols;
        aRows = locRows;

        for(int r = 0; r < locRows; r++){

            for(int c = 0; c < locCols; c++){

                RectT<T>  lRect(locTempX, locTempY, aSmWidth, aSmWidth);
                argGrid.push_back(lRect );

                locTempX += aSmWidth;
                locIndex ++;
            }

            locTempX = locStX;
            locTempY += aSmWidth;

        }



    }

    template <class T>
    void shift_grid_right(std::vector<RectT<T> > &aGrid, int aImageWidth, int aLgWidth, int aSmWidth){

        int locCols = calc_grid_dim(aImageWidth, aLgWidth, aSmWidth);  
        int lShiftOffset = aImageWidth-((aLgWidth-aSmWidth)+(locCols*aSmWidth));

        for(size_t i = 0; i < aGrid.size(); i++){
            aGrid.at(i).x += lShiftOffset;
        }
    }

    template <class T>
    void shift_grid_down(std::vector<RectT<T> > &aGrid, int aImageHeight, int aLgHeight, int aSmHeight){

        int locRows = calc_grid_dim(aImageHeight, aLgHeight, aSmHeight);  
        int lShiftOffset = aImageHeight-((aLgHeight-aSmHeight)+(locRows*aSmHeight));

        for(size_t i = 0; i < aGrid.size(); i++){
            aGrid.at(i).y += lShiftOffset;
        }


    }

    template <class T>
    void shift_grid(std::vector<RectT<T> > &aGrid, int aXOffset, int aYOffset){

        for(size_t i = 0; i < aGrid.size(); i++){
            aGrid.at(i).y += aYOffset;
            aGrid.at(i).x += aXOffset;
        }

    }

}


#endif	/* GRIDFUNCTIONS_H */

