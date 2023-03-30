/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ArgParser.cpp
 * Author: brian
 * 
 * Created on July 26, 2017, 9:19 AM
 */

#include "ArgParser.h"

namespace glch{

ArgParser::ArgParser() {
}

ArgParser::ArgParser(const ArgParser& orig) {
}

ArgParser::~ArgParser() {
}

/**
 * Displays a help menu;
 */
void ArgParser::help(){

    std::cout << "Command:\tNumb args:\tUsage:\tRequires:\n\t\tDescription:" << std::endl;
    for(std::map<std::string, ArgData>::iterator it = vArguments.begin(); it != vArguments.end(); it++){
        std::cout << (*it).first << "\t\t" << (*it).second.vNumbArgs << "\t\t" << (*it).second.vUsage << "\t\t";
        glch::print_vect_fn((*it).second.vReqFlags);
        std::cout << "\n\t\t" << (*it).second.vDescription << std::endl;
        std::cout << std::endl;
    }

}

/**
 * Inserts an argument into the argparser.
 * e.g. insert("-help",0,"-help","Displays this help menu.");
 *      insert("-test",1,"-test [PrintCount]", "Prints test a PrintCount times.");
 * @param aArgName The name of the command line argument
 * @param aNumbArgs Number of parameters for the argument.
 * @param aUsage Text outlining the usage of the argument.
 * @param aDescription Text description of the argument
 */
void ArgParser::insert(std::string aArgName, int aNumbArgs, std::string aUsage, std::string aDescription){

    std::pair<std::string, ArgData> lInsert;
    lInsert.first = aArgName;
    lInsert.second.vNumbArgs = aNumbArgs;
    lInsert.second.vUsage = aUsage;
    lInsert.second.vDescription = aDescription;
    lInsert.second.vFound = false;
    lInsert.second.vArgs.resize(aNumbArgs);

    vArguments.insert(lInsert);

}

/**
 * Inserts an argument into the argparser.
 * e.g. insert("-help",0,"-help","Displays this help menu.");
 *      insert("-test",1,"-test [PrintCount]", "Prints test a PrintCount times.");
 * @param aArgName The name of the command line argument
 * @param aNumbArgs Number of parameters for the argument.
 * @param aUsage Text outlining the usage of the argument.
 * @param aDescription Text description of the argument
 * @param aReqFlags The argument flags required to operate this argument.
 */
void ArgParser::insert(std::string aArgName, int aNumbArgs, std::string aUsage, std::string aDescription, glch::AStringList aReqFlags){

    std::pair<std::string, ArgData> lInsert;
    lInsert.first = aArgName;
    lInsert.second.vNumbArgs = aNumbArgs;
    lInsert.second.vUsage = aUsage;
    lInsert.second.vDescription = aDescription;
    lInsert.second.vFound = false;
    lInsert.second.vArgs.resize(aNumbArgs);
    lInsert.second.vReqFlags = aReqFlags;
    
    vArguments.insert(lInsert);

}


/**
 * Checks if an command line argument was input.
 * @param aArgName The name of the command line argument to check for.
 * @return True if the command line argument was set.
 */
bool ArgParser::is_set(std::string aArgName){

    std::map<std::string, ArgData>::iterator it = vArguments.find(aArgName);

    if(it != vArguments.end()){
        return (*it).second.vFound;
    } else {
        return false;
    }

}

/**
 * Gets the command line argument parameter at aIndex.  Using the insert example:
 * e.g. arg("-Test",0) would yield [PrintCount]
 * @param aArgName Name of the command line argument to pull the parameter from.
 * @param aIndex The index of the parameter.
 * @return Returns the value of the command line argument parameter if it exists.
 */
glch::AString ArgParser::arg(std::string aArgName, int aIndex){
    if(counts(aArgName) > aIndex){
        return args(aArgName).at(aIndex);
    } else {
        return "";
    }
}

/**
 * Gets the command line argument parameter at aIndex, returns aDefaultVal
 * if the parameter is not set.  Using the insert example:
 * e.g. arg("-Test",0,5) would yield [PrintCount] if -Test is set, 5 otherwise.
 * @param aArgName Name of the command line argument to pull the parameter from.
 * @param aIndex The index of the parameter.
 * @return Returns the value of the command line argument parameter if it exists.
 */
glch::AString ArgParser::arg(std::string aArgName, int aIndex, glch::AString aDefaultVal){
    
    if(is_set(aArgName)){
        return arg(aArgName,aIndex);
    }
    
    return aDefaultVal;
}

/**
 * Gets the value of the parameters from the command line argument 
 * @param aArgName The name of the command line argument to pull the parameters for.
 * @return A list of the values assigned to the command line argument.
 */
std::vector<glch::AString> ArgParser::args(std::string aArgName){

    std::map<std::string, ArgData>::iterator it = vArguments.find(aArgName);

    if(it != vArguments.end()){
        return (*it).second.vArgs;
    } else {
        std::vector<glch::AString> lRet;
        return lRet;
    }

}

/**
 * Returns the number of parameters the command line argument takes.
 * @param aArgName The name of the command line argument to look up.
 * @return The number of parameters of the command line argument.
 */
int ArgParser::counts(std::string aArgName){

    std::map<std::string, ArgData>::iterator it = vArguments.find(aArgName);

    if(it != vArguments.end()){
        return (*it).second.vNumbArgs;
    } else {
        return 0;
    }

}

void ArgParser::check_flags(){
    bool lError = false;
    for(std::map<std::string, ArgData>::iterator it = vArguments.begin(); it != vArguments.end(); it++){
        
        for(glch::AStringList::iterator itj = (*it).second.vReqFlags.begin(); itj != (*it).second.vReqFlags.end(); itj++){
            if(is_set((*it).first) && !is_set((*itj))){
                std::cout << "Error, " << (*it).first << " requires the " << (*itj) << " option.  See help for further details.\n";
                lError = true;
            }
        }
        
    }
    
    if(lError){
        exit(0);
    }
    
}

/**
 * Parses the command line arguments passed to the main function. e.g.
 * int main(argc, char* argv[]){
 *  parse(argc,argv);
 *  return 0;
 * }
 * @param argc Count of arguments.
 * @param argv Vector of arguments.
 */
void ArgParser::parse(int argc, char* argv[]){

    glch::StringList lArgs(argc);

    for(int i = 0; i < argc; i++){
        lArgs.at(i) = argv[i];
    }
    
    parse(lArgs);
}

void ArgParser::parse(glch::StringList lArgs){

    for(std::map<std::string, ArgData>::iterator it = vArguments.begin(); it != vArguments.end(); it++){
        
        size_t lFind = glch::find_string_in_vect(lArgs,(*it).first);


        if(lFind != GLCH_NOT_FOUND){
            (*it).second.vFound = true;

            for(int j = 0; j < (*it).second.vNumbArgs; j++){

                if(lArgs.size() > lFind+j+1){
                    (*it).second.vArgs.at(j) = lArgs.at(lFind+j+1);
                } else {
                    std::cout << "Warning, " << (*it).first << " is missing argument: " << j << std::endl;
                }
            }
        }
    }
    

    check_flags();
}

}