/* 
 * File:   AStringFunctions.h
 * Author: brian
 *
 * Created on April 25, 2016, 9:26 AM
 */

#ifndef ASTRINGFUNCTIONS_H
#define	ASTRINGFUNCTIONS_H

#include "AString.h"
#include "FileStrings.h"

namespace glch{

    /**
     * Parses a file name from a command string (path /foo/bar.txt e.g. d0-d1, into bar-foo) 
     * @param aFileName File name and path
     * @param aCommand Parsing command
     * @return A string parsed with the directory data.
     */
    glch::AString directory_parse(std::string aFileName, std::string aCommand);
    
    /**
     * Parses the base file name  from a command string (foo-bar-blaw.txt e.g. f2-f0, into blaw-foo
     * @param aFileName
     * @param aCommand
     * @param aDelim
     * @return 
     */
    glch::AString file_name_parse(std::string aFileName, std::string aCommand, std::string aDelim = "-");

}
    
#endif	/* ASTRINGFUNCTIONS_H */

