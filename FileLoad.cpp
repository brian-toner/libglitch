

#include "FileLoad.h"
#include "AString.h"

namespace glch {

    /**
     * Returns the size of a file using file streams.
     * @param aFileName path of file.
     * @return Size of file.
     */
    size_t file_size (std::string aFileName) {
      long unsigned int lBegin,lEnd;                    //Start and stop of the file
      std::ifstream lMyFile (aFileName.c_str());        //Input file stream we are loading

      lBegin = lMyFile.tellg();
      lMyFile.seekg (0, std::ios::end);
      lEnd = lMyFile.tellg();
      lMyFile.close();

      //Once we found the start and end of the file return their difference
      return (lEnd-lBegin); 
    }

    /**
     * Saves a text file from a string buffer.
     * @param aFileName Name of file being saved.
     * @param aStringBuffer String buffer containing the save data.
     */
    void save_text_file(std::string aFileName, std::string &aStringBuffer){

        std::ofstream lInput;

        lInput.open(aFileName.c_str());
        lInput << aStringBuffer;
        lInput.close();

    }

    /**
     * Saves a text file from a string buffer.
     * @param aFileName Name of file being saved.
     * @param aStringBuffer String buffer containing the save data.
     */
    void append_text_file(std::string aFileName, std::string &aStringBuffer){

        std::ofstream lInput;

        lInput.open(aFileName.c_str(), std::ios_base::app);
        lInput << aStringBuffer;
        lInput.close();

    }
    
    /**
     * Loads a text file specified from FileName, data is returned as a string.
     * @param aFileName Name of text file being loaded into memory.
     * @return String containing document.
     */
    std::string load_text_file(std::string aFileName){

        std::ifstream lInput;                           //Input string of loaded file.
        long unsigned int lSize = file_size(aFileName); //Size of file being loaded.
        std::string lReturn = "";                       //Container for return value.

        if(lSize > 0){
            lReturn.resize(lSize);
            char * locPt = &lReturn.at(0);

            lInput.open(aFileName.c_str(), std::ios::binary | std::ios::in);
            lInput.read(locPt,lSize);
            lInput.close();
        }

        return lReturn;
    }

    /**
     * Counts the number of delimitators contained in the file.
     * @param aFileName File being scanned.
     * @param aDelim Character we are searching for in the file.
     * @return Number of instances of delimitation found in file. 
     */
    size_t count_file_delim(std::string aFileName, char aDelim){

        std::ifstream locInput;
        long unsigned int locSize = file_size(aFileName);
        long unsigned int locCount = 0; 
        std::vector<char> locData;

        locData.resize(locSize);
        char * locPt = &locData.at(0);

        locInput.open(aFileName.c_str());

        locInput.read(locPt,locSize);

        locInput.close();

        for(long unsigned int i = 0; i < locSize; i++){

            if(locData.at(i) == aDelim){
                locCount++;
            }
        }

        return locCount;
    }


    /**
     * Loads a file into a string buffer.
     * @param aFileName Name of file being loaded into the buffer.
     * @param aBuffer Buffer to load data into.
     */ 
    void load_file(std::string aFileName, std::string &aBuffer){

        std::vector<char> locData; //Buffer we are copying data to.
        aBuffer = "";

        load_file(aFileName, &locData);


        for(size_t i = 0; i < locData.size(); i++)
            aBuffer += locData.at(i);

    }

    /**
     * Loads a file into a string buffer.
     * @param aFileName Name of file being loaded into the buffer.
     * @param aBuffer Buffer to load data into.
     */     
    void load_file(std::string aFileName, std::vector<unsigned char> &aBuffer){

        char *lBuffer;                            //Points to the location of our buffer location, locReturn
        long unsigned int lFileSize = 0;          //Size the buffer needs to be
        std::ifstream lFile(aFileName.c_str()); //File stream data

        aBuffer.clear();

        //Gets size of file if it exists.
        if( lFile.is_open() ){
            lFileSize = file_size(aFileName);
        }

        //Resizes the buffer and loads the data into it.
        if(lFileSize > 0){

            aBuffer.resize(lFileSize);
            lBuffer = (char *)&aBuffer.at(0);

            lFile.read(lBuffer, lFileSize);
        }

        lFile.close();    
    }

    /**
     * Loads a file into a string buffer.
     * @param aFileName Name of file being loaded into the buffer.
     * @param aBuffer Buffer to load data into.
     */ 
    void load_file(std::string argFileName, std::vector<char> *locReturn){

        char *locBuffer;                            //Points to the location of our buffer location, locReturn
        long unsigned int locFileSize = 0;          //Size the buffer needs to be
        std::ifstream locFile(argFileName.c_str()); //File stream data

        locReturn->clear();

        //Gets size of file if it exists.
        if( locFile.is_open() ){
            locFileSize = file_size(argFileName);
        }

        //cout << "File Size: " << locFileSize << endl;

        //Resizes the buffer and loads the data into it.
        if(locFileSize > 0){

            locReturn->resize(locFileSize);
            locBuffer = &locReturn->at(0);

            locFile.read(locBuffer, locFileSize);
        }

        locFile.close();

    }

    /**
    * Function that checks if aFileName exists by checking if we can
    *  open it or not.
    * @param argFileName -String containing filename we are checking for
    * @return -True if file exists, false if file does not exist.
    */
    bool file_exists(std::string  aFileName){
        std::ifstream file(aFileName.c_str()); //File stream we are working with.
        bool locReturn = false; //Assume file does not exist.

        //If the stream is able to open the file then it must exist.
        if( file.is_open() ){
            locReturn = true;
        }

        file.close();
        return locReturn;

    }


}