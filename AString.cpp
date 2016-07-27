/* 
 * File:   AString.cpp
 * Author: brian
 * 
 * Created on January 16, 2015, 2:38 PM
 */

#include "AString.h"
#include "VectorFunctions.h"

namespace glch{

    /**
     * Default constructor.  Nothing special happens here.
     */
    AString::AString(){
    }

    /**
     * Uses the parent class string constructor to take the input string.
     * @param aInput The input string to copy into this string.
     */
    AString::AString(std::string aInput) : std::string(aInput){
        //(std::string)(*this) = argInput;
        //this->assign(argInput);
    }

    /**
     * Appends a null terminated string into this string.
     * @param aInput Input string to copy in to this string.
     */
    AString::AString(const char* aInput){
        int i = 0;
        while(aInput[i] != 0x00){
            (*this) += aInput[i];
            i++;
        }

    }

    /**
     * Copy constructor.  Uses the default parent string for copy construction.  Also
     * assigns the AString to this.
     * @param orig Original value to copy over.
     */
    AString::AString(const AString& orig) : std::string(orig) {
        (*this) = orig;
    }

    
    /**
     * Takes an argument in the string defined by the marker (default '%')
     * and replaces it with the input value.  i.e. "This is a string %1" will
     * be changed into "This is a string INPUT_VALUE".  The lowest valued marker
     * will be replaced first.
     * @param aInput Input value to replace the argument by.
     * @param aAddressMarker The marker used to define the arguments, default value of '%'.
     * @return A new AString with a replaced value.
     */
    AString AString::argr(AString aInput, string aAddressMarker){
        AString lRet = *this;
        size_t lAddress = find_min_arg(lRet);
        
        return replace_all_args(lRet,aInput,lAddress,aAddressMarker);
        
    }

    
    
    AString AString::arg(AString aInput, string aAddressMarker){
        AString lRet = *this;
        size_t lAddress = find_min_arg(lRet);
        
        string lAddStr = aAddressMarker + to_string(lAddress);
        std::vector<size_t> lPos;
        in_str(lRet, lPos, lAddStr);

        for(std::vector<size_t>::iterator it = lPos.begin(); it != lPos.end(); it++){
            if(arg_at(lRet,*it) == lAddress){
                lRet.replace((*it), lAddStr.length(), aInput);
                for(std::vector<size_t>::iterator itj = it+1; itj != lPos.end(); itj++){
                    (*itj) += aInput.length()-lAddStr.length();
                }
                
            }
        }
        
        return lRet;
        
    }
    
    AString AString::arg(std::vector<char> &aInput, string aAddressMarker){
        AString lRet = *this;
        size_t lAddress = find_min_arg(lRet);
        
        string lAddStr = aAddressMarker + to_string(lAddress);
        std::vector<size_t> lPos;
        in_str(lRet, lPos, lAddStr);

        for(std::vector<size_t>::iterator it = lPos.begin(); it != lPos.end(); it++){
            if(arg_at(lRet,*it) == lAddress){
                lRet.erase(lRet.begin()+(*it),lRet.begin()+(*it)+lAddStr.length());
                lRet.insert(lRet.begin()+(*it),aInput.begin(),aInput.end());

                for(std::vector<size_t>::iterator itj = it+1; itj != lPos.end(); itj++){
                    (*itj) += aInput.size()-lAddStr.length();
                }
                
            }
        }
        
        return lRet;
        
    }
    
    /**
     * Recursively replaces all matching arguments.
     * @param aRet String we are replacing arguments of.
     * @param aInput String we are replacing arguments with.
     * @param aAddress The address we are looking to replace.
     * @param aAddressMarker The marker used to identify the markers.
     * @return A new string with the arguments replaced.
     */
    AString AString::replace_all_args(AString &aRet, AString aInput, size_t aAddress, string aAddressMarker){
        
        size_t lAddress = find_min_arg(aRet);

        if(lAddress != aAddress){
            return aRet;
        }
        
        string lAddStr = aAddressMarker + to_string(aAddress);
        std::vector<size_t> lPos;
        in_str(aRet, lPos, lAddStr);

        for(std::vector<size_t>::iterator it = lPos.begin(); it != lPos.end(); it++){

            if(arg_at(aRet,*it) == lAddress){
                aRet.replace((*it), lAddStr.length(), aInput);
            }
        }
        
        return replace_all_args(aRet,aInput,aAddress,aAddressMarker);
        
    }
    
    AString& AString::erase_all_strings(std::string aFind){
        
        size_t lFinder = find(aFind);
        
        while(lFinder != std::string::npos){
            //std::cout << "Found at: " << lFinder << std::endl;
            erase(lFinder,aFind.length());
            lFinder = find(aFind);
        }
                
        return *this;  
    }
    
    AString& AString::replace_all_strings(std::string aFind, std::string aReplace){
        
        size_t lFinder = find(aFind);
        
        while(lFinder != std::string::npos){
            replace(lFinder,aFind.length(),aReplace);
            lFinder = find(aFind);
        }
                
        return *this;   
    }
    
    /**
     * Converts a char input into a string.  Through om::to_string(T).
     * @param aInput Input value to convert.
     */     
    AString::AString(char aInput){
        *this = to_string(aInput);
    }

    /**
     * Converts an unsigned char input into a string.  Through om::to_string(T).
     * @param aInput Input value to convert.
     */       
    AString::AString(unsigned char aInput){
        *this = to_string(aInput);
    }

    /**
     * Converts a short input into a string.  Through om::to_string(T).
     * @param aInput Input value to convert.
     */       
    AString::AString(short aInput){
        *this = to_string(aInput);
    }
    
    /**
     * Converts an unsigned short input into a string.  Through om::to_string(T).
     * @param aInput Input value to convert.
     */       
    AString::AString(unsigned short aInput){
        *this = to_string(aInput);
    }  

    /**
     * Converts an int input into a string.  Through om::to_string(T).
     * @param aInput Input value to convert.
     */       
    AString::AString(int aInput){
        *this = to_string(aInput);
    }
    
    /**
     * Converts an unsigned int input into a string.  Through om::to_string(T).
     * @param aInput Input value to convert.
     */       
    AString::AString(unsigned int aInput){
        *this = to_string(aInput);
    }
    
    /**
     * Converts a long input into a string.  Through om::to_string(T).
     * @param aInput Input value to convert.
     */       
    AString::AString(long aInput){
        *this = to_string(aInput);
    }

    /**
     * Converts a unsigned long input into a string.  Through om::to_string(T).
     * @param aInput Input value to convert.
     */       
    AString::AString(unsigned long aInput){
        *this = to_string(aInput);
    }
    
    /**
     * Converts a float input into a string.  Through om::to_string(T).
     * @param aInput Input value to convert.
     */       
    AString::AString(float aInput){
        *this = to_string(aInput);
    }
        
    /**
     * Converts a double input into a string.  Through om::to_string(T).
     * @param aInput Input value to convert.
     */       
    AString::AString(double aInput){
        *this = to_string(aInput);
    }  
    
    /**
     * Converts the AString into a boolean.
     * @return Returns true for numeric values greater than one or 'true' string.
     * False otherwise.
     */       
    bool AString::toBool(){
        if(compare("true") == 0){
            return true;
        } else if (compare("false") == 0){
            return false;
        }
        return (bool)toInt();
    }

    /**
     * Converts the AString into an char (first character).
     * @return The string converted into an char.  
     */       
    char AString::toChar(){
        char lRet = 0;
        
        try{
            lRet = string_to_type<char>(*this);
        } catch (RuntimeErrorReport lError){
            lRet = std::numeric_limits<char>::quiet_NaN();
        }

        return lRet;        
    }
    
    /**
     * Converts the AString into an unsigned char (first character).
     * @return The string converted into an unsigned char.  
     */        
    unsigned char AString::toUChar(){
        unsigned char lRet = 0;
        
        try{
            lRet = string_to_type<unsigned char>(*this);
        } catch (RuntimeErrorReport lError){
            lRet = std::numeric_limits<unsigned char>::quiet_NaN();
        }

        return lRet;        
    }

    /**
     * Converts the AString into a short.
     * @return The string converted into a short.  
     * The result will be 0 if it is not a number.
     */        
    short AString::toShort(){
        short lRet = 0;
        try{
            lRet = string_to_type<short>(*this);
        } catch (RuntimeErrorReport lError){
            lRet = std::numeric_limits<short>::quiet_NaN();
        }

        return lRet;
    }

    
    /**
     * Converts the AString into an unsigned short.
     * @return The string converted into an unsigned short.  
     * The result will be 0 if it is not a number.
     */         
    unsigned short AString::toUShort(){
        unsigned short lRet = 0;
        try{
            lRet = string_to_type<unsigned short>(*this);
        } catch (RuntimeErrorReport lError){
            lRet = std::numeric_limits<unsigned short>::quiet_NaN();
        }

        return lRet;
    }
    
    /**
     * Converts the AString into an int.
     * @return The string converted into an int.  
     * The result will be 0 if it is not a number.
     */       
    int AString::toInt(){
        int lRet = 0;
        try{
            lRet = string_to_type<int>(*this);
        } catch (RuntimeErrorReport lError){
            lRet = std::numeric_limits<int>::quiet_NaN();
        }

        return lRet;
    }

    /**
     * Converts the AString into an unsigned int.
     * @return The string converted into an unsigned int.  
     * The result will be 0 if it is not a number.
     */       
    unsigned int AString::toUInt(){
        unsigned int lRet = 0;
        try{
            lRet = string_to_type<unsigned int>(*this);
        } catch (RuntimeErrorReport lError){
            lRet = std::numeric_limits<unsigned int>::quiet_NaN();
        }

        return lRet;
    }
       
    /**
     * Converts the AString into a long.
     * @return The string converted into a long.  
     * The result will be 0 if it is not a number.
     */      
    long AString::toLong(){
        long lRet = 0;
        try{
            lRet = string_to_type<long>(*this);
        } catch (RuntimeErrorReport lError){
            lRet = std::numeric_limits<long>::quiet_NaN();
        }

        return lRet;
    }

    /**
     * Converts the AString into an unsigned long.
     * @return The string converted into an unsigned long.  
     * The result will be 0 if it is not a number.
     */       
    unsigned long AString::toULong(){
        unsigned long lRet = 0;
        try{
            lRet = string_to_type<unsigned long>(*this);
        } catch (RuntimeErrorReport lError){
            lRet = std::numeric_limits<unsigned long>::quiet_NaN();
        }

        return lRet;
    }    
    
    /**
     * Converts the AString into a float.
     * @return The string converted into a float.  
     * NaN if string is not a number.
     */        
    float AString::toFloat(){
        float lRet = 0;
        try{
            lRet = string_to_type<float>(*this);
        } catch (RuntimeErrorReport lError){
            lRet = std::numeric_limits<float>::quiet_NaN();
        }

        return lRet;
    }

    /**
     * Converts the AString into a double.
     * @return The string converted into a double.  
     * NaN if string is not a number.
     */            
    double AString::toDouble(){
        double lRet = 0;
        try{
            lRet = string_to_type<double>(*this);
        } catch (RuntimeErrorReport lError){
            lRet = std::numeric_limits<double>::quiet_NaN();
        }

        return lRet;
    }

    /**
     * Converts the AString into a boolean.
     * @return Returns true for numeric values greater than one or 'true' string.
     * False otherwise.
     */    
    AString::operator bool(){
        return toBool();
    }

    /**
     * Converts the AString into an char (first character).
     * @return The string converted into an char.  
     */       
    AString::operator char(){
        return toChar();
    }

    /**
     * Converts the AString into an unsigned char (first character).
     * @return The string converted into an unsigned char.  
     */       
    AString::operator unsigned char(){
        return toUChar();
    }
 
    /**
     * Converts the AString into a short.
     * @return The string converted into a short.  
     * The result will be 0 if it is not a number.
     */          
    AString::operator short(){
        return toShort();
    }

    /**
     * Converts the AString into an unsigned short.
     * @return The string converted into an unsigned short.  
     * The result will be 0 if it is not a number.
     */      
    AString::operator unsigned short(){
        return toUShort();
    }
    
    /**
     * Converts the AString into an int.
     * @return The string converted into an int.  
     * The result will be 0 if it is not a number.
     */     
    AString::operator int(){
        return toInt();
    }

    /**
     * Converts the AString into an unsigned int.
     * @return The string converted into an unsigned int.  
     * The result will be 0 if it is not a number.
     */      
    AString::operator unsigned int(){
        return toUInt();
    }
    
    /**
     * Converts the AString into a long.
     * @return The string converted into a long.  
     * The result will be 0 if it is not a number.
     */    
    AString::operator long(){
        return toLong();
    }

    /**
     * Converts the AString into an unsigned long.
     * @return The string converted into an unsigned long.  
     * The result will be 0 if it is not a number.
     */    
    AString::operator unsigned long(){
        return toULong();
    }

    /**
     * Converts the AString into a float.
     * @return The string converted into a float.  
     * NaN if string is not a number.
     */    
    AString::operator float(){
        return toFloat();
    }

    /**
     * Converts the AString into a double.
     * @return The string converted into a double.  
     * NaN if string is not a number.
     */    
    AString::operator double(){
        return toDouble();
    }

    /**
     * Increment operator.  The string is converted to a double and
     * incremented.
     * @return The AString with the new incremented value.
     */    
    AString& AString::operator ++(){
        double lValue = toDouble();
        lValue++;
        *this = lValue;

        return *this;
    }
    
    /**
     * Increment operator.  The string is converted to a double and
     * incremented.
     * @return The AString with the new incremented value.
     */            
    AString& AString::operator ++(int){
        double lValue = toDouble();
        lValue++;
        *this = lValue;

        return *this;
    }    
   
    /**
     * Splits an AString into a list of AString.
     * @param aDelim the delimitation string used to determine the split locations.
     * Default value is comma ','.
     * @return A list split apart at the delimitation string.
     */    
    std::vector<AString> AString::split(std::string aDelim){
        std::vector<std::string> lSplit = glch::split_string(*this,aDelim);
        std::vector<AString> lRet(lSplit.size());
        
        size_t i = 0;
        for(std::vector<std::string>::iterator it = lSplit.begin(); it != lSplit.end(); it++, i++){
            lRet.at(i) = (*it);
        }
        
        return lRet;
        
    }

    /**
     * Splits an AString into a list of numeric ranges.
     * @param aDelim Character to denote the range.
     * @return List of numbers in the range.
     */
    std::vector<AString> AString::cron(long aMin, long aMax){
        std::vector<AString> lValues = split("/");
        std::vector<AString> lRanges = lValues.at(0).split(",");
        AString lBuffer;
        
        
        std::vector<AString> lRet;
        long lStep = 1;
        
        
        if(this->find("/") != std::string::npos){
            lStep = lValues.at(1);
        }
        
        for(size_t i = 0; i < lRanges.size(); i++){
            bool lSplitFlag = false;
            
            if(lRanges.at(i).find("-") != std::string::npos){
                std::vector<AString> lSplit = lRanges.at(i).split("-");
                std::vector<long> lFullRange = glch::range(lSplit.at(0).toLong(),lSplit.at(1).toLong(),lStep);
                lBuffer.push_vector(lFullRange);
                lSplitFlag = true;
            }
            
            if(lRanges.at(i).find(",") != std::string::npos){
                std::vector<AString> lFullRange = lRanges.at(i).split(",");
                lBuffer.push_vector(lFullRange);
                lSplitFlag = true;
            }            
            
            if(lRanges.at(i).find("*") != std::string::npos){
                std::vector<long> lFullRange = glch::range(aMin,aMax,lStep);
                lBuffer.push_vector(lFullRange);
                lSplitFlag = true;
            }
            
            if(!lSplitFlag){
                lBuffer << lRanges.at(i);
            }
            
        }
        
        lRet = lBuffer.split(",");
        //lBuffer.print();
        
        return lRet;
    }
    
    
    size_t AString::find_nth(std::string aValue, size_t aCount, size_t aPos){
        
        size_type lIndex = aPos;
        size_t lCount = 0;
        size_t lRet = 0;
        
        //std::cout << "Length: " << aValue.length() << " : " << aPos << std::endl;
        
        do{
            lRet = find(aValue,lIndex);
            if(lRet == std::string::npos){
                return std::string::npos;
            }
            //std::cout << "Find: " << lRet << " : " << lCount << " : " << aCount << " : " << lIndex << std::endl;
            lIndex = lRet+aValue.length();
            lCount ++;
        } while (lCount < aCount+1);
        
        return lRet;
    }
    
    AString AString::csv(size_t aRow, size_t aCol){
        return table(aRow,aCol,",","\n");
    }
    
    void AString::csv_replace(std::string aValue, size_t aRow, size_t aCol){
        table_replace(aValue,aRow,aCol,",","\n");
    }
    
    size_t AString::csv_row_count(){
        return table_row_count("\n");
    }
    
    size_t AString::csv_col_count(size_t aRow){
        return table_col_count(aRow,",","\n");
    }
    
    AString AString::table_row(size_t aRow, std::string aDelimRow){
        
        size_t lStartRow = 0;
        size_t lEndRow = 0;
        
        AString lRet = "";
        size_t lOffset = 0;
        
        if(aRow != 0){
            lStartRow = find_nth(aDelimRow,aRow-1,0);
            lEndRow = find_nth(aDelimRow,aRow,0);
            lOffset = 1;
        } else {
            lEndRow = find_nth(aDelimRow,aRow,0);
        }
        
        if(lStartRow == std::string::npos){
            lRet = "";
        } else {
            lRet = substr(lStartRow+lOffset,lEndRow-lStartRow-lOffset);
        }
        
        return lRet;
    }
    
    size_t AString::table_row_count(std::string aDelimRow){
        
        size_type lIndex = 0;
        size_t lCount = 0;
        size_t lRet = 0;
        
        do{
            lRet = find(aDelimRow,lIndex);
            lIndex = lRet+aDelimRow.length();
            lCount ++;
            
        } while (lRet != std::string::npos || lRet == length()-1);
            
      
        return lCount;
        
    }
    
    size_t AString::table_col_count(size_t aRow, std::string aDelimCol, std::string aDelimRow){

        size_t lOffset = 0;
        size_t lStartRow = 0;
        size_t lEndRow = 0;
        size_t lIndex = 0;
        size_t lCount = 0;
        size_t lRet = 0;
        
        if(aRow != 0){
            lStartRow = find_nth(aDelimRow,aRow-1,0);
            lEndRow = find_nth(aDelimRow,aRow,0);
            lOffset = 1;
        } else {
            lEndRow = find_nth(aDelimRow,aRow,0);
        }
     
        lIndex = lStartRow+lOffset;

        while (lRet != std::string::npos && lRet < lEndRow) {
            lRet = find(aDelimCol,lIndex);
            lIndex = lRet+aDelimCol.length();

            lCount ++;
        }
        
        return lCount;
    }
    
    void AString::table_replace(std::string aValue, size_t aRow, size_t aCol, std::string aDelimCol, std::string aDelimRow){
        
        size_t lStart = 0;
        size_t lEnd = 0;
        size_t lStartRow = 0;
        size_t lEndRow = 0;
        
        AString lRet = "";
        
        size_t lOffset = 0;
        if(aRow != 0){
            lStartRow = find_nth(aDelimRow,aRow-1,0);
            lEndRow = find_nth(aDelimRow,aRow,0);
        } else {
            lEndRow = find_nth(aDelimRow,aRow,0);
        }
        
        
        if(aCol == 0){
            //lStart = 0;
            lStart = lStartRow;
            lEnd = find_nth(aDelimCol,aCol,lStartRow);
            
            if(aRow != 0){
                lOffset = aDelimCol.length();
            }
            
        } else {
            lStart = find_nth(aDelimCol,aCol-1,lStartRow);
            lEnd = find_nth(aDelimCol,aCol,lStartRow);
            lOffset = aDelimCol.length();
        }
        
        if(lEnd > lEndRow){
            lEnd = lEndRow;
        }
        
        this->replace(lStart+lOffset,lEnd-lStart-lOffset,aValue);
        
        
    }
    
    AString AString::table(size_t aRow, size_t aCol, std::string aDelimCol, std::string aDelimRow){

        size_t lStart = 0;
        size_t lEnd = 0;
        size_t lStartRow = 0;
        size_t lEndRow = 0;
        
        AString lRet = "";
        
        size_t lOffset = 0;
        if(aRow != 0){
            lStartRow = find_nth(aDelimRow,aRow-1,0);
            lEndRow = find_nth(aDelimRow,aRow,0);
        } else {
            lEndRow = find_nth(aDelimRow,aRow,0);
        }
        
        
        if(aCol == 0){
            //lStart = 0;
            lStart = lStartRow;
            lEnd = find_nth(aDelimCol,aCol,lStartRow);
            
            if(aRow != 0){
                lOffset = aDelimCol.length();
            }
            
        } else {
            lStart = find_nth(aDelimCol,aCol-1,lStartRow);
            lEnd = find_nth(aDelimCol,aCol,lStartRow);
            lOffset = aDelimCol.length();
        }
        
        if(lEnd > lEndRow){
            lEnd = lEndRow;
        }
        
        if(lStart == std::string::npos){
            lRet = "";
        } else {
            lRet = substr(lStart+lOffset,lEnd-lStart-lOffset);
        }
        
        //std::cout << "CSV-Data: " << lIndex << " : " << lStart << " : " << lEnd << std::endl;
        
        return lRet;
    }
    
    /**
     * Prints the contents of the AString.
     * @param aDelim The string used to terminate the string in the input.  Default newline.
     */    
    void AString::print(AString aDelim){
        std::cout << *this << aDelim;
    }
    
    
    
    
    
}