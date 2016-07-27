/* 
 * File:   FileStrings.h
 * Author: brian
 *
 * Created on June 19, 2014, 5:44 PM
 */

#ifndef FILESTRINGS_H
#define	FILESTRINGS_H

#include <iostream>
#include <algorithm> 
#include <vector>

#include "AString.h"

namespace glch {

    /**
     * Returns the directory structure of a file path.  Program cuts off last forward or back slash.
     * @param argFileName The full path and file.
     * @return The path leading to the file.
     */
    std::string get_path(std::string argFileName);
    
    /**
     * Returns the name of the file with the extension and path stripped.
     * @param argFileName Full file/path of file.
     * @param argDelim The extension delimitation character.
     * @return The base name of the file.
     */
    std::string get_file_base_name(std::string argFileName, char argDelim = '.');
    
    /**
     * Returns the extension of the file.
     * @param argFileName Full file/path of file.
     * @param argToUpper Converts the return value to upper case.
     * @return 
     */
    std::string get_extension(std::string argFileName, bool argToUpper = true);
    
    /**
     * Returns the last part of the filename.  Cuts the last part of the string up to the
     * last occurrence of the delimitation character.
     * @param argFileName Full file/path of file.
     * @param argDelim The delimitation character.
     * @return The last part of the string up to the final occurrence of the
     * delimitation character.
     */
    std::string get_ending(std::string argFileName, char argDelim);
    
    /**
     * Gets the name of the file included extension.
     * @param argPath Path of file we are getting the file name of.
     * @return The name of the file without the path.
     */
    std::string get_file_name(std::string argPath);

    /**
     * Converts a file path into a vector of strings.
     * @param aInput Input file path.
     * @param aDst vector where the parts of the path are being copied to.
     */    
    void path_to_vector(std::string argInput, std::vector<std::string> &argOutputVect);

}

#endif	/* FILESTRINGS_H */

