/* 
 * File:   main.cpp
 * Author: brian
 *
 * Created on January 4, 2016, 6:59 PM
 */

#define RUNPROG false

#ifdef RUNPROG

#include <cstdlib>
#include <set>
#include <map>

#include "libglitch.h"
#include "AString.h"

using namespace std;
using namespace glch;


int main________(){
    
    vector<PointF> lpts;
    lpts.push_back(PointF(5,6));
    lpts.push_back(PointF(7,9));
    lpts.push_back(PointF(22,15));
    lpts.push_back(PointF(14,17));
    lpts.push_back(PointF(4,3));
    PointF lCent = centroid(lpts);
    double lTheta = orientation(lpts);
    vector<PointF> lMBR = minimal_bounding_rect(lpts);
    vector<PointF> lCvx = convex_hull(lpts);
    
    rotate_polygon(lpts,lCent,-lTheta);
    
    
    
    RectF lBounding = bounding_rect(lpts);
    vector<PointF> lBoundingPoly = lBounding.polygon();
    
    for(size_t i = 0; i < lpts.size(); i++){
        lpts.at(i).print();
    }
    
    std::cout << std::endl;
    for(size_t i = 0; i < lBoundingPoly.size(); i++){
        lBoundingPoly.at(i).print();
    }

    std::cout << std::endl;
    for(size_t i = 0; i < lMBR.size(); i++){
        lMBR.at(i).print();
    }
    
    std::cout << std::endl;
    for(size_t i = 0; i < lCvx.size(); i++){
        lCvx.at(i).print();
    }    
    
    return 0;
}

int main____(){

    MatT<unsigned short> lBrown;
    MatT<unsigned char> lOut;
    glch::load_pgm("/home/brian/Research/Andre/figment.csee.usf.edu/pub/DDSM/cases/normals/normal_02/case0200/TAPE_A_0200_1.COMB.16_PGM",lBrown);

    scale_mat_values(lBrown,lOut, 0, 255);
    glch::save_pgm("/home/brian/Research/Andre/figment.csee.usf.edu/pub/DDSM/cases/normals/normal_02/case0200/NEW_TAPE_A_0200_1.COMB.16_PGM",lOut);
    
    //char lSplit[2] = {0x0A,0x00};
    //AString lTest("P5%1%2 %3%1%4");
    //lTest.arg(lSplit).print();
    
    return 0;
}



class DFA{
public:
    
    std::set<std::string> vStates;
    std::vector<char> vAlphabet;
    std::map<std::string, std::map<char, std::string> > vDelta;
    std::string vStartState;
    std::set<std::string> vAcceptStates;
    std::string vCurrentState;
    
    DFA(){};
    DFA(std::set<std::string> aStates, 
        std::vector<char> aAlphabet, 
        std::map<std::string, std::map<char, std::string> > aDelta,
        std::string aStartState,
        std::set<std::string> aAcceptStates){
        
        vStates = aStates;
        vAlphabet = aAlphabet;
        vDelta = aDelta;
        vStartState = aStartState;
        vAcceptStates = aAcceptStates;
        vCurrentState = aStartState;
    }
    
    DFA(const DFA& orig) : vStates(orig.vStates),
                            vAlphabet(orig.vAlphabet),
                            vDelta(orig.vDelta),
                            vStartState(orig.vStartState),
                            vAcceptStates(orig.vAcceptStates) {
        
    }
    
    DFA(glch::AString aDelta){
        
        glch::AStringList lTransitions = aDelta.split("\n");
        
        vStartState = lTransitions.at(0);
        vCurrentState = vStartState;
        glch::AStringList lAcceptStates = lTransitions.at(1).split(",");
        glch::AStringList lAlphabet = lTransitions.at(2).split(",");
        
        
        for(glch::AStringList::iterator it = lAcceptStates.begin(); it != lAcceptStates.end(); it++){
            vAcceptStates.insert((*it));
        }

        for(glch::AStringList::iterator it = lAlphabet.begin(); it != lAlphabet.end(); it++){
            vAlphabet.push_back((*it).at(0));
        }
        
        for(glch::AStringList::iterator it = lTransitions.begin()+3; it != lTransitions.end(); it++){
            glch::AStringList lFunctions = (*it).split(",");
            vStates.insert(lFunctions.at(0));
            
            for(size_t i = 1; i < lFunctions.size(); i++){
                vDelta[lFunctions.at(0)][vAlphabet.at(i)] = lFunctions.at(i);
            }
        } 
    }

    std::string compute(char aInput){       
        vCurrentState = vDelta[vCurrentState][aInput];
        return vCurrentState;
        
    }
    
    bool accepted(){
        if(vAcceptStates.find(vCurrentState) != vAcceptStates.end()){
            return true;
        }
        
        return false;
    }
    
    void print(){
        std::cout << vCurrentState << " : " << accepted() << std::endl;
    }
    
private:
    
};

int main_table_manip(){

    std::vector<std::string> lDelim = glch::AString("///;\n;,").to_vector<std::string>(";");
        
    //glch::AString lTable = "hello,world,test,new\n\"abcd,efgh\",\"1234,3456\",\"111,222\",aaa,bbb\n\"ghijklm\",333,444,\"555,666\"\n///\ntest,test2,test3\nabc,def,ghi\njkl,mno,pqr";
    glch::AString lTable = "1,2,3,4\n5,6,7,8,9\n10,11\n///\n12,13\n14,15,16\n///\n17\n18,19,20,21,22,23";
    //lTable.print();
    size_t aDimension = 0;
    
    
//    for(size_t i = 0; i < lTable.table_dim_count(aDimension,aIndex,aDelim,aTextDelim); i++){
//        aIndex.at(aDimension) = i;
//        glch::AString lColName = table(aIndex,aDelim,aTextDelim);
//
//        std::cout << aDimName << " : " << lColName << std::endl;
//
//        if(lColName == aDimName){
//            lRet = i;
//            break;
//        }
//
//    }
    
    lTable.print();
    
//    std::cout << lTable.table_dim_index("hello",2,glch::AString("0,0,0"),lDelim) << std::endl;
//    std::cout << lTable.table_dim_index("world",2,glch::AString("0,0,0"),lDelim) << std::endl;
//    std::cout << lTable.table_dim_index("test",2,glch::AString("0,0,0"),lDelim) << std::endl;
//    std::cout << std::endl; 
//    std::cout << lTable.table_dim_index("test",2,glch::AString("1,0,0"),lDelim) << std::endl;
//    std::cout << lTable.table_dim_index("test2",2,glch::AString("1,0,0"),lDelim) << std::endl;
//    std::cout << lTable.table_dim_index("test3",2,glch::AString("1,0,0"),lDelim) << std::endl;
//    std::cout << lTable.table_dim_index("test4",2,glch::AString("1,0,0"),lDelim) << std::endl;
//    std::cout << std::endl; 
//    
//    std::cout << lTable.table_dim_index("abc",1,glch::AString("1,0,0"),lDelim) << std::endl;
//    std::cout << lTable.table_dim_index("jkl",1,glch::AString("1,0,0"),lDelim) << std::endl;
//    std::cout << lTable.table_dim_index("test",1,glch::AString("1,0,0"),lDelim) << std::endl;
//    std::cout << lTable.table_dim_index("none",1,glch::AString("1,0,0"),lDelim) << std::endl;
//    std::cout << std::endl;
//    
//    std::cout << lTable.table_dim_index("hello",1,glch::AString("0,0,0"),lDelim) << std::endl;
//    std::cout << lTable.table_dim_index("jkl",1,glch::AString("0,0,0"),lDelim) << std::endl;
//    std::cout << lTable.table_dim_index("test",1,glch::AString("0,0,0"),lDelim) << std::endl;
//        
    
    
    
    
}

int main_test_table(){
    
    glch::AString lTable = "\"a-,-de-,-ghi\"-,-jkl:::::::a-,-de-,-ghi-,-jkl:::::::a-,-de-,-ghi-,-jkl:::::::123-,-4567-,-891011:::::::12-,-1314-,-151617:::::::///////////18-,-1920-,-212123:::::::242526-,-27282930-,-3132333435:::::::12-,-1314-,-151617:::::::///////////ababa-,-de-,-ghi:::::::123-,-4567-,-891011:::::::12-,-1314-,-151617:::::::";
    
    std::cout << lTable.table(0, 0, 0, "///////////", ":::::::", "-,-") << std::endl;
    std::cout << lTable.table(1, 0, 0, "///////////", ":::::::", "-,-") << std::endl;
    std::cout << lTable.table(2, 0, 0, "///////////", ":::::::", "-,-") << std::endl;
    
    std::vector<size_t> lIndex = glch::AString("2,0,0").to_vector<size_t>();
    std::vector<std::string> lDelim = glch::AString("///////////;:::::::;-,-").to_vector<std::string>(";");
    
    std::cout << lTable.table(lIndex,lDelim) << std::endl;
    
    std::cout << lTable.count_between("-,-",9,-1) << std::endl;
    
    std::cout << lTable.table_dim_count(0,glch::AString("0,0,0"),lDelim) << std::endl;
    std::cout << lTable.table_dim_count(1,glch::AString("0,0,0"),lDelim) << std::endl;
    std::cout << lTable.table_dim_count(2,glch::AString("0,0,0"),lDelim) << std::endl;
    
    for(size_t i = 0; i < lTable.table_dim_count(0,glch::AString(""),lDelim); i++){
        for(size_t j = 0; j < lTable.table_dim_count(1,glch::AString("%1").arg(i),lDelim); j++){
            for(size_t k = 0; k < lTable.table_dim_count(2,glch::AString("%1,%2").arg(i).arg(j),lDelim); k++){
                //std::cout << i << " : " << j << " : " << k << std::endl;
                std::cout << lTable.table(glch::AString("%1,%2,%3").arg(i).arg(j).arg(k),lDelim) << " ";
            }
            std::cout << std::endl;
        } 
        std::cout << "///\n";
    }
    
//    for(size_t i = 0; i < lTable.table_row_count("///////////"); i++){
//        
//    }
    
    //lTable.table_replace("Testing",2,1,"-,-",":::::::");
    //lTable.print();
    
}

int main_csv_stuff(){
    //glch::AString lTable = "'abcd,efgh',1234,3456\n\n,'111,222\n,aaa,bbb\n'ghijklm',333,444,555";

    glch::AString lTable = "hello,world,test,new\n\"abcd,efgh\",\"1234,3456\",\"111,222\",aaa,bbb\n\"ghijklm\",333,444,\"555,666\"\n///\ntest,test2,test3\nabc,def,ghi\njkl,mno,pqr";

    std::cout << lTable.table(0, 0, "\n///\n", "\n//////\n") << std::endl << std::endl;
    std::cout << lTable.table(1, 0, "\n///\n", "\n//////\n") << std::endl;
    
    std::cout << lTable.csv_col_index("hello",0) << std::endl;
    std::cout << lTable.csv_col_index("world",0) << std::endl;
    std::cout << lTable.csv_col_index("new",0) << std::endl;
    std::cout << lTable.csv_col_index("new1",0) << std::endl;

    std::cout << lTable.csv_col_index("test",1) << std::endl;
    std::cout << lTable.csv_col_index("test2",1) << std::endl;
    std::cout << lTable.csv_col_index("test3",1) << std::endl;
    std::cout << lTable.csv_col_index("test4",1) << std::endl;
    
    std::cout << lTable.csv_row_index("hello",0) << std::endl;
    std::cout << lTable.csv_row_index("\"abcd,efgh\"",0) << std::endl;
    std::cout << lTable.csv_row_index("\"ghijklm\"",0) << std::endl;
    std::cout << lTable.csv_row_index("new1",0) << std::endl;

    std::cout << lTable.csv_row_index("test",1) << std::endl;
    std::cout << lTable.csv_row_index("abc",1) << std::endl;
    std::cout << lTable.csv_row_index("jkl",1) << std::endl;
    std::cout << lTable.csv_row_index("test4",1) << std::endl;    
    
    //    std::cout << lTable.table(0,0,"'","\n") << std::endl;
//    std::cout << lTable.table(0,1,"'","\n") << std::endl;
//    std::cout << lTable.table(0,2,"'","\n") << std::endl;
//    std::cout << lTable.table(0,3,"'","\n") << std::endl;

    //std::cout << lTable.table(0,1,"\n","///").csv(0,0) << std::endl;
    
    //lTable.table(1,0,"\n","///").csv_replace("Testing",0,0);
//    lTable.csv_replace("Testing",1,0,0);
//    
//    std::cout << lTable << std::endl;
//    
    
    for(size_t i = 0; i < lTable.csv_page_count();i++){
        for(size_t j = 0; j < lTable.csv_row_count(i); j++){
            for(size_t k = 0; k < lTable.csv_col_count(i,j); k++){
                glch::AString lVal = glch::AString("\"%1-%2-%3\"").arg(i).arg(j).arg(k);
                //lTable.csv_replace(lVal,i,j,k);
                std::cout << lTable.csv(i,j,k) << " | ";
                //std::cout << i << " : " << j << " : " << k << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << "|||" << std::endl << std::endl;
    }
    
    
//    for(size_t i = 0; i < lTable.csv_row_count(); i++){
//        //std::cout << lTable.csv_col_count(i) << " : " << lTable.csv_row_count() << std::endl;
//        for(size_t j = 0; j < lTable.csv_col_count(i); j++){
//            glch::AString lVal = glch::AString("\"%1-%2\"").arg(i).arg(j);
//            lTable.csv_replace(lVal,i,j);
//            std::cout << lTable.csv(i,j) << " | ";
//        }
//        std::cout << std::endl;
//    }
    
    std::cout << lTable << std::endl;
    
//    std::cout << lTable.table(0,0,",","\n") << std::endl;
//    //std::cout << lTable.table(0,0,",","\n","") << std::endl;
//    std::cout << lTable.table(0,1,",","\n") << std::endl;
//    //std::cout << lTable.table(0,1,",","\n","") << std::endl;
//    std::cout << lTable.table(0,2,",","\n") << std::endl;
//    //std::cout << lTable.table(0,2,",","\n","") << std::endl;
//    std::cout << lTable.table(0,3,",","\n") << std::endl;
//    //std::cout << lTable.table(0,3,",","\n","") << std::endl;
//    std::cout << lTable.table(0,4,",","\n") << std::endl;
//    std::cout << lTable.table(1,0,",","\n") << std::endl;
//    std::cout << lTable.table(1,1,",","\n") << std::endl;
//    std::cout << lTable.table(1,2,",","\n") << std::endl;
//    std::cout << lTable.table(1,3,",","\n") << std::endl;
    //std::cout << lTable.find_ignore_tolkens(",",0,"'","'") << std::endl;
//std::cout << lTable.find(",",0,"'","'") << std::endl;
    
//    std::cout << lTable.find_nth(",",1,0,"'") << std::endl;
//    std::cout << lTable.find_nth(",",1,0) << std::endl;
//    std::cout << lTable.find_nth(",",2,0,"'") << std::endl;
//    std::cout << lTable.find_nth(",",2,0) << std::endl;
//    std::cout << lTable.find_nth(",",3,0,"'") << std::endl;
//    std::cout << lTable.find_nth(",",3,0) << std::endl;
}

int main_dirparse(){
    
    std::string lDelta = "S1\nS1\n\t,0,1\nS1,S2,S1\nS2,S1,S2";
    DFA lDFA(lDelta);

    lDFA.print();
    lDFA.compute('0');
    lDFA.print();
    lDFA.compute('1');
    lDFA.print();
    lDFA.compute('1');
    lDFA.print();
    lDFA.compute('0');
    lDFA.print();
    
    glch::AString lRet = glch::directory_parse("/abc/def/ghi/jkl/mno.txt", "%d1-%d0-%d1-%d4-%d4");
    lRet.print();
    
    glch::AString lRet2 = glch::file_name_parse("/abc/def/ghi/jkl/mno-pqr-stu.txt", "%f0-%f1-%d1");
    lRet2.print();
    
}

int main_1(){
    MatT<unsigned char> lBrown;
    MatT<unsigned char> lOut;
    glch::load_pgm("./test.pgm",lBrown);
    lOut = lBrown;
    lOut.zero();
    
    PolyT<int> lPoly(lBrown);
    lPoly.print();
    //lPoly.simplify(1);
    glch::simplify(lPoly.vData,3);
    
    std::cout << std::endl << std::endl;
    lPoly.print();
    std::cout << std::endl << std::endl;
    vector<Point> lPoints;
    //om::compute_line_points(Point(0,5),Point(0,0), lPoints);
    
    glch::compute_poly_points(lPoly.vData, lPoints);
    glch::print_vect_fn(lPoints, "\n");
    
    for(size_t i = 0; i < lPoints.size(); i++){
        glch::draw_point(lOut,lPoints.at(i),255);
        //om::save_pgm(AString("./out-%1.pgm").arg(i),lOut);
    }    
    glch::save_pgm(AString("./out-%1.pgm").argr(1),lOut);
    
    return 0;
}

int main_______(){
    
    MatT<unsigned char> lBrown;
    MatT<unsigned char> lOut;
    glch::load_pgm("./test.pgm",lBrown);
    lOut = lBrown;
    lOut.zero();
    
    
    std::cout << lBrown.rows << " : " << lBrown.cols << std::endl;
    BoundaryList lBoundaries;
    BoundaryList lTopBoundaries;
    Boundary lBoundary;
    
    compute_all_boundaries(lBrown,lBoundaries,lTopBoundaries);
    //lBoundary = find_boundary(lBrown,false);
    
    //om::draw_points(lOut,lBoundary,255);
    //om::draw_boundary(lBoundaries.back(),lOut);
    
    std::cout << lBoundaries.size() << std::endl;
    
    for(size_t i = 0; i < lBoundaries.size(); i++){
        //om::print_vect_fn(lBoundary);
        //om::draw_boundary(lBoundaries.at(i),lOut);
        //angle_sort(lBoundaries.at(i));
        //om::simplify(lBoundaries.at(i),1);
        glch::draw_poly(lOut,lBoundaries.at(i),255);
        //om::draw_points(lOut,lBoundaries.at(i),255);
        glch::save_pgm(AString("./out-%1.pgm").argr(i),lOut);
        lOut.zero();
        
        glch::print_vect_fn(lBoundaries.at(i));
        std::cout << std::endl << std::endl;
    }
    
    

    return 0;
}

/*
int main_random_noise_image(){
    //http://lodev.org/cgtutor/randomnoise.html
    //size_t lSize = 10;
    vector<MatT<unsigned char> > lTemp;
    MatT<unsigned char> lSave;
    lTemp.resize(3);

    for(size_t i = 0; i < 3; i++){
        std::cout << i << " : " << pow(2,i+1) << std::endl;
        lTemp.at(i).resize(1024,1024 );
        random_noise(lTemp.at(i),128,255);
        
    }

    glch::save_ppm("./random_color.ppm",lTemp);
    std::cout << "test" << std::endl;
    sum_mat(lTemp,lSave);
    
    glch::save_pgm("./random.pgm",lSave);

    return 0;
}



int main_random_noise_and_scaling(){
    //http://lodev.org/cgtutor/randomnoise.html
    //size_t lSize = 10;
    vector<MatT<unsigned char> > lTemp;
    vector<MatT<unsigned char> > lOut;
    MatT<unsigned char> lSave;
    lTemp.resize(10);
    lOut.resize(10);
    for(size_t i = 0; i < 10; i++){
        std::cout << i << " : " << pow(2,i+1) << std::endl;
        lTemp.at(i).resize(pow(2,i+1),pow(2,i+1) );
        random_noise(lTemp.at(i),0,255);
        
        lOut.at(i).resize(1024,1024);
        glch::scale_mat_size(lTemp.at(i),lOut.at(i));
        linear_interpolate(lOut.at(i),lOut.at(i));
        glch::save_pgm(AString("./random-%1.pgm").argr(i) ,lTemp.at(i));
        glch::save_pgm(AString("./random-scale-%1.pgm").argr(i) ,lOut.at(i));
    }
    std::cout << "test" << std::endl;
    sum_mat(lOut,lSave);
    
    glch::save_pgm("./random.pgm",lSave);


    
    //corners_to_center(lTemp,lTemp);
    //lTemp.print("");
    
    return 0;
}
*/
int main________________________(){
    //om::seed_rand();

    std::vector<MatT<double> > lBrown;
    //MatT<unsigned char> lAvg;
    size_t lSize = 32;
    MatT<double> lTemp(lSize,lSize);
    MatT<double> lTemp2(lSize,lSize);
    MatT<unsigned char> lTemp3(lSize,lSize);
    MatT<double> lMag(lSize,lSize);
    MatT<double> lPhase(lSize,lSize);
    MatT<double> lPS(lSize,lSize);
    
    //double lSqSize = 16;
    //draw_filled_rect(lTemp,Rect(lSize/2-lSqSize/2,lSize/2-lSqSize/2,lSqSize,lSqSize),255);
    //random_noise(lTemp,0,1);
    glch::load_pgm("./trans.pgm",lTemp);
    
    lTemp2.resize(lTemp.rows,lTemp.cols);
    lTemp3.resize(lTemp.rows,lTemp.cols);
    lMag.resize(lTemp.rows,lTemp.cols);
    lPhase.resize(lTemp.rows,lTemp.cols);
    lPS.resize(lTemp.rows,lTemp.cols);
    glch::scale_mat_values(lTemp,lTemp,0,1);
    glch::scale_mat_values(lTemp,lTemp3,0,255);
    glch::save_pgm("./test-rect.pgm",lTemp3);
    
    
    //random_noise(lTemp2,0,255);
    
    lBrown.push_back(lTemp);
    lBrown.push_back(lTemp2);

    //glch::compute_fft_2d(lBrown,1);
    magnitude_phase_fft(lBrown.at(0),lBrown.at(1),lMag,lPhase);
    powerspectrum_fft(lBrown.at(0),lBrown.at(1),lPS);
    //lMag.apply(log);
    corners_to_center(lMag,lMag);
    //std::cout << om::min(lMag.data) << " : " << om::max(lMag.data) << std::endl;
    //return 0;
    glch::scale_mat_values(lMag,lTemp3,0,255);
    glch::save_pgm("./test-fft-mag.pgm",lTemp3);
    //lPhase.apply(log);
    //corners_to_center(lPhase,lPhase);    
    glch::scale_mat_values(lPhase,lTemp3,0,255);
    glch::save_pgm("./test-fft-phase.pgm",lTemp3);
    
    corners_to_center(lPS,lPS); 
    glch::scale_mat_values(lPS,lTemp3,0,255);
    glch::save_pgm("./test-fft-ps.pgm",lTemp3);
    
    glch::scale_mat_values(lBrown.at(0),lTemp3,0,255);
    glch::save_pgm("./test-fft-real-t.pgm",lTemp3);
    glch::scale_mat_values(lBrown.at(1),lTemp3,0,255);
    glch::save_pgm("./test-fft-cplx-t.pgm",lTemp3);
    
    //glch::compute_fft_2d(lBrown,-1);
    
    glch::scale_mat_values(lBrown.at(0),lTemp3,0,255);
    glch::save_pgm("./test-fft-real.pgm",lTemp3);
    glch::scale_mat_values(lBrown.at(1),lTemp3,0,255);
    glch::save_pgm("./test-fft-cplx.pgm",lTemp3);
    

    
    //for(size_t i = 0; i < lSize; i++){
    //     brownian(1000,500,0,65535.0*1.0/lSize,10000,lBrown.at(i));
    //}
    
    //sum_mat(lBrown,lAvg);
    
    //om::load_pgm("./test.pgm",lTemp);
    //om::save_pgm("./test-copy.pgm",lTemp);
    //om::load_pgm("./test-copy.pgm",lTemp);
    //om::save_pgm("test-avg.ppm",lAvg);
    
    //om::load_ppm("./test.ppm",lBrown);
    //om::save_ppm("./test-copy.ppm",lBrown);
    
    return 0;
}

int main_modf(){
    double lVal = 255.55;
    for(int i = -750; i < 750; i++){
        std::cout << i << " : " << quotient(i,lVal)*fabs(lVal)+modf(i,lVal) << " : " << quotient(i,lVal) << " : " << remainder(i,lVal) << " : " << modf(i,lVal) << std::endl;
    }
}

int main_convolve(){
    MatT<double> lDst;
    MatT<double> lKer;
    MatT<double> lGauss;
    //str_to_mat("3,3|-1,0,1,-2,0,2,-1,0,1",lKer);
    str_to_mat("3,3|.111,.111,.111,.111,.111,.111,.111,.111,.111",lKer);
    
    MatT<double> lImg;
    str_to_mat("4,4|1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16",lImg);
    
    lDst = glch::convolve(lImg,lKer);
    
    
    lKer.print();
    lImg.print();
    lDst.print();
    
    gen_gaussian(10,10,lGauss);
    lGauss.print();
    
    lDst = glch::convolve(lImg,lGauss);
    lDst.print();
    std::cout << glch::sum_vector(lGauss.data) << std::endl;
}

int main_gauss(){
    
    MatT<double> lGauss;
    MatT<double> lDGauss;
    MatT<unsigned int> lConv;
    gen_gaussian_scaled(7,7,lGauss,255);
    normalize_matrix(lGauss, lDGauss);
    //lGauss.print();
    //lDGauss.print();
    
    glch::save_pgm("test_gauss.ppm",lGauss);
    
    convert_matrix(lGauss,lConv);
    lConv.print();
}

int main_shift(){
    MatT<double> lImg;
    str_to_mat("4,4|1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16",lImg);
    
    glch::shift_matrix(lImg,1,-1);
    
    lImg.print();
}

int main_shift_flip(){
    
    MatT<double> lImg;
    MatT<double> lImg2;
    MatT<double> lDst;

    str_to_mat("4,4|1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16",lImg);
    str_to_mat("5,5|1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25",lImg2);
    
    lImg.print();
    for(int i = -5; i < 5; i++){
        std::cout << i << std::endl;
        glch::shift_matrix(lImg,lDst,i,i);
        lDst.print();
    }
    
    
    flip_matrix_v(lImg);
    flip_matrix_h(lImg);
    lImg.print();
    
    flip_matrix_v(lImg2);
    flip_matrix_h(lImg2);
    lImg2.print();
}

int main_brown_shift(){

    glch::seed_rand();
    MatT<unsigned char> lBrown;
    
    for(int i = 0; i < 1; i++){
        brownian2(512,512,-1,1,-1,1,1,0,255,1000000,lBrown,true);
    }
    
    glch::save_pgm("test_brown.pgm",lBrown);
    shift_matrix(lBrown,-lBrown.cols/2,-lBrown.rows/2);
    glch::save_pgm("test_brown_sh.pgm",lBrown);
    
}

int main_fft(){
    glch::seed_rand();
    MatT<unsigned char> lBrown;
    MatT<unsigned char> lReal;
    MatT<unsigned char> lImag;
    std::vector<MatT<double> > lFFT;
    
    for(int i = 0; i < 1; i++){
        brownian2(512,512,-1,1,-1,1,1,0,255,1000000,lBrown,true);
    }
    
    glch::save_pgm("test_brown.pgm",lBrown);
    
    
    glch::compute_fft_2d_fwd(lBrown,lFFT);
    //magnitude_phase_fft(lBrown.at(0),lBrown.at(1),lMag,lPhase);
    //powerspectrum_fft(lBrown.at(0),lBrown.at(1),lPS);
    //lMag.apply(log);
    //normalize_matrix(lFFT.at(0), lFFT.at(0));
    //normalize_matrix(lFFT.at(1), lFFT.at(1));
    
    glch::scale_mat_values(lFFT.at(0),lReal,0,255);
    glch::scale_mat_values(lFFT.at(0),lImag,0,255);
    
    //convert_matrix(lFFT.at(0),lReal);
    //convert_matrix(lFFT.at(1),lImag);
    
    //corners_to_center(lFFT.at(0),lFFT.at(0));
    //corners_to_center(lFFT.at(1),lFFT.at(1));
    
    //glch::compute_fft_2d()
    
    glch::save_pgm("test_mag.pgm",lReal);
    glch::save_pgm("test_phse.pgm",lImag);
    
    glch::compute_fft_2d_rev(lFFT,lBrown);
    glch::save_pgm("test_brown_r.pgm",lBrown);
    
    shift_matrix(lBrown,-lBrown.cols/2,-lBrown.rows/2);
    glch::save_pgm("test_brown_sh.pgm",lBrown);
    
}

int main_resize_mat(){
    MatT<double> lImg;
    str_to_mat("4,4|1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16",lImg);
    
    MatT<double> lImg2;
    str_to_mat("4,4|1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16",lImg2);
    
    resize_mat(lImg,17,17);
    std::cout << lImg.rows << " : " << lImg.cols << std::endl;
    lImg.print();
    
    resize_mat_pad(lImg2, 17,17);
    std::cout << lImg2.rows << " : " << lImg2.cols << std::endl;
    lImg2.print();
    
}

void compute_parameters(std::vector<Point> aCluster){
    
    //print_vect_fn(aCluster);
    //std::cout << std::endl;
    std::vector<Point> lTP1 = pts_to_toppts(aCluster);
    BoundaryList lTopBound = compute_top_boundary(lTP1);
    Boundary lBL = get_boundary_points(lTP1);
    
    Boundary lTop = lTopBound.at(0);
    simplify(lTop,1);
    Boundary lCVX = convex_hull_new(lTop);
    //std::cout << area(lTop) << " : " << area(lCVX) << std::endl;
    

    
//    print_vect_fn(lTop);
//    std::cout << std::endl;
//    std::cout << std::endl;
//    print_vect_fn(lCVX);
//    std::cout << std::endl;
//    std::cout << std::endl;
//    print_vect_fn(aCluster);
//    std::cout << std::endl;
//    std::cout << std::endl;
    
    Moments lMoment;
    lMoment.set_moments(aCluster,10);
//    lMoment.vCentroid.print();
//    std::cout << "===============================" << std::endl;
//    
//    lMoment.vM.print();
//    std::cout << "===============================" << std::endl;
//    
//    lMoment.vMu.print();
//    std::cout << "===============================" << std::endl;
//    
//    lMoment.vNu.print();
//    
//    std::cout << "===============================" << std::endl;
//    print_vect(lMoment.vHu);
//    
//    std::cout << "\n===============================" << std::endl;
//    
    
    double lArea = glch::moment(aCluster,0,0);
    double lDiameter = glch::diameter_taxicab(aCluster);
    double lPerimeter = 0;
    std::vector<PointF> lBoundingRect = minimal_bounding_rect(aCluster);
    double lBRArea = area(lBoundingRect);
    
    double lEdges = 0;
    double lCorners = 0;
    
    count_top_features(lBL,lEdges,lCorners);    
    lPerimeter = lEdges;

    double lCirc = (4*3.14*lArea)/(lPerimeter*lPerimeter);
    double lFI = (4*lArea)/(lPerimeter*lDiameter);
    double lCER = lCorners/lEdges;
    double lOrientation = orientation(aCluster);
    double lWaviness = perimeter(lTop)/perimeter(lCVX);
    double lConvexAreaRatio = area(lTop)/area(lCVX);
    double lMinD, lMaxD;
    glch::min_max_distances(lCVX,lMinD,lMaxD);
    double lAspectRatio = lMinD/lMaxD;
    double lAreaRatio = lArea/lBRArea;
    
    std::cout << lArea << " : "  << lBRArea << " : " << lDiameter << " : " << lPerimeter << " : " << lCorners << " : " << lCirc << " : " << lFI << " : " << lCER << " : " << lWaviness << " : " << lAspectRatio << " : " << lAreaRatio << " : " << lConvexAreaRatio << " : " << lOrientation << " : " << lMoment.vCentroid.x << " : " << lMoment.vCentroid.y << " : ";    
    print_vect(lMoment.vHu, " : ");
    
    std::cout << std::endl;
}

#include "Parser.h"

int main_check_float(){
    
    cout << glch::is_float("1.1e1") << endl;
    cout << glch::is_float("1234567890101112312312312432141142123425.1e1") << endl;
    cout << glch::is_decimal("abc1234567890101112312312312432141142123425.1e1") << endl;
    cout << glch::is_decimal("abc1234567890101112312312312432141142123425.1e1abc") << endl;
    cout << glch::is_decimal("1234567890101112312312312432141142123425.1e1abc") << endl;
    cout << glch::is_decimal("1234567890101112312312312432141142123425.1876876867e-11234.766756") << endl;
    
}

long unsigned int front_white(glch::AString val){
    for(int i = 0;i < val.size(); i++){
        if(val[i] != ' ' && val[i] != '\t' && val[i] != '\n' && val[i] != '\r' && val[i] != '\f'){
            return i;
        }
    }
    return std::string::npos;
}

// first space at the end  end_white(" 12345   ") == 6
long unsigned int end_white(glch::AString val){
    for(int i = val.size()-1; i != 0; i--){
        if(val[i] != ' ' && val[i] != '\t' && val[i] != '\n' && val[i] != '\r' && val[i] != '\f'){
            return i;
        }
    }
    return std::string::npos;
}

glch::AString trim(glch::AString val){
    
    size_t f = front_white(val);
    size_t b = end_white(val);
    
    if(f==0 && b==std::string::npos){
        return val;
    }
    
    if(f==std::string::npos && b==std::string::npos){
        return "";
    }
    return val.substr(f, b-f+1);
    
}

glch::AString remove_special_chars(glch::AString val){
    
    return val.replace_all_strings("\n","").replace_all_strings("\t","").replace_all_strings("\r","").replace_all_strings("\f","");
}

glch::AString join(glch::AStringList val, int start, int end, glch::AString delim = "-"){
    
    glch::AString ret = "";
    for(int i = start; i < end; i++){
        ret.append(val[i],delim);
    }
    
    return ret;
}

void test_end_white(){
    
    std::cout << end_white(" 12345   ") << " : " << (end_white(" 12345   ") == 5) <<std::endl;
    std::cout << end_white(" 12345") << " : " <<(end_white(" 12345") == 5) <<std::endl;
    std::cout << end_white("    ") << " : " << (end_white("    ") == std::string::npos) <<std::endl;
}

void test_front_white(){
    
    std::cout << front_white(" 12345   ") << " : " << (front_white(" 12345   ") == 1) <<std::endl;
    std::cout << front_white("12345 ") << " : " << (front_white("12345 ") == 0) <<std::endl;
    std::cout << front_white("   ") << " : " << (front_white("   ") == std::string::npos) <<std::endl;
}

void test_trim(){
    
    std::cout << "'" << trim(" 12345   ") << "' : " << (trim(" 12345   ") == "12345") << std::endl;
    std::cout << "'" << trim("12345") << "' : " << (trim("12345") == "12345") << std::endl;
    std::cout << "'" << trim("12345 \n  ") << "' : " << (trim("12345 \n  ") == "12345") << std::endl;
    std::cout << "'" << trim(" \t  12345") << "' : " << (trim(" \t  12345") == "12345") << std::endl;
    std::cout << "'" << trim("   ") << "' : " << (trim("   ") == "") << std::endl;
    std::cout << "'" << trim("e") << "' : " << (trim("e") == "e") << std::endl;
}

void test_join(){
    
    glch::AString test = "abc,def,ghi,jkl";
    glch::AStringList vals = test.to_vector<AString>();
    
    std::cout << join(vals,1,3,"-") << " : " << (join(vals,1,3,"-") == "def-ghi") << std::endl;
    std::cout << join(vals,2,4,"-") << " : " << (join(vals,2,4,"-") == "ghi-jkl") << std::endl;
    std::cout << join(vals,0,2,"-") << " : " << (join(vals,0,2,"-") == "abc-def") << std::endl;
    
}

glch::AString generate_rule(glch::AString unparsedRule){
    
    if(!trim(unparsedRule).size()){
        return "";
    }
    
//    std::cout << "===================================" << std::endl;
//    std::cout << unparsedRule << std::endl;
//    std::cout << "===================================" << std::endl;
//    

    
    glch::AString ret = "";
    glch::AStringList lSplitTokens = unparsedRule.split(":");
    
    //glch::print_vect(lSplitTokens,"\n");
    glch::AString expr = trim(lSplitTokens[0]);
    
    
    glch::AStringList splitwhiter = remove_special_chars(lSplitTokens[1]).split("|");
    
    //std::cout << std::endl;
    
    for(int i = 0; i < splitwhiter.size(); i++){
        
        glch::AStringList splitterms = trim(splitwhiter[i]).split(" ");
        //glch::AStringList jointersm(splitterms.size()-1);
        glch::AString rule = expr + " " + splitterms[0] + " " + join(splitterms,1,splitterms.size());
        //std::cout << rule << std::endl;
        ret = ret + rule + "\n";
        
        //build sub rules
        for(int j = 1; j < splitterms.size()-1; j++){
            //jointersm[j-1] = join(splitterms,j,splitterms.size()) + " " + splitterms[j] + " " + join(splitterms,j+1,splitterms.size());
            ret = ret + join(splitterms,j,splitterms.size()) + " " + splitterms[j] + " " + join(splitterms,j+1,splitterms.size()) + "\n";;
            
        }
        
        //glch::print_vect(jointersm,"\n");
        
    }
    
    return ret;
    
}

glch::AString replace_symbols(glch::AString unparsedRule){
    unparsedRule.replace_all_strings("'('", "<LEFTP>");
    unparsedRule.replace_all_strings("')'", "<RIGHTP>");
    unparsedRule.replace_all_strings("'['", "<LEFTB>");
    unparsedRule.replace_all_strings("']'", "<RIGHTB>");
    unparsedRule.replace_all_strings("'{'", "<LEFTS>");
    unparsedRule.replace_all_strings("'}'", "<RIGHTS>");
    unparsedRule.replace_all_strings("'<'", "<LEFTC>");
    unparsedRule.replace_all_strings("'>'", "<RIGHTR>");       
    unparsedRule.replace_all_strings("' '", "<SPACE>"); 
    unparsedRule.replace_all_strings("'!'", "<EXCL>"); 
    unparsedRule.replace_all_strings("'*'", "<MUL>"); 
    unparsedRule.replace_all_strings("'/'", "<DIV>"); 
    unparsedRule.replace_all_strings("'+'", "<ADD>"); 
    unparsedRule.replace_all_strings("'-'", "<SUB>"); 
    unparsedRule.replace_all_strings("'?'", "<QM>"); 
    unparsedRule.replace_all_strings("'%'", "<MOD>"); 
    unparsedRule.replace_all_strings("'^'", "<XOR>"); 
    unparsedRule.replace_all_strings("'|'", "<OR>"); 
    unparsedRule.replace_all_strings("'&'", "<AND>"); 
    unparsedRule.replace_all_strings("'='", "<EQ>"); 
    unparsedRule.replace_all_strings("','", "<COMMA>"); 
    unparsedRule.replace_all_strings("':'", "<COLON>"); 
    unparsedRule.replace_all_strings("';'", "<SEMICOLON>");    
    
    return unparsedRule;
    
}

glch::AString parse_short_grammar(){
        
    //glch::AString lSample = glch::load_text_file("./c_grammar_full.txt");
    glch::AString lSample = glch::load_text_file("./grammar_float_v3");
    std::cout << lSample << std::endl;
    glch::AStringList lSplit1 = lSample.split("%%");
    
    
    glch::AString grammar = "";
    
    glch::AStringList lSplit = replace_symbols(lSplit1[1]).split(";");
    
    for(int i = 0; i < lSplit.size(); i++){
        //glch::AString test = generate_rule(lSplit.at(lSplit.size()-2));
        glch::AString test = generate_rule(lSplit.at(i));
        //std::cout << test << std::endl;
        grammar = grammar + test;
    }
    
    cout << grammar << std::endl;
    
    return grammar;
    
    //glch::print_vect(lSplit);
    
    glch::AStringList lSplitTokens = lSplit.at(lSplit.size()-2).split(":");
    
    glch::print_vect(lSplitTokens,"\n");
    glch::AString expr = trim(lSplitTokens[0]);
    
    //glch::AStringList splitwhitel = lSplitTokens[0].replace_all_strings("\n","").replace_all_strings("\t","");
    //glch::print_vect(splitwhitel);
    
    glch::AStringList splitwhiter = remove_special_chars(lSplitTokens[1]).split("|");
    
    std::cout << std::endl;
    
    for(int i = 0; i < splitwhiter.size(); i++){
        
        glch::AStringList splitterms = trim(splitwhiter[i]).split(" ");
        glch::AStringList jointersm(splitterms.size()-1);
        glch::AString rule = expr + " " + splitterms[0] + " " + join(splitterms,1,splitterms.size());
        std::cout << rule << std::endl;
        
        //build sub rules
        for(int j = 1; j < splitterms.size()-1; j++){
            jointersm[j-1] = join(splitterms,j,splitterms.size()) + " " + splitterms[j] + " " + join(splitterms,j+1,splitterms.size());
        }
        
        glch::print_vect(jointersm,"\n");
        
    }
    
    //cout << lSplitTokens[1].replace_all_strings("\n","").replace_all_strings("\t","") << std::endl;
    
    
    
    
}

void build_test_grammar(glch::AString grammar){
    
    //glch::AString lFile = glch::load_text_file("./grammar_fixed_v9");
    //grammar = lFile;
    
    glch::AStringList lInput = grammar.split("\n");
    
    Parser lParser;

//        lParser.add_rule("<FLOAT>", "<SIGN> <DIGIT>");
//        lParser.add_rule("<FLOAT>", "<SIGN> <DIGITEX>");
//        lParser.add_rule("<FLOAT>", "<DOT> <DIGIT>");
//        lParser.add_rule("<FLOAT>", "<DOT> <DIGITEX>");
//        lParser.add_rule("<FLOAT>", "<DIGIT> <DIGIT>");
//        lParser.add_rule("<FLOAT>", "<DIGIT> <DIGITEX>");
//        lParser.add_rule("<FLOAT>", "<DIGIT> <DOT>");
//        lParser.add_rule("<FLOAT>", "<DIGIT> <DOTDIG>");
//        lParser.add_rule("<FLOAT>", "<DIGIT> <EXPONENT>");
//        lParser.add_rule("<FLOAT>", "<SIGN> <DOTDIG>");
//        lParser.add_rule("<FLOAT>", "<SIGN> <DIGDOT>");
//        lParser.add_rule("<FLOAT>", "0");
//        lParser.add_rule("<FLOAT>", "1");
//        lParser.add_rule("<FLOAT>", "2");
//        lParser.add_rule("<FLOAT>", "3");
//        lParser.add_rule("<FLOAT>", "4");
//        lParser.add_rule("<FLOAT>", "5");
//        lParser.add_rule("<FLOAT>", "6");
//        lParser.add_rule("<FLOAT>", "7");
//        lParser.add_rule("<FLOAT>", "8");
//        lParser.add_rule("<FLOAT>", "9");
//        lParser.add_rule("<DOTDIG>", "<DOT> <DIGIT>");
//        lParser.add_rule("<DOTDIG>", "<DOT> <DIGITEX>");
//        lParser.add_rule("<DIGDOT>", "<DIGIT> <DOT>");
//        lParser.add_rule("<DIGDOT>", "<DIGIT> <DOTDIG>");
//        lParser.add_rule("<DIGITEX>", "<DIGIT> <EXPONENT>");
//        lParser.add_rule("<DIGIT>", "<DIGIT> <DIGIT>");
//        lParser.add_rule("<SIGNDIG>", "<SIGN> <DIGIT>");
//        lParser.add_rule("<DIGIT>", "0");
//        lParser.add_rule("<DIGIT>", "1");
//        lParser.add_rule("<DIGIT>", "2");
//        lParser.add_rule("<DIGIT>", "3");
//        lParser.add_rule("<DIGIT>", "4");
//        lParser.add_rule("<DIGIT>", "5");
//        lParser.add_rule("<DIGIT>", "6");
//        lParser.add_rule("<DIGIT>", "7");
//        lParser.add_rule("<DIGIT>", "8");
//        lParser.add_rule("<DIGIT>", "9");
//        lParser.add_rule("<SIGN>", "-");
//        lParser.add_rule("<SIGN>", "+");
//        lParser.add_rule("<DOT>", ".");
//        lParser.add_rule("<EXPONENT>", "<EXPSYM> <FLOATE>");
//        lParser.add_rule("<EXPSYM>", "e");
//        lParser.add_rule("<EXPSYM>", "E");
//        lParser.add_rule("<FLOATE>", "0");
//        lParser.add_rule("<FLOATE>", "1");
//        lParser.add_rule("<FLOATE>", "2");
//        lParser.add_rule("<FLOATE>", "3");
//        lParser.add_rule("<FLOATE>", "4");
//        lParser.add_rule("<FLOATE>", "5");
//        lParser.add_rule("<FLOATE>", "6");
//        lParser.add_rule("<FLOATE>", "7");
//        lParser.add_rule("<FLOATE>", "8");
//        lParser.add_rule("<FLOATE>", "9");
//        lParser.add_rule("<FLOATE>", "<SIGN> <DIGIT>");
//        lParser.add_rule("<FLOATE>", "<SIGN> <DIGITEX>");
//        lParser.add_rule("<FLOATE>", "<DOT> <DIGIT>");
//        lParser.add_rule("<FLOATE>", "<DOT> <DIGITEX>");
//        lParser.add_rule("<FLOATE>", "<DIGIT> <DIGIT>");
//        lParser.add_rule("<FLOATE>", "<DIGIT> <DIGITEX>");
//        lParser.add_rule("<FLOATE>", "<DIGIT> <DOT>");
//        lParser.add_rule("<FLOATE>", "<DIGIT> <DOTDIG>");
//        lParser.add_rule("<FLOATE>", "<DIGIT> <EXPONENT>");
//        lParser.add_rule("<FLOATE>", "<SIGN> <DOTDIG>");
//        lParser.add_rule("<FLOATE>", "<SIGN> <DIGDOT>");
        
//    for(size_t i = 0; i < lInput.size()-1; i++){
//        glch::AStringList lRules = lInput.at(i).split(" ");
//        lParser.add_variable(lRules.at(0));
//    }
//    
//    
    for(size_t i = 0; i < lInput.size()-1; i++){

        glch::AStringList lRules = trim(lInput.at(i)).split(" ");
        glch::AString lRule = "";
        if(lRules.size() == 3){
            lRule = glch::AString("%1 %2").arg(lRules.at(1)).arg(lRules.at(2));
            std::cout << glch::AString("'%1' '%2'").arg(lRules.at(1)).arg(lRules.at(2)) << std::endl;
        } else {
            lRule = lRules.at(1);
            std::cout << glch::AString("'%1'").arg(lRules.at(1)) << std::endl;
        }
        
        lParser.add_rule(lRules.at(0),lRule);
        
    }
    
    
    //lParse.print_cols();
    lParser.print_rules();
    
    lParser.map_inputs();
      
    
    lParser.build_parse_matrix("-22.33e-3.222").print();
    
    
    
    //LenList vData;
    //vData["Test1.3"] = 44;
    
    //Evaluator lEval;
    //lEval.vParser = lParse;
    
    //cout << lEval.evaluate("22",vData) << endl;
    
}

int main(){
    
    glch::AString grammar = parse_short_grammar();
    build_test_grammar(grammar);
    
    
    return 0;
    
    glch::AString lSample = glch::load_text_file("./sample");
    //glch::AString lSample = glch::load_text_file("./sample_float");
    lSample = lSample.split("\n").at(0);
    //glch::AString lFile = glch::load_text_file("./grammar_test");
    glch::AString lFile = glch::load_text_file("./grammar_fixed_v9");
    //glch::AString lFile = glch::load_text_file("./grammar_float");
    //glch::AString lFile = glch::load_text_file("./grammar_float_v2");
    glch::AStringList lInput = lFile.split("\n");
    Parser lParse;
    
    for(size_t i = 0; i < lInput.size()-1; i++){
        glch::AStringList lRules = lInput.at(i).split(" ");
        lParse.add_variable(lRules.at(0));
    }
    
    
    for(size_t i = 0; i < lInput.size()-1; i++){

        glch::AStringList lRules = lInput.at(i).split(" ");
        glch::AString lRule = "";
        if(lRules.size() == 3){
            lRule = glch::AString("%1 %2").arg(lRules.at(1)).arg(lRules.at(2));
        } else {
            lRule = lRules.at(1);
        }
        
        lParse.add_rule(lRules.at(0),lRule);
        
    }
    
    
    //lParse.print_cols();
    //lParse.print_rules();
    
    lParse.map_inputs();
    
    
    //lParse.vConnections.print_maps();
    //BinaryTree lTree = lParse.build_parse_matrix(lSample.c_str());
    //lTree.print();
    cout << "|" << lSample.c_str() << "|" << endl;
    
    //std::map<glch::AString,glch::AString> vData;
    //vData["Test1.3"] = 44;
    LenList vData;
    vData["Test1.3"] = 44;
    vData["x"] = 101;
    vData["y"] = 0;
    vData["Test[0]"] = 11;
    vData["Test[1]"] = 22;
    vData["Test[2]"] = 33;
    //cout << "Evaluating..." << endl;
    Evaluator lEval;
    lEval.vParser = lParse;
    //lEval.vData = vData;
    //cout << "Evaluating..." << endl;
    
    //cout << lEval.evaluate(lSample,vData) << endl;
    cout << lEval.evaluate("22.333e-1.234",vData) << endl;
    
    cout << lEval.evaluate("3",vData) << endl;
    
    cout << lEval.evaluate("Test1.3",vData) << endl;
    
    cout << lEval.evaluate("4+3",vData) << endl;
    cout << lEval.evaluate("4.0+3.0*2.0",vData) << endl;
    cout << lEval.evaluate("4.0+3.0^2.0",vData) << " : " << 4.0+3.0*3.0 << endl;
    cout << lEval.evaluate("4+3/2",vData) << endl;
    cout << lEval.evaluate("Test1.3+1",vData) << endl;
    cout << lEval.evaluate("Test1.3",vData) << " : " << 44 << endl;
    cout << lEval.evaluate("11.324",vData) << " : " << 11.324 << endl;
    cout << lEval.evaluate("5+x*2+5",vData) << " : " << 5+101*2+5 << endl;
    cout << lEval.evaluate("5",vData) << " : " << 5 << endl;
    cout << lEval.evaluate("x",vData) << " : " << 101 << endl;
    cout << lEval.evaluate("4*x^2/2",vData) << " : " << 4*(101*101)/2 << endl;
    cout << lEval.evaluate("4*x^(2/2)",vData) << " : " << 4*101 << endl;
    cout << lEval.evaluate("3/4",vData) << " : " << 3.0/4.0 << endl;
    cout << lEval.evaluate("Abc<-x+5",vData) << " : " << 101+5 << endl;
    cout << lEval.evaluate("Abc",vData) << " : " << 101+5 << endl;
    cout << lEval.evaluate("x",vData) << " : " << 101 << endl;
    
    cout << lEval.evaluate("Test1.3+Test1.3+Test1.3+Test1.3",vData) << " : " << 44*4 << endl;
    cout << lEval.evaluate("(Test1.3)*(Test1.3+Test1.3)^Test1.3",vData) << " : " << 44*pow(88,44) << endl;
    
    cout << lEval.evaluate("5+Test[y+0]",vData) << " : " << 11+5 << endl;
    cout << lEval.evaluate("5+Test[y+1]",vData) << " : " << 22+5 << endl;
    cout << lEval.evaluate("5+Test[x^0+0*0+0+1]",vData) << " : " << 33+5 << endl;
    cout << lEval.evaluate("(Test[0]+Test[1])*(Test[0]+Test[2])",vData) << " : " << (11+22)*(11+33) << endl;
    
    
    cout << lEval.evaluate("Test[y+0]<-66",vData) << " : " << 66 << endl;
    cout << lEval.evaluate("66?5:7",vData) << " : " << 5 << endl;
    cout << lEval.evaluate("0?5:7",vData) << " : " << 7 << endl;
    cout << lEval.evaluate("x?5:7",vData) << " : " << 5 << endl;
    cout << lEval.evaluate("(x?1:0)?5:7",vData) << " : " << 5 << endl;
    cout << lEval.evaluate("(y?1:0)?5:7",vData) << " : " << 7 << endl;
    cout << lEval.evaluate("Test1.3?5:7",vData) << " : " << 5 << endl;
    cout << lEval.evaluate("Test1.3>5?5:7",vData) << " : " << 5 << endl;
    cout << lEval.evaluate("Test1.3>5?5+x:7+x",vData) << " : " << 5+101 << endl;
    cout << lEval.evaluate("Test1.3>5?5+x:7+x",vData) << " : " << 5+101 << endl;
    
    cout << lEval.evaluate("Test[4]<-Test1.3>5?(1?5+x:3):7+x",vData) << " : " << 5+101 << endl;
    cout << lEval.evaluate("Test[4]",vData) << " : " << 5+101 << endl;
    
    
}

int main_parse(){
    
    
    Parser lParse;
    //lParse.add_rule("S","A B");
    //lParse.add_rule("A","A A");
    //lParse.add_rule("A","a");
    //lParse.add_rule("B","B B");
    //lParse.add_rule("B","b");
    
    lParse.add_rule("<EXPR>","<LPAREN> <BODY>");
    lParse.add_rule("<LPAREN>","(");
    lParse.add_rule("<BODY>","<OPR> <RPAREN>");
    lParse.add_rule("<BODY>","<VAR> <RPAREN>");
    lParse.add_rule("<RPAREN>",")");
    lParse.add_rule("<OPR>","<UNION> <VAR>");
    lParse.add_rule("<OPR>","<CONCAT> <VAR>");
    lParse.add_rule("<OPR>","<CLOSURE> <VAR>");
    lParse.add_rule("<OPR>","<CLOSURE> <EXPR>");
    
    lParse.add_rule("<VAR>","<VAR> <VAR>");
    lParse.add_rule("<VAR>","<EXPR> <EXPR>");
    lParse.add_rule("<VAR>","a");
    lParse.add_rule("<VAR>","b");
    lParse.add_rule("<VAR>","c");
    lParse.add_rule("<VAR>","#");
    lParse.add_rule("<VAR>","/");
    lParse.add_rule("<VAR>","<VAR> <EXPR>");
    lParse.add_rule("<VAR>","<EXPR> <VAR>");
    
    lParse.add_rule("<CONCAT>",".");
    lParse.add_rule("<UNION>","|");
    lParse.add_rule("<CLOSURE>","*");       
    
    lParse.print_rules();
    
    lParse.build_parse_matrix("(.(*(|abc))(*a))").print();
    
}

int main_rand_string(){
    
    srand(time(NULL));
    
    std::cout << glch::random_string(36) << std::endl;
    std::cout << glch::random_string(36) << std::endl;
    std::cout << glch::random_string(36) << std::endl;
    std::cout << glch::random_string(36) << std::endl;
    std::cout << glch::random_string(36) << std::endl;
}

int main_stats(){
    
    AString lScores = "46,47,47,53,53,54,54,54,61,61,61,61,61,66,66,66,66,67,67,69,80";
    
    std::cout << "Mean: " << glch::calc_average(&lScores.to_vector<double>().at(0),lScores.to_vector<double>().size()) << std::endl;
    //std::cout << "Mean: " << glch::ca(lScores.to_vector<double>()) << std::endl;
    std::cout << 1-glch::poz(1.25) << std::endl;
    std::cout << 1-glch::poz(1.25) << std::endl;
    //glch::LinearModel lLM(lScores.to_vector<double>());
    //glch::calc_q()
    
    return 0;
}

int main_brackets(){
    
    AString lTest = "{'abc':{'a':123,'b':234,'c':345},'bbb':{'a':123,'b':234,'c':345},'def':{}}";
                   //0123456789012345678901234567890123
                   //0000000000111111111122222222222333
    
    //lTest = "for(size_t i = 0; i < lBTrack.size(); i++){std::cout << lBTrack.at(i).varStart << \" : \" << lBTrack.at(i).varEnd << \" : \" << lBTrack.at(i).varType << \" : \" << lBTrack.at(i).varBranch << std::endl;}";
    
    std::vector<Bracket> lBrackets;
    glch::build_bracket_list(lBrackets);
    std::vector<string> lSRAL;
    std::vector<glch::AString> lSRALAString;
    
    std::vector<BracketTrack> lBTrack;
    glch::split_brackets(lTest,lBTrack);
    
    for(size_t i = 0; i < lBTrack.size(); i++){
        std::cout << lBTrack.at(i).varStart << " : " << lBTrack.at(i).varEnd << " : " << lBTrack.at(i).varType << " : " << lBTrack.at(i).varBranch << std::endl;
    }
    
    glch::string_to_sral(lTest,lSRAL);

    glch::convert_vector(lSRAL,lSRALAString);
    
    glch::print_vect(lSRALAString,"\n");
    
    std::cout << lSRALAString.at(1).dict_size() << std::endl;
    for(size_t i = 0; i < lSRALAString.at(1).dict_size(); i++){
        std::cout << lSRALAString.at(1).dict_label(i) << " : " << lSRALAString.at(1).dict_value(i) << std::endl;
    }
    
    lSRALAString.at(2).dict_set("555",0);
    lSRALAString.at(2).print();
    
    std::cout << lSRALAString.at(1).dict_label_index("bbb") << std::endl;
    std::cout << lSRALAString.at(2).dict_label_index("c") << std::endl;
    std::cout << lSRALAString.at(2).dict_label_index("cde") << std::endl;
    
    std::cout << lSRALAString.at(1).dict_label("bbb") << std::endl;


}

int main_poly(){
    
//    std::cout << on_line(PointF(35,62),PointF(38,62),PointF(34.9,62));
//    std::cout << on_line(PointF(35,62),PointF(38,62),PointF(34.95,62));
//    std::cout << on_line(PointF(35,62),PointF(38,62),PointF(35,62));
//    std::cout << on_line(PointF(35,62),PointF(38,62),PointF(38,62));
//    std::cout << on_line(PointF(35,62),PointF(38,62),PointF(38.05,62));
//    std::cout << on_line(PointF(35,62),PointF(38,62),PointF(38.1,62));
//    std::cout << on_line(PointF(35,62),PointF(38,62),PointF(39,62));
//    
//    return 0;
    
//    std::vector<Point> lPt;
//    
//    lPt.push_back(Point(5,5));
//    lPt.push_back(Point(6,6));
//    lPt.push_back(Point(7,7));
//    
//    Rect lBR = bounding_rect(lPt);
//    std::vector<Point> lPBDY = lBR.polygon();
//    
//    std::vector<PointF> lMBR = minimal_bounding_rect(lPt);
//    
//    std::cout << area(lMBR) << std::endl;
//    
//    lBR.print();
//    print_vect_fn(lPBDY);
//    std::cout << std::endl;
//    print_vect_fn(lMBR);
//    
//    return 0;
    
    glch::MatT<uchar> lMat(20,20);

    //lMat.at(Point(1,1)) = 0xFF;
    //lMat.at(Point(2,1)) = 0xFF;
    //lMat.at(Point(1,2)) = 0xFF;
    //lMat.at(Point(2,2)) = 0xFF;
    //lMat.at(Point(3,3)) = 0xFF;
    
    //lMat.printt<int>();
    
    glch::load_pgm("y-mask.pgm",lMat);
  
    ImgClusters lICluster;
    lICluster.analyze_image(lMat);
    Cluster::header().print();
    lICluster.print();
    
    std::vector<Point> lCirc = glch::circ(Point(20,20),10);
    //print_vect_fn(lCirc);
    
    
    glch::draw_filled_poly(lMat,lCirc,128.0);
    
    glch::save_pgm("./test_circ.pgm",lMat);
    
//    BoundaryList lClusters = glch::extract_clusters(lMat,8);
//    
//    for(size_t i = 0; i < lClusters.size(); i++){
//
//        compute_parameters(lClusters.at(i));
//    
//    }
    
}

int main_bl_corner(){
    
    glch::MatT<uchar> lMat(4,4);

    lMat.at(6) = 0xFF;
    lMat.at(9) = 0xFF;
    
    BoundaryList lClusters = glch::extract_clusters(lMat,8);
    //std::vector<Point> lPts = mask_to_pts(lMat);
    std::vector<Point> lTP1 = pts_to_toppts(lClusters.at(0));
    
    
    //BoundaryList lBL = compute_top_boundary(lTP1);
    
    Boundary lTBL = lTP1; //lBL.at(0);


    double lArea = glch::moment(lTBL,0,0)/20;
    double lDiameter = glch::diameter(lTBL)/10;
    double lPerimeter = glch::perimeter(lTBL)/5;      
    
    double lCirc = (4*3.14*lArea)/(lPerimeter*lPerimeter);
    double lFI = (4*lArea)/(lPerimeter*lDiameter);

    double lEdges = 0;
    double lCorners = 0;
    
    count_top_features(lTBL,lEdges,lCorners);    
    
    std::cout << lArea << " : "  << lDiameter << " : " << lPerimeter << " : " << lEdges << " : " << lCorners << " : " << lCirc << " : " << lFI << std::endl;    

//    std::cout << "Printing Boundary List: " << std::endl;
//    for(size_t i = 0; i < lBL.size(); i++){
//        
//        glch::print_vect_fn(lBL.at(i));
//        std::cout << std::endl << std::endl;
//        
//    }    
    
    
}

int main_calib_bound(){
    
    glch::MatT<uchar> lMat;
    glch::load_pgm("calib_ellipse.pgm",lMat);
    
    BoundaryList lBL = extract_clusters(lMat,4);
    
    for(size_t i = 0; i < lBL.size(); i++){
        //print_vect_fn(lBL.at(i));
        double lEdges = 0;
        double lCorners = 0;
        
        //BoundaryList lTBL = compute_small_boundary(lBL.at(i));
        BoundaryList lTBL = compute_top_boundary(lBL.at(i));
        PolyT<int> lPoly;
        
        
        
        //count_top_features(lTBL.at(0),lEdges,lCorners);
        double lArea1 = lBL.at(i).size();
        double lArea2 = glch::area(lTBL.at(0));
        
        double lDiameter = 0;
        double lPerimeter = lTBL.at(0).size();
        

        try{
            lDiameter = (glch::diameter(lTBL.at(0)));
            //lPerimeter = glch::perimeter(lTBL.at(0));            
        } catch (std::out_of_range lError){
            
        }
        
        double lCirc = (4*3.14*lArea1)/(lPerimeter*lPerimeter);
        double lFI = (4*lArea1)/(lPerimeter*lDiameter);
        
        std::cout << lArea1 << " : "  << lDiameter << " : " << lPerimeter << " : " << lCirc << " : " << lFI << std::endl;
        
        //std::cout << lArea1 << " : " << lArea2 << " : "  << lDiameter << " : " << lPerimeter << " : " << lCirc << " : " << lFI << " : "  << lEdges << " : " << lCorners << std::endl;
        
       // std::cout << lBL.at(i).size() << " : " << lTBL.at(0).size() << " : " << lEdges << " : " << lCorners << " : " << lDiameter << " : " << lCorners/lEdges << " : " << lCirc << " : " << lFI << std::endl;
    }
    
    
    
}

int main_bound1(){
    
    glch::Point lPoint = glch::Point(2,2);
    glch::MatT<uchar> lMat(5,5);
    glch::MatT<uchar> lTempMat;
    
    lMat.at(6) = 0xFF;
    lMat.at(7) = 0xFF;
    lMat.at(8) = 0xFF;
    lMat.at(9) = 0xFF;
    lMat.at(11) = 0xFF;
    lMat.at(13) = 0xFF;
    lMat.at(14) = 0xFF;
    lMat.at(16) = 0xFF;
    lMat.at(17) = 0xFF;
    lMat.at(18) = 0xFF;    
    
    //lMat.at(4) = 0xFF;
    //lMat.at(5) = 0xFF;
    //lMat.at(7) = 0xFF;
    //lMat.at(8) = 0xFF;
    
    //lMat.at(9) = 0xFF;
    
    //glch::resize_mat(lMat,lTempMat,lMat.cols*3,lMat.rows*3);
    //lMat = lTempMat;
    lTempMat = lMat;
    lTempMat.zero();
    
    lMat.printt<int>();

    
    //std::vector<Point> lBoundary = get_boundary_points(lMat);
    
    //BoundaryList lBL = trace_boundary(lBoundary);
    double lEdges = 0;
    double lCorners = 0;
    
    BoundaryList lBL = compute_top_boundary(lMat);
    count_top_features(lBL.at(0),lEdges,lCorners);
    //lBL = remove_corners(lBL);
    
    std::cout << "EC: " << lEdges << " : " << lCorners << std::endl;
    //lBL = compute_small_boundary(lMat);
    
    Boundary lLgBoundary = lBL.at(0);//small_to_large_boundary(lBL.at(0));
    std:: cout << std::endl;
    glch::print_vect_fn(lLgBoundary);
    
    PolyT<int> lPoly(lBL.at(0));
    PointF lCentroid = glch::centroid(lBL.at(0));
    std::cout << std::endl;
    lCentroid.print();
    std::cout << "M00: " << glch::moment(lBL.at(0),0,0) << std::endl;
    std::cout << "M01: " << glch::moment(lBL.at(0),0,1) << std::endl;
    std::cout << "M10: " << glch::moment(lBL.at(0),1,0) << std::endl;
    std::cout << "C00: " << glch::normalized_central_moment(lBL.at(0),lCentroid,0,0) << std::endl;
    std::cout << "C01: " << glch::normalized_central_moment(lBL.at(0),lCentroid,0,1) << std::endl;
    std::cout << "C10: " << glch::normalized_central_moment(lBL.at(0),lCentroid,1,0) << std::endl;
    
    
    
    std::cout << "P00: " << poly_moment(lBL.at(0),0,0) << std::endl;
    std::cout << "P01: " << poly_moment(lBL.at(0),0,1) << std::endl;
    std::cout << "P10: " << poly_moment(lBL.at(0),1,0) << std::endl;
    
    std::cout << "Area: " << glch::area(lBL.at(0)) << std::endl;
    std::cout << "Perimeter: " << glch::perimeter(lBL.at(0)) << std::endl;
    std::cout << "Diameter: " << glch::diameter(lBL.at(0)) << std::endl;
    
//    for(std::vector<Point>::iterator it = lBoundary.begin(); it != lBoundary.end(); it++){
//        lTempMat.at((*it)) = 0xFF;
//        
//    }
   
    std::cout << "Printing Boundary List: " << std::endl;
    for(size_t i = 0; i < lBL.size(); i++){
        glch::print_vect_fn(lBL.at(i));
        std::cout << std::endl << std::endl;
        //for(std::vector<Point>::iterator it = lBL.at(i).begin(); it != lBL.at(i).end(); it++){
        //    lTempMat.at((*it)) = 0xFF;
        //    lTempMat.printt<int>();
        //}
        
    }
    std::cout << "\nEnd Printing Boundary List: " << std::endl;
    
    
//    for(size_t r = 0; r < lMat.rows; r++){
//        for(size_t c = 0; c < lMat.cols; c++, i++){
//            //std::cout << i << " : " << is_boundary_point(Point(c,r), lMat) << std::endl;
//            if(is_boundary_point(Point(c,r), lMat)){
//                lTempMat.at(Point(c,r)) = 0xFF;
//            }
//        }
//    }
    
    
    //lTempMat.printt<int>();
    
    //glch::print_vect_fn(lBoundary);
    
}

int main_evo(){

    glch::seed_rand();
    
    glch::GeneBuilder lP1;
    
    lP1.insert_gene("xval",1,1);
    lP1.insert_gene("yval",1,1);
    
    lP1.mutate_all();
    lP1.print();
    std::vector<double> lXVals = glch::randt_vector<double>(0,1000,2);
    
    std::cout << "Value: " << std::endl;
    glch::print_vect(lXVals);
    std::cout << std::endl;
    
    
    std::cout << lP1.compute(lXVals );
    
    
}

int main_imgcrop(int argc, char* argv[]){
    
    MatT<unsigned short> lOrig;
    MatT<unsigned short> lXSM;
    glch::load_xsm_us("./1015-2007.xsm",lXSM);
    glch::load_pgm("/home/brian/git-work/wtmmanalysis/0000595-20041026_092011-L_MLO.pgm",lOrig);
    
    MatT<unsigned short> lSave = lOrig.submat(glch::Rect(1015,2007,360,360));
    
    glch::save_pgm("./1015-2007-test.pgm",lSave);
    glch::save_pgm("./1015-2007.pgm",lXSM);
    
//    MatT<unsigned char> lOrig;
//    glch::load_pgm("./CropTest.pgm",lOrig);
//    MatT<unsigned char> lSave = lOrig.submat(glch::Rect(3,3,5,5));
//    glch::save_pgm("./CropTest-res.pgm",lSave);
//    
    
//    MatT<unsigned short> lImg;
//    MatT<unsigned short> lXSM;
//    
//    glch::load_pgm("./test-cutting-region.pgm",lImg);
//    glch::save_xsm("./test-cutting-region.xsm",lImg);
//    glch::load_xsm("./test-cutting-region.xsm",lXSM);
//    glch::save_pgm("./test-cutting-region-final.pgm",lXSM);
    
    //MatT<unsigned short> lSave = lImg.submat(glch::Rect(1078,1246,359,359));
    
    //glch::save_pgm("./test-cutting-region.pgm",lSave);
    
    
}

int main_args(int argc, char* argv[]){
    
    int lArgc = 2;
    char* lArgv[] = {"libglitch", "-wtmm"};
    
    glch::ArgParser lArgs;
    lArgs.insert("-help", 0, "-help", "Shows this help menu.");
    lArgs.insert("-wtmm", 2, "-wtmm /path/to/image.pgm /path/to/output", "Runs the wtmm transformation and chaining on a pgm image.", glch::AString("-image,-mask").split(",") );
    lArgs.insert("-image", 0, "-input /path/to/image.pgm", "Sets the input image");
    lArgs.insert("-mask", 0, "-mask /path/to/mask.pgm", "Sets the mask image");    
    
    lArgs.help();
    
    lArgs.parse(argc, argv);
    
    
}

int main_color(){
    
    MatImageC lImg = gen_mat_image<unsigned char>(16,16,3);
    
    glch::set_mat_image(lImg,0,0,ScalarF(1,5,9));
    glch::set_mat_image(lImg,1,1,ScalarF(2,6,10));
    glch::set_mat_image(lImg,2,2,ScalarF(3,7,11));
    glch::set_mat_image(lImg,3,3,ScalarF(4,8,12));

    glch::set_mat_image(lImg,0,0,ScalarF(255,0,0));
    glch::set_mat_image(lImg,1,1,ScalarF(0,255,0));
    glch::set_mat_image(lImg,2,2,ScalarF(0,0,255));
    glch::set_mat_image(lImg,3,3,ScalarF(255,255,255));
    
    glch::save_ppm("test_matimgc.ppm",lImg);
    
    for(int i = 0; i < 3; i++){
        std::cout << i << std::endl;
        lImg.at(i).print();
    }
    
}

int main_perlin(){
    
    glch::seed_rand();
    std::vector<MatT<unsigned char> > lBrown(7);
    MatT<unsigned char> lOut;
    
    
    for(int i = 4; i < 11; i++){

        int lWH = pow(2,i);
        int lSteps = lWH*pow(log10(lWH),10)/6;
        std::cout << lWH << " : " << log10(lWH) << " : " << pow(log10(lWH),10) << " : " << lSteps << std::endl;
        brownian2(lWH,lWH,-1,1,-1,1,10,0,255,lSteps,lBrown.at(i-4),false);
        //brownian2(500,500,randf(-1,0),randf(0,1),randf(-1,0),randf(0,1),1,0,255,1000000,lBrown.at(0),false);
        //brownian2(500,500,randf(-1,0),randf(0,1),randf(-1,0),randf(0,1),1,0,255,1000000,lBrown.at(1),false);
        //brownian2(500,500,randf(-1,0),randf(0,1),randf(-1,0),randf(0,1),1,0,255,1000000,lBrown.at(2),false); 
        resize_mat(lBrown.at(i-4),1024,1024);
        glch::save_pgm(AString("test_avg_%1.pgm").arg(i),lBrown.at(i-4));
    }
    
    glch::average_mat(lBrown,lOut);
    glch::save_pgm("test_avg.pgm",lOut);
}

int main_brown(){
    glch::seed_rand();
    std::vector<MatT<unsigned char> > lBrown(3);

    for(int i = 0; i < 5; i++){
        brownian2(500,500,-1,1,-1,1,5,0,255,1000000,lBrown.at(0),false);
        brownian2(500,500,-1,1,-1,1,5,0,255,1000000,lBrown.at(1),false);
        brownian2(500,500,-1,1,-1,1,5,0,255,1000000,lBrown.at(2),false);
        
        //brownian2(500,500,randf(-1,0),randf(0,1),randf(-1,0),randf(0,1),1,0,255,1000000,lBrown.at(0),false);
        //brownian2(500,500,randf(-1,0),randf(0,1),randf(-1,0),randf(0,1),1,0,255,1000000,lBrown.at(1),false);
        //brownian2(500,500,randf(-1,0),randf(0,1),randf(-1,0),randf(0,1),1,0,255,1000000,lBrown.at(2),false);        
    }
    
    std::cout << "Applying Gaussian" << std::endl;
    
    MatT<double> lGauss;
    MatT<double> lDGauss;
    MatT<double> lKer;
    str_to_mat("3,3|-1,-1,-1,2,2,2,-1,-1,-1",lKer);
    gen_gaussian_scaled(50,50,lGauss,255);
    //normalize_matrix(lGauss, lDGauss);
    //lGauss.print();

    //lBrown.at(0) = glch::convolve(lBrown.at(0),lDGauss);
    //lBrown.at(1) = glch::convolve(lBrown.at(1),lDGauss);
    //lBrown.at(2) = glch::convolve(lBrown.at(2),lDGauss);
    
//    lBrown.at(0) = glch::convolve(lBrown.at(0),lKer);
//    lBrown.at(1) = glch::convolve(lBrown.at(1),lKer);
//    lBrown.at(2) = glch::convolve(lBrown.at(2),lKer);
    
    glch::save_ppm("test.ppm",lBrown);
    glch::save_pgm("test_gs.ppm",lBrown.at(0));
    //lBrown.print(" ");
    //lGauss.print();
    return 0;
}

/*
 * 
 */
int main__() {

    RectListT<double> lRectList;
    std::vector<size_t> lSimilarID;
    std::vector<RectT<double> > lSimilar;
    
    lRectList.vData.push_back( Rect(5,5,10,10) );
    lRectList.vData.push_back( Rect(5,6,10,10) );
    lRectList.vData.push_back( Rect(5,7,10,10) );
    lRectList.vData.push_back( Rect(5,8,10,10) );
    lRectList.vData.push_back( Rect(4,9,10,10) );
    lRectList.vData.push_back( Rect(5,10,10,10) );
    lRectList.vData.push_back( Rect(5,11,10,10) );
    lRectList.vData.push_back( Rect(5,12,10,10) );
    lRectList.vData.push_back( Rect(5,13,10,10) );
    lRectList.vData.push_back( Rect(5,14,10,10) );
    lRectList.vData.push_back( Rect(5,15,10,10) );
    lRectList.vData.push_back( Rect(25,25,13,13) );
    lRectList.vData.push_back( Rect(25,25,13,13) );
    lRectList.vData.push_back( Rect(25,25,13,13) );
    lRectList.vData.push_back( Rect(25,25,13,13) );
    
    //std::cout << lRectList.vData.size() << std::endl;
    //lSimilar = find_similar_rects(lRectList.vData, Rect(5,5,10,10), .8);
    
    //lRectList.filter_duplicate_rects(.8);
    //std::cout << lRectList.vData.size() << std::endl;
    
    //for(size_t i = 0; i < lRectList.vData.size(); i++){
    //    lRectList.vData.at(i).print();
    //}
    
    //for(size_t i = 0; i < lSimilar.size(); i++){
    //    lSimilar.at(i).print();
    //}
    
    //average_rects(lSimilar).print();
    
    //lSimilarID.push_back(11);
    
    //find_all_similar_rects_index(lRectList.vData,lSimilarID,0,.8);
    //std::cout << "similar index: " << std::endl;
    //for(size_t i = 0; i < lSimilarID.size(); i++){
    //    std::cout << lSimilarID.at(i) << ", ";
    //}    
    //std::cout << "end" << std::endl;
    
    IndexArray lList = find_list_all_similar_rects(lRectList.vData,.8);
    
    for(size_t i = 0; i < lList.size(); i++){
        for(size_t j = 0; j < lList.at(i).size(); j++){
            std::cout << lList.at(i).at(j) << ", ";
        }
        std::cout << std::endl;
    }
    
    lRectList.filter_similar_average(.8);
    lRectList.print();
    
    return 0;
}

#endif