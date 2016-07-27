/* 
 * File:   RectListT.h
 * Author: brian
 *
 * Created on January 4, 2016, 7:40 PM
 */

#ifndef RECTLISTT_H
#define	RECTLISTT_H

#include <vector>
#include "RectT.h"

namespace glch{

    #ifndef IndexList
        typedef std::vector<size_t> IndexList;
    #endif

    #ifndef IndexArray
        typedef std::vector< IndexList > IndexArray;
    #endif
    
    template <class T>
    class RectListT {
    public:
        RectListT(){};
        RectListT(const RectListT& orig){};
        virtual ~RectListT(){};
        
        std::vector<RectT<T> > vData;
        
        void resize_rects(double argReduceSizeRatio){

            for(size_t i = 0; i < size(); i++){
                at(i).resize(argReduceSizeRatio);
            }            
            
        }

        void resize_rects(Rect argMinSize, Rect argMaxSize){

            for(size_t i = 0; i < size(); i++){
                at(i).resize(argMinSize, argMaxSize);
            }
            
        }
        
        void filter_duplicate_rects(double aOverlap){

            std::vector<RectT<T> > locOutRect;

            for(size_t i = 0; i < size(); i++){
                bool tempCopy = true;
                if( rect_list_contains_similar(locOutRect, at(i),aOverlap ) ){
                    tempCopy = false;
                }
                    
                if(tempCopy){
                    locOutRect.push_back(at(i));
                }
            }

            vData = locOutRect;

        }

        void filter_duplicate_rects(double aOverlap, double aDistance){

            std::vector<RectT<T> > locOutRect;

            for(size_t i = 0; i < size(); i++){
                bool tempCopy = true;
                if( rect_list_contains_similar(locOutRect, at(i),aOverlap,aDistance) ){
                    tempCopy = false;
                }
                    
                if(tempCopy){
                    locOutRect.push_back(at(i));
                }
            }

            vData = locOutRect;

        }        
        
        void to_squares(){
            for(size_t i = 0; i < size(); i++){
                vData.at(i).to_square();
            }
            
        }
        
        template <class U>
        bool contains_similar(RectT<U> lRect, double aOverlap){
            return rect_list_contains_similar(vData,lRect,aOverlap);
        }

        template <class U>
        bool contains_similar(RectT<U> lRect, double aOverlap,double aDistance){
            return rect_list_contains_similar(vData,lRect,aOverlap,aDistance);
        }
        
        void filter_similar_merge(double aOverlap){
            
            IndexArray lIndexArray = find_list_all_similar_rects(vData,aOverlap);
            std::vector< RectT<T> > lRects;
            std::vector< RectT<T> > lTempRects;
            
            for(int i = 0; i < lIndexArray.size(); i++){
                for(size_t j = 0; j < lIndexArray.at(i).size(); j++){
                    size_t lIndex = lIndexArray.at(i).at(j);
                    lTempRects.push_back( at(lIndex ) );
                }
                
                lRects.push_back(merge_rects(lTempRects));
                lTempRects.clear();
                
            }
            
            vData = lRects;
            
        }

        void filter_similar_merge(double aOverlap, double aDistance){
            
            IndexArray lIndexArray = find_list_all_similar_rects(vData,aOverlap, aDistance);
            std::vector< RectT<T> > lRects;
            std::vector< RectT<T> > lTempRects;
            
            for(int i = 0; i < lIndexArray.size(); i++){
                for(size_t j = 0; j < lIndexArray.at(i).size(); j++){
                    size_t lIndex = lIndexArray.at(i).at(j);
                    lTempRects.push_back( at(lIndex ) );
                }
                
                lRects.push_back(merge_rects(lTempRects));
                lTempRects.clear();
                
            }
            
            vData = lRects;
            
        }
                
        void filter_similar_average(double aOverlap){
            
            IndexArray lIndexArray = find_list_all_similar_rects(vData,aOverlap);
            std::vector< RectT<T> > lRects;
            std::vector< RectT<T> > lTempRects;
            
            for(size_t i = 0; i < lIndexArray.size(); i++){
                for(size_t j = 0; j < lIndexArray.at(i).size(); j++){
                    size_t lIndex = lIndexArray.at(i).at(j);
                    lTempRects.push_back( at(lIndex ) );
                }
                
                lRects.push_back(average_rects(lTempRects));
                lTempRects.clear();
                
            }
            
            vData = lRects;
            
        }
        
        void filter_similar_average(double aOverlap, double aDistance){
            
            IndexArray lIndexArray = find_list_all_similar_rects(vData,aOverlap,aDistance);
            std::vector< RectT<T> > lRects;
            std::vector< RectT<T> > lTempRects;
            
            for(int i = 0; i < lIndexArray.size(); i++){
                for(size_t j = 0; j < lIndexArray.at(i).size(); j++){
                    size_t lIndex = lIndexArray.at(i).at(j);
                    lTempRects.push_back( at(lIndex ) );
                }
                
                lRects.push_back(average_rects(lTempRects));
                lTempRects.clear();
                
            }
            
            vData = lRects;
            
        }        
        
        RectT<T>& at(size_t aIndex){
            return vData.at(aIndex);
        }
        
        size_t size(){
            return vData.size();
        }
        
        void print(){
            for(size_t i = 0; i < size(); i++){
                at(i).print();
            }
        }
        
    private:

    };


    template <class T>
    bool rect_list_contains_similar(std::vector<RectT<T> > lRectList, RectT<T> lRect, double aOverlap){

        for(size_t i = 0; i < lRectList.size(); i++){
            if(lRectList.at(i) == lRect){
                return true;
            }

            if(lRectList.at(i).overlap_ratio(lRect) >= aOverlap || lRect.overlap_ratio(lRectList.at(i))){
                return true;
            }
        }

        return false;
    }
    
    template <class T, class U>
    std::vector<RectT<T> > find_similar_rects(std::vector<RectT<T> > &lRectList, RectT<U> lRect, double aOverlap){
        std::vector<RectT<T> > lSimliarRects;

        for(size_t i = 0; i < lRectList.size(); i++){
            if(lRect.similar(lRectList.at(i),aOverlap)){
                lSimliarRects.push_back(lRectList.at(i));
            }
        }

        return lSimliarRects;
    }

    template <class T, class U>
    std::vector<RectT<T> > find_similar_rects(std::vector<RectT<T> > &lRectList, RectT<U> lRect, double aOverlap, double aDistance){
        std::vector<RectT<T> > lSimliarRects;

        for(size_t i = 0; i < lRectList.size(); i++){
            if(lRect.similar(lRectList.at(i),aOverlap,aDistance)){
                lSimliarRects.push_back(lRectList.at(i));
            }
        }

        return lSimliarRects;
    }    
    
    template <class T, class U>
    std::vector<size_t > find_similar_rects_index(std::vector<RectT<T> > &lRectList, RectT<U> lRect, double aOverlap){
        std::vector<size_t> lSimilarRects;

        for(size_t i = 0; i < lRectList.size(); i++){
            if(lRect.similar(lRectList.at(i),aOverlap)){
                lSimilarRects.push_back(i);
            }
        }

        return lSimilarRects;
    }

    template <class T, class U>
    std::vector<size_t > find_similar_rects_index(std::vector<RectT<T> > &lRectList, RectT<U> lRect, double aOverlap, double aDistance){
        std::vector<size_t> lSimilarRects;

        for(size_t i = 0; i < lRectList.size(); i++){
            if(lRect.similar(lRectList.at(i),aOverlap,aDistance)){
                lSimilarRects.push_back(i);
            }
        }

        return lSimilarRects;
    }
    
    template <class T>
    void find_all_similar_rects_index(std::vector<RectT<T> > &lRectList, std::vector<size_t> &aIndexList, size_t aIndex, double aOverlap){
        std::vector<size_t> lSimilarRects;

        if(aIndex >= aIndexList.size()){
            return;
        }
        
        lSimilarRects = find_similar_rects_index(lRectList,lRectList.at(aIndexList.at(aIndex)),aOverlap);
        
        for(size_t i = 0; i < lSimilarRects.size(); i++){ 
        
            bool lPush = true;
            for(size_t j = 0; j < aIndexList.size(); j++){
                if(aIndexList.at(j) == lSimilarRects.at(i)){
                    lPush = false;
                    break;
                }
            }
            if(lPush){
                aIndexList.push_back(lSimilarRects.at(i));
            }
            
        }

        find_all_similar_rects_index(lRectList,aIndexList,aIndex+1,aOverlap);
    }

    template <class T>
    void find_all_similar_rects_index(std::vector<RectT<T> > &lRectList, std::vector<size_t> &aIndexList, size_t aIndex, double aOverlap, double aDistance){
        std::vector<size_t> lSimilarRects;

        if(aIndex >= aIndexList.size()){
            return;
        }
        
        lSimilarRects = find_similar_rects_index(lRectList,lRectList.at(aIndexList.at(aIndex)),aOverlap,aDistance);
        
        for(size_t i = 0; i < lSimilarRects.size(); i++){ 
        
            bool lPush = true;
            for(size_t j = 0; j < aIndexList.size(); j++){
                if(aIndexList.at(j) == lSimilarRects.at(i)){
                    lPush = false;
                    break;
                }
            }
            if(lPush){
                aIndexList.push_back(lSimilarRects.at(i));
            }
            
        }

        find_all_similar_rects_index(lRectList,aIndexList,aIndex+1,aOverlap);
    }    
    
    template <class T>
    IndexArray find_list_all_similar_rects(std::vector<RectT<T> > &lRectList, double aOverlap){
        std::vector<size_t> lIndex;
        std::vector<bool> lMask(lRectList.size(),true);
        IndexArray lRet;
        
        for(size_t i = 0; i < lRectList.size(); i++){
            if(lMask.at(i)){
                lIndex.clear();
                lIndex.push_back(i);
                find_all_similar_rects_index(lRectList,lIndex,0,aOverlap);
                
                for(size_t j = 0; j < lIndex.size(); j++){
                    lMask.at(lIndex.at(j)) = false;
                }

                if(lIndex.size() > 0){
                    lRet.push_back(lIndex);
                }
            }
            
        }
        
        return lRet;
        
        
    }
    
    template <class T>
    IndexArray find_list_all_similar_rects(std::vector<RectT<T> > &lRectList, double aOverlap, double aDistance){
        std::vector<size_t> lIndex;
        std::vector<bool> lMask(lRectList.size(),true);
        IndexArray lRet;
        
        for(size_t i = 0; i < lRectList.size(); i++){
            if(lMask.at(i)){
                lIndex.clear();
                lIndex.push_back(i);
                find_all_similar_rects_index(lRectList,lIndex,0,aOverlap,aDistance);
                
                for(size_t j = 0; j < lIndex.size(); j++){
                    lMask.at(lIndex.at(j)) = false;
                }

                if(lIndex.size() > 0){
                    lRet.push_back(lIndex);
                }
            }
            
        }
        
        return lRet;
        
        
    }    
    
    template <class T>
    RectT<T> average_rects(std::vector<RectT<T> > lRectList){
        RectT<T> lRect;
        for(size_t i = 0; i < lRectList.size(); i++){
            lRect.x += lRectList.at(i).x;
            lRect.y += lRectList.at(i).y;
            lRect.width += lRectList.at(i).width;
            lRect.height += lRectList.at(i).height;
        }
        
        lRect.x /= lRectList.size();
        lRect.y /= lRectList.size();
        lRect.width /= lRectList.size();
        lRect.height /= lRectList.size();
        
        return lRect;
    }

    template <class T>
    RectT<T> merge_rects(std::vector<RectT<T> > lRectList){
        RectT<T> lRect = lRectList.at(0);
        
        for(size_t i = 1; i < lRectList.size(); i++){
            lRect = lRect.get_merged_rect(lRectList.at(i));
        }
 
        return lRect;
    }
    
    
}

#endif	/* RECTLISTT_H */

