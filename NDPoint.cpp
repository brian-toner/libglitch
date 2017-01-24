/* 
 * File:   NDPoint.cpp
 * Author: brian
 * 
 * Created on May 14, 2015, 11:53 AM
 */

#include "NDPoint.h"

NDPoint::NDPoint() {
}

NDPoint::NDPoint(const NDPoint& orig) : vPoints(orig.vPoints) {
}

NDPoint::~NDPoint() {
}

NDPoint::NDPoint(size_t arg1){
    vPoints.push_back(arg1);
}
    
NDPoint::NDPoint(size_t arg1, size_t arg2){
    vPoints.push_back(arg1);
    vPoints.push_back(arg2);
}

NDPoint::NDPoint(size_t arg1, size_t arg2, size_t arg3){
    vPoints.push_back(arg1);
    vPoints.push_back(arg2);
    vPoints.push_back(arg3);
}

NDPoint::NDPoint(size_t arg1, size_t arg2, size_t arg3, size_t arg4){
    vPoints.push_back(arg1);
    vPoints.push_back(arg2);
    vPoints.push_back(arg3);
    vPoints.push_back(arg4);
}

NDPoint::NDPoint(size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5){
    vPoints.push_back(arg1);
    vPoints.push_back(arg2);
    vPoints.push_back(arg3);
    vPoints.push_back(arg4);
    vPoints.push_back(arg5);
} 

NDPoint::NDPoint(size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6){
    vPoints.push_back(arg1);
    vPoints.push_back(arg2);
    vPoints.push_back(arg3);
    vPoints.push_back(arg4);
    vPoints.push_back(arg5);
    vPoints.push_back(arg6);
} 

NDPoint::NDPoint(size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6, size_t arg7){
    vPoints.push_back(arg1);
    vPoints.push_back(arg2);
    vPoints.push_back(arg3);
    vPoints.push_back(arg4);
    vPoints.push_back(arg5);
    vPoints.push_back(arg6);
    vPoints.push_back(arg7);
} 

NDPoint::NDPoint(size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6, size_t arg7, size_t arg8){
    vPoints.push_back(arg1);
    vPoints.push_back(arg2);
    vPoints.push_back(arg3);
    vPoints.push_back(arg4);
    vPoints.push_back(arg5);
    vPoints.push_back(arg6);
    vPoints.push_back(arg7);
    vPoints.push_back(arg8);
} 

NDPoint::NDPoint(size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6, size_t arg7, size_t arg8, size_t arg9){
    vPoints.push_back(arg1);
    vPoints.push_back(arg2);
    vPoints.push_back(arg3);
    vPoints.push_back(arg4);
    vPoints.push_back(arg5);
    vPoints.push_back(arg6);
    vPoints.push_back(arg7);
    vPoints.push_back(arg8);
    vPoints.push_back(arg9);
}    

NDPoint::NDPoint(size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6, size_t arg7, size_t arg8, size_t arg9, size_t arg10){
    vPoints.push_back(arg1);
    vPoints.push_back(arg2);
    vPoints.push_back(arg3);
    vPoints.push_back(arg4);
    vPoints.push_back(arg5);
    vPoints.push_back(arg6);
    vPoints.push_back(arg7);
    vPoints.push_back(arg8);
    vPoints.push_back(arg9);
    vPoints.push_back(arg10);
}