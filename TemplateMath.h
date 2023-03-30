/* 
 * File:   TemplateMath.h
 * Author: brian
 *
 * Created on July 7, 2015, 11:23 AM
 */

#ifndef GLCH_TEMPLATEMATH_H
#define	GLCH_TEMPLATEMATH_H

namespace glch{

    /**
     * Multiplication operation.  Intended to be used by apply.
     * @param arg1 First value.
     * @param arg2 Second value.
     * @return arg1*arg2
     */    
    template <class T>
    T mul(T arg1, T arg2){
        return arg1*arg2;
    }

    /**
     * Addition operation.  Intended to be used by apply.
     * @param arg1 First value.
     * @param arg2 Second value.
     * @return arg1+arg2
     */    
    template <class T>
    T add(T arg1, T arg2){
        T locReturn = arg1+arg2;
        return locReturn;
    }

    /**
     * Modulus operation.  Intended to be used by apply.
     * @param arg1 First value.
     * @param arg2 Second value.
     * @return arg1%arg2
     */    
    template <class T>
    T mod(T arg1, T arg2){
        T locReturn = arg1%arg2;
        return locReturn;
    }

    /**
     * Subtraction operation.  Intended to be used by apply.
     * @param arg1 First value.
     * @param arg2 Second value.
     * @return arg1-arg2
     */
    template <class T>
    T sub(T arg1, T arg2){
        return arg1-arg2;
    }

    /**
     * Division operation.  Intended to be used by apply.
     * @param arg1 First value.
     * @param arg2 Second value.
     * @return arg1/arg2
     */
    template <class T>
    T div(T arg1, T arg2){
        return arg1/arg2;
    }

    /**
     * Sums the values in a vector.
     * @param aVector Vector being summed across.
     * @return The sum of all the elements of the vector.
     */
    template <class T>
    double sum(std::vector<T> aVector){
        return sum_vector(aVector);
    }

    /**
     * Computes the sign of the value.  Returns 1 if Val >= 0, -1 otherwise.
     * @param aVal Value we are taking the sign of.
     * @return The sign of the input value.
     */
    template <class T>
    double sign(T aVal){
        return (aVal >= 0)?1.0:-1.0;
    }

    /**
     * Applies an operation to two vectors.  If one vector is larger than the other
     * then the vector is resized to match the size difference.  The added elements
     * are treated as zeroes.
     * @param aV1 First vector.
     * @param aV2 Second vector.
     * @param fn Operation being applied to the vectors.
     * @return A new vector with the results from the operation on V1 and V2.
     */
    template <class T>
    std::vector<T> apply(std::vector<T> &aV1, std::vector<T> &aV2, T (*fn)(T,T)){
        std::vector<T> lRet(aV1.size(),0);
        size_t lV1Size = aV1.size();
        size_t lV2Size = aV2.size();

        //This is a bit of a mess, but doing it this way prevents a full copy of both variables
        //Resize V2 if V1 has more elements
        if(lV1Size > lV2Size){

            std::vector<T> lV2 = aV2;
            lV2.resize(lV2Size);

            for(size_t i = 0; i < lV1Size; i++){
                lRet.at(i) = fn(aV1.at(i),lV2.at(i));
            }
        //Resize V1 if V2 has more elements
        } else if (lV1Size < lV2Size){

            std::vector<T> lV1 = aV1;
            lV1.resize(lV2Size);
            lRet.resize(lV2Size,0);

            for(size_t i = 0; i < lV2Size; i++){
                lRet.at(i) = fn(lV1.at(i),aV2.at(i));
            }
        //Compute the direct result if both have the same size.  
        } else {

            for(size_t i = 0; i < lV1Size; i++){
                lRet.at(i) = fn(aV1.at(i),aV2.at(i));
            }
        }

        return lRet;
    }

    /**
     * Applies a scalar to a vector through the function.
     * @param aV1 First vector.
     * @param aV2 Second vector.
     * @param fn Operation being performed.
     * @return A new vector with the results from the operation on V1 and V2.
     */
    template <class T>
    std::vector<T> apply(std::vector<T> &aV1, T aV2, T (*fn)(T,T)){
        std::vector<T> lV2(aV1.size(),aV2);
        return apply(aV1,lV2,fn);
    }

}

#endif	/* GLCH_TEMPLATEMATH_H */

