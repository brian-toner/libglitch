/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   validator.cpp
 * Author: brian
 *
 * Created on July 16, 2018, 7:54 AM
 */

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <Parser.h>

#include "AStringFunctions.h"
#include "Boundary.h"
#include "NDArray.h"
#include "ShapeProperties.h"
#include "GeneBuilder.h"
#include "GeneList.h"
#include "../Cluster.h"

using namespace std;
/*
 * Simple C++ Test Suite
 */

double xsq(double x){
    return x*x;
}

double fprime(double x, double (*f)(double), double dx = 0.001){
    double ret = (f(x+dx)-f(x))/dx;
    return ret;
}

double mult2(double aVal){
    return aVal*2;
}

double my_pow(double x, int exp){
    double ret = x;
    for(int i = 1; i < exp; i++){
        ret *= x;
    }

    return ret;
}

double my_fac(int val){
    double ret = 1;

    for(int i = 1; i < val+1; i++){
        ret *= i;
    }

    return ret;
}

double my_sin(double x){
    //return x - my_pow(x,3)/my_fac(3) + my_pow(x,5)/my_fac(5);
    //return x - my_pow(x,3)/my_fac(3) + my_pow(x,5)/my_fac(5) - my_pow(x,7)/my_fac(7) + my_pow(x,9)/my_fac(9);

    double ret = 0;
    double j = 2;
    for(int i = 1; i < 20; i += 2, j++){
        ret += my_pow(-1,j)*my_pow(x,i)/my_fac(i);
        //cout << "i: " <<  i << " j:" << j << " x^i :" << my_pow(x,i) << " x! : " << my_fac(i) << " -1^j : " << my_pow(-1,j) << endl;
    }

    return ret;
}

class Validate{
public:
    
    static long msec_ellapsed(clock_t aBeginTime){
        double lEndTime = double( clock() - aBeginTime )/CLOCKS_PER_SEC*1000;
        
        return (long)lEndTime;
        
    }
    
    static long usec_ellapsed(clock_t aBeginTime){
        double lEndTime = double( clock() - aBeginTime )/CLOCKS_PER_SEC*1000000;
        
        return (long)lEndTime;
        
    }
    
    static long sec_ellapsed(clock_t aBeginTime){
        double lEndTime = double( clock() - aBeginTime )/CLOCKS_PER_SEC;
        
        return (long)lEndTime;
        
    }
    
    static bool compare(double actual, double expected){
        //cout << "Comparing (a/e): " << actual << " " << expected << "\n";
        if(expected==actual){
            
            //cout << "Pass\n";
            return true;
        }

        //cout << "Error, values don't match\n";
        return false;

    }

    template <class T>
    static bool compare_t(T actual, T expected){
        //cout << "Comparing (a/e): " << actual << " " << expected << "\n";
        if(expected==actual){
            
            //cout << "Pass\n";
            return true;
        }

        //cout << "Error, values don't match\n";
        return false;

    }
    
    static bool compare(string actual, string expected){
        //cout << "Comparing (a/e): " << actual << " " << expected << "\n";
        if(expected==actual){
            
            //cout << "Pass\n";
            return true;
        }

        //cout << "Error, values don't match\n";
        return false;

    }
    
    static bool fuzzy_compare(double actual, double expected, double delta = .01){
        //cout << "Fuzzy Comparing (a/e): " << actual << " " << expected << "+/-" << delta << "\n";
        //cout << (actual-delta <= expected) << " : " << (actual+delta >=expected) << endl;
        if(actual-delta <= expected && actual+delta >=expected){
            //cout << "Pass\n";
            return true;
        }

        //cout << "Error, values don't match\n";
        return false;
    }

    template <class T>
    static bool compare_tmr_t(clock_t& aTimer, string name, string suit, T actual, T expected){
        
        std::cout << "%TEST_STARTED% " << name << " (" << suit << ")" << std::endl;
        bool ret = compare_t<T>(actual,expected);
        //double lEndTime = (double( clock() - aTimer )/CLOCKS_PER_SEC );
        long lEndTime = usec_ellapsed(aTimer);
        passfail(ret,name,suit,actual,expected,lEndTime);
        
        std::cout << "%TEST_FINISHED% time=" << lEndTime << " " << name << " (" << suit << ")" <<  std::endl << std::endl;
        aTimer = clock();
        return ret;
    }
    
    static bool compare_tmr(clock_t& aTimer, string name, string suit, double actual, double expected){
        
        std::cout << "%TEST_STARTED% " << name << " (" << suit << ")" << std::endl;
        bool ret = compare(actual,expected);
        //double lEndTime = (double( clock() - aTimer )/CLOCKS_PER_SEC );
        long lEndTime = usec_ellapsed(aTimer);
        passfail(ret,name,suit,actual,expected,lEndTime);
        
        std::cout << "%TEST_FINISHED% time=" << lEndTime << " " << name << " (" << suit << ")" <<  std::endl << std::endl;
        aTimer = clock();
        return ret;
    }
    
    static bool compare_tmr(clock_t& aTimer, string name, string suit, string actual, string expected){
        
        std::cout << "%TEST_STARTED% " << name << " (" << suit << ")" << std::endl;
        bool ret = compare(actual,expected);
        //double lEndTime = (double( clock() - aTimer )/CLOCKS_PER_SEC );
        long lEndTime = usec_ellapsed(aTimer);
        passfail(ret,name,suit,actual,expected,lEndTime);
        
        std::cout << "%TEST_FINISHED% time=" << lEndTime << " " << name << " (" << suit << ")" <<  std::endl << std::endl;
        aTimer = clock();
        return ret;
    }
    
    static bool compare_neq_tmr(clock_t& aTimer, string name, string suit, string actual, string expected){
        
        std::cout << "%TEST_STARTED% " << name << " (" << suit << ")" << std::endl;
        bool ret = !compare(actual,expected);
        //double lEndTime = (double( clock() - aTimer )/CLOCKS_PER_SEC );
        long lEndTime = usec_ellapsed(aTimer);
        passfail(ret,name,suit,actual,expected,lEndTime);
        
        std::cout << "%TEST_FINISHED% time=" << lEndTime << " " << name << " (" << suit << ")" <<  std::endl << std::endl;
        aTimer = clock();
        return ret;
    }
    
    static bool fuzzy_compare_tmr(clock_t& aTimer, string name, string suit, double actual, double expected, double delta = .01){
        
        std::cout << "%TEST_STARTED% " << name << " (" << suit << ")" << std::endl;
        bool ret = fuzzy_compare(actual,expected,delta);
        
        //double lEndTime = (double( clock() - aTimer )/CLOCKS_PER_SEC );
        long lEndTime = usec_ellapsed(aTimer);
        passfail(ret,name,suit,actual,expected,lEndTime);
        std::cout << "%TEST_FINISHED% time=" << lEndTime << " " << name << " (" << suit << ")" <<  std::endl << std::endl;
        aTimer = clock();
        return ret;
    }
    
    template<class T>
    static void passfail(bool pf, string name, string suit, T actual, T expected, long aTime){
        if(!pf){
            std::cout << "%TEST_FAILED% time=" << aTime << " testname=" << name  << " (" << suit << ") " << "message=Error: values don't match. ";
//            std::cout << actual << endl;
//            std::cout << expected << endl;
        } else {
            std::cout << "%TEST_PASSED% time=" << aTime << " testname=" << name  << " (" << suit << ")\n";
//            std::cout << actual << endl;
//            std::cout << expected << endl;
        }
        std::cout << "actual="<< actual << " | expected="<< expected << std::endl;
    }
    
//    static void my_fac_test(){
//        cout << "Testing my_fac:" << endl;
//        bool pass = true;
//
//        pass &= compare("my_fac", "validator", my_fac(1), 1);
//        pass &= compare("my_fac", "validator", my_fac(2), 2);
//        pass &= compare("my_fac", "validator", my_fac(3), 6);
//        pass &= compare("my_fac", "validator", my_fac(4), 24);
//        pass &= compare("my_fac", "validator", my_fac(5), 120);
//        pass &= compare("my_fac", "validator", my_fac(6), 720);
//
//        if(pass){
//            cout << "Pass: my_fac\n\n";
//        } else {
//            cout << "Fail: my_fac\n\n";
//        }
//    }
//
//    static void my_pow_test(){
//        cout << "Testing my_pow:" << endl;
//        bool pass = true;
//
//        std::cout << "%SUITE_STARTING% validator" << std::endl;
//        std::cout << "%SUITE_STARTED%" << std::endl;
//        
//        pass &= compare("my_pow", "validator", my_pow(-1,0), 1);
//        pass &= compare("my_pow", "validator", my_pow(-1,2), 1);
//        pass &= compare("my_pow", "validator", my_pow(1,1), 1);
//        pass &= compare("my_pow", "validator", my_pow(2,2), 4);
//        pass &= compare("my_pow", "validator", my_pow(3,3), 27);
//        pass &= compare("my_pow", "validator", my_pow(4,4), 256);
//        pass &= compare("my_pow", "validator", my_pow(5,5), 3125);
//        pass &= compare("my_pow", "validator", my_pow(6,6), 46656);
//
//        if(pass){
//            cout << "Pass: my_pow\n\n";
//        } else {
//            cout << "Fail: my_pow\n\n";
//        }
//        
//        std::cout << "%SUITE_FINISHED% time=" << time(NULL) << std::endl;
//    }
//
//    static void mult2_test(){
//        cout << "Testing mult2:" << endl;
//        bool pass = true;
//
//        pass &= compare("mult2", "validator", mult2(2), 4);
//        pass &= compare("mult2", "validator", mult2(4), 8);
//        pass &= compare("mult2", "validator", mult2(9), 18);
//        pass &= compare("mult2", "validator", mult2(50), 100);
//        pass &= compare("mult2", "validator", mult2(51), 102);
//
//        if(pass){
//            cout << "Pass: mult2\n\n";
//        } else {
//            cout << "Fail: mult2\n\n";
//        }
//
//    }
//
//    static void sin_test(){
//        cout << "Testing my_sin:" << endl;
//        bool pass = true;
//
//        std::cout << "%SUITE_STARTING% fprime" << std::endl;
//        std::cout << "%SUITE_STARTED%" << std::endl;
//        
//        pass &= fuzzy_compare("my_sin", "validator", my_sin(0.0),      0.0);
//        pass &= fuzzy_compare("my_sin", "validator", my_sin(.25),      0.24740395925452294);
//        pass &= fuzzy_compare("my_sin", "validator", my_sin(.3),       0.29552020666133955);
//        pass &= fuzzy_compare("my_sin", "validator", my_sin(.5),       0.4794255386042);
//        pass &= fuzzy_compare("my_sin", "validator", my_sin(3),        0.1411200080598672);
//        pass &= fuzzy_compare("my_sin", "validator", my_sin(3.14/2.0), 0.9999996829318346);
//        pass &= fuzzy_compare("my_sin", "validator", my_sin(3.14/3),   0.8657598394923444);
//        pass &= fuzzy_compare("my_sin", "validator", my_sin(3.14/4.0), 0.706825181105366);
//        pass &= fuzzy_compare("my_sin", "validator", my_sin(3.14),     0.0015926529164868282);
//
//        if(pass){
//            cout << "Pass: my_sin\n\n";
//        } else {
//            cout << "Fail: my_sin\n\n";
//        }
//        
//        std::cout << "%SUITE_FINISHED% time=" << time(NULL) << std::endl;
//    }
//
//    static void fprime_test(){
//        cout << "Testing xsq:" << endl;
//        
//        std::cout << "%SUITE_STARTING% fprime" << std::endl;
//        std::cout << "%SUITE_STARTED%" << std::endl;
//    
//        bool pass = true;
//
//        for(double i = 0; i < 50; i = i + .1){
//            pass &= fuzzy_compare("xsq", "fprime", fprime(i,xsq), 2*i);
//        }
//
//        if(pass){
//            cout << "Pass: xsq\n\n";
//        } else {
//            cout << "Fail: xsq\n\n";
//        }
//        
//        std::cout << "%SUITE_FINISHED% time=" << time(NULL) << std::endl;
//    }

    static bool test_new_parse(){
        
        std::string lSuiteName = "glch AliasList";
        std::cout << "%SUITE_STARTING% " << lSuiteName << std::endl;
        std::cout << "%SUITE_STARTED%" << std::endl;
        
         clock_t lBeginTime = clock();
        
        glch::AliasList lList;
        glch::AString lEquation = "test1 + test2 + 55.323";
        glch::AString lFixed = lList.fix_equation(lEquation);

        lList.set_data_value("test1","3.33");
        lList.set_data_value("test2","7.77");
        lList.set_data_value("test[1]","3.14");
        lList.set_data_value("t","1");
        
        glch::Evaluator lEval;
        lEval.load_file("./grammar_fixed_v9");

        compare_tmr(lBeginTime,"Numb Alias",lSuiteName,lEval.evaluate(lFixed,lList),3.33+7.77+55.323);
        
        compare_tmr(lBeginTime,"Numb Alias",lSuiteName,lEval.evaluate("test1<-test1*test2",lList.vData),25.8741);
        compare_tmr(lBeginTime,"Numb Alias",lSuiteName,lEval.evaluate("test1",lList.vData),25.8741);
        compare_tmr(lBeginTime,"Numb Alias",lSuiteName,lEval.evaluate("test[1]",lList.vData),3.14);
        compare_tmr(lBeginTime,"Numb Alias",lSuiteName,lEval.evaluate("test[1+t]<-test[1]+test1",lList.vData),3.14+25.8741);
        compare_tmr(lBeginTime,"Numb Alias",lSuiteName,lEval.evaluate("test[2]",lList.vData),3.14+25.8741);
        
        //glch::Evaluator lFloatEval;
        //lFloatEval.load_file("./grammar_float");
        //lFloatEval.evaluate("553.1223e-147",lList.vData);
        //glch::is_float("3.14159");
        
        long lEndTime = usec_ellapsed(lBeginTime);
        std::cout << "%SUITE_FINISHED% time=" << std::fixed << lEndTime << std::endl;
        
    }
    
    static bool test_equation_fix(){
        
        std::string lSuiteName = "glch AliasList";
        std::cout << "%SUITE_STARTING% " << lSuiteName << std::endl;
        std::cout << "%SUITE_STARTED%" << std::endl;
        
         clock_t lBeginTime = clock();
        
        glch::AliasList lList;
        glch::AString lEquation = "test1+test2*test1/test3^testxyz+55.323";
        glch::AString lFixed = lList.fix_equation(lEquation);
        

        lList.set_data_value("test1","3.33");
        
        
        lList.set_alias_value("n","5.0");
        lList.set_alias_value("W","7.0");
        lList["l"] = 22.3;
        lList["r"] = 2.22;
        //lList.set_alias_value("test3","8.0");
        //lList.set_alias_value("testxyz","9.0");
        
        lList.set_alias_value("55.323","1234");
        
        glch::AString lBackSub = lList.back_subsitute_equation(lFixed);
        
        //lList.print();
        
        glch::AString lBackSubVal = lList.back_subsitute_values(lFixed);
        
        
        compare_neq_tmr(lBeginTime,"Check Results 1",lSuiteName,lEquation,lFixed);
        compare_tmr(lBeginTime,"Check Results 2",lSuiteName,lEquation,lBackSub);
        compare_neq_tmr(lBeginTime,"Check Results 3",lSuiteName,lEquation,lBackSubVal);
        
        
        //compare_tmr(lBeginTime,"Values 1",lSuiteName,lList["n"],"5.0");
        //compare_tmr(lBeginTime,"Values 2",lSuiteName,lList["W"],"7.0");
        
        //compare_tmr(lBeginTime,"Values",lSuiteName,lList["55.323"],"55.323");
        
        compare_tmr(lBeginTime,"Numb Alias 1",lSuiteName,lList.alias_size(),5);
        
        lList.erase_numerics();
        compare_tmr(lBeginTime,"Numb Alias 2",lSuiteName,lList.alias_size(),4);
        
        
        
        //lFixed = lList.fix_equation(lEquation);
        //lBackSub = lList.back_subsitute_equation(lFixed);
        //compare_neq_tmr(lBeginTime,"Check Results",lSuiteName,lEquation,lFixed);
        //compare_tmr(lBeginTime,"Check Results",lSuiteName,lEquation,lBackSub);
        
        
        
        
        
        //glch::Evaluator lEval;
        //lEval.load_file("./grammar_fixed_v9");
        //std::cout << lEval.evaluate(lFixed,lList) << endl;
        
        
        
        long lEndTime = usec_ellapsed(lBeginTime);
        std::cout << "%SUITE_FINISHED% time=" << std::fixed << lEndTime << std::endl;
        
    }
    
    static void test_randstring(){
        
        std::string lSuiteName = "glch random_string";
        std::cout << "%SUITE_STARTING% " << lSuiteName << std::endl;
        std::cout << "%SUITE_STARTED%" << std::endl;
        
        
        std::vector<string> lRandStrings;
        
        for(int i = 0; i < 100000; i++){
            lRandStrings.push_back(glch::random_string(10));
        }
        
        std::sort(lRandStrings.begin(),lRandStrings.end());
        
//        for(int i = 0; i < 10000; i++){
//            cout << lRandStrings.at(i) << endl;
//        }
        
        clock_t lBeginTime = clock();
        compare_tmr(lBeginTime,"random_string 1",lSuiteName,lRandStrings.front().substr(0,1),"A");
        compare_tmr(lBeginTime,"random_string 2",lSuiteName,lRandStrings.back().substr(0,1),"z");
        compare_tmr(lBeginTime,"random_string 3",lSuiteName,lRandStrings.front().substr(1,1),"0");
        compare_tmr(lBeginTime,"random_string 4",lSuiteName,lRandStrings.back().substr(1,1),"z");
        
        //for(int i = 0; i < 100; i++){
        //    compare_tmr(lBeginTime,"random_string",glch::random_string(10),
        //}
        

        
        //double lEndTime = (double( clock() - aTimer )/CLOCKS_PER_SEC );
        long lEndTime = usec_ellapsed(lBeginTime);
        std::cout << "%SUITE_FINISHED% time=" << std::fixed << lEndTime << std::endl;
        
    }
    
    static void test_sharedpointer(){
        
        std::string lSuiteName = "glch SharedPointer";
        std::cout << "%SUITE_STARTING% " << lSuiteName << std::endl;
        std::cout << "%SUITE_STARTED%" << std::endl;
        clock_t lBeginTime = clock();
        
        glch::SharedPointer<int> lPtr1;
        glch::SharedPointer<int> lPtr2;
        glch::SharedPointer<int> lPtr3(new int);
        
        compare_tmr(lBeginTime,"SharedPointer_1",lSuiteName,lPtr1.count(),0);
        lPtr1 = glch::SharedPointer<int>(new int(55));
        compare_tmr(lBeginTime,"SharedPointer_2",lSuiteName,lPtr1.count(),1);
        compare_tmr(lBeginTime,"SharedPointer_2",lSuiteName,*lPtr1,55);
        lPtr2 = lPtr1;
        compare_tmr(lBeginTime,"SharedPointer_3",lSuiteName,lPtr1.count(),2);
        lPtr2 = lPtr3;
        compare_tmr(lBeginTime,"SharedPointer_4",lSuiteName,lPtr1.count(),1);
        compare_tmr(lBeginTime,"SharedPointer_5",lSuiteName,lPtr3.count(),2);
        glch::SharedPointer<int> lPtr4 = lPtr3;
        compare_tmr(lBeginTime,"SharedPointer_6",lSuiteName,lPtr4.count(),3);

        lPtr4 = lPtr1;
        lPtr1.clear();
        compare_tmr(lBeginTime,"SharedPointer_7",lSuiteName,lPtr1.count(),0);
        compare_tmr(lBeginTime,"SharedPointer_8",lSuiteName,lPtr3.count(),2);
        compare_tmr(lBeginTime,"SharedPointer_9",lSuiteName,lPtr4.count(),1);
        compare_tmr(lBeginTime,"SharedPointer_9",lSuiteName,*lPtr4,55);
        
        //double lEndTime = (double( clock() - aTimer )/CLOCKS_PER_SEC );
        long lEndTime = usec_ellapsed(lBeginTime);
        std::cout << "%SUITE_FINISHED% time=" << std::fixed << lEndTime << std::endl;
    }
    
    static void test_random_int(){
        std::string lSuiteName = "glch random.h";
        std::cout << "%SUITE_STARTING% " << lSuiteName << std::endl;
        std::cout << "%SUITE_STARTED%" << std::endl;
        clock_t lBeginTime = clock();
        
        for(int k = 0; k < 25; k++){
            vector<int> lNumbs(2);
            lNumbs.at(0) = glch::randint(0,100);
            lNumbs.at(1) = glch::randint(0,100);
            
            std::sort(lNumbs.begin(), lNumbs.end());
            
            int lMin = lNumbs.front();
            int lMax = lNumbs.back();
            int lRange = lMax-lMin;
            int lCount = 100000;
            int lCountPerBin = lCount/lRange;
            int lVariance = lCountPerBin*.65;

            vector<int> lInts(lCount);
            std::map<int,int> lBins;
            for(int i = 0; i < lCount; i++){
                lInts.at(i) = glch::randint(lMin,lMax);
                lBins[lInts.at(i)]++;
            }

            std::sort(lInts.begin(),lInts.end());

            compare_tmr(lBeginTime,"MinRandInt",lSuiteName,lInts.front(),lMin);
            compare_tmr(lBeginTime,"MaxRandInt",lSuiteName,lInts.back(),lMax);

            for(int i = lMin; i < lMax+1; i++){
                fuzzy_compare_tmr(lBeginTime,glch::AString("Bin %1").arg(i), lSuiteName, lBins.at(i), lCountPerBin, lVariance);
            }
        }
        
        
        //double lEndTime = (double( clock() - aTimer )/CLOCKS_PER_SEC );
        long lEndTime = usec_ellapsed(lBeginTime);
        std::cout << "%SUITE_FINISHED% time=" << std::fixed << lEndTime << std::endl;
    }
    
    static void test_astring_fns(){
        std::string lSuiteName = "glch::AStringFunctions";
        std::cout << "%SUITE_STARTING% " << lSuiteName << std::endl;
        std::cout << "%SUITE_STARTED%" << std::endl;
        clock_t lBeginTime = clock();
        
        compare_tmr(lBeginTime,"DirectoryParse",lSuiteName,glch::directory_parse("/test1/test2","%d0-%d1"),"test2-test1");
        compare_tmr(lBeginTime,"DirectoryParse",lSuiteName,glch::directory_parse("/blarg/test1/test2","%d0-%d1"),"test2-test1");
        compare_tmr(lBeginTime,"DirectoryParse",lSuiteName,glch::directory_parse("/blarg/test1/test2","%d0-%d2"),"test2-blarg");
        
        compare_tmr(lBeginTime,"DirectoryParse",lSuiteName,glch::file_name_parse("/abc/xyz/test1/test2","%d0-%d1","-"),"test2-test1");
        compare_tmr(lBeginTime,"DirectoryParse",lSuiteName,glch::file_name_parse("/blarg/test1/test2","%d0-%d1","-"),"test2-test1");
        compare_tmr(lBeginTime,"DirectoryParse",lSuiteName,glch::file_name_parse("/blarg/test1/test2","%d0-%d2","-"),"test2-blarg");
        compare_tmr(lBeginTime,"DirectoryParse",lSuiteName,glch::file_name_parse("/blarg/test1/test2-123-145","%d0-%d2-%f0","-"),"test2-123-145-blarg-test2");
        compare_tmr(lBeginTime,"DirectoryParse",lSuiteName,glch::file_name_parse("/blarg/test1/test2-123-145","%d2-%f1_%f0","-"),"blarg-123_test2");
        
        //double lEndTime = (double( clock() - aTimer )/CLOCKS_PER_SEC );
        long lEndTime = usec_ellapsed(lBeginTime);
        std::cout << "%SUITE_FINISHED% time=" << std::fixed << lEndTime << std::endl;
    }
    
    static void test_astring(){
        std::string lSuiteName = "glch::AString";
        std::cout << "%SUITE_STARTING% " << lSuiteName << std::endl;
        std::cout << "%SUITE_STARTED%" << std::endl;
        clock_t lBeginTime = clock();
        
        compare_tmr(lBeginTime,"String",lSuiteName,glch::AString("Hello"),"Hello");
        compare_tmr(lBeginTime,"StringArg",lSuiteName,glch::AString("Hello%1%2%3").arg(1).arg(2).arg(3),"Hello123");
        compare_tmr(lBeginTime,"StringArg",lSuiteName,glch::AString("Hello%1%2%3").arg(1111).arg(2222).arg(3333),"Hello111122223333");
        compare_tmr(lBeginTime,"StringArg",lSuiteName,glch::AString("Hello %1 %2 %3 %1 %2").arg(1111).arg(2222).arg(3333),"Hello 1111 2222 3333 1111 2222");
        compare_tmr(lBeginTime,"StringArg",lSuiteName,glch::AString("Hello%1%2%3 %1").arg(1).arg(2).arg(3),"Hello123 1");
        compare_tmr(lBeginTime,"StringArg",lSuiteName,glch::AString("Hello%1%2%3-%1").arg(1).arg(2).arg(3),"Hello123-1");
        compare_tmr(lBeginTime,"StringArg",lSuiteName,glch::AString("Hello%1%2%3%1").arg("abc").arg("ttt").arg("ZZZ"),"HelloabctttZZZabc");
        
        compare_tmr(lBeginTime,"toDouble",lSuiteName,glch::AString("1234.555").toDouble(),1234.555);
        compare_tmr(lBeginTime,"toFloat",lSuiteName,glch::AString(".0001234555").toFloat(),.0001234555f);
        compare_tmr(lBeginTime,"toInt",lSuiteName,glch::AString("5.5").toInt(),5);
        compare_tmr(lBeginTime,"toLong",lSuiteName,glch::AString("5.5").toLong(),5);
        compare_tmr(lBeginTime,"toUInt",lSuiteName,glch::AString("-5").toUInt(),(unsigned int)-5);
        compare_tmr(lBeginTime,"toULong",lSuiteName,glch::AString("-5").toULong(),(unsigned long)-5);
        compare_tmr(lBeginTime,"toBool",lSuiteName,glch::AString("1").toBool(),1);
        
        compare_tmr(lBeginTime,"Erase All Strings",lSuiteName,glch::AString("abc defg xxxcyyyazxcv").erase_all_strings("xc"),"abc defg xxyyyazv");
        compare_tmr(lBeginTime,"Erase All Strings",lSuiteName,glch::AString("abc defg xxxbcyyyazxbcv").erase_all_strings("bc"),"a defg xxxyyyazxv");
        
        compare_tmr(lBeginTime,"Replace All Strings",lSuiteName,glch::AString("abc defg xxxbcyyyazxbcv").replace_all_strings("bc","TUVW"),"aTUVW defg xxxTUVWyyyazxTUVWv");
        compare_tmr(lBeginTime,"Replace All Strings",lSuiteName,glch::AString("abc defg xxxbcyyyazxbcv").replace_all_strings("b","TUVW"),"aTUVWc defg xxxTUVWcyyyazxTUVWcv");
        
        compare_tmr(lBeginTime,"Inc",lSuiteName,glch::AString("5")++,6);
       
        glch::AStringList lSplit = glch::AString("55,6457,ABCD,7zzr").split(",");
        
        compare_tmr(lBeginTime,"Split",lSuiteName,lSplit.at(0),55);
        compare_tmr(lBeginTime,"Split",lSuiteName,lSplit.at(1),6457);
        compare_tmr(lBeginTime,"Split",lSuiteName,lSplit.at(2),"ABCD");
        compare_tmr(lBeginTime,"Split",lSuiteName,lSplit.at(3),"7zzr");
        
        glch::AStringList lSplitT = glch::AString("55,\"6457,ABCD\",7zzr").split(",","\"","\"");
        
        compare_tmr(lBeginTime,"Split Tolken",lSuiteName,lSplitT.at(0),55);
        compare_tmr(lBeginTime,"Split Tolken",lSuiteName,lSplitT.at(1),"6457,ABCD");
        compare_tmr(lBeginTime,"Split Tolken",lSuiteName,lSplitT.at(2),"7zzr");
        
        
        //double lEndTime = (double( clock() - aTimer )/CLOCKS_PER_SEC );
        long lEndTime = usec_ellapsed(lBeginTime);
        std::cout << "%SUITE_FINISHED% time=" << std::fixed << lEndTime << std::endl;
    }
    
    static void test_segment_eqn(){
        std::string lSuiteName = "Find Float";
        std::cout << "%SUITE_STARTING% " << lSuiteName << std::endl;
        std::cout << "%SUITE_STARTED%" << std::endl;
        
        clock_t lBeginTime = clock();
        
        compare_tmr(lBeginTime,"Nested Float 1",lSuiteName, glch::find_float("1+1.23e-33+4", 0),"1.23e-33");
        compare_tmr(lBeginTime,"Nested Float 2",lSuiteName, glch::find_float("a1123+4.6-1231.23e-33+abc+def", 0),"1231.23e-33");
        compare_tmr(lBeginTime,"Nested Float 3",lSuiteName, glch::find_float("1+1.23e33+4", 0),"1.23e33");
        compare_tmr(lBeginTime,"Nested Float 4",lSuiteName, glch::find_float("1+-1.23e33+4", 0),"-1.23e33");
        compare_tmr(lBeginTime,"Nested Float 5",lSuiteName, glch::find_float("1+1e3+4", 0),"1e3");
        compare_tmr(lBeginTime,"Nested Float 6",lSuiteName, glch::find_float("-1e3", 0),"-1e3");
        compare_tmr(lBeginTime,"Nested Float 7",lSuiteName, glch::find_float("XYZ[1]-1.23e33+4", 0),"1.23e33");
        compare_tmr(lBeginTime,"Nested Float 8",lSuiteName, glch::find_float("XYZ[-1.23e33+4]", 0),"-1.23e33");
        compare_tmr(lBeginTime,"Nested Float 9",lSuiteName, glch::find_float("XYZ[-123.e.33+4]", 0),"-123.e.33");
        compare_tmr(lBeginTime,"Nested Float 10",lSuiteName, glch::find_float("XYZ[-12333+4]", 0),"");
        compare_tmr(lBeginTime,"Nested Float 11",lSuiteName, glch::find_float("22.333e-12", 0),"22.333e-12");
        compare_tmr(lBeginTime,"Check Float 12",lSuiteName, glch::find_float("Test1", 0),"e");
        compare_tmr(lBeginTime,"Check Float 13",lSuiteName, glch::find_float("Test1+Test2", 0),"e");
        compare_tmr(lBeginTime,"Check Float 14",lSuiteName, glch::find_float("est1+Test2", 0),"e");
        compare_tmr(lBeginTime,"Check Float 15",lSuiteName, glch::find_float("Abc12.0e-30", 0),"e");
        compare_tmr(lBeginTime,"Check Float 16",lSuiteName, glch::find_float("12.0e-30abc", 0),"e");
        compare_tmr(lBeginTime,"Check Float 17",lSuiteName, glch::find_float("Abc12.0+e-30", 0),"e-30");
        
        std::map<glch::AString,glch::AString> lDst;
        glch::AString lEqn = "1+1e3112+2.3e-43+3+5.3e-16";
        std::string lNewEqn = replace_floats(lEqn,lDst);
        
        compare_neq_tmr(lBeginTime,"Replace Floats",lSuiteName, lEqn,lNewEqn);
        
        std::vector<string> lSplits = glch::split_equation(lEqn);
        compare_tmr(lBeginTime,"Split 1",lSuiteName, lSplits.at(0),"1");
        compare_tmr(lBeginTime,"Split 2",lSuiteName, lSplits.at(1),"1e3112");
        compare_tmr(lBeginTime,"Split 3",lSuiteName, lSplits.at(2),"2.3e-43");
        compare_tmr(lBeginTime,"Split 4",lSuiteName, lSplits.at(3),"3");
        compare_tmr(lBeginTime,"Split 5",lSuiteName, lSplits.at(4),"5.3e-16");
        
        lSplits.clear();
        lSplits = glch::split_equation("Test1.3+Test2+test3+abcde");
        lNewEqn = replace_floats(lEqn,lDst);
        compare_tmr(lBeginTime,"Split 1.1",lSuiteName, lSplits.at(0),"Test1.3");
        compare_tmr(lBeginTime,"Split 1.2",lSuiteName, lSplits.at(1),"Test2");
        compare_tmr(lBeginTime,"Split 1.3",lSuiteName, lSplits.at(2),"test3");
        compare_tmr(lBeginTime,"Split 1.4",lSuiteName, lSplits.at(3),"abcde");
        
        long lEndTime = usec_ellapsed(lBeginTime);
        std::cout << "%SUITE_FINISHED% time=" << std::fixed << lEndTime << std::endl;
    }
    
    static void test_parser(){
        
        std::string lSuiteName = "glch::parser";
        std::cout << "%SUITE_STARTING% " << lSuiteName << std::endl;
        std::cout << "%SUITE_STARTED%" << std::endl;
        
        
        double lTest13 = 44;
        double x = 101;
        double y = 0;
        double lAbc = 0;
        vector<double> lTest = glch::AString("11,22,33,0,0,0,0,0").to_vector<double>();
        
        glch::LenList vData;
        vData["Test1.3"] = 44;
        vData["x"] = 101;
        vData["y"] = 0;
        vData["Test[0]"] = 11;
        vData["Test[1]"] = 22;
        vData["Test[2]"] = 33;
        glch::Evaluator lEval;
        lEval.load_file("./grammar_fixed_v9");
        //lEval.vParser = lParse;
        clock_t lBeginTime = clock();
        fuzzy_compare_tmr(lBeginTime,"Floats1",lSuiteName, lEval.evaluate("22.333e-12",vData).toDouble(), 22.333e-12L);
        fuzzy_compare_tmr(lBeginTime,"Floats2",lSuiteName, lEval.evaluate("22.333e12",vData).toDouble(), 22.333e12L);
        fuzzy_compare_tmr(lBeginTime,"Floats3",lSuiteName, lEval.evaluate("-22.333e12",vData).toDouble(), -22.333e12L);
        fuzzy_compare_tmr(lBeginTime,"Floats4",lSuiteName, lEval.evaluate("-22.333e-12",vData).toDouble(), -22.333e-12L);
        fuzzy_compare_tmr(lBeginTime,"Floats5",lSuiteName,lEval.evaluate("11.324",vData),11.324);
        
        compare_tmr(lBeginTime,"Digit1",lSuiteName,lEval.evaluate("3",vData).toDouble(),3);
        compare_tmr(lBeginTime,"Digit2",lSuiteName,lEval.evaluate("5",vData),5);
        compare_tmr(lBeginTime,"Digit3",lSuiteName,lEval.evaluate("55",vData),55);
        compare_tmr(lBeginTime,"Digit4",lSuiteName,lEval.evaluate("55123",vData),55123);
        
        compare_tmr(lBeginTime,"Variables1",lSuiteName,lEval.evaluate("Test1.3",vData),lTest13);
        compare_tmr(lBeginTime,"Variables2",lSuiteName,lEval.evaluate("x",vData),x);
        compare_tmr(lBeginTime,"Variables3",lSuiteName,lEval.evaluate("y",vData),y);
        
        compare_tmr(lBeginTime,"Add",lSuiteName,lEval.evaluate("4 + 3",vData),4+3);
        compare_tmr(lBeginTime,"AddMult",lSuiteName,lEval.evaluate("4.0+3.0*2.0",vData),4.0+3.0*2.0);
        compare_tmr(lBeginTime,"AddPow",lSuiteName,lEval.evaluate("4.0+3.0^2.0",vData),4.0+3.0*3.0);
        compare_tmr(lBeginTime,"AddDiv",lSuiteName,lEval.evaluate("4+3/2",vData),4.0+3.0/2.0);
        compare_tmr(lBeginTime,"VarAdd",lSuiteName,lEval.evaluate("Test1.3+1",vData),lTest13+1);
        compare_tmr(lBeginTime,"Division",lSuiteName,lEval.evaluate("3/4",vData),3.0/4.0);
        
        compare_tmr(lBeginTime,"Equation1",lSuiteName,lEval.evaluate("5+x*2+5",vData),5+101*2+5);
        compare_tmr(lBeginTime,"Equation2",lSuiteName,lEval.evaluate("4 *x^2/2",vData),4*(x*x)/2);
        compare_tmr(lBeginTime,"Equation3",lSuiteName,lEval.evaluate("4*x^(2/2)",vData),4*x);
        
        compare_tmr(lBeginTime,"Assign",lSuiteName,lEval.evaluate("Abc <- x+5",vData),(lAbc=x+5));
        compare_tmr(lBeginTime,"Variables4",lSuiteName,lEval.evaluate("Abc",vData),lAbc);

        compare_tmr(lBeginTime,"Equation4",lSuiteName,lEval.evaluate("Test1.3+Test1.3+Test1.3+Test1.3",vData),lTest13+lTest13+lTest13+lTest13);
        fuzzy_compare_tmr(lBeginTime,"Equation5",lSuiteName,lEval.evaluate("(Test1.3)*(Test1.3+Test1.3)^Test1.3",vData),lTest13*pow(lTest13+lTest13,lTest13),1e85);

        compare_tmr(lBeginTime,"Equation6",lSuiteName,lEval.evaluate("5+Test[y+0]",vData), 5+lTest[y+0]);
        compare_tmr(lBeginTime,"Equation7",lSuiteName,lEval.evaluate("5+Test[y+1]",vData), 5+lTest[y+1]);

        compare_tmr(lBeginTime,"Equation8",lSuiteName,lEval.evaluate("5+Test[x^0+0*0+0+1]",vData),5+lTest[1+0*0+0+1]);
        compare_tmr(lBeginTime,"Equation9",lSuiteName,lEval.evaluate("(Test[0]+Test[1])*(Test[0]+Test[2])",vData),(lTest[0]+lTest[1])*(lTest[0]+lTest[2]));
        compare_tmr(lBeginTime,"AssignArray",lSuiteName,lEval.evaluate("Test[y+0]<-66",vData),lTest[y+0]=66);
        compare_tmr(lBeginTime,"Ternary1",lSuiteName,lEval.evaluate("66?5:7",vData),66?5:7);
        compare_tmr(lBeginTime,"Ternary2",lSuiteName,lEval.evaluate("0?5:7",vData),0?5:7);
        compare_tmr(lBeginTime,"Ternary3",lSuiteName,lEval.evaluate("x?5:7",vData),x?5:7);
        compare_tmr(lBeginTime,"Ternary4",lSuiteName,lEval.evaluate("(x?1:0)?5:7",vData),(x?1:0)?5:7);
        //compare_tmr(lBeginTime,"Ternary5",lSuiteName,lEval.evaluate("(y?1:0)?5:7",vData),(y?1:0)?5:7);
        compare_tmr(lBeginTime,"Ternary6",lSuiteName,lEval.evaluate("Test1.3?5:7",vData),lTest13?5:7);
        compare_tmr(lBeginTime,"Ternary7",lSuiteName,lEval.evaluate("Test1.3>5?5:7",vData),lTest13>5?5:7);
        compare_tmr(lBeginTime,"Ternary8",lSuiteName,lEval.evaluate("Test1.3>5?5+x:7+x",vData),lTest13>5?5+x:7+x);
        compare_tmr(lBeginTime,"Ternary9",lSuiteName,lEval.evaluate("Test1.3>5?5+x:7+x",vData),lTest13>5?5+x:7+x);
        
        compare_tmr(lBeginTime,"TernaryArray",lSuiteName,lEval.evaluate("Test[4]<-Test1.3>5?(1?5+x:3):7+x",vData),lTest[4]=lTest13>5?(1?5+x:3):7+x);
        compare_tmr(lBeginTime,"Array",lSuiteName,lEval.evaluate("Test[4]",vData),lTest[4]);

        
        fuzzy_compare_tmr(lBeginTime,"Equation10",lSuiteName,lEval.evaluate("(5+x*3)*3/2+6.33^2+5%2",vData),(5+x*3)*3.0/2.0+6.33*6.33+5%2);
        fuzzy_compare_tmr(lBeginTime,"Equation11",lSuiteName,lEval.evaluate("5+x*3*3/2+6.33^2+5%2",vData),5+x*3*3.0/2.0+6.33*6.33+5%2);
        fuzzy_compare_tmr(lBeginTime,"Equation12",lSuiteName,lEval.evaluate("Test[3]<-5+x*3*3/2+6.33^2+5%2",vData),lTest[3]=5+x*3*3.0/2.0+6.33*6.33+5%2);
        
        compare_tmr(lBeginTime,"Comp",lSuiteName,lEval.evaluate("x>7",vData),x>7);
        compare_tmr(lBeginTime,"Comp",lSuiteName,lEval.evaluate("y=0",vData),y==0);
        compare_tmr(lBeginTime,"Comp",lSuiteName,lEval.evaluate("x>7&y=0",vData),x>7&&y==0);
        compare_tmr(lBeginTime,"Comp",lSuiteName,lEval.evaluate("x<7|y=0",vData),x<7||y==0);
        compare_tmr(lBeginTime,"Comp",lSuiteName,lEval.evaluate("x<7&y=0|!(x?x>y|y=0:5*x)",vData),(x<7)&&(y=1)||!(x?(x>y||y==0):(5*x)));
        
        compare_tmr(lBeginTime,"LongVarName",lSuiteName,lEval.evaluate("Flag.allowhug&Flag.introduce&Flag.allowhug&Flag.introduce&Flag.allowhug&Flag.introduce&Flag.allowhug&Flag.introduce&Flag.allowhug&Flag.introduce&Flag.allowhug&Flag.introduce",vData),"0");
        compare_tmr(lBeginTime,"LongVarName",lSuiteName,lEval.evaluate("Flag.allowhug&Flag.introduce",vData),"0");
        compare_tmr(lBeginTime,"LongVarName",lSuiteName,lEval.evaluate("Person2.relationship>=5",vData).toBool(),0);
        
        //double lEndTime = (double( clock() - aTimer )/CLOCKS_PER_SEC );
        long lEndTime = usec_ellapsed(lBeginTime);
        std::cout << "%SUITE_FINISHED% time=" << std::fixed << lEndTime <<  std::endl;
    }
    
    
    
    
    static void test_boundary(){
        
        glch::MatT<uchar> lCalibSq;
        glch::AString lCalibSqPath = "./calib_sq.pgm";
        //lCalibSqPath = "./calib_edge.pgm";
        lCalibSqPath = "./y-mask.pgm";
        lCalibSqPath = "./calib_circ.pgm";
        
        glch::load_pgm(lCalibSqPath,lCalibSq);
        glch::MatT<uchar> lSaveSq(lCalibSq.cols,lCalibSq.rows);
        glch::MatT<uchar> lSaveCl(lCalibSq.cols,lCalibSq.rows);
        
         glch::MatT<uchar> lSaveTopSq(lCalibSq.cols*3,lCalibSq.rows*3);       
        //std::vector<glch::Point> lPts = glch::get_boundary_points(lCalibSq);
        
        
         
        std::vector<glch::Point> lMaskPts = glch::mask_to_pts(lCalibSq);
        glch::BoundaryList lClusters = glch::extract_clusters(lMaskPts,4);
        
        
//        for(int i = 0; i < lClusters.size(); i++){
//            std::cout << lClusters.at(i).size() << endl;
//        }
//        
        
        std::cout << glch::ShapeProperties<int>::header() << endl;
        
        for(size_t i = 0; i < lClusters.size(); i++){
            //glch::print_vect_fn(lBoundary.at(i));
            //std::cout << endl;
            //glch::print_vect_fn(lTopBoundary.at(i));
            
            
            
            
            //glch::compute_top_boundary()
            glch::BoundaryList lLargeBoundary = glch::compute_large_boundary(lClusters.at(i));
            std::vector<glch::Point> lTop = lLargeBoundary.front();
            
            glch::BoundaryList lBoundary = glch::large_to_small_boundary(lLargeBoundary);
            //glch::BoundaryList lBoundary = glch::compute_boundary(lClusters.at(i));
            std::vector<glch::Point> lBdy = lBoundary.front();
            
            
            
            glch::draw_points(lSaveCl,lClusters.at(i),255);
            glch::draw_points(lSaveSq,lBdy,255);
            glch::draw_points(lSaveTopSq,lTop,255);
            
            //std::vector<glch::PointF> lDTop;
            
//            for(size_t j = 0; j < lTopBoundary.front().size(); j ++){
//                lDTop.push_back(lTopBoundary.front().at(j));
//                lDTop.at()
//            }
            
            //glch::ShapeProperties<int> lSP;
            //lSP.initialize(lBdy);
            
            glch::ShapeProperties<int> lTopSP;
            lTopSP.initialize(lTop);
            //std::cout << "TopData" << lTopSP.vArea << " : " << lTopSP.vPerimeter << " : " << lTopSP.vDiameter << " : " << lTopSP.vFilamentRatio << endl;
            //std::cout << "Data: " << lSP.to_string() << endl;
            std::cout << lTopSP.to_string() << ",";
            std::cout << lClusters.at(i).size() << ",";
            std::cout << lBdy.size() << endl;
            //glch::centroid(lDTop).print();
//            glch::PointF lCent = glch::centroid(lTop);
//            lCent.print();
//            std::cout << glch::central_moment(lTop,lCent,0,0) << endl;
//            std::cout << glch::central_moment(lTop,lCent,0,1) << endl;
//            std::cout << glch::central_moment(lTop,lCent,1,0) << endl;
//            std::cout << glch::central_moment(lTop,lCent,1,1) << endl;
//            std::cout << glch::central_moment(lTop,lCent,0,2) << endl;
//            std::cout << glch::central_moment(lTop,lCent,2,0) << endl;
//            std::cout << glch::central_moment(lTop,lCent,1,2) << endl;
//            std::cout << glch::central_moment(lTop,lCent,2,1) << endl;
//            std::cout << glch::central_moment(lTop,lCent,2,2) << endl;
            //glch::centroid(lTopBoundary.front()).print();
            //glch::print_vect_fn(lTopBoundary.front());
            
            
            
//            double lArea = glch::area(lBoundary.at(i));
//            double lPerim = glch::perimeter(lBoundary.at(i));
//            double lDiam = glch::diameter(lBoundary.at(i));
//            double lFI = lPerim*lDiam/(4*lArea);
//            
//            double lTopArea = glch::area(lTopBoundary.front());
//            double lTopPerim = glch::perimeter(lTopBoundary.front());
//            double lTopDiam = glch::diameter(lTopBoundary.front());
//            double lTopFI = lTopPerim*lTopDiam/(4*lTopArea);
            
           
            //std::cout << "Area: " << lArea << " : " << lPerim << " : " << lDiam << " : " << lFI << endl;
            //std::cout << "TopArea: " << lTopArea << " : " << lTopPerim << " : " << lTopDiam << " : " << lTopFI << endl;
            
            
        }
        
//        for(size_t i = 0; i < lTopBoundary.size(); i++){
//            std::cout << i << " : " << lTopBoundary.size() << endl;
//            
//            std::cout << endl;
//        }
        
        
        //glch::save_pgm("./calib_sq_bdy.pgm", lSaveSq);
        //glch::save_pgm("./calib_edge_bdy.pgm", lSaveSq);
        //glch::save_pgm("./y-mask_bdy.pgm", lSaveSq);
        //glch::save_pgm("./y-mask_top-bdy.pgm", lSaveTopSq);
        //glch::save_pgm("./y-mask_cl.pgm", lSaveCl);
        
        glch::save_pgm("./cir_bdy.pgm", lSaveSq);
        glch::save_pgm("./cir_top-bdy.pgm", lSaveTopSq);
        glch::save_pgm("./cir_cl.pgm", lSaveCl);
    }
    
    static void test_gene(){
        
        srand(time(NULL));
        
        glch::GeneList lGenes1;
        glch::GeneList lGenes2;
        
        lGenes1.insert_gene(glch::Gene("Test1",.5,0,0,false,false,-50,50,0,5));
        lGenes1.insert_gene(glch::Gene("Test2",.6,0,0,false,false,-50,50,0,5));
        lGenes1.insert_gene(glch::Gene("Test3",.7,0,0,false,false,-50,50,0,5));
        lGenes1.insert_gene(glch::Gene("Test4",.8,0,0,false,false,-50,50,0,5));
        
        lGenes2.insert_gene(glch::Gene("TestA",.2,0,0,false,false,-50,50,0,5));
        lGenes2.insert_gene(glch::Gene("TestB",.3,0,0,false,false,-50,50,0,5));
        lGenes2.insert_gene(glch::Gene("TestC",.4,0,0,false,false,-50,50,0,5));
        lGenes2.insert_gene(glch::Gene("TestD",.5,0,0,false,false,-50,50,0,5));
        
        lGenes1.print();
        //lGenes1.mutate();
        //lGenes1.print();
        
        lGenes2.print();
        //lGenes2.mutate();
        //lGenes2.print();
        
        glch::GeneList lGenes3 = glch::GeneList::breed(lGenes1,lGenes2);
        lGenes3.print();
        //lGenes3.mutate();
        //lGenes3.print();
        
//        glch::GeneBuilder lBuilder;
//        
//        std::vector<double> lTest1 = glch::AString(".5,.7,.7,.8,.9,.2");
//        std::vector<double> lTest2 = glch::AString(".2,.3,.5,.6,.2,.4");
//        std::vector<double> lTest3 = glch::breed_vects(lTest1,lTest2);
//        
//        glch::print_vect(lTest3);
//        std::cout << endl;
//        
//        
//        lBuilder.insert_gene("Test1",.1,.1,0,1);
//        lBuilder.insert_gene("Test2",.1,.1,0,1);
//        
//        for(int i = 0; i < 100; i++){
//            std::cout << glch::mutate_norm(.5) << " ";
//        }
//        
//        lBuilder.print();
        
//        for(int i = -1000; i < 1000; i++){
//            std::cout << glch::normal_dist(i/100.0,0,1) << " ";
//            if(i%100==0){
//                std::cout << endl;
//            }
//        }
        
    }
    
    static void test_primes(){
        std::string lSuiteName = "glch::primes";
        std::cout << "%SUITE_STARTING% " << lSuiteName << std::endl;
        std::cout << "%SUITE_STARTED%" << std::endl;
        clock_t lBeginTime = clock();
        
        compare_tmr_t<unsigned long>(lBeginTime,"prime(100)",lSuiteName,glch::prime(100),541);
        compare_tmr_t<unsigned long>(lBeginTime,"prime(1000)",lSuiteName,glch::prime(1000),7919);
        compare_tmr_t<unsigned long>(lBeginTime,"prime(10000)",lSuiteName,glch::prime(10000),104729);
        compare_tmr_t<unsigned long>(lBeginTime,"prime(100000)",lSuiteName,glch::prime(100000),1299709);
        compare_tmr_t<unsigned long>(lBeginTime,"prime(1000000)",lSuiteName,glch::prime(1000000),15485863);
        compare_tmr_t<unsigned long>(lBeginTime,"prime(10000000)",lSuiteName,glch::prime(10000000),179424673);
        //compare_tmr_t<unsigned long>(lBeginTime,"prime(100000000)",lSuiteName,glch::prime(100000000),2038074743);
        
        //double lEndTime = (double( clock() - aTimer )/CLOCKS_PER_SEC );
        long lEndTime = usec_ellapsed(lBeginTime);
        std::cout << "%SUITE_FINISHED% time=" << std::fixed << lEndTime << std::endl;
    }
    
    static void run(){
        //my_fac_test();
        //my_pow_test();
        //mult2_test();
        //sin_test();
        //fprime_test();
        
//        test_segment_eqn();
//        test_parser();
//        test_astring();
//        test_astring_fns();
//        test_random_int();
//        test_sharedpointer();
//        test_randstring();
//        
//        test_equation_fix();
//        test_new_parse();
        
//        test_boundary();
        
        //test_gene();
        
        //glch::save_boundary_data("/mnt/ramdrive/results/p093_04/img-360-256/r-mask.pgm","/mnt/ramdrive/results/p093_04/img-360-256/r-mask.csv","/mnt/ramdrive/results/p093_04/img-360-256/r-mask_alt.csv");
        //glch::save_boundary_data("/mnt/ramdrive/results/p093_04/img-360-256/b-mask.pgm","/mnt/ramdrive/results/p093_04/img-360-256/b-mask.csv","/mnt/ramdrive/results/p093_04/img-360-256/b-mask_alt.csv");
        //glch::save_boundary_data("/mnt/ramdrive/results/p093_04/img-360-256/y-mask.pgm","/mnt/ramdrive/results/p093_04/img-360-256/y-mask.csv","/mnt/ramdrive/results/p093_04/img-360-256/y-mask_alt.csv");
        //glch::save_boundary_data("/mnt/ramdrive/results/p093_04/img-360-256/ns-mask.pgm","/mnt/ramdrive/results/p093_04/img-360-256/ns-mask.csv","/mnt/ramdrive/results/p093_04/img-360-256/ns-mask_alt.csv");

        //test_primes();
        
        for(int i = 8234; i < 1000000; i++){
            //std::cout << "Prime: " << i << " : " << glch::prime(i) << std::endl;
            //std::cout << glch::prime(i) << " : " << glch::counting_every_row(i) << std::endl;
            std::vector<unsigned long> lCounts = glch::counting_every_row_all(i);
            //glch::print_vect(lCounts);
            glch::AString lOutput;
            glch::AString lOutput2;
            //lOutput.push_vector(lCounts);
            //lOutput += "\n";
            
            lOutput2 << lCounts.at(0);
            lOutput2 << lCounts.at(2);
            lOutput2 += "\n";
            //std::cout << std::endl;
            //glch::append_text_file("./prime_residue.txt",lOutput);
            glch::append_text_file("./prime_residue2.txt",lOutput2);
        }
        
        //std::cout << glch::prime(9592) << " : " << glch::counting_every_row(9592) << std::endl;
    }
};

void test1() {
    std::cout << "validator test 1" << std::endl;
}

void test2() {
    std::cout << "validator test 2" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (validator) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    //std::cout << "%SUITE_STARTING% validator" << std::endl;
    //std::cout << "%SUITE_STARTED%" << std::endl;

    //std::cout << "%TEST_STARTED% test1 (validator)" << std::endl;
    Validate::run();
    //std::cout << "%TEST_FINISHED% time=0 test1 (validator)" << std::endl;
    
//    std::cout << "%TEST_STARTED% test1 (validator)" << std::endl;
//    test1();
//    std::cout << "%TEST_FINISHED% time=0 test1 (validator)" << std::endl;
//
//    std::cout << "%TEST_STARTED% test2 (validator)\n" << std::endl;
//    test2();
//    std::cout << "%TEST_FINISHED% time=0 test2 (validator)" << std::endl;

    //std::cout << "%SUITE_FINISHED% time=" << time(NULL) << std::endl;

    return (EXIT_SUCCESS);
}

