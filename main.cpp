/* 
 * File:   main.cpp
 * Author: brian
 *
 * Created on January 4, 2016, 6:59 PM
 */

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

int main(){

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

int main______(){
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

    glch::compute_fft_2d(lBrown,1);
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
    
    glch::compute_fft_2d(lBrown,-1);
    
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

int main_____(){
    glch::seed_rand();
    std::vector<MatT<unsigned short> > lBrown(3);
    
    brownian(1000,0,0,65535,100000,lBrown.at(0));
    brownian(1000,0,0,65535,100000,lBrown.at(1));
    brownian(1000,0,0,65535,100000,lBrown.at(2));
    
    glch::save_ppm("test.ppm",lBrown);
    //lBrown.print(" ");
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

