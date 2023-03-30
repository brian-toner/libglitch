/* 
 * File:   AString.h
 * Author: brian
 *
 * Created on January 16, 2015, 2:38 PM
 */

#ifndef GLCH_ASTRING_H
#define	GLCH_ASTRING_H


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm> 
#include <limits> //For handeling NaN
#include "stringconversion.h"
#include "StringAddress.h"
#include "VectorFunctions.h"

using namespace std;

namespace glch{

    typedef std::vector<std::string> StringList;
    typedef std::vector<char> CharList;

    typedef class AString : public std::string {
        
        public:

            /**
             * Takes an argument in the string defined by the marker (default '%')
             * and replaces it with the input value.  i.e. "This is a string %1" will
             * be changed into "This is a string INPUT_VALUE".  The lowest valued marker
             * will be replaced first.
             * @param aInput Input value to replace the argument by.
             * @param aAddressMarker The marker used to define the arguments, default value of '%'.
             * @return A new AString with a replaced value.
             */            
            AString argr(AString aInput, string aAddressMarker = "%");

            AString arg(AString aInput, string aAddressMarker = "%");
            
            AString arg(std::vector<char> &aInput, string aAddressMarker = "%");
            
            /**
             * Recursively replaces all matching arguments.
             * @param aRet String we are replacing arguments of.
             * @param aInput String we are replacing arguments with.
             * @param aAddress The address we are looking to replace.
             * @param aAddressMarker The marker used to identify the markers.
             * @return A new string with the arguments replaced.
             */            
            AString replace_all_args(AString &aRet, AString aInput, size_t aAddress, string aAddressMarker);
            
            AString& erase_all_strings(std::string aFind);
            
            AString& replace_all_strings(std::string aFind, std::string aReplace);
            
            /**
             * Default constructor.  Nothing special happens here.
             */            
            AString();
            
            /**
             * Uses the parent class string constructor to take the input string.
             * @param aInput The input string to copy into this string.
             */            
            AString(std::string argInput);
            
            /**
             * Appends a null terminated string into this string.
             * @param aInput Input string to copy in to this string.
             */            
            AString(const char* argInput);
            
            /**
             * Copy constructor.  Uses the default parent string for copy construction.  Also
             * assigns the AString to this.
             * @param orig Original value to copy over.
             */            
            AString(const AString& orig);

            /**
             * Converts a char input into a string.  Through om::to_string(T).
             * @param aInput Input value to convert.
             */              
            AString(char aInput);
            
            /**
             * Converts an unsigned input into a string.  Through om::to_string(T).
             * @param aInput Input value to convert.
             */              
            AString(unsigned char aInput);
            
            /**
             * Converts a short input into a string.  Through om::to_string(T).
             * @param aInput Input value to convert.
             */              
            AString(short aInput);
            
            /**
             * Converts an unsigned short input into a string.  Through om::to_string(T).
             * @param aInput Input value to convert.
             */              
            AString(unsigned short aInput);
            
            /**
             * Converts an int input into a string.  Through om::to_string(T).
             * @param aInput Input value to convert.
             */              
            AString(int aInput);
            
            /**
             * Converts an unsigned int input into a string.  Through om::to_string(T).
             * @param aInput Input value to convert.
             */              
            AString(unsigned int aInput);
            
            /**
             * Converts a long input into a string.  Through om::to_string(T).
             * @param aInput Input value to convert.
             */              
            AString(long aInput);
            
            /**
             * Converts an unsigned long input into a string.  Through om::to_string(T).
             * @param aInput Input value to convert.
             */              
            AString(unsigned long aInput);
            
            /**
             * Converts a float input into a string.  Through om::to_string(T).
             * @param aInput Input value to convert.
             */            
            AString(float aInput);
            
            /**
             * Converts a double input into a string.  Through om::to_string(T).
             * @param aInput Input value to convert.
             */
            AString(double aInput);

            /**
             * Converts the AString into a boolean.
             * @return Returns true for numeric values greater than one or 'true' string.
             * False otherwise.
             */            
            bool             toBool();
            
            /**
             * Converts the AString into an char (first character).
             * @return The string converted into an char.  
             */              
            char             toChar();
            
            /**
             * Converts the AString into an unsigned char (first character).
             * @return The string converted into an unsigned char.  
             */                
            unsigned char    toUChar();
            
            /**
             * Converts the AString into a short.
             * @return The string converted into a short.  
             * The result will be 0 if it is not a number.
             */                
            short            toShort();
            
            /**
             * Converts the AString into an unsigned short.
             * @return The string converted into an unsigned short.  
             * The result will be 0 if it is not a number.
             */                
            unsigned short   toUShort(); 
            
            /**
             * Converts the AString into an int.
             * @return The string converted into an int.  
             * The result will be 0 if it is not a number.
             */              
            int              toInt();
            
            /**
             * Converts the AString into an unsigned int.
             * @return The string converted into an unsigned int.  
             * The result will be 0 if it is not a number.
             */               
            unsigned int     toUInt();
            
            /**
             * Converts the AString into a long.
             * @return The string converted into a long.  
             * The result will be 0 if it is not a number.
             */            
            long             toLong();
            
            /**
             * Converts the AString into an unsigned long.
             * @return The string converted into an unsigned long.  
             * The result will be 0 if it is not a number.
             */            
            unsigned long    toULong();
            
            /**
             * Converts the AString into a float.
             * @return The string converted into a float.  
             * NaN if string is not a number.
             */            
            float            toFloat();
            
            /**
             * Converts the AString into a double.
             * @return The string converted into a double.  
             * NaN if string is not a number.
             */            
            double           toDouble();

            /**
             * Converts the AString into a boolean.
             * @return Returns true for numeric values greater than one or 'true' string.
             * False otherwise.
             */
            operator bool();
            
            /**
             * Converts the AString into an char (first character).
             * @return The string converted into an char.  
             */             
            operator char();
            
            /**
             * Converts the AString into an unsigned char (first character).
             * @return The string converted into an unsigned char.  
             */             
            operator unsigned char();
            
            /**
             * Converts the AString into a short.
             * @return The string converted into a short.  
             * The result will be 0 if it is not a number.
             */            
            operator short();
            
            /**
             * Converts the AString into an unsigned short.
             * @return The string converted into an unsigned short.  
             * The result will be 0 if it is not a number.
             */              
            operator unsigned short();
            
            /**
             * Converts the AString into an int.
             * @return The string converted into an int.  
             * The result will be 0 if it is not a number.
             */            
            operator int();
            
            /**
             * Converts the AString into an unsigned int.
             * @return The string converted into an unsigned int.  
             * The result will be 0 if it is not a number.
             */            
            operator unsigned int();
            
            /**
             * Converts the AString into a long.
             * @return The string converted into a long.  
             * The result will be 0 if it is not a number.
             */
            operator long();
            
            /**
             * Converts the AString into an unsigned long.
             * @return The string converted into an unsigned long.  
             * The result will be 0 if it is not a number.
             */
            operator unsigned long();
            
            /**
             * Converts the AString into a float.
             * @return The string converted into a float.  
             * NaN if string is not a number.
             */
            operator float();
            
            /**
             * Converts the AString into a double.
             * @return The string converted into a double.  
             * NaN if string is not a number.
             */
            operator double();            
            
            /**
             * Increment operator.  The string is converted to a double and
             * incremented.
             * @return The AString with the new incremented value.
             */
            AString& operator ++();
            
            /**
             * Increment operator.  The string is converted to a double and
             * incremented.
             * @return The AString with the new incremented value.
             */            
            AString& operator ++(int);
            
            /**
             * Less than operator.  The string and input value are converted
             * and compared using the less than operator.  T is required to have
             * (double) operator.
             * @param aValue Comparison value.
             * @return True if the double converted input value is greater than
             * the double converted AString.
             */
            template <class T>
            bool operator <(T aValue);

            /**
             * Greater than operator.  The string and input value are converted
             * and compared using the greater than operator.  T is required to have
             * (double) operator.
             * @param aValue Comparison value.
             * @return True if the double converted input value is less than
             * the double converted AString.
             */            
            template <class T>
            bool operator >(T aValue);

            /**
             * Equality operator.  The string and input value are converted
             * and compared using the equality than operator.  T is required to have
             * (double) operator.
             * @param aValue Comparison value.
             * @return True if the double converted input value is equal to
             * the double converted AString.
             */              
            template <class T>
            bool operator ==(T aValue);          

            bool operator ==(const char* aValue){
                return (compare(string(aValue)) == 0);
            }

            bool operator ==(std::string aValue){
                return (compare(aValue) == 0);
            }
            
            bool operator ==(AString aValue){
                return (compare(aValue) == 0);
            }            

            template <class T>
            std::vector<T> to_vector(std::string aDelim = ","){
                std::vector<AString> lSplit = split(aDelim);
                std::vector<T> lRet(lSplit.size());
                
                for(size_t i = 0; i < lSplit.size(); i++){
                    lRet.at(i) = lSplit.at(i);
                }
                
                return lRet;
            }
            
            template <class T>
            operator std::vector<T>(){
                return to_vector<T>();
            }
            
            /**
             * Not equal operator.  The string and input value are converted
             * and compared using the not equal operator.  T is required to have
             * (double) operator.
             * @param aValue Comparison value.
             * @return True if the double converted input value is not equal to
             * the double converted AString.
             */               
            template <class T>
            bool operator !=(T aValue); 
           
            /**
             * Pushes data into the AString in the form of a comma separated list.  
             * @param aData Data to push in.
             * @return This AString.
             */
            template <class T>
            AString& operator <<(T aData);
            
            template <class T>
            AString& append(T aData, std::string aDelim = ",");
            
            /**
             * Splits an AString into a list of AString.
             * @param aDelim the delimitation string used to determine the split locations.
             * Default value is comma ','.
             * @return A list split apart at the delimitation string.
             */
            std::vector<AString> split(std::string aDelim);

            std::vector<AString> split(std::string aDelim, std::string aIgnoreTolkenStart, std::string aIgnoreTolkenEnd);
            
            /**
             * Splits an AString into a list of numeric ranges.
             * @param aDelim Character to denote the range.
             * @return List of numbers in the range.
             */
            std::vector<AString> cron(long aMin = 0, long aMax = 100);
            
            size_t find_nth(std::string aValue, size_t aCount, size_t aPos, std::string aTolkenStart, std::string aTolkenEnd);
            size_t find_nth(std::string aValue, size_t aCount, size_t aPos);
            size_t find_ignore_tolkens(std::string aValue, size_t aIndex, std::string aIgnoreTolkenStart, std::string aIgnoreTolkenEnd);
            
            size_t dict_size();
            AString dict_label(AString aElement, std::string aTextDelim = "'", bool aStripTextDelim = true);
            AString dict_label(size_t aElement, std::string aTextDelim = "'", bool aStripTextDelim = true);
            size_t dict_label_index(glch::AString aLabel, std::string aTextDelim = "'", bool aStripTextDelim = true);
            AString dict_value(AString aElement, std::string aTextDelim = "'", bool aStripTextDelim = true);
            AString dict_value(size_t aElement, std::string aTextDelim = "'", bool aStripTextDelim = true);
            AString& dict_set(AString aValue, size_t aElement, std::string aTextDelim = "'");
            
            AString csv(size_t aCol, std::string aTextDelim = "\"", bool aStripTextDelim = false);
            
            AString csv(size_t aPage, size_t aRow, size_t aCol, std::string aTextDelim = "\"");
            AString csvi(size_t aPage, size_t aRow, std::string aCol, std::string aTextDelim = "\"");
            AString& csv_replace(std::string aValue, size_t aPage, size_t aRow, size_t aCol, std::string aTextDelim = "\"");
            size_t csv_row_count(size_t aPage, std::string aTextDelim = "\"");
            size_t csv_col_count(size_t aPage, size_t aRow, std::string aTextDelim = "\"");            
            size_t csv_page_count(std::string aTextDelim = "\"");
            size_t csv_col_index(std::string aColName, size_t aPage, std::string aTextDelim = "\"");
            size_t csv_row_index(std::string aRowName, size_t aPage, std::string aTextDelim = "\"");
            
            AString csvi(size_t aRow, std::string aCol, std::string aTextDelim = "\"", bool aStripTextDelim = false);
            AString csv(size_t aRow, size_t aCol, std::string aTextDelim = "\"", bool aStripTextDelim = false);
            AString& csv_replace(std::string aValue, size_t aRow, size_t aCol, std::string aTextDelim = "\"");
            size_t csv_row_count(std::string aTextDelim = "\"");
            size_t csv_col_count(size_t aRow = 0, std::string aTextDelim = "\"");
            size_t csv_col_index(std::string aColName, std::string aTextDelim = "\"");
            size_t csv_row_index(std::string aRowName, std::string aTextDelim = "\"");
            
            void find_bounds(size_t aIndex, size_t aStartPos, size_t aEndPos, std::string aDelim, size_t &lStart, size_t &lEnd, std::string aTextDelim = "\"");
            size_t count_between(std::string aDelim, size_t aStartPos, size_t aEndPos, std::string aTextDelim = "\"");
            
            AString& table_replace(std::string aValue, size_t aPlane, size_t aRow, size_t aCol, std::string aDelimPlane, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim = "\"");
            AString& table_replace(std::string aValue, vector<size_t> aIndex, std::vector<std::string> aDelims, std::string aTextDelim);
            AString table(vector<size_t> aIndex, std::vector<std::string> aDelims, std::string aTextDelim = "\"");
            AString table(size_t aPlane, std::string aDelimPlane, std::string aTextDelim = "\"");
            size_t table_dim_count(size_t aDimension, vector<size_t> aIndex, std::vector<std::string> aDelims, std::string aTextDelim = "\"");
            //size_t table_dim_index(std::string aDimName, size_t aDimension, std::vector<size_t> aIndex, std::vector<std::string> aDelim, std::string aTextDelim = "\"");
            
            AString table(size_t aPlane, size_t aRow, size_t aCol, std::string aDelimPlane, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim = "\"");
            AString table(size_t aRow, size_t aCol, std::string aDelimRow = "\n", std::string aDelimCol = ",", std::string aTextDelim = "\"");
            AString& table_replace(std::string aValue, size_t aRow, size_t aCol, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim = "\"");
            AString table_row(size_t aRow, std::string aDelimRow, std::string aTextDelim = "\"");
            
            size_t table_page_count(std::string aDelimPage, std::string aTextDelim = "\"");
            size_t table_row_count(std::string aDelimRow, std::string aTextDelim = "\"");
            size_t table_row_count(size_t aPage, std::string aDelimPage, std::string aDelimRow, std::string aTextDelim = "\"");
            size_t table_col_count(size_t aRow, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim = "\"");
            size_t table_col_count(size_t aPage, size_t aRow, std::string aDelimPage, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim = "\"");
            
            size_t table_row_index(std::string aRowName, size_t aPage, std::string aDelimPage, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim = "\"");
            size_t table_row_index(std::string aRowName, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim = "\"");
            size_t table_col_index(std::string aColName, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim = "\"");
            size_t table_col_index(std::string aColName, size_t aPage, std::string aDelimPage, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim = "\"");
            template<class T>
            AString& push_vector(std::vector<T> aValues);
            

            bool contains(std::string aVal);

            /**
             * Prints the contents of the AString.
             * @param aDelim The string used to terminate the string in the input.  Default newline.
             */
            void print(AString aDelim = "\n");

            //virtual ~AString();
            
            
            
        private:
            
    } astring;

    
    template<class T>
    AString& AString::push_vector(std::vector<T> aValues){
        
        for(size_t i = 0; i < aValues.size(); i++){
            *this << aValues.at(i);
        }
        
        return *this;
    }  
       
    
    /**
     * Less than operator.  The string and input value are converted
     * and compared using the less than operator.  T is required to have
     * (double) operator.
     * @param aValue Comparison value.
     * @return True if the double converted input value is greater than
     * the double converted AString.
     */    
    template <class T>
    bool AString::operator <(T aValue){
        return toDouble() < (double)aValue;    
    }    

    /**
     * Greater than operator.  The string and input value are converted
     * and compared using the greater than operator.  T is required to have
     * (double) operator.
     * @param aValue Comparison value.
     * @return True if the double converted input value is less than
     * the double converted AString.
     */        
    template <class T>
    bool AString::operator >(T aValue){
        return toDouble() > (double)aValue;    
    }

    /**
     * Equality operator.  The string and input value are converted
     * and compared using the equality than operator.  T is required to have
     * (double) operator.
     * @param aValue Comparison value.
     * @return True if the double converted input value is equal to
     * the double converted AString.
     */       
    template <class T>
    bool AString::operator ==(T aValue){
        return toDouble() == (double)aValue;    
    }      

    /**
     * Not equal operator.  The string and input value are converted
     * and compared using the not equal operator.  T is required to have
     * (double) operator.
     * @param aValue Comparison value.
     * @return True if the double converted input value is not equal to
     * the double converted AString.
     */        
    template <class T>
    bool AString::operator !=(T aValue){
        return toDouble() != (double)aValue;    
    } 
     
    /**
     * Pushes data into the AString in the form of a comma separated list.  
     * @param aData Data to push in.
     * @return This AString.
     */
    template <class T>
    AString& AString::operator <<(T aData){
        return append(aData);
    }    

    /**
     * Pushes data into the AString in the form of a comma separated list.  
     * @param aData Data to push in.
     * @return This AString.
     */
    template <class T>
    AString& AString::append(T aData, std::string aDelim){
        if(this->empty()){
            *this = aData;
        } else if (this->at(this->size()-1) == '\n' || AString(aData).compare("\n") == 0) {
            *this = *this + AString(aData);
        }else {
            *this = *this + aDelim + AString(aData);
        }

        return *this;
    }   
    
    typedef std::vector<AString> AStringList;
    typedef std::vector<AStringList> AStringArray;
    typedef std::vector<std::string> StringList;
    typedef std::vector<StringList> StringArray;
    
    
    AStringArray load_csv_file(std::string aFileName);
    
}

#endif	/* GLCH_ASTRING_H */

