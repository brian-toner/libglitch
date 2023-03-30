/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fft.h
 * Author: brian
 *
 * Created on June 25, 2017, 7:27 PM
 */

#ifndef GLCH_FFT_H
#define GLCH_FFT_H

#include <complex>
#include <iostream>
#include <valarray>

namespace glch{
    typedef std::complex<double> GLCHComplex;
    typedef std::valarray<GLCHComplex> GLCHCArray;

    void fft(GLCHCArray& x);
    void ifft(GLCHCArray& x);

}


#endif /* GLCH_FFT_H */

