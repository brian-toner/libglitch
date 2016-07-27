/* 
 * File:   DirectoryFunctions.h
 * Author: brian
 *
 * Created on January 13, 2016, 1:03 PM
 */

#ifndef DIRECTORYFUNCTIONS_H
#define	DIRECTORYFUNCTIONS_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>

#include "AString.h"

namespace glch{
    
    /**
     * Uses system calls to create a directory structure.
     * @param aDirectory Directory to create.
     * @return The system call return value.
     */    
    int makedir(std::string aDirectory);
    
    /**
     * Uses system calls to remove a directory and all files contained in the directory.
     * @param aDirectory Directory to remove.
     * @return  The system call return value;
     */    
    int rmdir(std::string aDirectory);
    
    
    std::string get_current_path();
    
    /**
     * Gets the home path of the user through the use of environmental variables.
     * HOMEPATH, HOME, HOMEDRIVE, USERPROFILE are all examined.
     * @return The user's home path.
     */    
    std::string get_home_path();
    
    /**
     * Checks if a directory exists.  If it does the function will return true.
     * Otherwise the function will return false.  This will not work for relative
     * path names.
     * @param aDirName Directory we are checking for.
     * @return True if the directory exists.  False otherwise.
     */
    bool directory_exists(std::string aDirName);

    /**
     * Checks if a folder exists, if it does not then it creates the folder.
     * 
     * @param argFolder Folder we want to ensure sure exists.
     * @param argHasFile If it's a file/folder combo.  We can strip off the file name 
     * and still create the directory.
     */
    void check_makedir(std::string argFolder, bool argHasFile = false);
}
#endif	/* DIRECTORYFUNCTIONS_H */

