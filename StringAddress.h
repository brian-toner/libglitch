/* 
 * File:   StringAddress.h
 * Author: brian
 *
 * Created on July 5, 2015, 12:19 PM
 */

#ifndef STRINGADDRESS_H
#define	STRINGADDRESS_H

#include <iostream>
#include <string>
#include <vector>

#include "stringconversion.h"

namespace glch{

    /**
     * Locates the position in the string where the maximum valued argument marker.
     * @param aInput Argument string. 
     * @param aMarker Argument identifier
     * @return Position of the largest argument.
     */
    size_t find_max_arg(const std::vector<std::string> &aInput, std::string aMarker = "%");
    
    /**
     * Locates the position in the string where the lowest valued argument marker.
     * @param aInput Argument string. 
     * @param aMarker Argument identifier
     * @return Position of the smallest argument.
     */    
    size_t find_min_arg(std::string aInput, std::string aMarker = "%");
    
    /**
     * Counts the number of arguments in the input string.
     * @param aInput The string with arguments to count.
     * @param aMarker The argument marker, by default '%'
     * @return The number of arguments in the Input.
     */    
    size_t count_args(std::string aInput, std::string aMarker = "%");
    
    /**
     * Reports the number of the argument at pos (i.e. %11 -> 11)  
     * @param aInput The input argument string.
     * @param aPos The position of the argument.  Will return (size_t)-1 if
     * there is not an argument located at the position.
     * @param aMarker The argument marker, default '%'
     * @return The number of the argument.
     */    
    size_t arg_at(std::string aInput, size_t aPos, std::string aMarker = "%");

    /**
     * Compares two strings with arguments
     * @param aInput1 First argument string.
     * @param aInput2 Second argument string.
     * @param aMarker Argument identifier
     * @return True if Input1 has a smaller min address than Input2.
     */
    bool compare_arg_str(std::string aInput1, std::string aInput2);

}

#endif	/* STRINGADDRESS_H */

