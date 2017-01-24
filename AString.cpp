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
     * Splits an AString into a list of AString.
     * @param aDelim the delimitation string used to determine the split locations.
     * Default value is comma ','.
     * @return A list split apart at the delimitation string.
     */    
    std::vector<AString> AString::split(std::string aDelim, std::string aIgnoreTolkenStart, std::string aIgnoreTolkenEnd){
        std::vector<std::string> lSplit = glch::split_string(*this,aDelim,aIgnoreTolkenStart,aIgnoreTolkenEnd);
        std::vector<AString> lRet(lSplit.size());
        
        size_t i = 0;
        for(std::vector<std::string>::iterator it = lSplit.begin(); it != lSplit.end(); it++, i++){
            lRet.at(i) = (*it);
            lRet.at(i).replace_all_strings(aIgnoreTolkenStart,"");
            lRet.at(i).replace_all_strings(aIgnoreTolkenEnd,"");
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
    
    size_t AString::find_ignore_tolkens(std::string aValue, size_t aIndex, std::string aIgnoreTolkenStart, std::string aIgnoreTolkenEnd){
        
        size_t lIgnoreCount = 0;
        bool lSameTolken = false;
        bool lIgnoreStart = false;
        
        if(aIgnoreTolkenStart.compare(aIgnoreTolkenEnd) == 0){
            lSameTolken = true;
        }

        for(size_t i = aIndex; i < length(); i++){

            if(lSameTolken && lIgnoreCount > 0){
                lIgnoreStart = true;
            } else {
                lIgnoreStart = false;
            }

            if(!lIgnoreStart && substr(i,aIgnoreTolkenStart.length()).compare(aIgnoreTolkenStart) == 0){
                lIgnoreCount ++;
                i += aIgnoreTolkenStart.length();
            }
            
            if(substr(i,aIgnoreTolkenEnd.length()).compare(aIgnoreTolkenEnd) == 0){
                lIgnoreCount --;
                i += aIgnoreTolkenEnd.length();
            }            
            
            if(lIgnoreCount == 0){
                if(substr(i,aValue.length()).compare(aValue) == 0){
                    return i;
                }
            }

        }
        
        return std::string::npos;
        
    }
    
    
    size_t AString::find_nth(std::string aValue, size_t aCount, size_t aPos, std::string aTolkenStart, std::string aTolkenEnd){
        
        size_type lIndex = aPos;
        size_t lCount = 0;
        size_t lRet = 0;
        
        //std::cout << "Length: " << aValue.length() << " : " << aPos << std::endl;
        
        do{
            lRet = find_ignore_tolkens(aValue,lIndex,aTolkenStart,aTolkenEnd);
            if(lRet == std::string::npos){
                return std::string::npos;
            }
            //std::cout << "Find: " << lRet << " : " << lCount << " : " << aCount << " : " << lIndex << std::endl;
            lIndex = lRet+aValue.length();
            lCount ++;
        } while (lCount < aCount+1);
        
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

    AString AString::csvi(size_t aRow, std::string aCol, std::string aTextDelim, bool aStripTextDelim){
        size_t lCol = csv_col_index(aCol,aTextDelim);
        if(lCol == std::string::npos){
            return "";
        } else {
            return csv(aRow, lCol, aTextDelim, aStripTextDelim);
        }
 
    }
    
    AString AString::csv(size_t aRow, size_t aCol, std::string aTextDelim, bool aStripTextDelim){
        AString lRet = table(aRow, aCol, "\n", ",", aTextDelim);
        if(aStripTextDelim){
            lRet.replace_all_strings(aTextDelim,"");
        }
        return lRet;
    }
    
    AString AString::csv(size_t aPage, size_t aRow, size_t aCol, std::string aTextDelim){
        return table(aPage, aRow, aCol, "\n///\n", "\n", ",");
    }
    
    AString AString::csvi(size_t aPage, size_t aRow, std::string aCol, std::string aTextDelim){
        size_t lCol = csv_col_index(aCol,aPage,aTextDelim);
        if(lCol == std::string::npos){
            return "";
        } else {
            return csv(aPage, aRow, lCol, aTextDelim);
        }
    }
    
    AString& AString::csv_replace(std::string aValue, size_t aRow, size_t aCol, std::string aTextDelim){
        return table_replace(aValue, aRow, aCol, "\n", ",", aTextDelim);
    }    
    
    AString& AString::csv_replace(std::string aValue, size_t aPage, size_t aRow, size_t aCol, std::string aTextDelim){
        return table_replace(aValue, aPage, aRow, aCol, "\n///\n", "\n", ",", aTextDelim);
    }

    size_t AString::csv_page_count(std::string aTextDelim){
        return table_page_count("\n///\n",aTextDelim);
    }
    
    size_t AString::csv_row_count(size_t aPage, std::string aTextDelim){
        return table_row_count(aPage, "\n///\n", "\n", aTextDelim);
    }

    size_t AString::csv_row_count(std::string aTextDelim){
        return table_row_count("\n",aTextDelim);
        
    }

    size_t AString::csv_col_count(size_t aRow, std::string aTextDelim){
        return table_col_count(aRow, "\n", ",", aTextDelim);
    }   
    
    size_t AString::csv_col_count(size_t aPage, size_t aRow, std::string aTextDelim){
        return table_col_count(aPage,aRow, "\n///\n", "\n", ",", aTextDelim);

    }
   


    size_t AString::csv_row_index(std::string aRowName, size_t aPage, std::string aTextDelim){
        return table(aPage, 0, "\n///\n", "\n///\n", aTextDelim).csv_row_index(aRowName,aTextDelim);
    }
    
    size_t AString::csv_col_index(std::string aColName, size_t aPage, std::string aTextDelim){
        return table(aPage, 0, "\n///\n", "\n", aTextDelim).csv_col_index(aColName,aTextDelim);;
    }
    

    
    size_t AString::csv_col_index(std::string aColName, std::string aTextDelim){
        return table_col_index(aColName, "\n", ",", aTextDelim);
    }

    size_t AString::csv_row_index(std::string aRowName, std::string aTextDelim){
        return table_row_index(aRowName, "\n", ",", aTextDelim);
    }

    size_t AString::table_page_count(std::string aDelimPage, std::string aTextDelim){

        std::vector<std::string> lDelim(1);
        lDelim.at(0) = aDelimPage;
        
        return table_dim_count(0,glch::AString(""),lDelim);
    }
    
    size_t AString::table_row_count(std::string aDelimRow, std::string aTextDelim){

        return table_page_count(aDelimRow,aTextDelim);
    }

    size_t AString::table_row_count(size_t aPage, std::string aDelimPage, std::string aDelimRow, std::string aTextDelim){

        std::vector<std::string> lDelim(2);
        lDelim.at(0) = aDelimPage;
        lDelim.at(1) = aDelimRow;
        
        return table_dim_count(1,glch::AString("%1").arg(aPage),lDelim,aTextDelim);
    }    
    
    size_t AString::table_col_count(size_t aRow, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim){
        
        return table_row_count(aRow,aDelimRow,aDelimCol,aTextDelim);   
    }    

    size_t AString::table_col_count(size_t aPage, size_t aRow, std::string aDelimPage, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim){

        std::vector<std::string> lDelim(3);
        lDelim.at(0) = aDelimPage;
        lDelim.at(1) = aDelimRow;
        lDelim.at(2) = aDelimCol;
        
        return table_dim_count(2,glch::AString("%1,%2").arg(aPage).arg(aRow),lDelim,aTextDelim);
        
    }   
    
    size_t AString::table_row_index(std::string aRowName, size_t aPage, std::string aDelimPage, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim){
        
        size_t lRet = std::string::npos;
        
        
        for(size_t i = 0; i < table_row_count(aPage,aDelimPage,aDelimRow,aTextDelim); i++){
            
            glch::AString lRowName = table(aPage, i, 0, aDelimPage, aDelimRow, aDelimCol, aTextDelim);

            if(lRowName.compare(aRowName) == 0 ){
                return i;
            }
            
        }
        
        return lRet;
        
    }
    
    size_t AString::table_row_index(std::string aRowName, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim){
        
        size_t lRet = std::string::npos;
        
        for(size_t i = 0; i < table_row_count(aDelimRow,aTextDelim); i++){
            
            glch::AString lRowName = table(i, 0, aDelimRow, aDelimCol, aTextDelim);

            if(lRowName.compare(aRowName) == 0 ){
                return i;
            }
            
        }
        
        return lRet;
        
    }
    
    size_t AString::table_col_index(std::string aColName, size_t aPage, std::string aDelimPage, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim){
        size_t lRet = std::string::npos;
        
        for(size_t i = 0; i < table_col_count(aPage, 0, aDelimPage, aDelimRow, aDelimCol, aTextDelim); i++){
            
            glch::AString lColName = table(aPage, 0, i, aDelimPage, aDelimRow, aDelimCol, aTextDelim);
            
            if(lColName == aColName){
                lRet = i;
                break;
            }
            
        }
        
        return lRet;
    }
    
    size_t AString::table_col_index(std::string aColName, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim){
        size_t lRet = std::string::npos;
        
        for(size_t i = 0; i < table_col_count(0, aDelimRow, aDelimCol, aTextDelim); i++){
            
            glch::AString lColName = table(0, i, aDelimRow, aDelimCol, aTextDelim);
            
            if(lColName == aColName){
                lRet = i;
                break;
            }
            
        }
        
        return lRet;
    }
 
    AString AString::table_row(size_t aRow, std::string aDelimRow, std::string aTextDelim){
        
        std::vector<std::string> lDelim(1);
        lDelim.at(0) = aDelimRow;

        return table_dim_count(0,glch::AString("%1").arg(aRow),lDelim);
        
    }
    
    void AString::find_bounds(size_t aIndex, size_t aStartPos, size_t aEndPos, std::string aDelim, size_t &lStart, size_t &lEnd, std::string aTextDelim){

        if(aIndex > 0){
            lStart = find_nth(aDelim,aIndex-1,aStartPos,aTextDelim,aTextDelim)+aDelim.length();
        } else {
            lStart = aStartPos;
        }
        lEnd = find_nth(aDelim,aIndex,aStartPos,aTextDelim,aTextDelim);

        if(lEnd > aEndPos){
            lEnd = aEndPos;
        }
        
    }
    
    /**
     * Counts the number of occurrences of aDelim between start position and end position. 
     * @param aDelim The string to find
     * @param aStartPos The start position for the search.
     * @param aEndPos The end position for the search.
     * @param aTextDelim The text delim to search past.
     * @return The number of counts of the search string.
     */
    size_t AString::count_between(std::string aDelim, size_t aStartPos, size_t aEndPos, std::string aTextDelim){

        size_t lIndex = aStartPos;
        size_t lCount = 0;
        
        while (lIndex != std::string::npos && lIndex < aEndPos) {
            
            lIndex = find_ignore_tolkens(aDelim,lIndex,aTextDelim,aTextDelim);
            if(lIndex != std::string::npos){
                lIndex += aDelim.length();
            }
            lCount ++;
        }
        
        return lCount;
    }
    
    AString& AString::table_replace(std::string aValue, vector<size_t> aIndex, std::vector<std::string> aDelims, std::string aTextDelim){
        
        std::vector<size_t> lStart(aIndex.size()+1,0);
        std::vector<size_t> lEnd(aIndex.size()+1,0);
        lEnd.at(0) = -1;
        AString lRet = "";
        
        for(size_t i = 1; i < aIndex.size()+1; i++){
            //std::cout << i << " : " << aIndex.at(i-1) << " : " << lStart.at(i-1) << " : " << lEnd.at(i-1) << " : " << aDelims.at(i-1) << " : " << lStart.at(i) << " : " << lEnd.at(i) << std::endl;
            find_bounds(aIndex.at(i-1),lStart.at(i-1),lEnd.at(i-1),aDelims.at(i-1),lStart.at(i),lEnd.at(i),aTextDelim);
        }
        
        replace(lStart.back(),lEnd.back()-lStart.back(),aValue);
        
        return *this;
    }    
    
    AString& AString::table_replace(std::string aValue, size_t aPlane, size_t aRow, size_t aCol, std::string aDelimPlane, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim){
        
        std::vector<std::string> lDelim(3);
        lDelim.at(0) = aDelimPlane;
        lDelim.at(1) = aDelimRow;
        lDelim.at(2) = aDelimCol;
        
        std::vector<size_t> lIndex = glch::AString("%1,%2,%3").arg(aPlane).arg(aRow).arg(aCol);
        table_replace(aValue,lIndex,lDelim,aTextDelim);
        
        return *this;

    }    

    AString& AString::table_replace(std::string aValue, size_t aRow, size_t aCol, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim){
        
        std::vector<std::string> lDelim(2);
        lDelim.at(0) = aDelimRow;
        lDelim.at(1) = aDelimCol;
        
        std::vector<size_t> lIndex = glch::AString("%1,%2").arg(aRow).arg(aCol);
        table_replace(aValue,lIndex,lDelim,aTextDelim);
        
        return *this;

    }    
    
    size_t AString::table_dim_count(size_t aDimension, vector<size_t> aIndex, std::vector<std::string> aDelims, std::string aTextDelim){
        
        std::vector<size_t> lStart(aDimension+1,0);
        std::vector<size_t> lEnd(aDimension+1,0);
        lEnd.at(0) = -1;

        for(size_t i = 1; i < aDimension+1; i++){
            find_bounds(aIndex.at(i-1),lStart.at(i-1),lEnd.at(i-1),aDelims.at(i-1),lStart.at(i),lEnd.at(i),aTextDelim);
            //std::cout << i << " : " << aIndex.at(i-1) << " : " << lStart.at(i-1) << " : " << lEnd.at(i-1) << " : " << aDelims.at(i-1) << " : " << lStart.at(i) << " : " << lEnd.at(i) << std::endl;
        }

        return count_between(aDelims.at(aDimension),lStart.at(aDimension),lEnd.at(aDimension),aTextDelim);
        
        
    }
//
//    size_t AString::table_dim_index(std::string aDimName, size_t aDimension, size_t &aCount, std::vector<size_t> aIndex, std::vector<std::string> aDelim, std::string aTextDelim){
//        
//        size_t lRet = std::string::npos;
//        
//        if(aDimension < aCount){
//            
//            for(size_t i = 0; i < table_dim_count(aDimension,aIndex,aDelim,aTextDelim); i++){
//                return table_dim_index(aDimName,aDimension,aCount++,aIndex,aDelim,aTextDelim);
//            }
//        } else {
//            glch::AString lColName = table(aIndex,aDelim,aTextDelim);
//            
//            if(lColName == aDimName){
//                return aIndex.at(aDimension);
//            }
//        }
//        
//    }
//    
//
//    size_t AString::table_dim_index(std::string aDimName, size_t aDimension, std::vector<size_t> aIndex, std::vector<std::string> aDelim, std::string aTextDelim){
//        size_t lRet = std::string::npos;
//        
//        for(size_t i = 0; i < table_dim_count(aDimension,aIndex,aDelim,aTextDelim); i++){
//            aIndex.at(aDimension) = i;
//            glch::AString lColName = table(aIndex,aDelim,aTextDelim);
//            
//            //std::cout << aDimName << " : " << lColName << std::endl;
//            
//            
//            
//            if(lColName == aDimName){
//                lRet = i;
//                break;
//            }
//            
//        }
//        
//        return lRet;
//    }    

    AString AString::table(vector<size_t> aIndex, std::vector<std::string> aDelims, std::string aTextDelim){
        
        std::vector<size_t> lStart(aIndex.size()+1,0);
        std::vector<size_t> lEnd(aIndex.size()+1,0);
        lEnd.at(0) = -1;
        AString lRet = "";
        
        for(size_t i = 1; i < aIndex.size()+1; i++){
            //std::cout << i << " : " << aIndex.at(i-1) << " : " << lStart.at(i-1) << " : " << lEnd.at(i-1) << " : " << aDelims.at(i-1) << " : " << lStart.at(i) << " : " << lEnd.at(i) << std::endl;
            find_bounds(aIndex.at(i-1),lStart.at(i-1),lEnd.at(i-1),aDelims.at(i-1),lStart.at(i),lEnd.at(i),aTextDelim);
        }

        if(lStart.back() == std::string::npos){
            lRet = "";
        } else {
            lRet = substr(lStart.back(),lEnd.back()-lStart.back());
        }
        
        return lRet;
    }
    
    AString AString::table(size_t aPlane, std::string aDelimPlane, std::string aTextDelim){

        std::vector<std::string> lDelim(1);
        lDelim.at(0) = aDelimPlane;
        
        return table(glch::AString("%1").arg(aPlane),lDelim,aTextDelim);
        
    }
    
    AString AString::table(size_t aPlane, size_t aRow, size_t aCol, std::string aDelimPlane, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim){

        std::vector<std::string> lDelim(3);
        lDelim.at(0) = aDelimPlane;
        lDelim.at(1) = aDelimRow;
        lDelim.at(2) = aDelimCol;
        
        return table(glch::AString("%1,%2,%3").arg(aPlane).arg(aRow).arg(aCol),lDelim,aTextDelim);

    }    
    
    AString AString::table(size_t aRow, size_t aCol, std::string aDelimRow, std::string aDelimCol, std::string aTextDelim){

        std::vector<std::string> lDelim(2);
        lDelim.at(0) = aDelimRow;
        lDelim.at(1) = aDelimCol;
        
        return table(glch::AString("%1,%2").arg(aRow).arg(aCol),lDelim,aTextDelim);

    }    
    
    /**
     * Prints the contents of the AString.
     * @param aDelim The string used to terminate the string in the input.  Default newline.
     */    
    void AString::print(AString aDelim){
        std::cout << *this << aDelim;
    }
    
    
    
    
    
}