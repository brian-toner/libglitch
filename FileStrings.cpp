
#include "FileStrings.h"


namespace glch {

    

    /**
     * Returns the name of the file with the extension and path stripped.
     * @param argFileName Full file/path of file.
     * @param argDelim The extension delimitation character.
     * @return The base name of the file.
     */
    std::string get_file_base_name(std::string argFileName, char argDelim){
        int locExtCount;
        int locBaseCount = argFileName.size()-1;

        std::string locReturn = "";

        while (argFileName.at(locBaseCount) != '/' && argFileName.at(locBaseCount) != '\\' && locBaseCount > 0){
            locBaseCount--;
        }

        locReturn = argFileName.substr(locBaseCount+1,argFileName.length()-locBaseCount);
        locExtCount = locReturn.size() - 1;

        while (locReturn.at(locExtCount) != argDelim && locExtCount > 0){
            locExtCount--;
        }

        if(locExtCount > 0){
            locReturn = locReturn.substr(0,locExtCount);
        }

        return locReturn;
    }

    /**
     * Returns the extension of the file.
     * @param argFileName Full file/path of file.
     * @param argToUpper Converts the return value to upper case.
     * @return 
     */    
    std::string get_extension(std::string argFileName, bool argToUpper){
        long locCount = argFileName.size()-1;
        std::string locReturn = "";

        while(argFileName.c_str()[locCount] != '.' && locCount > 0){
            locCount --;
        }

        locReturn = argFileName.substr(locCount+1,argFileName.length()-locCount);

        if(argToUpper)
            std::transform(locReturn.begin(), locReturn.end(),locReturn.begin(), ::toupper);

        return locReturn;

    }

    /**
     * Returns the last part of the filename.  Cuts the last part of the string up to the
     * last occurrence of the delimitation character.
     * @param argFileName Full file/path of file.
     * @param argDelim The delimitation character.
     * @return The last part of the string up to the final occurrence of the
     * delimitation character.
     */    
    std::string get_ending(std::string argFileName, char argDelim){
        long locCount = argFileName.size()-1;
        std::string locReturn = "";

        while(argFileName.c_str()[locCount] != argDelim && locCount > 0){
            locCount --;
        }

        locReturn = argFileName.substr(locCount+1,argFileName.length()-locCount);

        return locReturn;    
    }

    /**
     * Gets the name of the file included extension.
     * @param argPath Path of file we are getting the file name of.
     * @return The name of the file without the path.
     */    
    std::string get_file_name(std::string argPath){

        std::string locStrFolder = "";
        int i = argPath.length() - 1;

        while (argPath.at(i) != '/' && argPath.at(i) != '\\'){
            i--;
        }

        locStrFolder = argPath.substr(i+1,argPath.length()-i);

        return locStrFolder;

    }

    /**
     * Converts a file path into a vector of strings.
     * @param aInput Input file path.
     * @param aDst vector where the parts of the path are being copied to.
     */
    void path_to_vector(std::string aInput, std::vector<std::string> &aDst){

        std::vector<int> locDelimPos;
        aDst.clear();

        locDelimPos.push_back(0);

        //Searching for delimiters
        for(unsigned int i = 0; i < aInput.size(); i++){
            if(aInput.c_str()[i] == '/' || aInput.c_str()[i] == '\\'){
                locDelimPos.push_back(i);
            }
        }
        locDelimPos.push_back(aInput.size()); //Last delimiter at end of string

        aDst.resize(locDelimPos.size());

        //Cutting apart the string and placing in output
        for(unsigned int i = 0; i < locDelimPos.size()-1; i++){
            for(int j = locDelimPos.at(i); j < locDelimPos.at(i+1); j++){
                if(aInput.c_str()[j] != '/' || aInput.c_str()[j] != '\\')
                    aDst.at(i) += aInput.c_str()[j];
            }
        }

        //Removing any empty strings from output
        for(unsigned int i = 0; i < aDst.size(); i++){
            if(aDst.at(i).empty()){
                aDst.erase(aDst.begin() + i);
                i--;
            }
        }

    }

    
}