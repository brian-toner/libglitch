/* 
 * File:   MatT.h
 * Author: brian
 *
 * Created on July 20, 2015, 2:47 AM
 */

#ifndef GLCH_MATT_H
#define	GLCH_MATT_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <math.h>

//#include "FileLoad.h"
#include "PointT.h"
#include "RuntimeErrorReport.h"
#include "RectT.h"
#include "AString.h"
#include "VectorFunctions.h"
#include "TemplateMath.h"

namespace glch{

template <class T>
class MatT {
public:
    MatT();
    MatT(T* aData, size_t aRows, size_t aCols, bool aByRow = true);
    MatT(size_t aRows, size_t aCols, bool aByRow = true);
    MatT(const MatT& orig);
    virtual ~MatT(){};
    
    size_t rows;
    size_t cols;
    
    std::vector<size_t> orig_rows;
    std::vector<size_t> orig_cols;
    
    std::vector<T> data;
    std::vector<std::vector<size_t> > roi;
    //om::VectorT<T> data;
    //om::VectorT<size_t> roi;
    size_t roi_set;
    bool by_row;
    
    void swapbytes(){
        
        for(int i = 0; i < this->size(); i++){
            for(int j = 0; j < sizeof(T)/2; j++){
                unsigned char* lRef = (unsigned char*)(&this->at(i));

                lRef[0] = lRef[0]^lRef[sizeof(T)-j-1];
                lRef[sizeof(T)-j-1] = lRef[sizeof(T)-j-1] ^ lRef[0];
                lRef[0] = lRef[0]^lRef[sizeof(T)-j-1];

            }
        }
    }
    
    std::vector<size_t> & new_roi(){
        roi_set++;
        return get_roi();
    }
    
    std::vector<size_t>& get_roi(){
        
        if(roi_set > roi.size()){
            roi.resize(roi_set);
        }

        return roi.at(roi_set-1);
    }
    
    void zero(){
        for(size_t i = 0; i < size(); i++){
            at(i) = 0;
        }
    }
    
    size_t get_element(size_t aIndex){
        if(roi_set){
            
            return get_roi().at(aIndex);
        } else {
            return aIndex;
        }
    }
    
    size_t get_element(Point aPos){
        //return aPos.x*rows+aPos.y;
        return get_element(aPos.y*cols+aPos.x);
    }
    
    size_t get_element(size_t aX, size_t aY){
        return get_element(aY*cols+aX);
    }
    
    void clear_roi(){
        if(roi_set > 0){
            roi_set -= 1;
            rows = orig_rows.back();
            cols = orig_cols.back();

            orig_rows.pop_back();
            orig_cols.pop_back();
            roi.pop_back();
        }
    }
    
    void clear_all_roi(){
        roi_set = 0;
        rows = orig_rows.front();
        cols = orig_cols.front();
        
        orig_rows.clear();
        orig_cols.clear();
        roi.clear();
    }
    
    void pause_roi(size_t aROIIndex){
        if(aROIIndex > orig_rows.size()){
            throw RuntimeErrorReport("Error in pause_roi ROI Index does not exist.");
        }
        roi_set = aROIIndex;
        rows = orig_rows.at(aROIIndex);
        cols = orig_cols.at(aROIIndex);
    }
    
    void unpause_roi(){
        roi_set = orig_rows.size()-1;
        rows = orig_rows.back();
        cols = orig_cols.back();
        
    }
    
    void set_rows(AString aRowNumbers){
        AStringList lStringRows = aRowNumbers.split(",");
        std::vector<size_t> lRows;
        convert_vector(lStringRows, lRows);
        set_rows(lRows);
    }
    
    void set_rows(std::vector<size_t> aRowNumbers){
        
        
        new_roi().resize(aRowNumbers.size()*cols);
        size_t k = 0;
        
        for(size_t j = 0; j < cols; j++){
            for(size_t i = 0; i < aRowNumbers.size(); i++, k++){
                get_roi().at(k) = get_element(Point(j,aRowNumbers.at(i)) );
            }
        }
        
        orig_rows.push_back(rows);
        orig_cols.push_back(cols);
        rows = aRowNumbers.size();       
        
    }

    void set_cols(AString aColNumbers){
        AStringList lStringCols = aColNumbers.split(",");
        std::vector<size_t> lCols;
        convert_vector(lStringCols, lCols);
        set_cols(lCols);
    }
    
    void set_cols(std::vector<size_t> aColNumbers){
        
        new_roi().resize(aColNumbers.size()*rows);
        size_t k = 0;
        
        for(size_t j = 0; j < aColNumbers.size(); j++){
            for(size_t i = 0; i < rows; i++, k++){
                get_roi().at(k) = get_element(Point(aColNumbers.at(j),i));
            }
        }
        
        orig_rows.push_back(rows);
        orig_cols.push_back(cols);
        cols = aColNumbers.size();     
        roi_set = true;
    }
    
    void set_roi(Point aStart, Point aEnd){
        size_t lSizeX = (aEnd.x+1)-aStart.x;
        size_t lSizeY = (aEnd.y+1)-aStart.y;
        
        new_roi().resize(lSizeX*lSizeY);
        //roi_set = false;
        
        size_t i = 0;
        for(long r = aStart.y; r < aEnd.y+1; r++){
            for(long c = aStart.x; c < aEnd.x+1; c++, i++){
                std::cout << roi_set << " : " << c << " : " << r << std::endl;
                get_roi().at(i) = get_element(Point(c,r));
                std::cout << get_roi().at(i) << " : " << c << " : " << r << " : " << get_element(c,r) << std::endl;
                //lRet.at(Point(lX,lY)) = at(Point(c,r));
            }
        }

        orig_rows.push_back(rows);
        orig_cols.push_back(cols);
        rows = lSizeY;
        cols = lSizeX;        
        roi_set = true;
        
        //return lRet;
    }
    
    void resize(size_t aRows, size_t aCols);
    
    void resize_clone(size_t aRows, size_t aCols);
    
    size_t size(){return rows*cols;}
    
    void print(std::string aDelim = "\t");
    
    template<class U>
    void printt(std::string aDelim = "\t"){

        for(size_t r = 0; r < rows; r++){
            for(size_t c = 0; c < cols; c++){
                std::cout << (U)at(Point(c,r)) << aDelim;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        return;
    }
    
    template<class U>
    void save_csvt(std::string aFileName){
        AString lBuffer = "";

        for(size_t r = 0; r < rows; r++){
            for(size_t c = 0; c < cols; c++){
                lBuffer << (U)at(Point(c,r));
            }
            lBuffer << "\n";
        }
        save_text_file(aFileName,lBuffer);
        
        return;
    }
    
    void save_csv(std::string aFileName);
    
    T& at(Point aPos);
    T& at(size_t aX, size_t aY);
    T& at(size_t aPos);
    T& at_wrap(Point aPos);
    T  at_no_wrap(Point aPos);
    T  at_no_wrap(int aX, int aY);
    
    template <class U>
    operator MatT<U>(){
        MatT<U> lRet(rows,cols);

        for(size_t i = 0; i < size(); i++){
            lRet.at(i) = at(i);
        }
        
        return lRet;
    }
    
    //void setv(VectorT<T> &aData);
    /**
     * Sets the matrix to the values in aData
     * @param aData Data being copied into the matrix.
     */
    void setv(std::vector<T> &aData);
    
    void setv_val(std::vector<T> aData);
    
    MatT<T>& operator=(std::vector<T> aData);
    
    /**
     * Gets a row from the matrix
     * @param aRow The row to be copied from.
     * @return vector with a copy of the row elements from aRow
     */
    std::vector<T> getr(size_t aRow);
    
    /**
     * Gets a row from the matrix
     * @param aRow The row to be copied from.
     * @return vector with a copy of the row elements from aRow
     */
    MatT<T> getrm(size_t aRow);    
    
    /**
     * Gets a col from the matrix
     * @param aCol The col to be copied from.
     * @return vector with a copy of the col elements from aCol
     */   
    std::vector<T> getc(size_t aCol);

    /**
     * Gets a col from the matrix
     * @param aCol The col to be copied from.
     * @return vector with a copy of the col elements from aCol
     */   
    MatT<T> getcm(size_t aCol);  
    
    /**
     * Gets the sub matrix with the specified rectangular region.
     * @param aRegion Region we are copying.
     * @return New matrix copied from the region.
     */
    MatT<T> submat(Rect aRegion);
    
    /**
     * Gets a submatrix
     * @param aStart
     * @param aEnd
     * @return 
     */
    MatT<T> submat(Point aStart, Point aEnd);
    
    /**
     * Copies a matrix into this matrix.
     * @param aData Data being copied into the matrix.
     * @param aStartingPoint Point where the data will be copied to.  Default (0,0)
     * @return 
     */
    MatT<T>& copy(MatT<T> &aData, Point aStartingPoint = Point(0,0));
    MatT<T>& copy(MatT<T> &aData, Point aStartingPoint, Point aSrcPoint);
    
    MatT<T>& copy(MatT<T> &aData, glch::Rect aArea);
    /**
     * Sets a row to the values of aData
     * @param aData Data being copied into the matrix.
     * @param aRow Row being copied over.
     */
    void setr(std::vector<T> aData, size_t aRow);
    
    /**
     * Sets a col to the values of aData.
     * @param aData Data being copied into the matrix.
     * @param aCol Col being copied over.
     */
    void setc(std::vector<T> aData, size_t aCol);
    
    void swapr(size_t aRow1, size_t aRow2);
    void swapc(size_t aCol1, size_t aCol2);
    
    void applyr(std::vector<T> aData, size_t aRow, T(*fn)(T,T));
    void applyc(std::vector<T> aData, size_t aCol, T(*fn)(T,T));
    void applyr(T aData, size_t aRow, T(*fn)(T,T));
    void applyc(T aData, size_t aCol, T(*fn)(T,T));
    
    void applymat(T aData, T(*fn)(T,T));
    
    //void apply(T(*fn)(T));
    
    /**
     * Gets the determinate submatrix associated with leading column aCol;
     * @return 
     */
    MatT<T> det_sub_mat(Point aElement);
    
    /**
     * Finds the determinate of the the matrix.  Note this is not as fast as
     * it could be.  We could scan for rows/cols with the most zeros and use
     * those to speed up the operation.
     * @return 
     */
    T det();
    
private:

};

    template<class T>
    MatT<T>::MatT(){
        roi_set = false;
        by_row = true;
    }

    template<class T>
    MatT<T>::MatT(T* aData, size_t aRows, size_t aCols, bool aByRow){
        resize(aRows,aCols);
        roi_set = false;
        by_row = aByRow;
        
        for(size_t i = 0; i < rows*cols; i++){
            at(i) = aData[i];
        }
    }
    
    template<class T>
    MatT<T>::MatT(size_t aRows, size_t aCols, bool aByRow){
        resize(aRows,aCols);
        roi_set = false;
        by_row = aByRow;        
    }
    
    template<class T>
    MatT<T>::MatT(const MatT& orig) : rows(orig.rows), cols(orig.cols), orig_rows(orig.orig_rows), orig_cols(orig.orig_cols), data(orig.data), roi_set(orig.roi_set), by_row(orig.by_row){}

    template<class T>
    void MatT<T>::resize(size_t aRows, size_t aCols){
        cols = aCols;
        rows = aRows;

        data.resize(aCols*aRows);
 
    }

    template<class T>
    void MatT<T>::resize_clone(size_t aRows, size_t aCols){

        MatT<T> lData = *this; 
        resize(aRows,aCols);
        
        for(size_t i = 0; i < data.size(); i++){
            data.at(i) = 0;
        }
        
        
        for(size_t r = 0; r < lData.rows; r++){
            for(size_t c = 0; c < lData.cols; c++){
                at(c,r) = lData.at(c,r);    
            }
        }
        
    }
    
    template<class T>
    void MatT<T>::print(std::string aDelim){
        

        for(size_t r = 0; r < rows; r++){
            for(size_t c = 0; c < cols; c++){
                std::cout << at(Point(c,r)) << aDelim;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        
        return;
    }
    
    
    
    template<class T>
    void MatT<T>::save_csv(std::string aFileName){
        AString lBuffer = "";

        for(size_t r = 0; r < rows; r++){
            for(size_t c = 0; c < cols; c++){
                lBuffer << at(Point(c,r));
            }
            lBuffer << "\n";
        }
        save_text_file(aFileName,lBuffer);
        
        return;
    }    
    
    template<class T>
    T& MatT<T>::at(Point aPos){
        size_t lElement = get_element(aPos);
        //std::cout << lElement << std::endl;
        if(lElement > size()){
            throw RuntimeErrorReport("Point exceeds size of matrix.");
        }
        
        //T& lRet = data.at(aPos.y*cols+aPos.x);
        return at(lElement);
    }
    
    template<class T>
    T& MatT<T>::at(size_t aX, size_t aY){
        size_t lElement = get_element(aX,aY);
        if(lElement > size()){
            throw RuntimeErrorReport("Point exceeds size of matrix.");
        }
        return at(lElement);        
    }
    
    template<class T>
    T& MatT<T>::at_wrap(Point aPos){
        while(aPos.x < 0){
            aPos.x += cols;
        }
                
        while(aPos.y < 0){
            aPos.y += rows;
        }        
        
        aPos.x = aPos.x % cols;
        aPos.y = aPos.y % rows;
        
        return at(aPos);
        
    }    
    
    template<class T>
    T MatT<T>::at_no_wrap(int aX, int aY){
        if((size_t)aX > cols-1 || aX < 0){
            return 0;
        }
        
        if((size_t)aY > rows-1 || aY < 0){
            return 0;
        }

        return at(aX,aY);
        
    } 
    
    template<class T>
    T MatT<T>::at_no_wrap(Point aPos){
        if((size_t)aPos.x > cols-1 || aPos.x < 0){
            return 0;
        }
        
        if((size_t)aPos.y > rows-1 || aPos.y < 0){
            return 0;
        }

        return at(aPos);
        
    }        
    
    template<class T>
    T& MatT<T>::at(size_t aPos){
        return data.at(get_element(aPos));
    }
     
    
    //template<class T>
    //void MatT<T>::setv(VectorT<T> &aData){
    //    for(size_t i = 0; i < aData.size(); i++){
    //        at(i) = aData.at(i);
    //    }
    //}
    
    template<class T>
    void MatT<T>::setv(std::vector<T> &aData){
        
        size_t lCount = 0;
        for(size_t c = 0; c < cols; c++){
            for(size_t r = 0; r < rows; r++, lCount ++){
                at(Point(c,r)) = aData.at(lCount);
            }
        }
        
    }
    
    template<class T>
    void MatT<T>::setv_val(std::vector<T> aData){
        
        size_t lCount = 0;
        for(size_t c = 0; c < cols; c++){
            for(size_t r = 0; r < rows; r++, lCount ++){
                at(Point(c,r)) = aData.at(lCount);
            }
        }
        
    }
    
    template<class T>
    MatT<T>&  MatT<T>::operator=(std::vector<T> aData){
        setv_val(aData);
        return *this;
    }
    
    template<class T>
    std::vector<T> MatT<T>::getr(size_t aRow){
        std::vector<T> lRet(cols,0);
        
        for(size_t c = 0; c < cols; c++){
            lRet.at(c) = at(Point(c,aRow));
        }
        
        return lRet;
    }


    template<class T>
    MatT<T> MatT<T>::getrm(size_t aRow){
        MatT<T> lRet(1,cols);
        std::vector<T> lRow = getr(aRow);
        lRet.setv(lRow);
        return lRet;
    }  
    
    template<class T>
    std::vector<T> MatT<T>::getc(size_t aCol){
        std::vector<T> lRet(rows,0);
        
        for(size_t r = 0; r < rows; r++){
            lRet.at(r) = at(Point(aCol,r));
        }
        
        return lRet;
    }
    
    /**
     * Gets a col from the matrix
     * @param aCol The col to be copied from.
     * @return vector with a copy of the col elements from aCol
     */
    template<class T>
    MatT<T> MatT<T>::getcm(size_t aCol){
        MatT<T> lRet(rows,1);
        std::vector<T> lCol = getc(aCol);
        lRet.setv(lCol);
        return lRet;
    }    
    
    template<class T>
    MatT<T> MatT<T>::submat(Rect aRegion){
        return submat(aRegion.top_left(),aRegion.bottom_right());
    }
    
    template<class T>
    MatT<T> MatT<T>::submat(Point aStart, Point aEnd){
        size_t lSizeX = (aEnd.x+1)-aStart.x;
        size_t lSizeY = (aEnd.y+1)-aStart.y;
        
        MatT<T> lRet(lSizeY,lSizeX);
        
        size_t lX = 0;
        size_t lY = 0;
        for(long r = aStart.y; r < aEnd.y+1; r++, lY++){
            for(long c = aStart.x; c < aEnd.x+1; c++, lX++){
                lRet.at(Point(lX,lY)) = at(Point(c,r));
            }
            lX = 0;
        }
        
        return lRet;
    }    
    
    template<class T>
    MatT<T>& MatT<T>::copy(MatT<T> &aData, Point aStartingPoint){
        int minRows = (this->rows > aData.rows)?aData.rows : this->rows;
        int minCols = (this->cols > aData.cols)?aData.cols : this->cols;
        int lX = 0;
        int lY = 0;
        for(int r = aStartingPoint.y; r < aStartingPoint.y+minRows; r++, lY++){
            for(int c = aStartingPoint.x; c < aStartingPoint.x+minCols; c++, lX++){
                at(Point(c,r)) = aData.at(Point(lX,lY));
            }
            lX = 0;
        }
        
        return *this;
    }    

    template<class T>
    MatT<T>& MatT<T>::copy(MatT<T> &aData, Point aStartingPoint, Point aSrcPoint){
        int minRows = (this->rows > aData.rows)?aData.rows : this->rows;
        int minCols = (this->cols > aData.cols)?aData.cols : this->cols;
        int lX = 0;
        int lY = 0;
        for(int r = aStartingPoint.y; r < aStartingPoint.y+minRows; r++, lY++){
            for(int c = aStartingPoint.x; c < aStartingPoint.x+minCols; c++, lX++){
                at(Point(c,r)) = aData.at(Point(aSrcPoint.x+lX,aSrcPoint.y+lY));
            }
            lX = 0;
        }
        
        return *this;
    }  
    
    template<class T>
    MatT<T>& MatT<T>::copy(MatT<T> &aData, glch::Rect aArea){
        
        int lX = 0;
        int lY = 0;
        for(int r = aArea.y; r < aArea.bottom(); r++, lY++){
            for(int c = aArea.x; c < aArea.right(); c++, lX++){
                at(Point(c,r)) = aData.at(Point(c,r));
            }
            lX = 0;
        }
        
        return *this;
    }   
    
    template<class T>
    void MatT<T>::setr(std::vector<T> aData, size_t aRow){
        
        for(size_t c = 0; c < cols; c++){
            at(Point(c,aRow)) = aData.at(c);
        }
        
        return;
    }
    
    template<class T>
    void MatT<T>::setc(std::vector<T> aData, size_t aCol){
        
        for(size_t r = 0; r < rows; r++){
            at(Point(aCol,r)) = aData.at(r);
        }
        
        return;
    }
    
    template<class T>
    void MatT<T>::swapr(size_t aRow1, size_t aRow2){
        std::vector<T> lRow1 = getr(aRow1);
        std::vector<T> lRow2 = getr(aRow2);
        
        setr(lRow1,aRow2);
        setr(lRow2,aRow1);
    }
    
    template<class T>
    void MatT<T>::swapc(size_t aCol1, size_t aCol2){
        std::vector<T> lCol1 = getc(aCol1);
        std::vector<T> lCol2 = getc(aCol2);
        
        setc(lCol1,aCol2);
        setc(lCol2,aCol1);        
    }   
    
    
    template<class T>
    void MatT<T>::applyr(T aData, size_t aRow, T(*fn)(T,T)){
        std::vector<T> lRow = getr(aRow);
        std::vector<T> lRes = apply<T>(lRow,aData,fn);
        
        setr(lRes,aRow);
        
        return;
    }
    
    template<class T>
    void MatT<T>::applyr(std::vector<T> aData, size_t aRow, T(*fn)(T,T)){
        std::vector<T> lRow = getr(aRow);
        std::vector<T> lRes = apply(lRow,aData,fn);
        
        setr(lRes,aRow);
        
        return;
    }
    
    template<class T>
    void MatT<T>::applyc(T aData, size_t aCol, T(*fn)(T,T)){
        std::vector<T> lCol = getc(aCol);
        std::vector<T> lRes = apply(lCol,aData,fn);
        
        setc(lRes,aCol);
        
        return;
        
    }
    
    template<class T>
    void MatT<T>::applyc(std::vector<T> aData, size_t aCol, T(*fn)(T,T)){
        std::vector<T> lCol = getc(aCol);
        std::vector<T> lRes = apply(lCol,aData,fn);
        
        setc(lRes,aCol);
        
        return;
        
    }
    
    template<class T>
    void MatT<T>::applymat(T aData, T(*fn)(T,T)){
        
        for(size_t i = 0; i < size(); i++){
            at(i) = fn(at(i),aData);
        }
        
        return;
    }
    
//    template<class T>
//    void MatT<T>::apply(T(*fn)(T)){
//        
//        for(size_t i = 0; i < size(); i++){
//            at(i) = fn(at(i));
//        }
//    }
    
    template<class T>
    MatT<T> MatT<T>::det_sub_mat(Point aElement){
        
        MatT<T> lRet(rows-1,cols-1);
        
        size_t lCount = 0;
        for(size_t r = 0; r < rows; r++){
            for(size_t c = 0; c < cols; c++){
                if(r == (size_t)aElement.y || c == (size_t)aElement.x){
                    continue;
                }
                
                lRet.at(lCount) = at(Point(c,r));
                lCount ++;
            }
        }
        
        return lRet;
    }
    
    template<class T>
    T MatT<T>::det(){
        
        T lRet = 0;
        
        if(cols == 2){
            T lRet = (at(0)*at(3))-(at(1)*at(2));
            return(lRet);
        } else {
            std::vector<T> lVals(cols,0);
            
            for(size_t c = 0; c < cols; c++){
                MatT<T> lSubMat = det_sub_mat(Point(c,0));
                T lPow = (T)pow(-1,c);
                lVals.at(c) = lPow*at(Point(c,0))*lSubMat.det();
            }
            
            lRet = sum(lVals);
        }
        
        return lRet;

    }
    
    typedef MatT<double> MatF;
    typedef std::vector<MatT<unsigned char> > MatImageC;
    typedef std::vector<MatT<unsigned short> > MatImageUS;
    typedef std::vector<MatT<unsigned int> > MatImageUI;
    typedef std::vector<MatT<float> > MatImageF;
    typedef std::vector<MatT<double> > MatImageD;
}




#endif	/* GLCH_MATT_H */

