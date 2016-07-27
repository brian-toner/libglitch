#include "DirectoryFunctions.h"

namespace glch{

    /**
     * Uses system calls to create a directory structure.
     * @param aDirectory Directory to create.
     * @return The system call return value.
     */
    int makedir(std::string aDirectory){
        return system(glch::AString("mkdir -p %1").argr(aDirectory).c_str() );
    }
    
    /**
     * Uses system calls to remove a directory and all files contained in the directory.
     * @param aDirectory Directory to remove.
     * @return  The system call return value;
     */
    int rmdir(std::string aDirectory){
        return system(glch::AString("rm -rf %1").argr(aDirectory).c_str() );
    }

    std::string get_current_path(){
        
#if defined(WIN32) || defined(WIN64)
        wchar_t lCWD[1024];
        char* lCWDRet = (char*)_wgetcwd(lCWD,1024);
#else
        char lCWD[1024];
        char* lCWDRet = getcwd(lCWD,1024);
#endif
        std::string lRet = "";
        
        if(lCWDRet != NULL){
            lRet = lCWDRet;
        }
        
        return lRet;
    }
    
    /**
     * Gets the home path of the user through the use of environmental variables.
     * HOMEPATH, HOME, HOMEDRIVE, USERPROFILE are all examined.
     * @return The user's home path.
     */
    std::string get_home_path(){

        AStringList lEnvNames = AString("HOMEPATH,HOME,HOMEDRIVE,USERPROFILE").split(",");
        
        //Looping through the most common env names where home is contained.
        //This should be cross platform.
        for(AStringList::iterator it = lEnvNames.begin(); it != lEnvNames.end(); it++){
            
            if(getenv((*it).c_str()) != NULL){
                return getenv((*it).c_str());
            }
            
        }
        
        return "";
        //Last ditch effort.
        //return (getpwuid(getuid())->pw_dir);

    }
    
    /**
     * Checks if a directory exists.  If it does the function will return true.
     * Otherwise the function will return false.  This will not work for relative
     * path names.
     * @param aDirName Directory we are checking for.
     * @return True if the directory exists.  False otherwise.
     */    
    bool directory_exists(std::string aDirName){
        
        struct stat info;

        if( stat( aDirName.c_str(), &info ) != 0 ){
            return 0;
        } else if( info.st_mode & S_IFDIR ) {
            return 1;
        } else {
            return 0;
        }
        
    }

    /**
     * Checks if a folder exists, if it does not then it creates the folder.
     * 
     * @param argFolder Folder we want to ensure sure exists.
     * @param argHasFile If it's a file/folder combo.  We can strip off the file name 
     * and still create the directory.
     */
    void check_makedir(std::string argFolder, bool argHasFile){

        AString locFolder;

        if(argHasFile){
            locFolder = get_path(argFolder);

        } else {
            locFolder = argFolder.c_str();
        }

        //If the folder doesn't exist create.
        if(!directory_exists(locFolder)){
            makedir(locFolder);
        }    

    }
    
}