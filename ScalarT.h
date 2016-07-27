/* 
 * File:   ScalarT.h
 * Author: brian
 *
 * Created on July 4, 2015, 10:34 PM
 */

#ifndef SCALART_H
#define	SCALART_H

namespace glch{

template <class T>
struct ScalarT{
    T val[4];
    
    ScalarT(){
        val[0] = 0;
        val[1] = 0;
        val[2] = 0;
        val[3] = 0;
    }
    
    ScalarT(T arg0, T arg1 = 0, T arg2 = 0, T arg3 = 0){
        val[0] = arg0;
        val[1] = arg1;
        val[2] = arg2;
        val[3] = arg3;
    }
    
    ScalarT(const ScalarT &orig){
        val[0] = orig.val[0];
        val[1] = orig.val[1];
        val[2] = orig.val[2];
        val[3] = orig.val[3];
    }
    
};

typedef ScalarT<double> ScalarF; 


}

#endif	/* SCALART_H */

