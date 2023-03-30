/* 
 * File:   MatFunctions.h
 * Author: brian
 *
 * Created on July 10, 2015, 12:17 PM
 */

#ifndef GLCH_MATTFUNCTIONS_H
#define	GLCH_MATTFUNCTIONS_H

#include "FileLoad.h"
#include "MatT.h"
#include "PairT.h"
#include "TemplateMath.h"
#include "RectT.h"
#include "stringconversion.h"
#include "AString.h"
#include "miscfunctions.h"
#include "fft.h"
#include "ScalarT.h"
#include "StatsF.h"
#include "Moments.h"

#include <algorithm>
#include <iostream>
#include <map>     //cout, endl;

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
    inline T sum_col(MatT<T> &aMatrix, int aColNum){
        T lRet = 0;

        for(size_t r = 0; r < aMatrix.rows; r++){
            //lRet += aMatrix.at(Point(aColNum,r) );
            lRet += aMatrix.at(aColNum,r);
        }

        return lRet;
    }

    template <class T>
    inline std::vector<T> sum_cols(MatT<T> &aMatrix){
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
    void draw_filled_triangle(MatT<T> &aMat, PointT<U> aPt0, PointT<U> aPt1, PointT<U> aPt2, V aValue){
        
        double x0 = aPt0.x ,x1 = aPt1.x, x2 = aPt2.x, y0 = aPt0.y, y1 = aPt1.y, y2 = aPt2.y;
        PointT<U> lPt0 = aPt0;
        PointT<U> lPt1 = aPt1;
        PointT<U> lPt2 = aPt2;
        
        
        if(y1 < y0){
            PointT<U> t = lPt1;
            lPt1 = lPt0;
            lPt0 = t;
        }
        
        if(y2 < y0){
            PointT<U> t = lPt2;
            lPt2 = lPt0;
            lPt0 = t;
        }
        
        if(y2 < y1){
            PointT<U> t = lPt1;
            lPt1 = lPt2;
            lPt2 = t;
        }
        
        std::vector<PointT<U> > lLine01;
        std::vector<PointT<U> > lLine12;
        std::vector<PointT<U> > lLine02;
        
        compute_line_points(lPt0,lPt1,lLine01);
        compute_line_points(lPt1,lPt2,lLine12);
        compute_line_points(lPt0,lPt2,lLine02);
        
        draw_line(aMat, lPt0,lPt1, aValue);
        draw_line(aMat, lPt1,lPt2, aValue);
        draw_line(aMat, lPt0,lPt2, aValue);
        
        
        std::map<U, PointT<U> > lLine012Map;
        for(int i = 0; i != lLine01.size(); i++){
            if(lLine012Map.find(lLine01.at(i).y) == lLine012Map.end()){
                lLine012Map[lLine01.at(i).y] = lLine01.at(i);
            } else {
                if(lLine012Map[lLine01.at(i).y].x < lLine01.at(i).x){
                    lLine012Map[lLine01.at(i).y] = lLine01.at(i);
                }
            }
        }
        
        for(int i = 0; i != lLine12.size(); i++){
            if(lLine012Map.find(lLine12.at(i).y) == lLine012Map.end()){
                lLine012Map[lLine12.at(i).y] = lLine12.at(i);
            } else {
                if(lLine012Map[lLine12.at(i).y].x < lLine12.at(i).x){
                    lLine012Map[lLine12.at(i).y] = lLine12.at(i);
                }
            }
        }

        for(int i = 0; i < lLine02.size(); i++){
            draw_line(aMat,lLine02.at(i), lLine012Map[lLine02.at(i).y], aValue);
        }
        
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
            for(size_t x = x1; x < x2+1; x++){
                aMat.at(Point(x,y1)) = aValue;
            }
            return;            
        }
        
        if(lDeltaX == 0){
            double lY1 = std::min(y1,y2);
            double lY2 = std::max(y1,y2);
            for(size_t y = lY1; y < lY2+1; y++){
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
    
    template <class T>
    vector<PointT<T> > circ(PointT<T> aCentroid, T aRadius){
        double lSteps = aRadius*0.01;
        vector< PointT<T> > lRet;
        
        for(double x = -1*aRadius; x <= aRadius; x += lSteps){
            PointT<T> lPt(x,sqrt(aRadius*aRadius-x*x));
            if(fabs(lPt.y) < aRadius && fabs(lPt.x) < aRadius){
                lPt.x += aCentroid.x;
                lPt.y += aCentroid.y;
                
                lRet.push_back(lPt);
            }
        }
        
        for(double x = aRadius; x >= -1*aRadius; x -= lSteps){
            PointT<T> lPt(x,-1*sqrt(aRadius*aRadius-x*x));
            if(fabs(lPt.y) < aRadius && fabs(lPt.x) < aRadius){
                lPt.x += aCentroid.x;
                lPt.y += aCentroid.y;
                
                lRet.push_back(lPt);
            }
        }        
        
        return lRet;
    }
    
    template <class T, class U, class V>
    void draw_rect(MatT<T> &aMat, RectT<U> aRect, V aValue){
        Point lTL = aRect.top_left();
        Point lTR = Point(aRect.right()-1,aRect.top());
        Point lBL = Point(aRect.left(),aRect.bottom()-1);
        Point lBR = Point(aRect.right()-1,aRect.bottom()-1);
        
        //lTL.print();
        //lTR.print();
        //lBL.print();
        //lBR.print();
        
        //std::cout << glch::AString().arg(lTL << " : " << lTR << " : " << lBL << " : " << lBR << std::endl;
        
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
    
    template <class T>
    void resize_mat_pad(MatT<T> &aSrc, int aWidth, int aHeight){
        MatT<T> lTemp = aSrc;
        resize_mat_pad(lTemp,aSrc,aWidth,aHeight);
    }
    
    template <class T, class U>
    void resize_mat_pad(MatT<T> &aSrc, MatT<U> &aDst, int aWidth, int aHeight){
        aDst.resize(aWidth, aHeight);
        aDst.zero();
        
        for(size_t r = 0; r < aSrc.rows; r++){
            for(size_t c = 0; c < aSrc.cols; c++){
                aDst.at(Point(c,r)) = aSrc.at(Point(c,r));
            }
        }
        
    }
    
    template <class T>
    void resize_mat(MatT<T> &aSrc, int aWidth, int aHeight){
        MatT<T> lTemp = aSrc;
        resize_mat(lTemp,aSrc,aWidth,aHeight);
    }
    
    template <class T, class U>
    void resize_mat(MatT<T> &aSrc, MatT<U> &aDst, int aWidth, int aHeight){
        double aScaleX = (double)aWidth/(double)aSrc.cols;
        double aScaleY = (double)aHeight/(double)aSrc.rows;
        
        scale_mat_size(aSrc,aDst,aScaleX,aScaleY);
    }
    
    template <class T, class V>
    void scale_mat_size(MatT<T> &aSrc, V aScaleX, V aScaleY){
        MatT<T> lTemp = aSrc;
        scale_mat_size(lTemp,aSrc,aScaleX,aScaleY);
    }
    
    template <class T, class U, class V>
    void scale_mat_size(MatT<T> &aSrc, MatT<U> &aDst, V aScaleX, V aScaleY){
        aDst.resize(aSrc.rows*aScaleY, aSrc.cols*aScaleX);
        
        for(size_t i = 0; i < aSrc.cols; i++){
            for(size_t j = 0; j < aSrc.rows; j++){
                draw_filled_rect(aDst,Rect(floor(i*aScaleX),floor(j*aScaleY),ceil(aScaleX)+1,ceil(aScaleY)+1),aSrc.at(Point(i,j)));
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
    void draw_filled_poly_funky(MatT<T> &aMat, vector<PointT<U> > &aPoly, V aValue){
        
        //for(size_t i = 0; i < aPoly.size()-1; i++){
            //std::cout << aMat.cols << " : " << aMat.rows << " | " << aPoly.at(i).x << " : " << aPoly.at(i).y << " | " << aPoly.at(i+1).x << " : " << aPoly.at(i+1).y << std::endl;
        //    draw_line(aMat, aPoly.at(i), aPoly.at(i+1), aValue);
            
        //}
        
        //if(aPoly.front() != aPoly.back()){
        //draw_line(aMat, aPoly.front(), aPoly.back(), aValue);
        //}
        
        PointF lCentf = glch::centroid(aPoly);
        Point lCent(lCentf.x,lCentf.y);
        
        for(int i = 0; i < aPoly.size()-1; i++){
            draw_filled_triangle(aMat, aPoly.at(i), aPoly.at(i+1), lCent, aValue-(i%15)*15);
            //draw_filled_triangle(aMat, aPoly.at(i), lCent, aPoly.at(i+1), aValue);
            //draw_filled_triangle(aMat, aPoly.at(i+1), aPoly.at(i), lCent, aValue);
            //draw_filled_triangle(aMat, aPoly.at(i+1), lCent, aPoly.at(i), aValue);
            //draw_filled_triangle(aMat, lCent, aPoly.at(i), aPoly.at(i+1), aValue);
            //draw_filled_triangle(aMat, lCent, aPoly.at(i+1), aPoly.at(i), aValue);

                    
        }

        draw_filled_triangle(aMat, aPoly.front(), aPoly.back(), lCent, aValue-128);
        //draw_filled_triangle(aMat, aPoly.front(), lCent, aPoly.back(), aValue);
        //draw_filled_triangle(aMat, aPoly.back(), aPoly.front(), lCent, aValue);
        //draw_filled_triangle(aMat, aPoly.back(), lCent, aPoly.front(), aValue);
        //draw_filled_triangle(aMat, lCent, aPoly.front(), aPoly.back(), aValue);
        //draw_filled_triangle(aMat, lCent, aPoly.back(), aPoly.front(), aValue);
            
        //for(size_t r = 0; r < aMat.rows; r++){
        //    for(size_t c = 0; c < aMat.cols; c++){
        //        Point lPt(c,r);
        //        if(contains(aPoly,lPt)){
        //            aMat.at(lPt) = aValue;
        //        }
        //    }
        //}    
            
    }    
    
    template <class T, class U, class V>
    void draw_filled_poly_simple(MatT<T> &aMat, vector<PointT<U> > &aPoly, V aValue){
        
        
        std::map<U, PointT<U> > lMinX;
        std::map<U, PointT<U> > lMaxX;
        U lMinY = aMat.rows;
        U lMaxY = 0;
        
        std::vector<PointT<U> > lPolyCoords;
        
        for(int i = 0; i < aPoly.size()-1; i++){
            compute_line_points(aPoly.at(i), aPoly.at(i+1), lPolyCoords);
        }
        compute_line_points(aPoly.back(), aPoly.front(), lPolyCoords);   
        
        for(int i = 0; i < lPolyCoords.size(); i++){
            //lPolyCoords.at(i).print();
        
        //for(std::vector<PointT<U> >::iterator it = lPolyCoords.begin(); it < lPolyCoords.end(); it++){
            if(lMinY > lPolyCoords.at(i).y){
                
                lMinY = lPolyCoords.at(i).y;
            }
            
            if(lMaxY < lPolyCoords.at(i).y){
                
                lMaxY = lPolyCoords.at(i).y;
            }
            
            if(lMinX.find(lPolyCoords.at(i).y) == lMinX.end()){
                lMinX[lPolyCoords.at(i).y] = lPolyCoords.at(i);
            } else {
                if(lMinX[lPolyCoords.at(i).y].x > lPolyCoords.at(i).x){
                    lMinX[lPolyCoords.at(i).y] = lPolyCoords.at(i);
                }
            }
            
            if(lMaxX.find(lPolyCoords.at(i).y) == lMaxX.end()){
                lMaxX[lPolyCoords.at(i).y] = lPolyCoords.at(i);
            } else {
                if(lMaxX[lPolyCoords.at(i).y].x < lPolyCoords.at(i).x){
                    lMaxX[lPolyCoords.at(i).y] = lPolyCoords.at(i);
                }
            }
        }
        
        
        for(int y = lMinY; y < lMaxY+1; y++){
            draw_line(aMat,lMinX[y],lMaxX[y],aValue);
        }
        
    }
    
    
    template <class T, class U, class V>
    void draw_filled_poly(MatT<T> &aMat, vector<PointT<U> > &aPoly, V aValue){
        
        //for(size_t i = 0; i < aPoly.size()-1; i++){
            //std::cout << aMat.cols << " : " << aMat.rows << " | " << aPoly.at(i).x << " : " << aPoly.at(i).y << " | " << aPoly.at(i+1).x << " : " << aPoly.at(i+1).y << std::endl;
        //    draw_line(aMat, aPoly.at(i), aPoly.at(i+1), aValue);
            
        //}
        
        //if(aPoly.front() != aPoly.back()){
        //draw_line(aMat, aPoly.front(), aPoly.back(), aValue);
        //}
        
        PointF lCentf = glch::centroid(aPoly);
        Point lCent(lCentf.x,lCentf.y);
        
        for(int i = 0; i < aPoly.size()-1; i++){
            draw_filled_triangle(aMat, aPoly.at(i), aPoly.at(i+1), lCent, aValue);
            //draw_filled_triangle(aMat, aPoly.at(i), lCent, aPoly.at(i+1), aValue);
            //draw_filled_triangle(aMat, aPoly.at(i+1), aPoly.at(i), lCent, aValue);
            //draw_filled_triangle(aMat, aPoly.at(i+1), lCent, aPoly.at(i), aValue);
            //draw_filled_triangle(aMat, lCent, aPoly.at(i), aPoly.at(i+1), aValue);
            //draw_filled_triangle(aMat, lCent, aPoly.at(i+1), aPoly.at(i), aValue);

                    
        }

        draw_filled_triangle(aMat, aPoly.front(), aPoly.back(), lCent, aValue);
        //draw_filled_triangle(aMat, aPoly.front(), lCent, aPoly.back(), aValue);
        //draw_filled_triangle(aMat, aPoly.back(), aPoly.front(), lCent, aValue);
        //draw_filled_triangle(aMat, aPoly.back(), lCent, aPoly.front(), aValue);
        //draw_filled_triangle(aMat, lCent, aPoly.front(), aPoly.back(), aValue);
        //draw_filled_triangle(aMat, lCent, aPoly.back(), aPoly.front(), aValue);
            
        //for(size_t r = 0; r < aMat.rows; r++){
        //    for(size_t c = 0; c < aMat.cols; c++){
        //        Point lPt(c,r);
        //        if(contains(aPoly,lPt)){
        //            aMat.at(lPt) = aValue;
        //        }
        //    }
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
        
        int k = argStartPos;
        //int locCount = argStartPos;
        //int locStep = sizeof(U);
        
        for(size_t i = 0; i < argOutput.size(); i++, k+=sizeof(U)){
            argOutput.at(i) = *(U *)&argInput[k];;
            //locCount += locStep;    
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
    double calc_avg_h(glch::MatT<T> &aData){

        double lHValue;
        double lH1 = 0;
        for(int j = 0; j < aData.rows; j++){
            std::vector<double> lDSignal = mat_row_to_vect(aData,j);
            double lTemp = glch::calc_hurst(&(lDSignal.at(0)),aData.cols );  
            //std::cout << "H1: " << lTemp << std::endl;
            lH1 += lTemp;  
        }

        lH1 /= aData.rows;
        double lH2 = 0;
        for(int j = 0; j < aData.cols; j++){
            std::vector<double> lDSignal = mat_col_to_vect(aData,j);
            double lTemp = glch::calc_hurst(&(lDSignal.at(0)),aData.rows );
            //std::cout << "H2: " << lTemp << std::endl;
            lH2 += lTemp;  
        }
        lH2 /= aData.cols;

        lHValue = sqrt(lH1*lH1+lH2*lH2);
        return lHValue;
        
    }
        
    template<class T>
    double calc_avg_bin_h(glch::MatT<T> &aData, int aBinSize){

        double lHValue;
        double lH1 = 0;
        for(int j = 0; j < aData.rows; j++){
            std::vector<double> lDSignal = mat_row_to_vect(aData,j);
            double lTemp = glch::calc_bin_hurst(&(lDSignal.at(0)),aData.cols,aBinSize );  
            //std::cout << "H1: " << lTemp << std::endl;
            lH1 += lTemp;  
        }

        lH1 /= aData.rows;
        double lH2 = 0;
        for(int j = 0; j < aData.cols; j++){
            std::vector<double> lDSignal = mat_col_to_vect(aData,j);
            double lTemp = glch::calc_bin_hurst(&(lDSignal.at(0)),aData.rows,aBinSize );
            //std::cout << "H2: " << lTemp << std::endl;
            lH2 += lTemp;  
        }
        lH2 /= aData.cols;

        lHValue = sqrt(lH1*lH1+lH2*lH2);
        return lHValue;
    }

    template<class T>
    double calc_linmod_bin_h(glch::MatT<T> &aData, int aBinSize){

        CLinearModel lLinearModel;
        std::vector<glch::PointF> lPoints;
        
        for(int j = 0; j < aData.rows; j++){
            std::vector<double> lDSignal = mat_row_to_vect(aData,j);
            glch::push_bin_hurst(&(lDSignal.at(0)),aData.cols,lPoints,aBinSize );  
        }

        for(int j = 0; j < aData.cols; j++){
            std::vector<double> lDSignal = mat_col_to_vect(aData,j);
            glch::push_bin_hurst(&(lDSignal.at(0)),aData.rows,lPoints,aBinSize );
        }

        calculate_least_squares_regression(lLinearModel, lPoints, lPoints.size(), 0, lPoints.size()-1);
        return lLinearModel.vBetaHat;
    }

    
    
    template<class T>
    double calc_mag_bin_h(glch::MatT<T> &aData, int aBinSize){

        double lHValue;
        double lH1 = 0;
        std::vector<double> lDSignalR = mat_row_to_vect(aData,0);
        lH1 = glch::calc_bin_hurst(&(lDSignalR.at(0)),aData.cols,aBinSize );  

        double lH2 = 0;
        std::vector<double> lDSignalC = mat_col_to_vect(aData,0);
        lH2 = glch::calc_bin_hurst(&(lDSignalC.at(0)),aData.rows,aBinSize );

        lHValue = sqrt(lH1*lH1+lH2*lH2);
        return lHValue;
    }
    
    template <class T>
    std::vector<double> mat_to_vect(glch::MatT<T> &aData){
        std::vector<double> lDSignal(aData.size());
        for(int i = 0; i < aData.size(); i++){
            lDSignal.at(i) = aData.at(i);
        }    

        return lDSignal;
    }

    template<class T>
    std::vector<double> mat_row_to_vect(glch::MatT<T> &aData, int aRow){
        std::vector<T> lSignal = aData.getr(aRow);
        std::vector<double> lDSignal(lSignal.size());
        for(int i = 0; i < aData.cols; i++){
            lDSignal.at(i) = lSignal.at(i);
        }

        return lDSignal;
    }

    template<class T>
    std::vector<double> mat_col_to_vect(glch::MatT<T> &aData, int aCol){
            std::vector<T> lSignal = aData.getc(aCol);
            std::vector<double> lDSignal(lSignal.size());

            for(int i = 0; i < aData.rows; i++){
                lDSignal.at(i) = lSignal.at(i);
            }

            return lDSignal;
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
        int lFileSize = locData.size();
        int lPGMSplit = 0;

        int lSplitCount = 3;
        //Getting header data
        while(lPGMSplit < lSplitCount){

            if(locData.at(locSplit) == 0x0A){
                lPGMSplit ++;
            }

            if(locData.at(locSplit) == '#'){
                lSplitCount++;
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
        //int lRemainder = lFileSize-locSplit-locHeight*locWidth*log2(lDepth)/8;
        //locSplit += lRemainder;
        
        //std::cout << locWidth << " : " << locHeight << " : " << log2(lDepth)/8 << " : " << lFileSize << " : " << lRemainder << std::endl;
        
        aImage.resize(locHeight,locWidth);

        if(lDepth == (size_t)pow(2,8)){
            copy_type_to_mat<T,unsigned char>(locData,aImage,locSplit);
        } else if (lDepth == (size_t)pow(2,16) ){
            copy_type_to_mat<T,unsigned short>(locData,aImage,locSplit);
        } else if (lDepth == (size_t)pow(2,32)){
            copy_type_to_mat<T,unsigned int>(locData,aImage,locSplit);
        } else {
            throw RuntimeErrorReport("Invalid image depth: "+to_string(lDepth) );
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
    
    
    
    void save_xsm_us(string argFileName, MatT<unsigned short> &argSrc);
    void load_xsm_us(string locFile, MatT<unsigned short> &aImage);
    
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
    void save_pgm(string argFileName, MatT<T> &argSrc, string aHeaderComment = "Created with glitch library"){

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
    void save_ppm(string argFileName, std::vector<MatT<T> > &argSrc, string aHeaderComment = "Created with glitch library"){

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

        locCount--;
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
    void scale_mat_values(MatT<T> &aSrc, MatT<U> &aDst, double aSrcMin, double aSrcMax, double aDstMin, double aDstMax, bool aExcludeZeros = false){
        aDst.resize(aSrc.rows,aSrc.cols);
        map_vector(aSrc.data,aDst.data,aSrcMin,aSrcMax,aDstMin,aDstMax,aExcludeZeros);
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
    
    
    
    template <class T, class U>
    void convert_matrix(MatT<T> &aSrc, MatT<U> &aDst){
        aDst.resize(aSrc.rows, aSrc.cols);
        glch::convert_vector(aSrc.data,aDst.data);
        
    }    
    
    template <class T>
    void flip_matrix_h(MatT<T> &aSrc){
        MatT<T> lSrc = aSrc;
        flip_matrix_h(lSrc,aSrc);
    }
    
    template <class T>
    void flip_matrix_h(MatT<T> &aSrc, MatT<T> &aDst){
        
        aDst.resize(aSrc.rows, aSrc.cols);
        
        for(size_t r = 0; r < aSrc.rows; r++){

            for(size_t c = 0; c < aSrc.cols/2; c++){
                aDst.at(Point(c,r)) = aSrc.at(Point(aSrc.cols-c-1,r));
                aDst.at(Point(aSrc.cols-c-1,r)) = aSrc.at(Point(c,r));
            }

        }
        
    }
   
    template <class T>
    void flip_matrix_v(MatT<T> &aSrc){
        MatT<T> lSrc = aSrc;
        flip_matrix_v(lSrc,aSrc);
    }    
    
    template <class T>
    void flip_matrix_v(MatT<T> &aSrc, MatT<T> &aDst){
        
        aDst.resize(aSrc.rows, aSrc.cols);
        
        for(size_t c = 0; c < aSrc.cols; c++){
            
            for(size_t r = 0; r < aSrc.rows/2; r++){
                aDst.at(Point(c,r)) = aSrc.at(Point(c,aSrc.rows-r-1));
                aDst.at(Point(c,aSrc.rows-r-1)) = aSrc.at(Point(c,r));
            }

        }
        
    }
    
    template <class T>
    void shift_matrix_h(MatT<T> &aSrc, int aCountX){
        MatT<T> lSrc = aSrc;
        shift_matrix_h(lSrc,aSrc,aCountX);
    }
    
    template <class T>
    void shift_matrix_h(MatT<T> &aSrc, MatT<T> &aDst, int aCountX){
        
        int lCountX = -1*modf(aCountX,aSrc.cols);
        aDst.resize(aSrc.rows, aSrc.cols);
        int k = 0;
        
        if(lCountX < 0){
            lCountX += aSrc.cols;
        }

        if(lCountX > 0){
            for(size_t r = 0; r < aSrc.rows; r++){
                
                for(size_t c = lCountX; c < aSrc.cols; c++, k++){
                    aDst.at(Point(k,r)) = aSrc.at(Point(c,r));
                }

                for(int c = 0; c < lCountX; c++, k++){
                    aDst.at(Point(k,r)) = aSrc.at(Point(c,r));
                }
                
                k = 0;
            }
            
        } else {   
            aDst = aSrc;
        }

    }

    template <class T>
    void shift_matrix_v(MatT<T> &aSrc, int aCountY){
        MatT<T> lSrc = aSrc;
        shift_matrix_v(lSrc,aSrc,aCountY);
    }    
    
    template <class T>
    void shift_matrix_v(MatT<T> &aSrc, MatT<T> &aDst, int aCountY){
        
        int lCountY = -1*modf(aCountY,aSrc.rows);
        aDst.resize(aSrc.rows, aSrc.cols);
        int k = 0;
        
        if(lCountY < 0){
            lCountY += aSrc.rows;
        }

        if(lCountY > 0){
            for(size_t c = 0; c < aSrc.cols; c++){

                for(size_t r = lCountY; r < aSrc.rows; r++, k++){
                    aDst.at(Point(c,k)) = aSrc.at(Point(c,r));
                }

                for(int r = 0; r < lCountY; r++, k++){
                    aDst.at(Point(c,k)) = aSrc.at(Point(c,r));
                }
                
                k = 0;
            }
        } else {
            aDst = aSrc;
        }

    }

    template <class T>
    void shift_matrix(MatT<T> &aSrc, int aCountX, int aCountY){
        MatT<T> lTemp = aSrc;
        shift_matrix(lTemp,aSrc,aCountX,aCountY);
    }   
    
    template <class T>
    void shift_matrix(MatT<T> &aSrc, MatT<T> &aDst, int aCountX, int aCountY){
        shift_matrix_h(aSrc,aDst,aCountX);
        MatT<T> lTemp = aDst;
        shift_matrix_v(lTemp,aDst,aCountY);
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
    template <class T>
    void compute_fft_2d(std::vector< MatT<T> > &aSrc, int dir){

//        MatT<T> lReal;
//        MatT<T> lImag;
//        std::vector< MatT<T> > lRet;
        
        int m,twopm;
        size_t lRows = aSrc.at(0).rows;
        size_t lCols = aSrc.at(0).cols;
//        aDst.resize(2);
//        aDst.at(0).resize(lRows,lCols);
//        aDst.at(1).resize(lRows,lCols);
        
        
        
        /* Transform the rows */
        std::vector<double> real(lCols);
        std::vector<double> imag(lCols);

        GLCHCArray lComps;
        lComps.resize(lCols);
        //std:valarray<double> corpX(corps_tmp[i].data(), corps_tmp[i].size());
        
        if(!power_of_two(lCols,m,twopm)){
            std::cout << lCols << " : " << m << " : " << twopm << std::endl;
            std::cout << "Error... not power of 2...\n";
            return;
        }
                
        //std::cout << power_of_two(lCols,m,twopm) << std::endl;
        //std::cout << twopm << std::endl;
        
        //if (!power_of_two(lCols,m,twopm) || (size_t)twopm != lCols){
        //    return lRet;
        //}

        for (size_t j = 0; j < lRows; j++) {

            for (size_t i = 0; i < lCols; i++) {
                //lComps[i].real() = aSrc.at(0).at(Point(i,j));
                //lComps[i].imag() = aSrc.at(0).at(Point(i,j));
                lComps[i].real(aSrc.at(0).at(Point(i,j)));
                lComps[i].imag(aSrc.at(0).at(Point(i,j)));
                
                //real[i] = aSrc.at(0).at(Point(i,j));
                //imag[i] = aSrc.at(0).at(Point(i,j));
            }

            //FFT(dir,m,real,imag);
            if(dir){
                glch::fft(lComps);
            } else {
                glch::ifft(lComps);
            }
                    
            for (size_t i = 0; i < lCols; i++) {
                aSrc.at(0).at(Point(i,j)) = lComps[i].real();
                aSrc.at(1).at(Point(i,j)) = lComps[i].imag();
                
                //aSrc.at(0).at(Point(i,j)) = real[i];
                //aSrc.at(1).at(Point(i,j)) = imag[i];
            }
        }

        real.clear();
        imag.clear();
        
        real.resize(lRows);
        imag.resize(lRows);
        lComps.resize(lRows);
        /* Transform the columns */

        power_of_two(lRows,m,twopm);
        //if (!power_of_two(lRows,m,twopm) || (size_t)twopm != lRows){
        //    return lRet;
        //}

        for (size_t i = 0; i < lCols; i++) {
            
            for (size_t j = 0; j < lRows; j++) {
                lComps[j].real(aSrc.at(0).at(Point(i,j)));
                lComps[j].imag(aSrc.at(0).at(Point(i,j)));
                
                //real[j] = aSrc.at(0).at(Point(i,j));
                //imag[j] = aSrc.at(0).at(Point(i,j));
            }

           //FFT(dir,m,real,imag);
            if(dir){
                glch::fft(lComps);
            } else {
                glch::ifft(lComps);
            }
            
            for (size_t j=0; j < lRows; j++) {
                aSrc.at(0).at(Point(i,j)) = lComps[j].real();
                aSrc.at(1).at(Point(i,j)) = lComps[j].imag();
                
                //aSrc.at(0).at(Point(i,j)) = real[j];
                //aSrc.at(1).at(Point(i,j)) = imag[j];
            }
        }

//        lRet.push_back(lReal);
//        lRet.push_back(lImag);
//        
//       return lRet;
    }

    template<class T>
    void compute_fft_2d_fwd(MatT<T> &aSrc, std::vector< MatT<double> > &aDst){
        //std::cout << "fwd" << std::endl;

        //std::vector< MatT<double> > lDst;
        aDst.resize(2);
        

        //std::cout << "Test1204" << std::endl;
        convert_matrix(aSrc,aDst.at(0));
        aDst.at(1).resize(aSrc.rows,aSrc.cols);
        //glch::convert_vector(aSrc.data,aDst.at(0).data);
        
        //std::cout << "Test1207" << std::endl;
        compute_fft_2d(aDst,1);
        //std::cout << "Test1209" << std::endl;
        
        

        
        //std::cout << "fwd_end" << std::endl;
    }
    
    template<class T>
    void compute_fft_2d_rev(std::vector< MatT<double> > &aSrc, MatT<T> &aDst){
        //std::cout << "rev" << std::endl;
        std::vector< MatT<double> > lDst(2);

        lDst.at(0) = aSrc.at(0);
        lDst.at(1) = aSrc.at(1);
        
        compute_fft_2d(lDst,0);
        glch::convert_vector(lDst.at(0).data,aDst.data);
        
        
        //flip_matrix_v(aDst);
        //flip_matrix_h(aDst);
        //shift_matrix(aDst,1,1);
        
        //std::cout << "rev_end" << std::endl;
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

    template <class T, class U>
    MatT<T> convolve_fft(MatT<T> &aSrc, MatT<U> &aKernel){
        MatT<T> aDst;
        MatT<double> lKernel;
        std::vector<MatT<double> > lFFT;
        std::vector<MatT<double> > lKernelFFT;
        
        lKernel.resize(aKernel.rows,aKernel.cols);
        glch::scale_mat_values(aKernel,lKernel,0,1);


        glch::resize_mat_pad(lKernel,aSrc.cols,aSrc.rows);
        glch::shift_matrix(lKernel,(aSrc.cols-aKernel.cols)/2.0,(aSrc.rows-aKernel.rows)/2.0);
        aDst.resize(aSrc.rows, aSrc.cols);
        
        glch::compute_fft_2d_fwd(aSrc,lFFT);
        glch::compute_fft_2d_fwd(lKernel,lKernelFFT);
        
        //corners_to_center(lFFTOrig.at(0),lFFTOrig.at(0));
        //corners_to_center(lFFTOrig.at(1),lFFTOrig.at(1));
        //glch::shift_matrix(lFFT.at(0),lFFT.at(0).cols/2,lFFT.at(0).rows/2);
        //glch::shift_matrix(lFFT.at(1),lFFT.at(1).cols/2,lFFT.at(0).rows/2);
    
        lFFT.at(0) = mat_mult(lFFT.at(0),lKernelFFT.at(0));
        //lFFT.at(1) = mat_mult(lFFT.at(1),lKernelFFT.at(1));
        //lFFT.at(1) = mat_mult(lFFT.at(1),lKernel);
        
        //corners_to_center(lFFTOrig.at(0),lFFTOrig.at(0));
        //corners_to_center(lFFTOrig.at(1),lFFTOrig.at(1));
        //glch::shift_matrix(lFFT.at(0),-lFFT.at(0).cols/2,-lFFT.at(0).rows/2);
        //glch::shift_matrix(lFFT.at(1),-lFFT.at(1).cols/2,-lFFT.at(0).rows/2);
        
        glch::compute_fft_2d_rev(lFFT,aDst);
        
        return aDst;
    }
    
    template <class T, class U>
    MatT<T> convolve(MatT<T> &aSrc, MatT<U> &aKernel){
        MatT<T> aDst;
        aDst.resize(aSrc.rows, aSrc.cols);
        
        for(size_t r = 0; r < aSrc.rows; r++){
            for(size_t c = 0; c < aSrc.cols; c++){
                aDst.at(Point(c,r)) = convolve_one(r,c,aSrc,aKernel);
            }
        }
        
        
        
        double lMatSum = glch::sum(aKernel.data);
        if(lMatSum != 0){
            for(size_t i = 0; i < aDst.size(); i++){
                aDst.at(i) = fabs(aDst.at(i)/lMatSum);
            }
        }
        
        
        return aDst;
    }
    
    template <class T, class U>
    T convolve_one(int aRow, int aCol, MatT<T> &aSrc, MatT<U> &aKernel){
    
        T lRet = 0;
        int lOffsetR = aKernel.rows/2;
        int lOffsetC = aKernel.cols/2;
        
        for(size_t r = 0; r < aKernel.rows; r++){
            for(size_t c = 0; c < aKernel.cols; c++){
                glch::Point lPt1 = Point(aCol-lOffsetC+c,aRow-lOffsetR+r);
                glch::Point lPt2 = Point(c,r);
                
                if( !(lPt1.x < 0 || lPt1.y < 0 || lPt1.x > aSrc.cols || lPt1.y > aSrc.rows) ){
                    lRet += aSrc.at_no_wrap(Point(aCol-lOffsetC+c,aRow-lOffsetR+r))*aKernel.at(Point(c,r));
                }
            }
            
        }
        
        return lRet;
    }    
    
    template <class T>
    void gen_gaussian(int aWidth, int aHeight, MatT<T> &aDst, double A = 1, double a = .5, double b = 0, double c = .5){

        aDst.resize(aHeight,aWidth);
        
        double x0 = aWidth/2;
        double y0 = aHeight/2;
            
        for(int y = 0; y < aHeight; y++){
            for(int x = 0; x < aWidth; x++){
                aDst.at(Point(x,y)) = gauss(x,y,x0,y0,A,a,b,c);
            }
        }
            
//        double lSum = glch::sum_vector(aDst.data);
//        
//        for(int i = 0; i < aDst.size(); i++){
//            aDst.at(i) /= lSum;
//        }
        
    }

    template <class T>
    void gen_gaussian_dx(int aWidth, int aHeight, MatT<T> &aDst, double A = 1, double a = .5, double b = 0, double c = .5){

        aDst.resize(aHeight,aWidth);
        
        double x0 = aWidth/2;
        double y0 = aHeight/2;
            
        for(int y = 0; y < aHeight; y++){
            for(int x = 0; x < aWidth; x++){
                aDst.at(Point(x,y)) = gauss_dx(x,y,x0,y0,A,a,b,c);
            }
        }
            
//        double lSum = glch::sum_vector(aDst.data);
//        
//        
//        for(int i = 0; i < aDst.size(); i++){
//            aDst.at(i) /= lSum;
//        }
        
    }    

    template <class T>
    void gen_gaussian_dy(int aWidth, int aHeight, MatT<T> &aDst, double A = 1, double a = .5, double b = 0, double c = .5){

        aDst.resize(aHeight,aWidth);
        
        double x0 = aWidth/2;
        double y0 = aHeight/2;
            
        for(int y = 0; y < aHeight; y++){
            for(int x = 0; x < aWidth; x++){
                aDst.at(Point(x,y)) = gauss_dy(x,y,x0,y0,A,a,b,c);
            }
        }
            
//        double lSum = glch::sum_vector(aDst.data);
//        
//        for(int i = 0; i < aDst.size(); i++){
//            aDst.at(i) /= lSum;
//        }
        
    }   
    
    template <class T>
    void gen_gaussian_scaled(int aWidth, int aHeight, MatT<T> &aDst, double aA = 255){

        aDst.resize(aHeight,aWidth);
        
        double x0 = aWidth/2;
        double y0 = aHeight/2;
            
        for(int y = 0; y < aHeight; y++){
            for(int x = 0; x < aWidth; x++){
                aDst.at(Point(x,y)) = gauss(x,y,x0,y0,aA,5/(x0*x0),0,5/(y0*y0));
            }
        }
        
    }
    
    template <class T>
    void gen_gaussian_scaled_dx(int aWidth, int aHeight, MatT<T> &aDst, double aA = 255){

        aDst.resize(aHeight,aWidth);
        
        double x0 = aWidth/2;
        double y0 = aHeight/2;
            
        for(int y = 0; y < aHeight; y++){
            for(int x = 0; x < aWidth; x++){
                aDst.at(Point(x,y)) = gauss_dx(x,y,x0,y0,aA,5/(x0*x0),0,5/(y0*y0));
            }
        }

//        double lSum = glch::sum_vector(aDst.data);
//        
//        for(int i = 0; i < aDst.size(); i++){
//            aDst.at(i) /= lSum;
//        }        
    }

    template <class T>
    void gen_gaussian_scaled_dy(int aWidth, int aHeight, MatT<T> &aDst, double aA = 255){

        aDst.resize(aHeight,aWidth);
        
        double x0 = aWidth/2;
        double y0 = aHeight/2;
            
        for(int y = 0; y < aHeight; y++){
            for(int x = 0; x < aWidth; x++){
                aDst.at(Point(x,y)) = gauss_dy(x,y,x0,y0,aA,5/(x0*x0),0,5/(y0*y0));
            }
        }

//        double lSum = glch::sum_vector(aDst.data);
//        
//        for(int i = 0; i < aDst.size(); i++){
//            aDst.at(i) /= lSum;
//        }         
    }
    
    template <class T>
    void normalize_matrix(MatT<T>& aSrc, MatT<double>& aDst){
        
        double lSum = glch::sum_vector(aSrc.data);
        aDst.resize(aSrc.rows,aSrc.cols);
        
        for(size_t i = 0; i < aDst.size(); i++){
            aDst.at(i) = aSrc.at(i) / lSum;
        }
        
    }
    
    
    template <class T>
    std::vector< MatT<T> > gen_mat_image(int aRows, int aCols, int aChannels){
        std::vector< MatT<T> > lRet(aChannels);
        
        for(int i = 0; i < aChannels; i++){
            lRet.at(i).resize(aRows,aCols);
            lRet.at(i).zero();
        }
        
        return lRet;
    }

    template <class T>
    void set_mat_image(std::vector< MatT<T> >& aSrc, int aX, int aY, ScalarF aVal){
        
        for(size_t i = 0; i < aSrc.size(); i++){
            aSrc.at(i).at(Point(aX,aY)) = aVal.val[i];
        }
        
    }
    
    template <class T>
    MatT<unsigned char> threshold_image(MatT<T> &aSrc, T aVal){
        
        MatT<unsigned char> lRet(aSrc.rows, aSrc.cols);
        
        
        
        for(int i = 0; i < aSrc.rows; i++){
            for(int j = 0; j < aSrc.cols; j++){
                lRet.at(Point(j,i)) = (aSrc.at(Point(j,i)) > aVal)*255;
            }
        }
        
        
        return lRet;
    }
    
    
} //End om

#endif	/* MATTFUNCTIONS_H */

