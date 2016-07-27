/* 
 * File:   SRAL.cpp
 * Author: brian
 * 
 * Created on July 5, 2015, 1:13 PM
 */

#include "SRAL.h"

namespace glch{


/**
 * Changes a string into a Self Referencing Address List.  This means that a string
 * which is spit apart by brackets is placed into a list that can be self referenced.
 * @param argInput
 * @param argOutVect
 */
void string_to_sral(std::string argInput, std::vector<std::string> &argOutVect, std::vector<Bracket> *argBracket){
    
    std::vector<Bracket> locBracket;
    std::vector<BracketTrack> locTracker;
    std::vector<BracketTrack> locTrackerAdj;
    std::vector<BracketTrack> locTrackerFinal;
    std::vector<std::string> locAddressedStr;
    std::vector<std::string> locFinalStrings;
    
    if(argBracket == NULL){
        build_bracket_list(locBracket);
    } else {
        locBracket = *argBracket;
    }
    
    split_brackets(argInput, locTracker);
    inject_addresses(argInput, locTracker, locTrackerAdj, locAddressedStr);

    for(int i = locAddressedStr.size()-1; i > -1 ; i--){

        if(!has_brackets(locAddressedStr.at(i),locBracket)  && in_str(locAddressedStr.at(i), "%") ){
            locFinalStrings.push_back(locAddressedStr.at(i));
        }
        
    }

    for(long unsigned int i = 0; i < locAddressedStr.size(); i++){
    
        split_brackets(locAddressedStr.at(i), locTrackerFinal);

        for(long unsigned int j = 0; j < locTrackerFinal.size(); j++){
            std::string locTemp = locAddressedStr.at(i);
            int locSize = locTrackerFinal.at(j).varEnd - locTrackerFinal.at(j).varStart - 1;
            std::string tempOutStr = locTemp.substr(locTrackerFinal.at(j).varStart + 1, locSize);
            
            if(!has_brackets(tempOutStr,locBracket) && in_str(tempOutStr, "%")){
                locFinalStrings.push_back(tempOutStr);
            }                      
        }
    }
    
    sort(locFinalStrings.begin(), locFinalStrings.end(), compare_arg_str);
    int locCount = 1;

    argOutVect.push_back(locFinalStrings.at(0));
    
    for(long unsigned int i = 0; i < locTracker.size(); i++){
        std::string tempSubStr;
        std::string tempLocAdd;

        tempLocAdd = "%" + to_string(i+1);    
        tempSubStr = argInput.substr(locTracker.at(i).varStart+1, locTracker.at(i).varEnd-locTracker.at(i).varStart-1);

        if(!has_brackets(tempSubStr,locBracket)){
            argOutVect.push_back(tempSubStr);
        } else {
            argOutVect.push_back(locFinalStrings.at(locCount));
            locCount ++;
        }     

    }    
}

Bracket bracket(char argLeft, char argRight){
    Bracket locReturn = {argLeft, argRight};
    return locReturn;
}

void build_bracket_list(std::vector<Bracket> &argBracketList){
    argBracketList.push_back(bracket('(', ')'));
    argBracketList.push_back(bracket('{', '}'));
    argBracketList.push_back(bracket('[', ']'));
    //argBracketList.push_back(bracket('<', '>'));
    argBracketList.push_back(bracket('\'', '\''));
    argBracketList.push_back(bracket('\"', '\"'));
    
}

BracketTrack bracket_track(size_t argType, size_t argStart, size_t argEnd, size_t argBranch){
    BracketTrack locReturn = {argType, argStart, argEnd, argBranch};
    return locReturn;
}

void split_brackets(std::string argInput, std::vector<BracketTrack> &argTracker){
    
    std::vector<Bracket> locBracket;
    build_bracket_list(locBracket);
    std::vector<int> locRefCounter;
    
    argTracker.clear();
    
    int locBracketCount = 0;
    
    for(size_t i = 0; i < argInput.size(); i++){
        //cout << i << endl;
        for(size_t j = 0; j < locBracket.size(); j ++){
            if(argInput.at(i) == locBracket.at(j).varLeft){
                locBracketCount ++;
                locRefCounter.push_back(locBracketCount);
                argTracker.push_back(bracket_track(j, i, 0, locRefCounter.size()));
                
            }
            
            if(argInput.at(i) == locBracket.at(j).varRight){
                int tempPoint = locRefCounter.at(locRefCounter.size()-1)-1;
                if(j == argTracker.at(tempPoint).varType){
                    
                    argTracker.at(tempPoint).varEnd = i;
                    locRefCounter.pop_back();
                } else {
                    throw RuntimeErrorReport("Error: Mismatched Delim");
                }
            }
            
            
        }
        
    }
    
}

void inject_addresses(std::string argInput, const std::vector<BracketTrack> &argTracker, std::vector<BracketTrack> &argTrackerAdj, std::vector<std::string> &argAddressedStr){
    
    //vector<BracketTrack> locTrackerAdj;
    
    argTrackerAdj = argTracker;

    argAddressedStr.clear();
    
    
    size_t locMaxChain = 0;
    for(long unsigned int i = 0; i < argTracker.size(); i++){
        if(argTracker.at(i).varBranch > locMaxChain){
            locMaxChain = argTracker.at(i).varBranch;
        }
    }    
    
    for(size_t i = locMaxChain; i > 0; i--){
        std::string locModString = argInput;
        
        for(long unsigned int j = 0; j < argTrackerAdj.size(); j++){
            
            if(argTrackerAdj.at(j).varBranch == i){

                std::string tempLocAdd = "%" + to_string(j + 1);
                std::string locTempBranch = locModString;
                std::string locTempSubSt = locModString;
                int tempBranchSize = argTrackerAdj.at(j).varEnd - argTrackerAdj.at(j).varStart + 1;
                int tempOffset = tempBranchSize - tempLocAdd.size();

                locTempBranch = locModString.substr(argTrackerAdj.at(j).varStart, tempBranchSize);
                locModString.replace(argTrackerAdj.at(j).varStart, tempBranchSize, tempLocAdd);
                locTempSubSt = locModString.substr(argTrackerAdj.at(j).varStart, tempLocAdd.size());
                
                //cout << locTempBranch << " : " << locModString << " : " << tempOffset << endl;
                
                argTrackerAdj.at(j).varEnd = argTrackerAdj.at(j).varStart + tempLocAdd.size();
                
                for(long unsigned int k = 0; k < argTrackerAdj.size(); k++){

                    if(argTrackerAdj.at(k).varStart > argTrackerAdj.at(j).varStart && argTrackerAdj.at(k).varBranch == i){
                        argTrackerAdj.at(k).varStart -= tempOffset;
                        argTrackerAdj.at(k).varEnd -= tempOffset;

                    }
                }
            }
        }
        
        argAddressedStr.push_back(locModString);
        
    }
    

}

bool has_brackets(std::string argInput, std::vector<Bracket> &argBracket){

    bool locReturn = false;

    for(long unsigned int i = 0; i < argBracket.size(); i++){
        std::string tempBracket;
        tempBracket = argBracket.at(i).varLeft;

        if(in_str(argInput,tempBracket)){
            locReturn = true;
        }
    }
    
    return locReturn;
}


}//END om