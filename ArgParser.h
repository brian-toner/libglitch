/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ArgParser.h
 * Author: brian
 *
 * Created on July 26, 2017, 9:19 AM
 */

#ifndef GLCH_ARGPARSER_H
#define GLCH_ARGPARSER_H

#include <vector>
#include "libglitch.h"
#include <map>

namespace glch{

struct ArgData{
    
    int vNumbArgs;                      //Number of parameters the argument has
    glch::AStringList vArgs;            //List of parameters
    bool vFound;                        //If the command line argument was found during the parsing.
    std::string vUsage;                 //The usage of the argument.
    std::string vDescription;           //Description of the command line argument.
    glch::AStringList vReqFlags;        //List of flags needed to utilize this argument.
    
};

class ArgParser {
public:
    ArgParser();
    ArgParser(const ArgParser& orig);
    virtual ~ArgParser();
    
    std::map<std::string, ArgData> vArguments;  //Number of arguments in the parse system

    /**
     * Displays a help menu;
     */
    void help();
    
    /**
     * Inserts an argument into the argparser.
     * e.g. insert("-help",0,"-help","Displays this help menu.");
     *      insert("-test",1,"-test [PrintCount]", "Prints test a PrintCount times.");
     * @param aArgName The name of the command line argument
     * @param aNumbArgs Number of parameters for the argument.
     * @param aUsage Text outlining the usage of the argument.
     * @param aDescription Text description of the argument
     */
    void insert(std::string aArgName, int aNumbArgs, std::string aUsage, std::string aDescription);
    
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
    void insert(std::string aArgName, int aNumbArgs, std::string aUsage, std::string aDescription, glch::AStringList aReqFlags);

    /**
     * Checks if an command line argument was input.
     * @param aArgName The name of the command line argument to check for.
     * @return True if the command line argument was set.
     */
    bool is_set(std::string aArgName);
    
    /**
     * Gets the command line argument parameter at aIndex.  Using the insert example:
     * e.g. arg("-Test",0) would yield [PrintCount]
     * @param aArgName Name of the command line argument to pull the parameter from.
     * @param aIndex The index of the parameter.
     * @return Returns the value of the command line argument parameter if it exists.
     */
    glch::AString arg(std::string aArgName, int aIndex);

    /**
     * Gets the command line argument parameter at aIndex, returns aDefaultVal
     * if the parameter is not set.  Using the insert example:
     * e.g. arg("-Test",0,5) would yield [PrintCount] if -Test is set, 5 otherwise.
     * @param aArgName Name of the command line argument to pull the parameter from.
     * @param aIndex The index of the parameter.
     * @return Returns the value of the command line argument parameter if it exists.
     */
    glch::AString arg(std::string aArgName, int aIndex, glch::AString aDefaultVal);
    
    /**
     * Gets the value of the parameters from the command line argument 
     * @param aArgName The name of the command line argument to pull the parameters for.
     * @return A list of the values assigned to the command line argument.
     */
    std::vector<glch::AString> args(std::string aArgName);
    
    /**
     * Returns the number of parameters the command line argument takes.
     * @param aArgName The name of the command line argument to look up.
     * @return The number of parameters of the command line argument.
     */
    int counts(std::string aArgName);
    
    /**
     * Scans over arguments and ensures that proper requirements are met.
     * If not error sounds and execution is terminated.
     */
    void check_flags();
    
    /**
     * Parses the command line arguments passed to the main function. e.g.
     * int main(argc, char* argv[]){
     *  parse(argc,argv);
     *  return 0;
     * }
     * @param argc Count of arguments.
     * @param argv Vector of arguments.
     */
    void parse(int argc, char* argv[]);
    void parse(glch::StringList aArgs);
    
private:

};

}

#endif /* GLCH_ARGPARSER_H */

