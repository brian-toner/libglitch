/* 
 * File:   NDPoint.h
 * Author: brian
 *
 * Created on May 14, 2015, 11:53 AM
 */

#ifndef NDPOINT_H
#define	NDPOINT_H

#include <vector>
#include <iostream>

using std::size_t;

class NDPoint {
public:
    NDPoint();
    NDPoint(const NDPoint& orig);
    virtual ~NDPoint();
    
    NDPoint(size_t arg1);
    NDPoint(size_t arg1, size_t arg2);
    NDPoint(size_t arg1, size_t arg2, size_t arg3);
    NDPoint(size_t arg1, size_t arg2, size_t arg3, size_t arg4);
    NDPoint(size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5);
    NDPoint(size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6);
    NDPoint(size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6, size_t arg7);
    NDPoint(size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6, size_t arg7, size_t arg8);
    NDPoint(size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6, size_t arg7, size_t arg8, size_t arg9);  
    NDPoint(size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6, size_t arg7, size_t arg8, size_t arg9, size_t arg10);
    
    std::vector<size_t> vPoints;
private:

};

#endif	/* NDPOINT_H */

