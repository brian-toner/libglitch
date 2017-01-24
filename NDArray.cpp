/* 
 * File:   NDArray.cpp
 * Author: brian
 * 
 * Created on May 14, 2015, 6:24 AM
 */

#include "NDArray.h"

NDArray::NDArray() {
}

NDArray::NDArray(const NDArray& orig) {
}

NDArray::~NDArray() {
}

void NDArray::set_number_dims(size_t aNumberOfDims){
    vDims.resize(aNumberOfDims);
    return;
}

void NDArray::set_dim(size_t aDimNumber, size_t aDimSize){
    if(aDimNumber > vDims.size()){
        std::cout << "Invalid Dimension: " << aDimNumber << std::endl;
        return;
    } else {
        vDims.at(aDimNumber) = aDimSize;
    }

    return;
}

void NDArray::set_dims(size_t *aDims, size_t aNDims){
    vDims.resize(aNDims);
    
    for(int i = 0; i < aNDims; i++){
        vDims.at(i) = aDims[i];
    }
    
    return;
}

void NDArray::set_dims(const std::vector<size_t> &aDims){
    vDims = aDims;
    
    return;
}

void NDArray::set_dims(NDPoint aDims){
    vDims = aDims.vPoints;
}

void NDArray::resize(size_t *aDims, size_t aNDims){
    
    set_dims(aDims,aNDims);
    resize();
    
    return;
}

void NDArray::resize(NDPoint aDims){
    set_dims(aDims);
    resize();
}

void NDArray::resize(){
    
    vSizes.resize(vDims.size()+1);
    
    if(vDims.size() == 0){
        std::cout << "Warning, resizing array to 0" << std::endl;
        return;
    }
    
    vSizes.at(0) = 1;
    
    int i = 1;
    for(std::vector<size_t>::iterator it = vDims.begin(); it != vDims.end(); it++, i++){
        vSizes.at(i) = vSizes.at(i-1)*(*it);
    }
    
    vData.resize(vSizes.back());
    
    return;
}

void NDArray::info(){
    
    std::cout << "Dimensions:" << std::endl;
    int i = 0;
    for(std::vector<size_t>::iterator it = vDims.begin(); it != vDims.end(); it++, i++){
        std::cout << i << " : " << (*it) << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "Sizes:" << std::endl;
    i = 0;
    for(std::vector<size_t>::iterator it = vSizes.begin(); it != vSizes.end(); it++, i++){
        std::cout << i << " : " << (*it) << std::endl;
    }
    std::cout << std::endl;
}

size_t NDArray::get_coord(size_t aElement, size_t aDim){
    return aElement/vSizes.at(aDim)%vDims.at(aDim);
}

void NDArray::print_element(std::vector<size_t> aCoords){
    print_element(&aCoords.at(0),aCoords.size());
    return;
}

void NDArray::print_element(size_t* aCoords, size_t aNDims){
    size_t lElement = 0;
    
    std::cout << "Element:" << std::endl;
    for(int i = 0; i < aNDims; i++){   
        lElement += aCoords[i]*vSizes.at(i);
        std::cout << aCoords[i] << " : " << vSizes.at(i) << std::endl;
    } 
    
    std::cout << lElement << std::endl;
    return;
}

void NDArray::print_element(NDPoint aCoords){
    print_element(&aCoords.vPoints.at(0),aCoords.vPoints.size());
    return;
}

void NDArray::print_coord(size_t aElement){
    
    int i = 0;
    for(std::vector<size_t>::iterator it = vDims.begin(); it != vDims.end(); it++, i++){
        std::cout << i << " : " << get_coord(aElement,i) << std::endl;
    }
    std::cout << std::endl;
    
}

void NDArray::print_data(){
    
    int i = 0;
    for(std::vector<uchar>::iterator it = vData.begin(); it != vData.end(); it++, i++){
        
        for(std::vector<size_t>::iterator itj = vSizes.begin()+1; itj != vSizes.end(); itj++){
            if( (i%(*itj)) == 0){
                //std::cout << i << " : " << (*itj) << std::endl;
                std::cout << std::endl;
            }
        }
        
        if((*it) == 0x00){
            std::cout << " :";
        } else {
            std::cout << (*it) << ":";
        }
        
    }
    std::cout << std::endl;
}

size_t NDArray::get_index(size_t* aCoords, size_t aNDims){
    size_t lElement = 0;

    for(int i = 0; i < aNDims; i++){
        
        lElement += aCoords[i]*vSizes.at(i);
    } 
    
    return lElement;
}

size_t NDArray::get_index(std::vector<size_t> &aCoords){
    return get_index(&aCoords.at(0), aCoords.size());
}

size_t NDArray::get_index(NDPoint aCoords){
    return get_index(&aCoords.vPoints.at(0),aCoords.vPoints.size());
}