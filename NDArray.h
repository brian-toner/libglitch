/* 
 * File:   NDArray.h
 * Author: brian
 *
 * Created on May 14, 2015, 6:24 AM
 */

#ifndef NDARRAY_H
#define	NDARRAY_H

#include <vector>
#include <iostream>
#include "NDPoint.h"

#ifndef uchar
typedef unsigned char uchar;
#endif

using std::size_t;

class NDArray {
public:
    NDArray();
    NDArray(const NDArray& orig);
    virtual ~NDArray();
    
    std::vector<size_t> vDims;
    std::vector<uchar> vData;
    std::vector<size_t> vSizes;
    
    /**
     * Returns the dimension size of the requested dimension.
     * @param aDimNumber The index of the dimension of interest
     * @return The size of the requested dimension.
     */
    size_t dim(size_t aDimNumber);
    void set_number_dims(size_t aNumberOfDims);
    void set_dim(size_t aDimNumber, size_t aDimSize);
    void set_dims(size_t *aDims, size_t aNDims);
    void set_dims(const std::vector<size_t> &aDims);
    void set_dims(NDPoint aDims);
    void resize();
    void resize(size_t *aDims, size_t aNDims);
    void resize(NDPoint aDims);
    void info();
    inline size_t get_coord(size_t aElement, size_t aDim);
    void print_element(std::vector<size_t> aCoords);
    void print_element(size_t* aCoords, size_t aNDims);
    void print_element(NDPoint aCoords);
    void print_coord(size_t aElement);
    void print_data();
    
    size_t get_index(NDPoint aCoords);
    size_t get_index(std::vector<size_t> &aCoords);
    size_t get_index(size_t* aCoords, size_t aNDims);
    
    template <class T>
    T& at(size_t aElement){
        return *(T*)(&vData.at(aElement)) ;
    }
    
    template <class T>
    T& at(NDPoint aCoords){
        return *(T*)&vData.at(get_index(aCoords));
    }
    
    template <class T>
    T& at(std::vector<size_t> &aCoords){
        return *(T*)&vData.at(get_index(aCoords));
    }
    
    template <class T>
    T& at(size_t* aCoords, size_t aNDims){
        return *(T*)&vData.at(get_index(aCoords,aNDims));
    }
private:

};

#endif	/* NDARRAY_H */

