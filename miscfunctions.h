/* 
 * File:   miscfunctions.h
 * Author: brian
 *
 * Created on April 21, 2015, 10:13 AM
 */

#ifndef GLCH_MISCFUNCTIONS_H
#define	GLCH_MISCFUNCTIONS_H

#include <vector>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include <algorithm>


namespace glch{
    
    int year();

    int month();
    
    int day(); 

    std::string wday();
    
    int hour();     

    int minute();

    int second();
    
    float usecond();
    
    /**
    * Copies one data vector to another.
    * @param aBegin The pointer to the destination vector.
    * @param aDataStart The pointer to the source vector.
    * @param aDataEnd The pointer to the element after the last element of the source vector.
    */
   void copy_data_vector(char* aDst, const char* aDataStart, const char* aDataEnd);

    /**
     * Finds ideal dimensions for a matrix with aSize elements
     * @param aSize Number of elements.
     * @return vector of two elements containing the size of the matrix.
     */
    std::vector<int> find_dims(int aSize);

    /**
     * Computes n choose k using the standard gamma function.
     * @param n Value of n.
     * @param k Value of k.
     * @return gamma(n+1)/(gamma(k+1)*gamma(n-k+1))
     */
    inline double n_choose_k(double n, double k){
        return lgamma(n+1)/(lgamma(k+1)*lgamma(n-k+1));   
    }

    /**
     * Recursively computes factorial.
     * @param x Value we are computing factorial of.
     * @return Factorial of x.
     */
    inline double factorial(double x) {
        return (x == 1 ? x : x * factorial(x - 1));
    }

    /**
     * Finds the factors of the input value.
     * @param aValue Value we are finding the factors of.
     * @return List of all the factors of the input value.
     */
    template <class T>
    std::vector<T> find_factors(T aValue){
        std::vector<T> lFactors;      //Output factors
        T lSize = aValue;             //We use this to scan through the factors.
        T lCurrentFactor = 1;         //Which factor we are currently on.
        
        for ( T i = 2; i <= lSize; ++i ){

            while ( lSize % i == 0 ) {
                //Check if the value we are modding out by is in the output.
                if(!value_in_vector(lFactors,i)){
                    lFactors.push_back(i);
                }
                lSize /= i;
                lFactors.push_back(lSize);
                lCurrentFactor++;
            }

        }
        
        std::sort(lFactors.rbegin(),lFactors.rend());
        return lFactors;
    }    
    
    /**
     * Maps one set of numbers into another set.
     * @param aInput: Number we are mapping from
     * @param aToRange: Range we are mapping to
     * @param aToMin: Min we are mapping to
     * @param aFromRange: Range we are mapping from.
     * @param aFromMin: Min we are mapping from
     * @return Mapped Value
     */
    double map_point(double aInput, double aToRange, double aToMin, double aFromRange, double aFromMin, bool aFlip);
    double map_point_exclude_zero(double aInput, double aToRange, double aToMin, int aFromRange, int aFromMin);
    
    double quotient(double aDividend, double aDivisor);
    double remainderf(double aDividend, double aDivisor);
    double modf(double aDividend, double aDivisor);
    
    bool power_of_two(int n,int &m,int &twopm);
    int FFT(int dir,int m, std::vector<double> &x, std::vector<double> &y);
    
    
    /**
     * Rounds a decimal value to a specified number of places
     * @param aNumber The number to round
     * @param aPlaces The number of places to round off to
     * @return The rounded number.
     */
    double round(double aNumber, int aPlaces);
    
    /**
     * Computes the percent error between the ideal value and measured value.
     * @param aIdeal Ideal value
     * @param aMeasured Measured value
     * @return The percent error between the two values.
     */
    double percent_error(double aIdeal, double aMeasured);
    
    /**
     * Converts a Pascal 48 bit real number into a double.
     * @param realValue The value to convert
     * @return The value converted into a double.
     */
    double real48ToDouble(char *aRealValue);
    
    
    double gauss(double x, double y, double x0, double y0, double A, double a, double b, double c);
    double gauss_dx(double x, double y, double x0, double y0, double A, double a, double b, double c);
    double gauss_dy(double x, double y, double x0, double y0, double A, double a, double b, double c);
    
    double normal_dist(double aX, double aMean, double aStdev);
    
    
    std::vector<unsigned long> sieve_of_eratosthenes(long x);
    unsigned long prime_upper_bound(unsigned long x);
    unsigned long approx_prime(unsigned long x);
    std::vector<unsigned long> sieve_two(unsigned long x);
    std::vector<unsigned long> primes(unsigned long x);
    unsigned long prime(unsigned long x);
    std::vector<unsigned long> factors(unsigned long x);
    //std::vector<unsigned long> triangle_sieve(unsigned long x);
    //std::vector<unsigned long> triangle_sieve_primes(unsigned long x);
     
    
    unsigned long counting_every_row(unsigned long maxPrime);
    std::vector<unsigned long> counting_every_row_all(unsigned long maxPrime);
}

#endif	/* GLCH_MISCFUNCTIONS_H */

