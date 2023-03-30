/* 
 * File:   strConvert.h
 * Author: brian
 *
 * Created on January 31, 2012, 2:41 PM
 */

#ifndef GLCH_STRCONVERTNEW_H
#define	GLCH_STRCONVERTNEW_H

#include <iostream>
#include <sstream>      //std::istringstream
#include <string>       //std::string
#include <vector>       //std::vector
#include <algorithm>    //sort
#include <limits>       //numeric_limits for NaN
#include <iomanip>      //setprecision
#include <math.h>

#include "FileLoad.h"
//#include "FileStrings.h"
#include "RuntimeErrorReport.h"

using namespace std;

namespace glch{

#define GLCH_NOT_FOUND (size_t)(-1)
    
    typedef std::vector<std::string> StringList;
    typedef std::vector<char> CharList;
    
    /**
     * Converts the string to the type of argInput
     * @param s -String we are converting from.
     * @return -Value of the converted string with type argInput
     */
    template <class T>
    inline T string_to_type(std::string const& aString)
    {
        std::istringstream lStream(aString);
        T lRet;
        
        //Pushing the stream into the return value.  If there is an error throw.
        if (!(lStream >> lRet)){
            throw RuntimeErrorReport("string_to_type(\"" + aString + "\")");
        }

        return lRet;
    }

    /**
    * Converts a wide range of data containers values into a string value (int, double, float etc)
    * using std::stringstream.  
    * @param t Argument we are converting into a string.
    * @return Returns a string value representing the input value.
    */
    template <class T>
    inline std::string to_string (const T& aInput){
        std::stringstream lStream;
        lStream << aInput;
        return lStream.str();
    }

    /**
    * Converts a wide range of data containers values into a string value (int, double, float etc)
    * using std::stringstream.  
    * @param t Argument we are converting into a string.
    * @return Returns a string value representing the input value.
    */
    template <class T>
    inline std::string to_quote_string (const T& aInput){
        std::stringstream lStream;
        lStream << aInput;
        return ("\"" + lStream.str() + "\"");
    }    

    /**
     * Deep copies a buffer of characters into a std::string
     * @param argBuffer data buffer being copied to string.
     * @param aIndex Starting index of deep copy.
     * @param aSize Number of characters being copied into the string.
     * @return New string created from the input buffer.
     */
    std::string buffer_to_string(char* aBuffer, size_t aIndex, size_t aSize);


    /**
     * Searches a vector of strings and reports back the index number of the vector 
     * where the string was located (exact match). If the string was not located in the vector then
     * (size_t)(-1) is returned.
     * @param aInput Vector of string being searched
     * @param aStringToFind String we are attempting to find in the input.
     * @return Location in the vector, otherwise (size_t)(-1)
     */
    size_t find_string_in_vect(vector<string> &aInput, string aStringToFind);
    
    
    size_t find_ignore_tolkens(std::string aString, std::string aFindValue, size_t aPosition, std::string aIgnoreTolkenStart, std::string aIgnoreTolkenEnd);
    
    /**
     * Reports if the Input contains the comparison string.  This is done through
     * the strings default find function.
     * @param aInput Input string being searched.
     * @param aStringToFind String we are attempting to find in the input.
     * @return True if the string is contained in the input, false otherwise.
     */
    bool in_str(std::string aInput, std::string aStringToFind);

    bool in_str(std::string aInput, std::vector<size_t> &aPositions, std::string aStringToFind, std::string aIgnoreTolkenStart, std::string aIgnoreTolkenEnd);    
    
    /**
     * Finds the positions of a string inside of a string.
     * @param aInput String being searched.
     * @param aPositions Locations of found strings.
     * @param aComp String being located
     * @return True if aComp was found at least once.
     */
    bool in_str(std::string aInput, std::vector<size_t> &aPositions, std::string aStringToFind);

    /**
     * Splits a string into a vector of strings at each delimitation point.
     * @param aInput Input string being split apart.
     * @param aDelim The delimitation string. 
     * @return Vector of strings.
     */
    std::vector<std::string> split_string(std::string aInput, std::string aDelim);

    std::vector<std::string> split_string(std::string aInput, std::vector<std::string> aDelim);

    std::vector<std::string> split_string(std::string aInput, std::string aDelim, std::string aIgnoreTolkenStart, std::string aIgnoreTolkenEnd);    
    
    /**
     * Removes all special characters from a string (aInput) and converts them to the 
     * delimitation character (aDelim).  Valid characters are considered letters, numbers
     * underscore period and dash.
     * @param aInput Input string being purged 
     * @param aReplaceString The string used to replace any non valid characters. 
     * @return New string with all special characters removed.
     */
    std::string deslug_string(std::string aInput, std::string aReplaceString = "_");
    
    /**
     * Removes all special characters from a string (aInput) and converts them to the 
     * delimitation character (aDelim).  Valid characters are considered letters, numbers
     * underscore period and dash.
     * @param aInput Input string being purged 
     * @param aReplaceString The string used to replace any non valid characters. 
     * @param aValidChars List of characters which will remain unchanged.
     * @return New string with all special characters removed.
     */
    std::string deslug_string(std::string aInput, std::string aReplaceString, vector<char> lValidChars);


    /**
     * Determines if the input string is actually a string encoded number.
     * If so, then return will be the length of the number.
     * This function uses: int is_number(const char*, int, int)
     * @param argInput -Input string we are checking for encoded numbers
     * @return -Length of the string encoded number, 0 if not a number.
     */
    int string_number_length(string argInput);

    
    /**
     * Runs through a string and determines if the string is an encoded number or not.
     * @param argInput Input data
     * @param aNumber Flag is set if the string is a number.
     * @param aNegative Flag is set if the string is a number and is negative.
     * @param aDecimal Flag is set if the string is a floating point number.
     * @param aBool Flag is set if the string is 'true' or 'false'.
     * @return Length of the string encoded number, 0 if not a number.
     */
    int string_number_length(string aInput,  bool &aNumber, bool &aNegative, bool &aDecimal, bool &aBool);
    
    /**
     * Determines if a string is a negative number.
     * @param aInput String encoded number.
     * @return True if the string is a number and is negative.
     */
    bool is_negative(string aInput);
    
    /**
     * Determines if a string is a number.
     * @param aInput String encoded number.
     * @return True if the string is a number.
     */
    bool is_number(string aInput);
    
    /**
     * Determines if the string is a floating point number.
     * @param aInput String encoded number.
     * @return True if the string is a floating point number.
     */
    bool is_decimal(string aInput);

    /**
     * Determines if the string is boolean (true or false)
     * @param aInput String encoded boolean.
     * @return True if the string is 'true' or 'false'.
     */
    bool is_boolean(std::string aInput);

    /**
     * Determines if a string contains 'true' or 'false'.
     * @param aInput Input data 
     * @param aPos Start position in the input
     * @param aMaxCount Maximum length we want to search, usually the length
     * of the input, but should not exceed the size of the input.
     * @param aBool
     * @return Returns 4 if 'true', 5 if 'false', or 0 if neither.
     */
    int string_boolean_length(const char *aInput, int aPos, bool &aBool);  
    
    /**
     * Runs through a string of const char and determines if from the starting position
     *  we have a string encoded number or not.
     * @param argInput Input data
     * @param argPos Start position in the input
     * @param argMaxCount -Maximum length we want to search, usually the length
     *              of the input, but should not exceed the size of the input.
     * @param aNumber Flag is set if the string is a number.
     * @param aNegative Flag is set if the string is a number and is negative.
     * @param aDecimal Flag is set if the string is a floating point number.
     * @param aBool Flag is set if the string is 'true' or 'false'.
     * @return Length of the string encoded number, 0 if not a number.
     */
    int string_number_length(const char *aInput, int aPos, int aMaxCount, bool &aNumber, bool &aNegative, bool &aDecimal, bool &aBool);

    /**
     * Determines if the character string contains a number at aPos
     * @param aInput The input string.
     * @param aPos Start position to search the input.
     * @param aMaxCount Maximum length to search, usually the length
     * of the input, but should not exceed the size of the input.
     * @return Length of the string encoded number, 0 if not a number.
     */
    int string_number_length(const char *aInput, int aPos, int aMaxCount);


    /**
     * Converts a string into a double.  If the string can not be converted into
     * a double, then the string is converted into NaN.
     * @param aInput The input string to be converted.
     * @return The numeric value of the string or NaN if the string can not be converted.
     */
    double string_to_double(std::string aInput);

    /**
     * Removes any occurances of ' ', '\t', or '\n' from the string.
     * @param aInput The input string.
     * @return Returns a copy of the original string with removed white space.
     */
    std::string remove_white_space(std::string aInput);


    /**
     * Takes a value, and turns it into a string of length aLength, fills in the
     * leading digits with zeros.  e.g. turns 10,3 into 010; or 1,3 into 001.
     * @param aInput The value we are converting.
     * @param aLength The size we want the string to be.
     * @return A string with the converted integer value.
     */
    template <class T>
    string value_to_string(T aInput, int aLength){

        string lReturn = to_string(aInput);

        for(int i = lReturn.length(); i < aLength; i++){
            if(aInput < pow(10,i)){
                lReturn = "0" + lReturn;
            }
        }

        return lReturn;
    }    
    

    
    
}

#endif	/* GLCH_STRCONVERT_H */

