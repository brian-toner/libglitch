/* 
 * File:   strConvert.cpp
 * Author: brian
 * 
 * Created on January 31, 2012, 2:41 PM
 */


#include "stringconversion.h"

namespace glch{


    /**
     * Deep copies a buffer of characters into a std::string
     * @param argBuffer data buffer being copied to string.
     * @param aIndex Starting index of deep copy.
     * @param aSize Number of characters being copied into the string.
     * @return New string created from the input buffer.
     */
    std::string buffer_to_string(char* aBuffer, size_t aIndex, size_t aSize){
        string lReturn;

        lReturn = "";
        for(long unsigned int i = 0; i < aSize; i++){
               lReturn = lReturn + aBuffer[aIndex + i];
        }

        return lReturn;
    }


    /**
     * Searches a vector of strings and reports back the index number of the vector 
     * where the string was located (exact match). If the string was not located in the vector then
     * (size_t)(-1) is returned.
     * @param aInput Vector of string being searched
     * @param aStringToFind String we are attempting to find in the input.
     * @return Location in the vector, otherwise (size_t)(-1)
     */
    size_t find_string_in_vect(vector<string> &aInput, string aStringToFind){
        size_t locReturn = 0;
        size_t i = 0;

        while (i != aInput.size() && aStringToFind.compare(aInput.at(i)) != 0){
            i ++;
        }

        if(i == aInput.size()){
            locReturn = (size_t)(-1);
        } else {
            locReturn = i;
        }

        return locReturn;
    }


    /**
     * Reports if the Input contains the comparison string.  This is done through
     * the strings default find function.
     * @param aInput Input string being searched.
     * @param aStringToFind String we are attempting to find in the input.
     * @return True if the string is contained in the input, false otherwise.
     */
    bool in_str(std::string aInput, std::string aStringToFind){
        bool lReturn = false;

        long unsigned int lFind = aInput.find(aStringToFind);
        if(lFind != std::string::npos){
            lReturn = true;
        }

        return lReturn;

    }

    /**
     * Finds the positions of a string inside of a string.
     * @param aInput String being searched.
     * @param aPositions Locations of found strings.
     * @param aComp String being located
     * @return True if aComp was found at least once.
     */
    bool in_str(std::string aInput, std::vector<size_t> &aPositions, std::string aStringToFind){

        bool lReturn = false;
        size_t lFind = 0;

        if(aStringToFind.length() == 0){
            return false;
        }
        
        lFind = aInput.find(aStringToFind);
        
        while(lFind != std::string::npos){

            if(lFind != std::string::npos){
                aPositions.push_back(lFind);
                lReturn = true;
            }
            
            lFind = aInput.find(aStringToFind,aStringToFind.size()+lFind);
            
        }


        return lReturn;    

    }

    bool in_str(std::string aInput, std::vector<size_t> &aPositions, std::string aStringToFind, std::string aIgnoreTolkenStart, std::string aIgnoreTolkenEnd){

        bool lReturn = false;
        size_t lFind = 0;

        if(aStringToFind.length() == 0){
            return false;
        }
        
        lFind = find_ignore_tolkens(aInput,aStringToFind,lFind,aIgnoreTolkenStart,aIgnoreTolkenEnd);
        
        while(lFind != std::string::npos){

            if(lFind != std::string::npos){
                aPositions.push_back(lFind);
                lReturn = true;
            }
            
            lFind = find_ignore_tolkens(aInput,aStringToFind,aStringToFind.size()+lFind,aIgnoreTolkenStart,aIgnoreTolkenEnd);
            
        }

        return lReturn;    
    }    
    
    
    size_t find_ignore_tolkens(std::string aString, std::string aFindValue, size_t aPosition, std::string aIgnoreTolkenStart, std::string aIgnoreTolkenEnd){
        
        size_t lIgnoreCount = 0;
        bool lSameTolken = false;
        bool lIgnoreStart = false;
        
        if(aIgnoreTolkenStart.compare(aIgnoreTolkenEnd) == 0){
            lSameTolken = true;
        }

        for(size_t i = aPosition; i < aString.length(); i++){

            if(lSameTolken && lIgnoreCount > 0){
                lIgnoreStart = true;
            } else {
                lIgnoreStart = false;
            }

            if(!lIgnoreStart && aString.substr(i,aIgnoreTolkenStart.length()).compare(aIgnoreTolkenStart) == 0){
                lIgnoreCount ++;
                i += aIgnoreTolkenStart.length();
            }
            
            if(aString.substr(i,aIgnoreTolkenEnd.length()).compare(aIgnoreTolkenEnd) == 0){
                lIgnoreCount --;
                i += aIgnoreTolkenEnd.length();
            }            
            
            if(lIgnoreCount == 0){
                if(aString.substr(i,aFindValue.length()).compare(aFindValue) == 0){
                    return i;
                }
            }

        }
        
        return std::string::npos;
        
    }    
    
    
    /**
     * Splits a string into a vector of strings at each delimitation point.
     * @param aInput Input string being split apart.
     * @param aDelim The delimitation string. 
     * @return Vector of strings.
     */
    std::vector<std::string> split_string(std::string aInput, std::string aDelim){
        std::vector<std::string> lRet;
        std::vector<size_t> aPositions;
        bool lSplit = in_str(aInput,aPositions,aDelim);
        size_t aDelimSize = aDelim.length();
        size_t aLast = 0;
        
        std::string lSplitStr = "";
        if(lSplit){
            for(std::vector<size_t>::iterator it = aPositions.begin(); it != aPositions.end(); it++){
                lSplitStr = aInput.substr(aLast,(*it)-aLast);
                aLast = (*it)+aDelimSize;
                lRet.push_back(lSplitStr);
            }
            
            
        } 
        lSplitStr = aInput.substr(aLast,aInput.length()-aLast);
        lRet.push_back(lSplitStr);
        
        return lRet;
    }

    /**
     * Splits a string into a vector of strings at each delimitation point.
     * @param aInput Input string being split apart.
     * @param aDelim The delimitation string. 
     * @return Vector of strings.
     */
    std::vector<std::string> split_string(std::string aInput, std::string aDelim, std::string aIgnoreTolkenStart, std::string aIgnoreTolkenEnd){
        std::vector<std::string> lRet;
        std::vector<size_t> aPositions;
        bool lSplit = in_str(aInput,aPositions,aDelim,aIgnoreTolkenStart,aIgnoreTolkenEnd);
        size_t aDelimSize = aDelim.length();
        size_t aLast = 0;
        
        std::string lSplitStr = "";
        if(lSplit){
            for(std::vector<size_t>::iterator it = aPositions.begin(); it != aPositions.end(); it++){
                lSplitStr = aInput.substr(aLast,(*it)-aLast);
                aLast = (*it)+aDelimSize;
                lRet.push_back(lSplitStr);
            }
            
            
        } 
        lSplitStr = aInput.substr(aLast,aInput.length()-aLast);
        lRet.push_back(lSplitStr);
        
        return lRet;
    }    
    
    
    /**
     * Removes all special characters from a string (aInput) and converts them to the 
     * delimitation character (aDelim).  Valid characters are considered letters, numbers
     * underscore period and dash.
     * @param aInput Input string being purged 
     * @param aReplaceString The string used to replace any non valid characters. 
     * @return New string with all special characters removed.
     */
    std::string deslug_string(std::string aInput, std::string aReplaceString){

        vector<char> lValidChars; //Vector containing all number characters
        for(char i = 48; i < 58; i++){
            lValidChars.push_back(i);
        }

        for(char i = 'a'; i < 'a'+26; i++){
            lValidChars.push_back(i);
        }

        for(char i = 'A'; i < 'A'+26; i++){
            lValidChars.push_back(i);
        }

        lValidChars.push_back('.');
        lValidChars.push_back('-');
        lValidChars.push_back('_');

        return deslug_string(aInput, aReplaceString, lValidChars);

    }
    
    /**
     * Removes all special characters from a string (aInput) and converts them to the 
     * delimitation character (aDelim).  Valid characters are considered letters, numbers
     * underscore period and dash.
     * @param aInput Input string being purged 
     * @param aReplaceString The string used to replace any non valid characters. 
     * @param aValidChars List of characters which will remain unchanged.
     * @return New string with all special characters removed.
     */
    std::string deslug_string(std::string aInput, std::string aReplaceString, vector<char> lValidChars){

        std::string locReturn = "";

        for(long unsigned int i = 0; i < aInput.size(); i++){
            bool tempIsValid = false;

            for(long unsigned int j = 0; j < lValidChars.size(); j++){
                if(aInput.at(i) == lValidChars.at(j)){
                    locReturn += aInput.at(i);
                    tempIsValid = true;
                }
            }

            if(!tempIsValid){
                locReturn += aReplaceString;
            }
        }

        return locReturn;
    }


    /**
     * Determines if the input string is actually a string encoded number.
     * If so, then return will be the length of the number.
     * This function uses: int is_number(const char*, int, int)
     * @param argInput -Input string we are checking for encoded numbers
     * @return -Length of the string encoded number, 0 if not a number.
     */
    int string_number_length(string argInput){
        bool lNumber,lNegative,lDecimal,lBool;
        return string_number_length(argInput.c_str(), 0, argInput.size(),lNumber,lNegative,lDecimal,lBool);
    }

    
/**
     * Runs through a string and determines if the string is an encoded number or not.
     * @param argInput Input data
     * @param aNumber Flag is set if the string is a number.
     * @param aNegative Flag is set if the string is a number and is negative.
     * @param aDecimal Flag is set if the string is a floating point number.
     * @param aBool Flag is set if the string is 'true' or 'false'.
     * @return Length of the string encoded number, 0 if not a number.
     */
    int string_number_length(string aInput,  bool &aNumber, bool &aNegative, bool &aDecimal, bool &aBool){
        return string_number_length(&aInput.at(0), 0, aInput.size(), aNumber, aNegative, aDecimal, aBool);
    }
    
    /**
     * Determines if a string is a negative number.
     * @param aInput String encoded number.
     * @return True if the string is a number and is negative.
     */
    bool is_negative(string aInput){
        bool lNumber,lNegative,lDecimal,lBool;
        string_number_length(aInput.c_str(), 0, aInput.size(),lNumber,lNegative,lDecimal,lBool);
        return lNegative;          
    }
    
    /**
     * Determines if a string is a number.
     * @param aInput String encoded number.
     * @return True if the string is a number.
     */
    bool is_number(string aInput){
        bool lNumber,lNegative,lDecimal,lBool;
        string_number_length(aInput.c_str(), 0, aInput.size(),lNumber,lNegative,lDecimal,lBool);
        return lNumber;        
    }
    
    /**
     * Determines if the string is a floating point number.
     * @param aInput String encoded number.
     * @return True if the string is a floating point number.
     */
    bool is_decimal(string aInput){
        bool lNumber,lNegative,lDecimal,lBool;
        string_number_length(aInput.c_str(), 0, aInput.size(),lNumber,lNegative,lDecimal,lBool);
        return lDecimal;
    }

    /**
     * Determines if the string is boolean (true or false)
     * @param aInput String encoded boolean.
     * @return True if the string is 'true' or 'false'.
     */
    bool is_boolean(std::string aInput){
        bool lBool;
        string_boolean_length(aInput.c_str(), 0, lBool);

        return lBool;
    }

    /**
     * Determines if a string contains 'true' or 'false'.
     * @param aInput Input data 
     * @param aPos Start position in the input
     * @param aMaxCount Maximum length we want to search, usually the length
     * of the input, but should not exceed the size of the input.
     * @param aBool
     * @return Returns 4 if 'true', 5 if 'false', or 0 if neither.
     */
    int string_boolean_length(const char *aInput, int aPos, bool &aBool){

        std::string locBool;
        aBool = false;

        for(int i = 0; i < 4; i++)
            locBool += aInput[aPos+i];

        if( locBool.compare("true") == 0  ){
            aBool = true;
            return 4;
        } 

        locBool.clear();

        for(int i = 0; i < 5; i++)
            locBool += aInput[aPos+i];

        if ( locBool.compare("false") == 0 ) {
            aBool = true;
            return 5;
        }

        return 0;
    }    
    
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
    int string_number_length(const char *aInput, int aPos, int aMaxCount, bool &aNumber, bool &aNegative, bool &aDecimal, bool &aBool){

        int lNumberSize = 0;        //Starts by assuming that the number size is 0.
        bool lIsNegative = false;   //Flag to determine if we have a negative number.
        bool lIsDecimal = false;  
        bool lScientific = false;
        bool lPeriod = false;
        
        char lCompare;              //Holds current char we are comparing against.
        size_t i = 0;               //Our counting integer, our position in the input.
        bool lIsNumb = true;        //Flag to determine if input is a number.
        
        lNumberSize = string_boolean_length(aInput, aPos, aBool);
        
        if(aBool){
            aNumber = true;
            aNegative = false;
            aDecimal = false;
            return lNumberSize;
        }        
        
        //Runs through the elements of input and proves if it is a number.
        while((int)i < aMaxCount && lIsNumb){
            lIsNumb = false;        //Each cycle we have to prove that the digit is numeric.
            lCompare = aInput[aPos+i];

            //Are we a negative number? Can only be negative at index 0.
            if(i == 0 && lCompare == '-'){
                lIsNegative = true;
                lNumberSize ++;
                lIsNumb = true;

            //Are we are in scientific notation.
            } else if(i != 0 && lCompare == 'e' && !lScientific){
                lNumberSize ++;
                lIsNumb = true;
                lIsDecimal = true;
                lScientific = true;
                lPeriod = false;
                
            //Contains a decimal.
            } else if(lCompare == '.' && !lPeriod){
                lNumberSize ++;
                lIsNumb = true;
                lIsDecimal = true;
                lPeriod = true;
                
            //Seeing if the string contains numbers.
            } else if(lCompare >= 48 && lCompare <= 58){
                lNumberSize ++;
                lIsNumb = true;
            
            }

            i++;
        }

        //Negative number can't just be a negative sign.
        if(lIsNegative && lNumberSize == 1){
            lNumberSize = 0;
        }

        if(aInput[lNumberSize-1] == 'e'){
            lNumberSize = 0;
        }
        
        if(lNumberSize > 0){
            aNumber = true;
            aNegative = lIsNegative;
            aDecimal = lIsDecimal;
        } else {
            aNumber = false;
            aDecimal = false;
            aNegative = false;
        }

        return lNumberSize;

    }

    /**
     * Determines if the character string contains a number at aPos
     * @param aInput The input string.
     * @param aPos Start position to search the input.
     * @param aMaxCount Maximum length to search, usually the length
     * of the input, but should not exceed the size of the input.
     * @return Length of the string encoded number, 0 if not a number.
     */
    int string_number_length(const char *aInput, int aPos, int aMaxCount){
        bool argNumber, argNegative, argDecimal, aBool;
        return string_number_length(aInput,aPos,aMaxCount,argNumber,argNegative,argDecimal, aBool);

    }


    /**
     * Converts a string into a double.  If the string can not be converted into
     * a double, then the string is converted into NaN.
     * @param aInput The input string to be converted.
     * @return The numeric value of the string or NaN if the string can not be converted.
     */
    double string_to_double(std::string aInput){

        if(string_number_length(aInput))
            return string_to_type<double>(aInput);

        return std::numeric_limits<double>::quiet_NaN();

    }

    /**
     * Removes any occurances of ' ', '\t', or '\n' from the string.
     * @param aInput The input string.
     * @return Returns a copy of the original string with removed white space.
     */
    std::string remove_white_space(std::string aInput){
        std::string lReturn;

        for(std::string::iterator it = aInput.begin(); it != aInput.end(); it++){
            if((*it) != ' ' && (*it) != '\t' && (*it) != '\n'){
                lReturn.push_back((*it));
            }
        }

        return lReturn;
    }

}