/* 
 * File:   MatFunctions.h
 * Author: brian
 *
 * Created on July 10, 2015, 12:17 PM
 */

#ifndef MATTFUNCTIONS_H
#define	MATTFUNCTIONS_H

#include "FileLoad.h"
#include "MatT.h"
#include "PairT.h"
#include "TemplateMath.h"
#include "RectT.h"
#include "stringconversion.h"
#include "AString.h"
#include "miscfunctions.h"


#include <algorithm>
#include <iostream>     //cout, endl;

namespace glch{

    template <class T>
    void rref(MatT<T> &aInput){
        size_t lLead = 0;
        size_t lCols = aInput.cols;
        size_t lRows = aInput.rows;

        for(size_t r = 0; (r < lRows); r++){

            if(lCols <= lLead){
                break;
            }

            size_t i = r;

            while (aInput.at(Point(lLead, i)) == (T)0){
                i++;

                if(lRows == i){
                    i = r;
                    lLead ++;

                    if(lCols-1 == lLead){
                        break;
                    }
                }
            }

            aInput.swapr(i,r);

            if(aInput.at(Point(lLead, r)) != (T)0){
                T lTemp = aInput.at(Point(lLead, r));
                aInput.applyr(lTemp,r,div);
            }

            for(i = 0; i < lRows; i++){
                if(i != r){
                    T lTemp = aInput.at(Point(lLead, i));
                    std::vector<T> lRowData = aInput.getr(r);
                    lRowData = apply(lRowData,lTemp,mul);
                    aInput.applyr(lRowData,i,sub);
                }
            }
            lLead ++;

        }

    }

    /**
     * Creates an identity matrix.
     * @param aCols
     * @return 
     */
    template <class T>
    MatT<T> id(size_t aCols){
        MatT<T> lRet(aCols, aCols);

        for(size_t r = 0; r < aCols; r++){
            lRet.at(Point(r,r)) = T(1);
        }

        return lRet;
    }

    /**
     * Computes the trace of a matrix.
     * @param aSrc
     * @return 
     */
    template <class T>
    T tr(MatT<T> &aSrc){
        T lRet = 0;

        for(size_t r = 0; r < aSrc.cols; r++){
            lRet += aSrc.at(Point(r,r));
        }

        return lRet;
    }

    /**
     * Transposes a matrix.
     * @param aSrc
     * @return 
     */
    template <class T>
    MatT<T> t(MatT<T> &aSrc){
        MatT<T> lRet(aSrc.cols,aSrc.rows);

        for(size_t r = 0; r < aSrc.rows; r++){
            for(size_t c = 0; c < aSrc.cols; c++){
                lRet.at(Point(r,c)) = aSrc.at(Point(c,r));
            }

        }

        return lRet;
    }

    
    template <class T>
    MatT<T> mat_oper(MatT<T> &aSrc1, MatT<T> &aSrc2, T (*fn)(T,T)){
        MatT<T> lRet(aSrc1.rows,aSrc1.cols);

        for(size_t r = 0; r < aSrc1.rows; r++){
            for(size_t c = 0; c < aSrc1.cols; c++){
                lRet.at(Point(c,r)) = fn( aSrc1.at(Point(c,r)), aSrc2.at(Point(c,r)) );
            }   
        }

        return lRet;
    }


    template <class T>
    MatT<T> mat_mult(MatT<T> &aSrc, MatT<T> &aSrc2){
        MatT<T> lRet(aSrc.rows,aSrc2.cols);

        for(size_t r = 0; r < aSrc.rows; r++){
            for(size_t c = 0; c < aSrc2.cols; c++){

                std::vector<T> lVect1 = aSrc.getr(r);
                std::vector<T> lVect2 = aSrc2.getc(c);

                std::vector<T> lMult = apply(lVect1,lVect2,mul);

                lRet.at(Point(r,c)) = sum(lMult);
            }

        }

        return lRet;
    }

    template <class T>
    MatT<T> inv_matrix(MatT<T> &aSrc){

        size_t lSize = (aSrc.rows > aSrc.cols)?aSrc.rows:aSrc.cols;
        MatT<T> lID = id<T>(lSize);
        MatT<T> lInv(lSize,lSize*2);
        MatT<T> lRet(lSize,lSize);

        for(size_t r = 0; r < aSrc.rows; r++){
            for(size_t c = 0; c < aSrc.cols; c++){
                lInv.at(Point(c,r) ) = aSrc.at(Point(c,r));
            }
        }

        for(size_t r = 0; r < lID.rows; r++){
            for(size_t c = 0; c < lID.cols; c++){
                lInv.at(Point(c+lSize,r) ) = lID.at(Point(c,r));
            }
        }

        rref(lInv);

        for(size_t r = 0; r < lRet.rows; r++){
            for(size_t c = 0; c < lRet.cols; c++){
                lRet.at(Point(c,r) ) = lInv.at(Point(c+lSize,r));
            }
        }

        return lRet;
    }

    template <class T>
    T norm_one(MatT<T> &aSrc){

        vector<T> lSums(aSrc.cols,0);

        for(size_t c = 0; c < aSrc.cols; c++){
            for(size_t r = 0; r < aSrc.rows; r++){
                lSums.at(c) += fabs(aSrc.at(Point(c,r)));

            }

        }

        std::sort(lSums.rbegin(), lSums.rend());
        T lRet = lSums.at(0);

        return lRet;
    }

    /**
     * Computes the one condition number of aSrc.
     * @param aSrc
     * @return 
     */
    template <class T>
    T kappa_one(MatT<T> &aSrc){
        T lEucNorm = norm_one(aSrc);
        MatT<T> lInv = inv_matrix(aSrc);
        T lInvEucNorm = norm_one(lInv);
        return lEucNorm*lInvEucNorm;
    }

    template <class T>
    T norm_inf(MatT<T> &aSrc){

        vector<T> lSums(aSrc.rows,0);

        for(size_t c = 0; c < aSrc.cols; c++){
            for(size_t r = 0; r < aSrc.rows; r++){
                lSums.at(r) += fabs(aSrc.at(Point(c,r)));

            }

        }

        std::sort(lSums.rbegin(), lSums.rend());
        T lRet = lSums.at(0);

        return lRet;
    }

    /**
     * Computes the infinite condition number of aSrc.
     * @param aSrc
     * @return 
     */
    template <class T>
    T kappa_inf(MatT<T> &aSrc){
        T lEucNorm = norm_inf(aSrc);
        MatT<T> lInv = inv_matrix(aSrc);
        T lInvEucNorm = norm_inf(lInv);
        return lEucNorm*lInvEucNorm;
    }

    /**
     * Calculates the Euclidean norm of the matrix aSrc
     * @param aSrc
     * @return 
     */
    template <class T>
    T norm_euc(MatT<T> &aSrc){

        T lSum;

        for(size_t c = 0; c < aSrc.cols; c++){
            for(size_t r = 0; r < aSrc.rows; r++){
                lSum += (aSrc.at(Point(c,r)))*(aSrc.at(Point(c,r)));

            }

        }

        T lRet = sqrt(lSum);

        return lRet;
    }

    /**
     * Computes the Euclidean condition number of aSrc.
     * @param aSrc
     * @return 
     */
    template <class T>
    T kappa_euc(MatT<T> &aSrc){
        T lEucNorm = norm_euc(aSrc);
        MatT<T> lInv = inv_matrix(aSrc);
        T lInvEucNorm = norm_euc(lInv);
        return lEucNorm*lInvEucNorm;
    }

    template <class T>
    void compute_QR(MatT<T> &aSrc, MatT<T> &aQ, MatT<T> &aR){

        //size_t lSize = aSrc.rows;
        aQ = glch::id<T>(aSrc.rows);
        aR = aSrc;

        aQ.print();
        aR.print();
        
        for(size_t j = 0; j < aSrc.cols; j++){

            Point lStartPt = Point(j,j);
            Point lEndPt = Point(j,aR.rows-1);
            lStartPt.print();
            lEndPt.print();
            
            MatT<T> lSubR = aR.submat(Point(0,j),Point(aR.cols-1,aR.rows-1));
            std::cout << "SubR" << std::endl;
            lSubR.print();
            std::cout << "R" << std::endl;
            aR.print();
            
            MatT<T> lSubMat = aR.submat(lStartPt, lEndPt);
            std::cout << "SubMat" << std::endl;
            lSubMat.print();

            T lNormX = norm_one(lSubMat);
            std::cout << lNormX << std::endl;
            T lSign = -1.0*sign( aR.at(Point(j,j)) );
            T lU1 = aR.at(Point(j,j)) - lSign*lNormX;
            MatT<T> lW = lSubMat;
            std::cout << "Test297" << std::endl;
            lW.applymat(lU1,div);
            std::cout << "Test299" << std::endl;
            lW.at(0) = 1;
            MatT<T> lWPrime = t(lW);
            std::cout << "Test302" << std::endl;
            T lTau = -lSign*lU1/lNormX;
            std::cout << "Test304" << std::endl;
            lW.applymat(lTau,mul);
            std::cout << "Test306" << std::endl;
            lWPrime.print();
            //lWPrime = t(lWPrime);
            //lWPrime.print();
            lSubR.print();
            lSubR = mat_mult(lWPrime,lSubR);
            std::cout << "Test308" << std::endl;
            //mat_oper(lSubR,mat_mult(lWPrime,lSubR));


        }

    }
 
    template <class T, class U>
    std::vector< PairT<T> > mat_to_pair(MatT<U> &aMat){

        std::vector< PairT<T> > lRet;
        lRet.resize(aMat.cols*aMat.rows);

        for(int i = 0; i < aMat.cols*aMat.rows; i++){
            lRet.at(i).first = i;
            lRet.at(i).second = aMat.at(i);
        }

        return lRet;
    }

    template <class T, class U>
    std::vector< PairT<T> > matcol_to_pair(MatT<U> &aMat, int aCol){

        std::vector< PairT<T> > lRet;
        lRet.resize(aMat.rows);

        for(int i = 0; i < aMat.rows; i++){
            lRet.at(i).first = i;
            lRet.at(i).second = aMat.at(Point(aCol,i) );
        }

        return lRet;
    }

    template <class T, class U>
    std::vector< PairT<T> > matrow_to_pair(MatT<U> &aMat, int aRow){

        std::vector< PairT<T> > lRet;
        lRet.resize(aMat.cols);

        for(int i = 0; i < aMat.cols; i++){
            lRet.at(i).first = i;
            lRet.at(i).second = aMat.at(Point(i,aRow) );
        }

        return lRet;
    }
    
    template <class T>
    inline T sum_col(const MatT<T> &aMatrix, int aColNum){
        T lRet = 0;

        for(int r = 0; r < aMatrix.rows; r++){
            lRet += aMatrix.at(Point(aColNum,r) );
        }

        return lRet;
    }

    template <class T>
    inline std::vector<T> sum_cols(const MatT<T> &aMatrix){
        std::vector<T> lRet;
        lRet.resize(aMatrix.cols);

        for(int i = 0; i < lRet.size(); i++){
            lRet.at(i) = sum_col<T>(aMatrix,i);
        }


        return lRet;
    }    
    
    template <class T, class U, class V> 
    void draw_point(MatT<T> &aMat, PointT<U> aPt, V aValue){
        aMat.at(aPt) = aValue;
    }
    
    template <class T, class U, class V> 
    void draw_line(MatT<T> &aMat, PointT<U> aPt1, PointT<U> aPt2, V aValue){
        double x1 = aPt1.x ,x2 = aPt2.x, y1 = aPt1.y, y2 = aPt2.y;
        if(x1 > x2){
            x1 = aPt2.x;
            x2 = aPt1.x;
            y1 = aPt2.y;
            y2 = aPt1.y;
        }
        
        double lDeltaX = x2 - x1;
        double lDeltaY = y2 - y1;
        double lError = 0;
        double lDeltaError = fabs(lDeltaY/lDeltaX);
        int y = y1;
        
        if(lDeltaY == 0){
            for(size_t x = x1; x < x2; x++){
                aMat.at(Point(x,y1)) = aValue;
            }
            return;            
        }
        
        if(lDeltaX == 0){
            double lY1 = std::min(y1,y2);
            double lY2 = std::max(y1,y2);
            for(size_t y = lY1; y < lY2; y++){
                aMat.at(Point(x1,y)) = aValue;
            }
            return;
        }
        
        for(size_t x = x1; x < x2; x++){
            aMat.at(Point(x,y)) = aValue;
            lError += lDeltaError;
            
            while(lError >= 0.5){
                aMat.at(Point(x,y)) = aValue;
                y += sign(y2 - y1);
                lError -= 1.0;
            }
        }
        
        aMat.at(Point(x1,y1)) = aValue;
        aMat.at(Point(x2,y2)) = aValue;
    }
   
    
    template <class T> 
    void compute_line_points(PointT<T> aPt1, PointT<T> aPt2, vector<Point> &aDst){
        double x1 = aPt1.x ,x2 = aPt2.x, y1 = aPt1.y, y2 = aPt2.y;
        std::vector<Point> lBuffer;
        bool lReverse = false;
        
        if(x1 > x2){
            x1 = aPt2.x;
            x2 = aPt1.x;
            y1 = aPt2.y;
            y2 = aPt1.y;
            lReverse = true;
        }
        
        double lDeltaX = x2 - x1;
        double lDeltaY = y2 - y1;
        double lError = 0;
        double lDeltaError = fabs(lDeltaY/lDeltaX);
        int y = y1;
        
        if(lDeltaY == 0){
            for(size_t x = x1; x < x2; x++){
                push_check(lBuffer,Point(x,y1));
            }
            push_check(lBuffer,Point(x2,y1));
      
        } else if(lDeltaX == 0){
            double lY1 = std::min(y1,y2);
            double lY2 = std::max(y1,y2);
            if(lY1 != y1){
                lReverse = true;
            }
            
            for(size_t y = lY1; y < lY2; y++){
                push_check(lBuffer,Point(x1,y));
            }
            push_check(lBuffer,Point(x1,lY2));

        } else {
        
            for(size_t x = x1; x < x2; x++){
                lBuffer.push_back(Point(x,y));
                lError += lDeltaError;

                while(lError >= 0.5){
                    push_check(lBuffer,Point(x,y));
                    y += sign(y2 - y1);
                    lError -= 1.0;
                }
            }

            push_check(lBuffer,Point(x2,y2));

        }
        
        if(lReverse){
            for(std::vector<Point>::reverse_iterator it = lBuffer.rbegin(); it != lBuffer.rend(); it++){
                push_check(aDst,(*it));
            }
        } else {
            for(std::vector<Point>::iterator it = lBuffer.begin(); it != lBuffer.end(); it++){
                push_check(aDst,(*it));
            }
        }
        
    }


    template <class T>
    void compute_poly_points(vector<PointT<T> > &aPoly, vector<Point> &aDst){
        
        for(size_t i = 0; i < aPoly.size()-1; i++){
            compute_line_points(aPoly.at(i), aPoly.at(i+1), aDst);
        }

        compute_line_points(aPoly.front(), aPoly.back(), aDst);

        
    } 
    
    template <class T, class U, class V>
    void draw_rect(MatT<T> &aMat, RectT<U> aRect, V aValue){
        Point lTL = aRect.top_left();
        Point lTR = Point(aRect.right()-1,aRect.top());
        Point lBL = Point(aRect.left(),aRect.bottom()-1);
        Point lBR = Point(aRect.right()-1,aRect.bottom()-1);
        
        draw_line(aMat,lTL,lTR,aValue);
        draw_line(aMat,lTR,lBR,aValue);
        draw_line(aMat,lBL,lBR,aValue);
        draw_line(aMat,lTL,lBL,aValue);
    }
    
    template <class T, class U, class V>
    void draw_filled_rect(MatT<T> &aMat, RectT<U> aRect, V aValue){
        
        for(U i = aRect.left(); i < aRect.right(); i++){
            for(U j = aRect.top(); j < aRect.bottom(); j++){
                aMat.at(Point(i,j)) = aValue;
            }
        }
        
    }    
    
    template <class T, class U, class V>
    void scale_mat_size(MatT<T> &aSrc, MatT<U> &aDst, V aScaleX, V aScaleY){
        aDst.resize(aSrc.rows*aScaleY, aSrc.cols*aScaleX);
        
        for(size_t i = 0; i < aSrc.cols; i++){
            for(size_t j = 0; j < aSrc.rows; j++){
                draw_filled_rect(aDst,Rect(floor(i*aScaleX),floor(j*aScaleY),ceil(aScaleX),ceil(aScaleY)),aSrc.at(Point(i,j)));
            }
        }
        
    }    
    
    template <class T, class U>
    void scale_mat_size(MatT<T> &aSrc, MatT<U> &aDst){
        double lScaleX = (double)aDst.cols/(double)aSrc.cols;
        double lScaleY = (double)aDst.rows/(double)aSrc.rows;
        
        scale_mat_size(aSrc,aDst,lScaleX,lScaleY);
        
    }
    
    template <class T, class U>
    void linear_interpolate(MatT<T> &aSrc, MatT<U> &aDst){
        MatT<U> lTemp;
        lTemp.resize(aSrc.rows,aSrc.cols);
        
        for(size_t r = 0; r < aSrc.rows; r++){
            for(size_t c = 0; c < aSrc.cols; c++){
                lTemp.at(Point(c,r)) = (aSrc.at_wrap(Point(r,c)) + aSrc.at_wrap(Point(r-1,c) ) + aSrc.at_wrap(Point(r+1,c)) + aSrc.at_wrap(Point(r,c+1)) + aSrc.at_wrap(Point(r,c-1)))/5.0;
            }
        }
        aDst = lTemp;
    }    
       
    
    template <class T, class U, class V>
    void draw_poly(MatT<T> &aMat, vector<PointT<U> > &aPoly, V aValue){
        
        for(size_t i = 0; i < aPoly.size()-1; i++){
            draw_line(aMat, aPoly.at(i), aPoly.at(i+1), aValue);
        }
        
        //if(aPoly.front() != aPoly.back()){
            draw_line(aMat, aPoly.front(), aPoly.back(), aValue);
        //}
        
    }
    
    template <class T, class U, class V>
    void draw_points(MatT<T> &aMat, vector<PointT<U> > &aPoly, V aValue){
        
        for(size_t i = 0; i < aPoly.size(); i++){
            draw_point(aMat, aPoly.at(i), aValue);
        }
        
        
    }    
    
    template <class T, class U>
    void average_mat(vector<MatT<T> > &aSrc, MatT<U> &aDst){
        double lLayers = aSrc.size();
        
        if(lLayers == 0){
            throw RuntimeErrorReport("Error in average_mat.  Source must contain at least one layer.");
        }
        MatT<double> lAvg(aSrc.at(0).rows,aSrc.at(0).cols);
        aDst.resize(aSrc.at(0).rows,aSrc.at(0).cols);
        aDst.zero();
        
        
        for(size_t i = 0; i < aSrc.at(0).size(); i++){
            for(size_t j = 0; j < lLayers; j++){
                lAvg.at(i) += aSrc.at(j).at(i);

            }            
        }

        for(size_t i = 0; i < aDst.size(); i++){
            lAvg.at(i) /= lLayers;
            aDst.at(i) = lAvg.at(i);
        }
        
        
        
    }

    template <class T, class U>
    void sum_mat(vector<MatT<T> > &aSrc, MatT<U> &aDst){
        double lLayers = aSrc.size();
        
        if(lLayers == 0){
            throw RuntimeErrorReport("Error in average_mat.  Source must contain at least one layer.");
        }

        aDst.resize(aSrc.at(0).rows,aSrc.at(0).cols);
        aDst.zero();
        
        
        for(size_t i = 0; i < aSrc.at(0).size(); i++){
            for(size_t j = 0; j < lLayers; j++){
                aDst.at(i) += aSrc.at(j).at(i);

            }            
        }
 
    }
    
    template <class T, class U>
    void copy_type_to_mat(vector<char> argInput, MatT<T> &argOutput, int argStartPos){
        
        int locCount = argStartPos;
        int locStep = sizeof(U);
        
        for(size_t i = 0; i < argOutput.size(); i++){
            argOutput.at(i) = *(U *)&argInput[locCount];;
            locCount += locStep;    
        }
           

    }    

    template <class T, class U>
    void copy_type_to_mat(vector<char> argInput, std::vector<MatT<T> > &argOutput, int argStartPos){
        
        int locCount = argStartPos;
        int locStep = sizeof(U);
        
        for(size_t i = 0; i < argOutput.at(0).size(); i++){
            for(size_t j = 0; j < argOutput.size(); j++){
                T locValue = *(U *)&argInput[locCount];
                argOutput.at(j).at(i) = locValue;
                locCount += locStep;                
            }
        }

    }    
    
    template<class T>
    void load_xsm(string locFile, MatT<T> &aImage){

        std::vector<char> locData;
        int locSplit = 0;
        string locHeader;
        vector<string> locSplitHeader;
        vector<string> locImageDim;
        int locWidth = 0;
        int locHeight = 0;

        load_file(locFile, &locData);

        //Getting header data.
        while(locData.at(locSplit) != 0x0A){
            locHeader += locData.at(locSplit);
            locSplit ++;
        }
        locSplit ++;

        locSplitHeader = glch::split_string(locHeader, " ");
        locImageDim = glch::split_string(locSplitHeader.at(2), "x");


        locWidth = string_to_type<int>(locImageDim.at(0));
        locHeight = string_to_type<int>(locImageDim.at(1));

        aImage.resize(locHeight,locWidth);
        copy_type_to_mat<T,float>(locData,aImage,locSplit);


    }
    
    template<class T>
    void load_pgm(string locFile, MatT<T> &aImage){

        std::vector<char> locData;
        int locSplit = 0;

        string locHeader;
        vector<string> locSplitHeader;
        vector<string> locImageDim;
        size_t locWidth = 0;
        size_t locHeight = 0;
        size_t lDepth = 0;
        
        load_file(locFile, &locData);
        int lPGMSplit = 0;

        //Getting header data
        while(lPGMSplit < 4){

            if(locData.at(locSplit) == 0x0A){
                lPGMSplit ++;
            }

            locHeader += locData.at(locSplit);
            locSplit ++;

        }

        char lSplit[2] = {0x0A,0x00};
        
        //Getting rid of comments and empty lines.
        locSplitHeader = glch::split_string(locHeader, lSplit );
        for(size_t i = 0; i < locSplitHeader.size(); i++){
            if(locSplitHeader.at(i).empty()){
                locSplitHeader.erase(locSplitHeader.begin()+i);
                i--;
            }
            
            if(locSplitHeader.at(i)[0] == '#'){
                locSplitHeader.erase(locSplitHeader.begin()+i);
                i--;                
            }
        }
      
        locImageDim = glch::split_string(locSplitHeader.at(1), " " );
        
        locWidth = string_to_type<int>(locImageDim.at(0));
        locHeight = string_to_type<int>(locImageDim.at(1));
        lDepth = string_to_type<int>(locSplitHeader.at(2))+1;

        aImage.resize(locHeight,locWidth);

        if(lDepth == (size_t)pow(2,8)){
            copy_type_to_mat<T,unsigned char>(locData,aImage,locSplit);
        } else if (lDepth == (size_t)pow(2,16)){
            copy_type_to_mat<T,unsigned short>(locData,aImage,locSplit);
        } else if (lDepth == (size_t)pow(2,32)){
            copy_type_to_mat<T,unsigned int>(locData,aImage,locSplit);
        } else {
            throw RuntimeErrorReport("Invalid image depth.");
        }        
        
    }    

    template<class T>
    void load_ppm(string locFile, std::vector<MatT<T> > &aImage){

        std::vector<char> locData;
        int locSplit = 0;

        string locHeader;
        vector<string> locSplitHeader;
        vector<string> locImageDim;
        int locWidth = 0;
        int locHeight = 0;
        size_t lDepth = 0;
        size_t lLayers = 0;
        
        load_file(locFile, &locData);
        int lPGMSplit = 0;

        //Getting header data
        while(lPGMSplit < 4){

            if(locData.at(locSplit) == 0x0A){
                lPGMSplit ++;
            }

            locHeader += locData.at(locSplit);
            locSplit ++;

        }
     
        char lSplit[2] = {0x0A,0x00};
        locSplitHeader = glch::split_string(locHeader, lSplit );
        
        for(size_t i = 0; i < locSplitHeader.size(); i++){
            if(locSplitHeader.at(i).empty()){
                locSplitHeader.erase(locSplitHeader.begin()+i);
                i--;
            }
            
            if(locSplitHeader.at(i)[0] == '#'){
                locSplitHeader.erase(locSplitHeader.begin()+i);
                i--;                
            }
        }        
        
        locImageDim = glch::split_string(locSplitHeader.at(1), " " );

        locWidth = string_to_type<int>(locImageDim.at(0));
        locHeight = string_to_type<int>(locImageDim.at(1));
        lDepth = string_to_type<int>(locSplitHeader.at(2))+1;
        lLayers = (locData.size()-locHeader.size())/(locWidth*locHeight)/(log(lDepth)/log(2.0)/8.0);

        aImage.resize(lLayers);
        for(size_t i = 0; i < lLayers; i++){
            aImage.at(i).resize(locHeight,locWidth);
        }

        if(lDepth == (size_t)pow(2,8)){
            copy_type_to_mat<T,unsigned char>(locData,aImage,locSplit);
        } else if (lDepth == (size_t)pow(2,16)){
            copy_type_to_mat<T,unsigned short>(locData,aImage,locSplit);
        } else if (lDepth == (size_t)pow(2,32)){
            copy_type_to_mat<T,unsigned int>(locData,aImage,locSplit);
        } else {
            throw RuntimeErrorReport("Invalid image depth.");
        }
        
        
    }    
    
    /**
     * Loads a ppm type file with multiple layers.  The difference here is that
     * for images with a bit depth greater than 2^16 they are loaded as floating points.
     * @param locFile File to load.
     * @param aImage Image to load file into.
     */
    template<class T>
    void load_pfm(string locFile, std::vector<MatT<T> > &aImage){

        std::vector<char> locData;
        int locSplit = 0;

        string locHeader;
        vector<string> locSplitHeader;
        vector<string> locImageDim;
        int locWidth = 0;
        int locHeight = 0;
        size_t lDepth = 0;
        size_t lLayers = 0;
        
        load_file(locFile, &locData);
        int lPGMSplit = 0;

        //Getting header data
        while(lPGMSplit < 4){

            if(locData.at(locSplit) == 0x0A){
                lPGMSplit ++;
            }

            locHeader += locData.at(locSplit);
            locSplit ++;

        }
     
        char lSplit[2] = {0x0A,0x00};
        locSplitHeader = glch::split_string(locHeader, lSplit );
        
        for(size_t i = 0; i < locSplitHeader.size(); i++){
            if(locSplitHeader.at(i).empty()){
                locSplitHeader.erase(locSplitHeader.begin()+i);
                i--;
            }
            
            if(locSplitHeader.at(i)[0] == '#'){
                locSplitHeader.erase(locSplitHeader.begin()+i);
                i--;                
            }
        }        
        
        locImageDim = glch::split_string(locSplitHeader.at(1), " " );

        locWidth = string_to_type<int>(locImageDim.at(0));
        locHeight = string_to_type<int>(locImageDim.at(1));
        lDepth = string_to_type<int>(locSplitHeader.at(2))+1;
        lLayers = (locData.size()-locHeader.size())/(locWidth*locHeight)/(log(lDepth)/log(2.0)/8.0);

        aImage.resize(lLayers);
        for(size_t i = 0; i < lLayers; i++){
            aImage.at(i).resize(locHeight,locWidth);
        }

        if(lDepth == (size_t)pow(2,8)){
            copy_type_to_mat<T,unsigned char>(locData,aImage,locSplit);
        } else if (lDepth == (size_t)pow(2,16)){
            copy_type_to_mat<T,unsigned short>(locData,aImage,locSplit);
        } else if (lDepth == (size_t)pow(2,32)){
            copy_type_to_mat<T,float>(locData,aImage,locSplit);
        } else if (lDepth == (size_t)pow(2,64)){
            copy_type_to_mat<T,double>(locData,aImage,locSplit);
        } else {
            throw RuntimeErrorReport("Invalid image depth.");
        }
        
        
    }    
    
    template <class T>
    void save_xsm(string argFileName, MatT<T> &argSrc){

        vector<char> locSave;
        string locHeader;
        int locCount = 0;
        int locStep = 4;
        std::ofstream locOut;

        locHeader = "Binary " + 
                to_string(1) + " " + 
                to_string(argSrc.cols) + "x" + to_string(argSrc.rows) + " " +
                to_string(argSrc.cols*argSrc.rows) + "(4 byte reals)";

        locSave.resize(locHeader.size() + 1 + 1*argSrc.cols*argSrc.rows*locStep);
        for(size_t i = 0; i < locHeader.size(); i++){
            locSave.at(i) = locHeader[i];
            locCount++;
        }

        locSave.at(locCount) = 0x0A;
        locCount++;

        for(size_t i = 0; i < argSrc.size(); i++){
            *(float*)&locSave.at(locCount) = argSrc.at(i);
            locCount += locStep;
        }
        

        locOut.open(argFileName.c_str());
        locOut.write(&locSave.at(0), locSave.size());
        locOut.close();
    }

    template <class T>
    void save_pgm(string argFileName, MatT<T> &argSrc, string aHeaderComment = "Created with analysis2d library"){

        vector<char> locSave;
        int locCount = 0;
        int locStep = sizeof(T);
        std::ofstream locOut;
        char lSplit[2] = {0x0A,0x00};
        AString lHeader = AString("P5%1#%2%1%3 %4%1%5%1").argr(lSplit).argr(aHeaderComment).argr(argSrc.cols).argr(argSrc.rows).argr((size_t)pow(2,8*sizeof(T))-1);

        locSave.resize(lHeader.size() + 1+argSrc.cols*argSrc.rows*locStep);
        for(size_t i = 0; i < lHeader.size(); i++){
            locSave.at(i) = lHeader[i];
            locCount++;
        }

        locSave.at(locCount) = 0x0A;
        //locCount++;

        for(size_t i = 0; i < argSrc.size(); i++){
            *(T*)&locSave.at(locCount) = argSrc.at(i);
            locCount += locStep;
        }

        locOut.open(argFileName.c_str());
        locOut.write(&locSave.at(0), locSave.size());
        locOut.close();
    }

    template <class T>
    void save_ppm(string argFileName, std::vector<MatT<T> > &argSrc, string aHeaderComment = "Created with analysis2d library"){

        vector<char> locSave;
        int locCount = 0;
        int locStep = sizeof(T);
        std::ofstream locOut;
        char lSplit[2] = {0x0A,0x00};
        AString lHeader = AString("P6%1#%2%1%3 %4%1%5%1").argr(lSplit).argr(aHeaderComment).argr(argSrc.at(0).cols).argr(argSrc.at(0).rows).argr((size_t)pow(2,8*sizeof(T))-1);

        locSave.resize(lHeader.size() + 1+argSrc.at(0).cols*argSrc.at(0).rows*locStep*argSrc.size());
        for(size_t i = 0; i < lHeader.size(); i++){
            locSave.at(i) = lHeader[i];
            locCount++;
        }

        locSave.at(locCount) = 0x0A;
        locCount++;

        for(size_t j = 0; j < argSrc.at(0).size(); j++){
            
            for(size_t i = 0; i < argSrc.size(); i++){
                *(T*)&locSave.at(locCount) = argSrc.at(i).at(j);
                locCount += locStep;                
            }

        }

        locOut.open(argFileName.c_str());
        locOut.write(&locSave.at(0), locSave.size());
        locOut.close();
    }
    
        
    
    /**
     * Scales the values of a matrix from one range to the min max range (inclusive)
     * specified.
     * @param aSrc Source matrix to transform.
     * @param aDst Destination matrix. (Can be the same as the source).
     * @param aMin Min value to scale to.
     * @param aMax Max value to scale to.
     */
    template <class T, class U>
    void scale_mat_values(MatT<T> &aSrc, MatT<U> &aDst, double aMin, double aMax){
        aDst.resize(aSrc.rows,aSrc.cols);
        map_vector(aSrc.data,aDst.data,aMin,aMax);
    }

    template <class T, class U>
    void scale_mat_values(MatT<T> &aSrc, MatT<U> &aDst, double aSrcMin, double aSrcMax, double aDstMin, double aDstMax){
        aDst.resize(aSrc.rows,aSrc.cols);
        map_vector(aSrc.data,aDst.data,aSrcMin,aSrcMax,aDstMin,aDstMax);
    }
    
    template <class T, class U>
    void magnitude_phase_fft(MatT<T> &aSrcReal, MatT<T> &aSrcImag, MatT<U> &aDstMagnitude, MatT<U> &aDstPhase){
        aDstMagnitude.resize(aSrcReal.rows, aSrcReal.cols);
        aDstPhase.resize(aSrcReal.rows, aSrcReal.cols);
        
        for(size_t i = 0; i < aSrcReal.size(); i++){
            aDstMagnitude.at(i) = sqrt(aSrcReal.at(i)*aSrcReal.at(i) +  aSrcImag.at(i)*aSrcImag.at(i))/aSrcReal.size();
            aDstPhase.at(i) = atan(aSrcImag.at(i)/aSrcReal.at(i));
        }
        
    }
    
    template <class T, class U>
    void powerspectrum_fft(MatT<T> &aSrcReal, MatT<T> &aSrcImag, MatT<U> &aPowerSpectrem){
        aPowerSpectrem.resize(aSrcReal.rows, aSrcReal.cols);

        for(size_t i = 0; i < aSrcReal.size(); i++){
            aPowerSpectrem.at(i) = (aSrcReal.at(i)*-1*aSrcImag.at(i))/(aSrcReal.size()*aSrcReal.size());
        }
        
    }    
    
    template <class T>
    void corners_to_center(MatT<T> &aSrc, MatT<T> &aDst){
        
        size_t cx = aSrc.cols/2;
        size_t cy = aSrc.rows/2;

        
        MatT<T> q0 = aSrc.submat(Rect(0,0,cx-1,cy-1));
        MatT<T> q1 = aSrc.submat(Rect(cx,0,cx-1,cy-1));
        MatT<T> q2 = aSrc.submat(Rect(0,cy,cx-1,cy-1));
        MatT<T> q3 = aSrc.submat(Rect(cx,cy,cx-1,cy-1));

        aDst.resize(aSrc.rows,aSrc.cols);
        aDst.zero();
        aDst.copy(q0,Point(cx,cy));
        aDst.copy(q3,Point(0,0));
        aDst.copy(q2,Point(cx,0));
        aDst.copy(q1,Point(0,cy));
        
    }
    

    
    /*-------------------------------------------------------------------------
        Perform a 2D FFT inplace given a complex 2D array
        The direction dir, 1 for forward, -1 for reverse
        The size of the array (nx,ny)
        Return false if there are memory problems or
           the dimensions are not powers of 2
     * http://paulbourke.net/miscellaneous/dft/
     * Cooley–Tukey FFT algorithm
     */
    template<class T>
    bool compute_fft_2d(std::vector<MatT<T> > &c, int dir){

        int m,twopm;
        size_t lRows = c.at(0).rows;
        size_t lCols = c.at(0).cols;
        /* Transform the rows */
        std::vector<double> real(lCols);
        std::vector<double> imag(lCols);

        if (!power_of_two(lCols,m,twopm) || (size_t)twopm != lCols){
            return(false);
        }

        for (size_t j = 0; j < lRows; j++) {

            for (size_t i = 0; i < lCols; i++) {
                real[i] = c.at(0).at(Point(i,j));
                imag[i] = c.at(1).at(Point(i,j));
            }

            FFT(dir,m,real,imag);

            for (size_t i = 0; i < lCols; i++) {
                c.at(0).at(Point(i,j)) = real[i];
                c.at(1).at(Point(i,j)) = imag[i];
            }
        }

        real.clear();
        imag.clear();
        real.resize(lRows);
        imag.resize(lRows);
        /* Transform the columns */

        if (!power_of_two(lRows,m,twopm) || (size_t)twopm != lRows){
            return(false);
        }

        for (size_t i = 0; i < lCols; i++) {

            for (size_t j = 0; j < lRows; j++) {
                real[j] = c.at(0).at(Point(i,j));
                imag[j] = c.at(1).at(Point(i,j));
            }

           FFT(dir,m,real,imag);

            for (size_t j=0; j < lRows; j++) {
                c.at(0).at(Point(i,j)) = real[j];
                c.at(1).at(Point(i,j)) = imag[j];
            }
        }

       return(true);
    }

    /**
     * Merges two rows in a matrix into a new matrix (aDst)
     * @param aSrc1 First Matrix
     * @param aSrc2 Second Matrix
     * @param aDst Destination Matrix
     * @param aSrc1Row The row we are copying from the first matrix into Dst.
     * @param aSrc2Row The row we are copying from the second matrix into Dst.
     * @param aDstRow The row of Dst we are copying into.
     */
    template <class T>
    void merge_rows(MatT<T> &aSrc1, MatT<T> &aSrc2, MatT<T> &aDst, size_t aSrc1Row, size_t aSrc2Row, size_t aDstRow){
        
        if(aDst.cols < aSrc1.cols+aSrc2.cols){
            throw RuntimeErrorReport("Error in merge_rows, Destination matrix needs to have at least aSrc1.cols+aSrc2.cols number of columns.");
        }
        
        for(size_t k = 0; k < aSrc1.cols; k++){
            aDst.at(k,aDstRow) = aSrc1.at(k,aSrc1Row);
        }

        size_t k1 = 0;
        for(size_t k = aSrc1.cols; k < aDst.cols; k++, k1++){
            aDst.at(k,aDstRow) = aSrc2.at(k1,aSrc2Row);
        }
                
    }
    
    /**
     * Performs a flattened Cartesian cross product of two matrices. 
     * @param aMatA First matrix
     * @param aMatB Second matrix
     * @return A new matrix containing the Cartesian cross product of the two matrices.
     */
    template <class T>
    MatT<T> cart_cross(MatT<T> &aMatA, MatT<T> &aMatB){
        
        MatT<T> lRet(aMatA.cols+aMatB.cols, aMatA.rows*aMatB.rows);
        
        size_t k = 0;
        
        for(size_t i = 0; i < aMatA.rows; i++){
            for(size_t j = 0; j < aMatB.rows; j++, k++){
                merge_rows(aMatA,aMatB,lRet,i,j,k);
            }
        }
        
        return lRet;
    }

    
    
    
} //End om

#endif	/* MATTFUNCTIONS_H */

