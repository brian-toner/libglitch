/* 
 * File:   OrderPair.h
 * Author: brian
 *
 * Created on April 19, 2015, 4:40 PM
 */

#ifndef ORDERPAIR_H
#define	ORDERPAIR_H

#include <vector>
#include <iostream>

namespace glch{

    template <class T>
    struct PairT{
        size_t first;
        T second;

        PairT(){
            first = (size_t)-1;
        }

        PairT(size_t aFirst, T aSecond){
            first = aFirst;
            second = aSecond;
        }

        PairT(const PairT &orig) : first(orig.first), second(orig.second){};

        bool operator>(const PairT<T> &aRight) const {
            return second > aRight.second;
        }

        bool operator<(const PairT<T> &aRight) const {
            return second < aRight.second;
        }

        bool operator==(const PairT<T> &aRight) const {
            return second == aRight.second;
        }    

        bool operator>=(const PairT<T> &aRight) const {
            return second >= aRight.second;
        }    

        bool operator<=(const PairT<T> &aRight) const {
            return second <= aRight.second;
        }    
    };

    typedef PairT<int> pair_int;


    template <class T>
    bool compare_sort_pair( const PairT<T> &aLeft, const PairT<T> &aRight){ 
        return aLeft.second > aRight.second; 
    }


}

#endif	/* ORDERPAIR_H */

