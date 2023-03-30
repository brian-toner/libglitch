/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MatTFunctions.h"


namespace glch{

    
    void save_xsm_us(string argFileName, MatT<unsigned short> &argSrc){

        vector<char> locSave;
        string locHeader;
        int locCount = 0;
        int locStep = 4;
        std::ofstream locOut;

        locHeader = "Binary " + 
                to_string(1) + " " + 
                to_string(argSrc.cols) + "x" + to_string(argSrc.rows) + " " +
                to_string(argSrc.cols*argSrc.rows) + "(4 byte reals)";

        locSave.resize(locHeader.size() + 1 + 1*argSrc.cols*argSrc.rows*locStep);
        for(size_t i = 0; i < locHeader.size(); i++){
            locSave.at(i) = locHeader[i];
            locCount++;
        }

        locSave.at(locCount) = 0x0A;
        locCount++;

        for(size_t i = 0; i < argSrc.size(); i++){
            *(float*)&locSave.at(locCount) = argSrc.at(i);
            locCount += locStep;
        }
        

        locOut.open(argFileName.c_str());
        locOut.write(&locSave.at(0), locSave.size());
        locOut.close();
    }
    
    
    void load_xsm_us(string locFile, MatT<unsigned short> &aImage){

        std::vector<char> locData;
        int locSplit = 0;
        string locHeader;
        vector<string> locSplitHeader;
        vector<string> locImageDim;
        int locWidth = 0;
        int locHeight = 0;

        load_file(locFile, &locData);

        //Getting header data.
        while(locData.at(locSplit) != 0x0A){
            locHeader += locData.at(locSplit);
            locSplit ++;
        }
        locSplit ++;

        locSplitHeader = glch::split_string(locHeader, " ");
        locImageDim = glch::split_string(locSplitHeader.at(2), "x");


        locWidth = string_to_type<int>(locImageDim.at(0));
        locHeight = string_to_type<int>(locImageDim.at(1));

        aImage.resize(locHeight,locWidth);
        copy_type_to_mat<unsigned short,float>(locData,aImage,locSplit);


    }
    
    
}


