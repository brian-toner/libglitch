/* 
 * File:   StringAddress.cpp
 * Author: brian
 * 
 * Created on July 5, 2015, 12:19 PM
 */

#include "StringAddress.h"

namespace glch{

    /**
     * Counts the number of arguments in the input string.
     * @param aInput The string with arguments to count.
     * @param aMarker The argument marker, by default '%'
     * @return The number of arguments in the Input.
     */
    size_t count_args(std::string aInput, std::string aMarker){

        size_t lReturn = 0;
        size_t lSearch = aInput.find(aMarker);

        while(lSearch != std::string::npos){
            std::string lTemp = aInput.substr(lSearch+aMarker.length());
            size_t lArgNumb = string_number_length(lTemp);
            lTemp = lTemp.substr(0,lArgNumb);
            lArgNumb = string_to_type<size_t>(lTemp);

            lReturn ++;

            lSearch = aInput.find(aMarker, lSearch+aMarker.length());   
        }

        return lReturn;

    }

    /**
     * Reports the number of the argument at pos (i.e. %11 -> 11)  
     * @param aInput The input argument string.
     * @param aPos The position of the argument.  Will return (size_t)-1 if
     * there is not an argument located at the position.
     * @param aMarker The argument marker, default '%'
     * @return The number of the argument.
     */
    size_t arg_at(std::string aInput, size_t aPos, std::string aMarker){

        size_t lReturn = (size_t)-1;
        size_t lArgNumb;
        std::string lTemp = aInput.substr(aPos+aMarker.length());
        std::string lChkMarker = aInput.substr(aPos,aMarker.length());
        
        if(lChkMarker.compare(aMarker) != 0){
            return lReturn;
        }
        
        lArgNumb = string_number_length(lTemp);
        
        if(lArgNumb > 0){
            lTemp = lTemp.substr(0,lArgNumb);
            lReturn = string_to_type<size_t>(lTemp);
        }
        
        return lReturn;    

    }

    /**
     * Locates the position in the string where the maximum valued argument marker.
     * @param aInput Argument string. 
     * @param aMarker Argument identifier
     * @return Position of the largest argument.
     */
    size_t find_max_arg(const std::vector<std::string> &argInVect, std::string aAddressMarker){

        size_t locReturn = 0;

        for(long unsigned int i = 0; i < argInVect.size(); i++){

            long unsigned int locSearch = argInVect.at(i).find(aAddressMarker);

            while(locSearch != std::string::npos){
                std::string locTemp = argInVect.at(i).substr(locSearch+aAddressMarker.length());
                long unsigned int locArgNumb = string_number_length(locTemp);
                locTemp = locTemp.substr(0,locArgNumb);
                locArgNumb = string_to_type<size_t>(locTemp);

                if(locArgNumb > locReturn){
                    locReturn = locArgNumb;
                }

                locSearch = argInVect.at(i).find(aAddressMarker, locSearch+aAddressMarker.length());   
            }
        }

        return locReturn;

    }


    /**
     * Locates the position in the string where the lowest valued argument marker.
     * @param aInput Argument string. 
     * @param aMarker Argument identifier
     * @return Position of the smallest argument.
     */
    size_t find_min_arg(std::string aInput, std::string aMarker){

        size_t lReturn = std::string::npos;
        size_t lSearch = aInput.find(aMarker);

        while(lSearch != std::string::npos){
            std::string lTemp = aInput.substr(lSearch+aMarker.length());
            size_t lArgMarker = string_number_length(lTemp);
            
            
            if(lArgMarker > 0){
                lTemp = lTemp.substr(0,lArgMarker);
                lArgMarker = string_to_type<size_t>(lTemp);
                
                if(lArgMarker < lReturn){
                    lReturn = lArgMarker;
                }
            }
            
            lSearch = aInput.find(aMarker, lSearch+aMarker.length()); 
             
        }

        return lReturn;

    }


    /**
     * Compares two strings with arguments
     * @param aInput1 First argument string.
     * @param aInput2 Second argument string.
     * @param aMarker Argument identifier
     * @return True if Input1 has a smaller min address than Input2.
     */
    bool compare_arg_str(std::string aInput1, std::string aInput2){
        return find_min_arg(aInput1) < find_min_arg(aInput2);
    }


}

