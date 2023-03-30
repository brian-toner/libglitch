#include "AStringFunctions.h"

namespace glch{

    glch::AString directory_parse(std::string aFileName, std::string aCommand){
        
        
        glch::AStringList lPath = glch::AString(aFileName).split("/");
        glch::AString lRet = aCommand;
        lPath.back() = get_file_base_name(aFileName);
        
        for(size_t i = 0; i < lPath.size(); i++){
            AString lCommandStr = AString("%d%1").argr(i);
            size_t lCommandPos = lRet.find(lCommandStr);
            size_t lCommandLen = lCommandStr.length();
            
            if(lCommandPos != std::string::npos){
                lRet.replace(lCommandPos,lCommandLen,lPath.at(lPath.size()-1-i));
                i--;
            }
        }
        
        return lRet;
    }
    
    glch::AString file_name_parse(std::string aFileName, std::string aCommand, std::string aDelim){
        
        glch::AString lRet = aCommand;
        glch::AString lBaseName = get_file_base_name(aFileName);
        glch::AStringList lSplitName = lBaseName.split(aDelim);
        
        for(size_t i = 0; i < lSplitName.size(); i++){
            
            AString lCommandStr = AString("%f%1").argr(lSplitName.size()-i-1);
            size_t lCommandPos = lRet.find(lCommandStr);
            size_t lCommandLen = lCommandStr.length();
            
            if(lCommandPos != std::string::npos){
                lRet.replace(lCommandPos,lCommandLen,lSplitName.at(lSplitName.size()-1-i));
                i--;
            }
            
        }
        
        lRet = directory_parse(aFileName,lRet);
 
        return lRet;        
    }

}