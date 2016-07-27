/* 
 * File:   FileLoad.h
 * Author: brian
 *
 * Created on June 19, 2014, 6:24 PM
 */

#ifndef FILELOAD_H
#define	FILELOAD_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

namespace glch {

    /**
     * Returns the size of a file using file streams.
     * @param aFileName path of file.
     * @return Size of file.
     */
    size_t file_size (std::string aFileName);
    
    /**
     * Saves a text file from a string buffer.
     * @param aFileName Name of file being saved.
     * @param aStringBuffer String buffer containing the save data.
     */
    void save_text_file(std::string aFileName, std::string &aStringBuffer);

    
    /**
     * Loads a text file specified from FileName, data is returned as a string.
     * @param aFileName Name of text file being loaded into memory.
     * @return String containing document.
     */
    std::string load_text_file(std::string aFileName);
    
    /**
     * Counts the number of delimitators contained in the file.
     * @param aFileName File being scanned.
     * @param aDelim Character we are searching for in the file.
     * @return Number of instances of delimitation found in file. 
     */
    size_t count_file_delim(std::string aFileName, char aDelim);

    /**
     * Loads a file into a string buffer.
     * @param aFileName Name of file being loaded into the buffer.
     * @param aBuffer Buffer to load data into.
     */
    void load_file(std::string aFileName, std::string &aBuffer);
    
    /**
     * Loads a file into a string buffer.
     * @param aFileName Name of file being loaded into the buffer.
     * @param aBuffer Buffer to load data into.
     */    
    void load_file(std::string aFileName, std::vector<unsigned char> &aBuffer);
    
    /**
     * Loads a file into a string buffer.
     * @param aFileName Name of file being loaded into the buffer.
     * @param aBuffer Buffer to load data into.
     */    
    void load_file(std::string aFileName, std::vector<char> *aBuffer);
    
    /**
    * Function that checks if aFileName exists by checking if we can
    *  open it or not.
    * @param argFileName -String containing filename we are checking for
    * @return -True if file exists, false if file does not exist.
    */
    bool file_exists(std::string aFileName);

}

#endif	/* FILELOAD_H */

