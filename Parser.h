/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.h
 * Author: brian
 *
 * Created on June 17, 2018, 9:46 AM
 */


#ifndef GLCH_PARSER_H
#define GLCH_PARSER_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <list>
#include <math.h>

#include <memory>

#include "MatT.h"
#include "random.h"
#include "PolygonFunctions.h"
#include "stringconversion.h"


using namespace std;

namespace glch{
template <class T>
void system_out_print(T input, int width = 5){
    cout << setw(width) << input ;
    
}

template <class T>
void system_out_println(T input, int width = 5){
    cout << setw(width) << input << endl;
}

std::string replace_floats(std::string aSrc, std::map<glch::AString, glch::AString>& aDst);
std::string find_float(glch::AString aEquation, size_t aPOS);
std::vector<std::string> split_equation(glch::AString aEquation);

template <class T>
class SharedPointer {
public:
    T* vPtr;
    size_t* vShared;
    
    T& operator*(){
        return *vPtr;
    }
    
    T& operator[](size_t aIndex){
        return vPtr[aIndex];
    }
    
    SharedPointer(){
        vPtr = NULL;
        vShared = NULL;
    }
    
    explicit SharedPointer(T *aPtr) {
        vPtr = aPtr;
        vShared = new size_t(1);
        
    } 
    
    SharedPointer(const SharedPointer& orig){
        vPtr = orig.vPtr;
        vShared = orig.vShared;
        
        inc_count();
    }
    
    ~SharedPointer(){
        //cout << "Destructor" << endl;
        clear();
        //cout << "End Destructor" << endl;
    }
    
    SharedPointer operator=(const SharedPointer& orig){
        //cout << "Assignment" << endl;
        clear();
        
        vPtr = orig.vPtr;
        vShared = orig.vShared;
        inc_count();
        
        return *this;
    }
    
    bool operator==(const T* aRHS) const{
        return vPtr==aRHS;
    }
    
    bool operator!=(const T* aRHS) const{
        return vPtr!=aRHS;
    }    
    
    T* operator->(){
        return vPtr;
    }
    
    operator bool() const{
        return vPtr!=NULL;
    }
    
    void clear(){
        if(vShared == NULL){
            return;
        }
        
        dec_count();
        
        
        if(*vShared == 0){
            delete vPtr;
            delete vShared;
        }
        
        vPtr = NULL;
        vShared = NULL;
    }
    
    void inc_count(){
        
        if(vShared != NULL){
            (*vShared)++;
        }
        
    }
    
    void dec_count(){
        
        if(vShared != NULL){
            (*vShared)--;
        }
        
    }
    
    size_t count(){
        if(vShared == NULL){
            return 0;
        }
        
        return *vShared;
    }
    
    bool is_null(){
        return vShared==NULL;
    }
    
};

class Node;

typedef SharedPointer<Node> SPNode;

class Node{
public:       
    string vKey;
    SPNode vLeft;
    SPNode vRight;
    SPNode vParent;
    string vUID;
    //NFA vNFA;
    
    Node(const Node& orig);
    
    Node();
    
    Node(string aKey);
    
    ~Node();
    
    void delete_tree();
    
    void print();
    
};





class BinaryTree {
public:    
    SPNode vRoot;
    //std::shared_ptr<Node> vRoot;
    
    BinaryTree(string aKey);
    
    BinaryTree();
    
    ~BinaryTree();
    
    BinaryTree(const BinaryTree& orig);
    
    void print();
    
};

struct Tuple{
    long first;
    long second;
    string name;
    
    Tuple();

    Tuple(long first, long second);

    Tuple(long first, long second, string name);
    
    Tuple(const Tuple& orig);

    bool operator ==(const Tuple& RHS) const;

    bool operator<(const Tuple& RHS) const;
};

class Connections{
public:

    struct Lineage{
        string orig;
        string name;
        string parent;
        
    };
    
    std::map<string, vector<Lineage> > vLineage;
    
    glch::MatT<int> vConnections;
    vector<string> vRowNames;
    vector<string> vColNames;

    std::map<Tuple, vector<long> > vStateMap;
    std::map<string, vector<long> > vTerminalMap;

    string vStartRule;

    Connections();

    Connections(const Connections& orig);

    void push_statemap(Tuple aTuple, long aState);

    void push_terminals(string aKey, long aState);

    bool has_row(string aValue);

    bool has_col(string aValue);

    void check_row_col_index(string aRow, string aCol);

    int row_index(string aValue);

    int col_index(string aValue);

    void add_variable(string aVariable);

    void add_rule(string aLHS, string aRHS);


    
    
    /**
     * Finds the columns where the symbol gets it's inputs from
     * @return Returns the column names.
     */
    vector<string> get_symbol_inputs(string aRow);

    string find_lineage(string aKey, string aSearch);

    Lineage get_lineage(string aKey, string aSearch);
    
    void gen_lineage_list(string aKey, string aSearch, vector< SPNode >& aNodeList);
    
    vector< SPNode > gen_lineage(string aKey, string aSearch);
    
    void print_lineage();
    
    void map_lineage();
    
    
    /**
     * Finds the columns where the symbol gets it's inputs from
     * @return Returns the column names.
     */
    void get_symbol_inputs_parent(string aRow, string aParent, vector<string>& aOrig, vector<string>& aDstName, vector<string>& aDstParent);
    
    /**
     * Finds the rows where the symbol outputs to (if it is a Variable)
     * @param aCol
     * @return
     */
    vector<string> get_symbol_outputs(string aCol);
    

    
    
    void map_inputs();

    void print_maps();
    
    


    /**
     * Finds the columns where the symbol gets it's inputs from and clears the value.
     * @return Returns the column names.
     */
    void clear_symbol_inputs(string aRow);

    bool has_connection(string aRowName, string aColName);

    void set_connection(string aRowName, string aColName, int aVal);

    void print(int aColWidth = 5);

    vector<string> generate_terminals();



    vector<string> generate_grammar();

};

class Trace{
public:

    string vRuleName;
    string vTerminalName;
    long vRule; //The column or the Variable column index
    long vFirstRule;
    long vSecondRule;
    Point vFirstPos;
    Point vSecondPos;

    Trace();

    Trace(const Trace& orig);

    bool operator==(const Trace& rhs);
    
    Trace& operator=(const Trace& orig);


    std::string to_string();

};


class TraceList {
public:

    glch::MatT< vector<Trace> > vDataNew;
    int vDiagStartC;
    int vDiagStartR;
    int vRowStart;
    int vColStart;
    Connections vConnections;
    int vDim;

    TraceList(const TraceList& orig);

    BinaryTree construct_single_tree();
    
    BinaryTree construct_tree_new();

    bool fix_tree( SPNode  aNode);
    
    
     SPNode  get_children_new(long aRule, const glch::Point& aIndex,  SPNode  aParent);


    void print();



    vector<long> get_terminal_map(string aTerminal);

    TraceList(string aInput, const Connections& aConnections);
    TraceList(std::vector<string> aInput, const Connections& aConnections);

    vector<Trace> build_pairs_new(Point aFirst, Point aSecond, vector<Trace>& aDst);

    
    
    vector<Trace> build_singles(Point aFirst, vector<Trace>& aDst);
    
    void find_branches_new(int aRow, int aCol);



    void scan_row(int aRow);

    void scan_rows();




};




class Parser {
public:
    Connections vConnections;
    

    
    Parser();
    
    Parser(const Parser& orig);
        
    void add_variable(string aVariable);
    
    void add_rule(string aLHS, string aRHS);
    
    vector<string> get_symbol_inputs(string aRow);
    
    vector<string> get_symbol_outputs(string aCol);
    
    void clear_symbol_inputs(string aRow);
    
    void print_cols();
    
    void print_rules();
    
    vector<string> generate_terminals();
    
    vector<string> generate_grammar();
    
    void map_inputs();

    Parser copy();
    
    void clear();
    
    
    BinaryTree build_parse_matrix(string aInput);
    BinaryTree build_parse_matrix(std::vector<string> aInput);
};





static bool is_float(glch::AString aInput){
    static Parser lParser;
    static bool lInit = true;
    if(lInit){
        lInit = false;
        lParser.add_rule("<FLOAT>", "<SIGN> <DIGIT>");
        lParser.add_rule("<FLOAT>", "<SIGN> <DIGITEX>");
        lParser.add_rule("<FLOAT>", "<DOT> <DIGIT>");
        lParser.add_rule("<FLOAT>", "<DOT> <DIGITEX>");
        lParser.add_rule("<FLOAT>", "<DIGIT> <DIGIT>");
        lParser.add_rule("<FLOAT>", "<DIGIT> <DIGITEX>");
        lParser.add_rule("<FLOAT>", "<DIGIT> <DOT>");
        lParser.add_rule("<FLOAT>", "<DIGIT> <DOTDIG>");
        lParser.add_rule("<FLOAT>", "<DIGIT> <EXPONENT>");
        lParser.add_rule("<FLOAT>", "<SIGN> <DOTDIG>");
        lParser.add_rule("<FLOAT>", "<SIGN> <DIGDOT>");
        lParser.add_rule("<FLOAT>", "0");
        lParser.add_rule("<FLOAT>", "1");
        lParser.add_rule("<FLOAT>", "2");
        lParser.add_rule("<FLOAT>", "3");
        lParser.add_rule("<FLOAT>", "4");
        lParser.add_rule("<FLOAT>", "5");
        lParser.add_rule("<FLOAT>", "6");
        lParser.add_rule("<FLOAT>", "7");
        lParser.add_rule("<FLOAT>", "8");
        lParser.add_rule("<FLOAT>", "9");
        lParser.add_rule("<DOTDIG>", "<DOT> <DIGIT>");
        lParser.add_rule("<DOTDIG>", "<DOT> <DIGITEX>");
        lParser.add_rule("<DIGDOT>", "<DIGIT> <DOT>");
        lParser.add_rule("<DIGDOT>", "<DIGIT> <DOTDIG>");
        lParser.add_rule("<DIGITEX>", "<DIGIT> <EXPONENT>");
        lParser.add_rule("<DIGIT>", "<DIGIT> <DIGIT>");
        lParser.add_rule("<SIGNDIG>", "<SIGN> <DIGIT>");
        lParser.add_rule("<DIGIT>", "0");
        lParser.add_rule("<DIGIT>", "1");
        lParser.add_rule("<DIGIT>", "2");
        lParser.add_rule("<DIGIT>", "3");
        lParser.add_rule("<DIGIT>", "4");
        lParser.add_rule("<DIGIT>", "5");
        lParser.add_rule("<DIGIT>", "6");
        lParser.add_rule("<DIGIT>", "7");
        lParser.add_rule("<DIGIT>", "8");
        lParser.add_rule("<DIGIT>", "9");
        lParser.add_rule("<SIGN>", "-");
        lParser.add_rule("<SIGN>", "+");
        lParser.add_rule("<DOT>", ".");
        lParser.add_rule("<EXPONENT>", "<EXPSYM> <FLOATE>");
        lParser.add_rule("<EXPSYM>", "e");
        lParser.add_rule("<EXPSYM>", "E");
        lParser.add_rule("<FLOATE>", "0");
        lParser.add_rule("<FLOATE>", "1");
        lParser.add_rule("<FLOATE>", "2");
        lParser.add_rule("<FLOATE>", "3");
        lParser.add_rule("<FLOATE>", "4");
        lParser.add_rule("<FLOATE>", "5");
        lParser.add_rule("<FLOATE>", "6");
        lParser.add_rule("<FLOATE>", "7");
        lParser.add_rule("<FLOATE>", "8");
        lParser.add_rule("<FLOATE>", "9");
        lParser.add_rule("<FLOATE>", "<SIGN> <DIGIT>");
        lParser.add_rule("<FLOATE>", "<SIGN> <DIGITEX>");
        lParser.add_rule("<FLOATE>", "<DOT> <DIGIT>");
        lParser.add_rule("<FLOATE>", "<DOT> <DIGITEX>");
        lParser.add_rule("<FLOATE>", "<DIGIT> <DIGIT>");
        lParser.add_rule("<FLOATE>", "<DIGIT> <DIGITEX>");
        lParser.add_rule("<FLOATE>", "<DIGIT> <DOT>");
        lParser.add_rule("<FLOATE>", "<DIGIT> <DOTDIG>");
        lParser.add_rule("<FLOATE>", "<DIGIT> <EXPONENT>");
        lParser.add_rule("<FLOATE>", "<SIGN> <DOTDIG>");
        lParser.add_rule("<FLOATE>", "<SIGN> <DIGDOT>");

        lParser.map_inputs();

    }
    glch::BinaryTree lTree = lParser.build_parse_matrix(aInput);
    //lTree.print();

    return lTree.vRoot->vKey != "NULL";
}

class LenPair{
public:
    
    glch::AString first;
    glch::AString second;
    
    LenPair();
    
    LenPair(glch::AString aFirst);
    
    LenPair(glch::AString aFirst, glch::AString aSecond);
    
    LenPair(const glch::LenPair& orig);
    
    glch::LenPair& operator=(const glch::LenPair& orig);
    
    bool operator>(const glch::LenPair& aComp) const;
    
    bool operator<(const glch::LenPair& aComp) const;
    
    bool operator==(const glch::LenPair& aComp);
    
    bool operator==(const glch::AString& aComp);
    
    void print(std::string aDelim);
    
};

    
class LenList{
public:
    
    std::vector<LenPair> data;
    
    LenList();
    
    LenList(const LenList& orig);
    
    size_t size();

    std::vector<LenPair>::iterator begin();

    std::vector<LenPair>::iterator end();

    void erase(glch::AString aKey);

    void erase(LenPair aInput);
    
    std::vector<LenPair>::iterator insert_sorted( LenPair aInput );
    
    std::vector<LenPair>::iterator find(glch::AString aKey);
    
    std::vector<LenPair>::iterator find(LenPair aInput);
    
    std::vector<LenPair>::iterator insert(LenPair aInput);
    
    std::vector<LenPair>::iterator insert(glch::AString aKey, glch::AString aVal);
    
    template <class T>
    glch::AString& operator[](T aKey){
        
        std::vector<LenPair>::iterator it = find(aKey);
        
        if(it == data.end()){
            return (*insert(aKey,"0")).second;
        }
        
        return (*it).second;
        
    }
    
    LenPair& at(size_t aKey);

    template <class T>
    glch::AString at_cp(T aKey){
        
        if(glch::is_float(aKey)){
            return aKey;
        }
        
        std::vector<LenPair>::iterator it = find(aKey);
        
        if(it == data.end()){
            return (*insert(aKey,"0")).second;
        }
        
        return (*it).second;
    }
    
    bool contains(glch::AString aKey);
    
    void print();
    
}; 

class AliasList{
public:
    LenList vData;
    map<glch::AString,glch::AString> aliases;
    map<glch::AString,glch::AString> raliases;
    
    size_t vAliasSize;
    
    AliasList(){
        vAliasSize = 1;
        
    }
    
    AliasList(const AliasList& orig) : vData(orig.vData), 
                                        aliases(orig.aliases), 
                                        raliases(orig.raliases),
                                        vAliasSize(orig.vAliasSize){};
    
    size_t alias_size(){
        return aliases.size();
    }
    
    void set_data_value(glch::AString aVariable, glch::AString aValue){
        vData[aVariable] = aValue;
    }
    
    void set_alias_value(glch::AString aAlias, glch::AString aValue){
        
        if(glch::is_float(aAlias)){
            return;
        }
        
        glch::AString lRet = raliases[aAlias];
        vData[lRet] = aValue;
    }
    
    glch::AString& get_alias_value(glch::AString aKey){
        
        //std::cout << "get_alias_value\n";
        //std::cout << aKey << endl;
        
        if(glch::is_float(aKey)){
            
            add_alias(aKey);
            return raliases[aliases[aKey]];
        }
        
        
        
        
        if(raliases.find(aKey) == raliases.end() ){
            glch::AString lAltKey = back_subsitute_equation(aKey);
            //std::cout << "Alt Key: " <<  lAltKey << endl;
            
            if(lAltKey.contains("[")){
                return vData[lAltKey];
                
            } else if(vData.find(lAltKey) != vData.end()){
                return vData[lAltKey];
                
            }
            
            throw glch::RuntimeErrorReport("Error, key not found: " + aKey);
            //return vData[aKey];
        }
        
        
        
        glch::AString lRet = raliases[aKey];
        //std::cout << "Key: " <<  lRet << endl;
        
        if(glch::is_float(lRet)){
            return raliases[aKey];
        }
        //std::cout << "Value: " << vData[lRet] << endl;
        
        return vData[lRet];
        
    }
    
    template <class T>
    glch::AString at_cp(T aAlias){
        
        return get_alias_value(aAlias);
        
    }
    
    
    
    
    
    
    /**
     * @brief Inter::fix_equation  This function splits apart a string on multiple tokens
     * and subsitutes the variables into the equation.
     * @param aEquation
     * @return
     */
    glch::AString fix_equation(glch::AString aEquation){

        glch::AString lCompactEqn = aEquation;
        lCompactEqn = lCompactEqn.erase_all_strings(" ");
        lCompactEqn = lCompactEqn.erase_all_strings("\t");
        
        //std::vector<std::string> lSymbols = glch::AString("!,&,|,=,>,<,+,-,*,/,%,^,(,),:,?,[,]").to_vector<string>(",");
        //std::vector<std::string> lSplits = glch::split_string(aEquation,lSymbols);
        std::vector<std::string> lSplits = split_equation(lCompactEqn);
        glch::AString lEquation = lCompactEqn;
        
        for(size_t i = 0; i<lSplits.size(); i++){
            //std::cout << lSplits.at(i) << endl;
            add_alias(lSplits.at(i));
        }

        size_t lPos = 0;
        for(size_t i = 0; i < lSplits.size(); i++){
            lPos = lEquation.find(lSplits.at(i),lPos);
            glch::AString lReplace = "%"+glch::to_string(i);
            //cout << lPos << " : " << lSplits.at(i) << endl;
            lEquation = lEquation.replace(lPos,lSplits.at(i).length(),lReplace);
            lPos = lPos+lReplace.length();
            //cout << "Eqn: " << lEquation << " : " << lPos << endl;
            
        }
        
        
        for(size_t i = 0; i<lSplits.size(); i++){
            
            glch::AString lAlias = get_alias(lSplits.at(i));
            //std::cout << lAlias << " : " << lSplits.at(i) << endl;
            //lEquation = lEquation.replace_all_strings(lSplits.at(i),lAlias);
            lEquation = lEquation.arg(lAlias);
        }
        
        return lEquation;

    }

    glch::AString back_subsitute_equation(glch::AString aEquation){
        
        //cout << "===================================\n";
        //cout << "Back sub....\n";
        //std::cout << aEquation << endl;
        
        //std::vector<std::string> lSymbols = glch::AString("!,&,|,=,>,<,+,-,*,/,%,^,(,),:,?,[,]").to_vector<string>(",");
        //std::vector<std::string> lSplits = glch::split_string(aEquation,lSymbols);
        std::vector<std::string> lSplits = split_equation(aEquation);
        
        glch::AString lEquation = aEquation;
        size_t lPos = 0;
        
        for(size_t i = 0; i < lSplits.size(); i++){
            lPos = lEquation.find(lSplits.at(i),lPos);
            glch::AString lReplace = "%"+glch::to_string(i);
            //cout << lPos << " : " << lSplits.at(i) << endl;
            lEquation = lEquation.replace(lPos,lSplits.at(i).length(),lReplace);
            lPos = lPos+lReplace.length();
            //cout << "Eqn: " << lEquation << " : " << lPos << endl;
            
        }
        
        //std::cout << lEquation << endl;
        
        
        for(size_t i = 0; i < lSplits.size(); i++){
            //std::cout << i << " : " << lEquation << " : " << lSplits.at(i) << endl;
            if(has_alias(lSplits.at(i)) && !glch::is_float(lSplits.at(i))){
                //cout << "Has alias..." << endl;
                //std::cout << lSplits.at(i) << " : " << aliases[lSplits.at(i)] << " : " << raliases[lSplits.at(i)] << endl;
                //lEquation = lEquation.replace_all_strings(lSplits.at(i),raliases[lSplits.at(i)]);
                
                lEquation = lEquation.arg(raliases[lSplits.at(i)]);
            } else {
                lEquation = lEquation.arg( lSplits.at(i) );
            }
            
            //std::cout << i << " : " << lEquation << endl;
        }
        
        //cout << "===================================\n";
        
//        for(map<glch::AString,glch::AString>::iterator it = raliases.begin(); it != raliases.end(); it++){
//            
//            lEquation = lEquation.replace_all_strings((*it).first,(*it).second);
//        }
        
        return lEquation;
    }
    
    glch::AString back_subsitute_values(glch::AString aEquation){
        
         //std::vector<std::string> lSymbols = glch::AString("!,&,|,=,>,<,+,-,*,/,%,^,(,),:,?,[,]").to_vector<string>(",");
        //std::vector<std::string> lSplits = glch::split_string(aEquation,lSymbols);
        std::vector<std::string> lSplits = split_equation(aEquation);
        
        glch::AString lEquation = aEquation;
        size_t lPos = 0;
        
        for(size_t i = 0; i < lSplits.size(); i++){
            lPos = lEquation.find(lSplits.at(i),lPos);
            glch::AString lReplace = "%"+glch::to_string(i);
            //cout << lPos << " : " << lSplits.at(i) << endl;
            lEquation = lEquation.replace(lPos,lSplits.at(i).length(),lReplace);
            lPos = lPos+lReplace.length();
            //cout << "Eqn: " << lEquation << " : " << lPos << endl;
            
        }
        
        for(size_t i = 0; i < lSplits.size(); i++){
            
            if(has_alias(lSplits.at(i)) && !glch::is_float(lSplits.at(i))){
                //std::cout << lSplits.at(i) << " : " << aliases[lSplits.at(i)] << " : " << raliases[lSplits.at(i)] << endl;
                lEquation = lEquation.arg( get_alias_value(lSplits.at(i)) );
                //lEquation = lEquation.replace_all_strings(lSplits.at(i),get_alias_value(lSplits.at(i)));
            } else {
                lEquation = lEquation.arg( lSplits.at(i) );
            }
        }
        
        return lEquation;
        
        //std::cout << "back_subsitute_values" << endl;
        
        //glch::AString lEquation = aEquation;
        
        //for(map<glch::AString,glch::AString>::iterator it = raliases.begin(); it != raliases.end(); it++){
            //std::cout << "Find/Replace: " << (*it).first << " : " << get_alias_value((*it).first) << endl;
        //    lEquation = lEquation.replace_all_strings((*it).first,get_alias_value((*it).first));
        //}
        
        //std::cout << "back_subsitute_values end" << endl;
        
        //return lEquation;
    }
    
    glch::AString fix_text(glch::AString aText){
        glch::AString lText = aText.c_str();

        for(size_t i = 0; i < vData.size(); i++){
            lText = lText.replace_all_strings(vData.at(i).first, vData.at(i).second.c_str());
        }

        return lText;
    }

    glch::AString get_alias(glch::AString aName){
        return add_alias(aName);
    }
    

    
    glch::AString add_alias(glch::AString aName){
        
        //cout << "Adding Alias:" << endl;
        size_t lFindCount = 0;
        
        if(aliases.find(aName) != aliases.end()){
            //cout << "Found: " << aName << " : " << aliases[aName] << endl;
            return aliases[aName];
        }
        
        glch::AString lAlias = glch::random_string(vAliasSize);
        //cout << "Generating random string..." << lAlias << endl;
        
        while(raliases.find(lAlias) != raliases.end()){
            lAlias = glch::random_string(vAliasSize);
            //cout << "Generating random string..." << lAlias << endl;
            
            if(lFindCount > 5){
                vAliasSize++;
            }
            
        }
        
        raliases[lAlias] = aName;
        aliases[aName] = lAlias;
        
        //cout << "Created: " << raliases[lAlias] << " : " << aliases[aName] << endl;
        
        return lAlias;
    }
    
    void erase_numerics(){
        
        for(map<glch::AString,glch::AString>::iterator it = aliases.begin(); it != aliases.end(); it++){
            
            if(glch::is_float((*it).first)){
                raliases.erase((*it).second);
                aliases.erase((*it).first);
            }
        }
        
    }
    
    void print(){
        
        std::cout << "============================================\n";
        
        cout << "\naliases:\n";
        for(map<glch::AString,glch::AString>::iterator it = aliases.begin(); it != aliases.end(); it++){
            std::cout << (*it).first << " : " << (*it).second << endl;
        }
        
        cout << "\nraliases:\n";
        for(map<glch::AString,glch::AString>::iterator it = raliases.begin(); it != raliases.end(); it++){
            std::cout << (*it).first << " : " << (*it).second << endl;
        }
        
        std::cout << endl;
        vData.print();
        
        std::cout << "============================================\n\n";
        
    }
    
    bool has_alias(glch::AString aAlias){
        return (aliases.find(aAlias) == aliases.end());
    }

    bool has_ralias(glch::AString aRAlias){
        return (raliases.find(aRAlias) == raliases.end());
    }
    
    glch::AString& operator[](glch::AString aKey){
        
        return get_alias_value(aKey);
    }
    
};

#ifdef EXPERIMENTAL_FALSE
class Eval {
public:
    
    
    typedef glch::AStringList (Evaluator::*command)(glch::AStringList&, AliasList&);

    Parser vParser;
    AliasList vAliases;
    std::map<string,command> vCommands;
    std::map<string, evalFn> vEvalFns;
    
    void load_data(glch::AString aFileData);

    void load_file(glch::AString aFileName);
    
    
    Eval();
    
    glch::AString evaluate(glch::AString aInput);

    glch::AString evaluate(glch::AString aInput, glch::Parser& aParser, AliasList& aData);

    glch::AString evaluate(glch::AString aInput, AliasList& aData);

    glch::AString evaluate(glch::AString aInput, LenList& aData){
        AliasList lData;
        lData.vData = aData;
        
        
        
        glch::AString lEquation = lData.fix_equation(aInput);
        //lData.print();
        
        glch::AString lRet = evaluate(lEquation,lData);
        aData = lData.vData;
        
        return lRet;
    }
    
    glch::AString evaluate( SPNode  aNode);
    
    glch::AString evaluate( SPNode  aNode, AliasList& aData);
    
    glch::AStringList evaluate_top( SPNode  aNode, AliasList& aData);
    
    glch::AStringList evaluate_right( SPNode  aNode, AliasList& aData);
    
    
    glch::AString evaluate_float( SPNode  aNode);
    glch::AString evaluate_ident( SPNode  aNode);
};
#endif

class Evaluator {
public:
    
    
    typedef glch::AStringList (Evaluator::*command)(glch::AStringList&, AliasList&);
    
    Parser vParser;
    AliasList vAliases;
    std::map<string,command> vCommands;

    void load_data(glch::AString aFileData);

    void load_file(glch::AString aFileName);
    
    
    glch::AStringList fn_equal(glch::AString v1, glch::AString v2, AliasList& aData);
    
    glch::AStringList fn_equal(glch::AStringList& aArgs, AliasList& aData);
    
    glch::AStringList fn_gt(glch::AString v1, glch::AString v2, AliasList& aData);
    
    glch::AStringList fn_gt(glch::AStringList& aArgs, AliasList& aData);
    
    glch::AStringList fn_lt(glch::AString v1, glch::AString v2, AliasList& aData);
    
    glch::AStringList fn_lt(glch::AStringList& aArgs, AliasList& aData);
    
    glch::AStringList fn_gte(glch::AString v1, glch::AString v2, AliasList& aData);
    
    glch::AStringList fn_gte(glch::AStringList& aArgs, AliasList& aData);
    
    glch::AStringList fn_lte(glch::AString v1, glch::AString v2, AliasList& aData);
    
    glch::AStringList fn_lte(glch::AStringList& aArgs, AliasList& aData);
    
    glch::AStringList fn_and(glch::AString v1, glch::AString v2, AliasList& aData);
    
    glch::AStringList fn_and(glch::AStringList& aArgs, AliasList& aData);
    
    glch::AStringList fn_or(glch::AString v1, glch::AString v2, AliasList& aData);
    
    glch::AStringList fn_or(glch::AStringList& aArgs, AliasList& aData);
    
    glch::AStringList fn_pow(glch::AString v1, glch::AString v2, AliasList& aData);
    
    glch::AStringList fn_pow(glch::AStringList& aArgs, AliasList& aData);
    
    glch::AStringList fn_mul(glch::AString v1, glch::AString v2, AliasList& aData);
    
    glch::AStringList fn_mul(glch::AStringList& aArgs, AliasList& aData);
    
    glch::AStringList fn_div(glch::AString v1, glch::AString v2, AliasList& aData);
    
    glch::AStringList fn_div(glch::AStringList& aArgs, AliasList& aData);
    
    glch::AStringList fn_mod(glch::AString v1, glch::AString v2, AliasList& aData);
    
    glch::AStringList fn_mod(glch::AStringList& aArgs, AliasList& aData);
    
    glch::AStringList fn_add(glch::AString v1, glch::AString v2, AliasList& aData);
    
    glch::AStringList fn_add(glch::AStringList& aArgs, AliasList& aData);
    
    glch::AStringList fn_sub(glch::AString v1, glch::AString v2, AliasList& aData);
    
    glch::AStringList fn_sub(glch::AStringList& aArgs, AliasList& aData);
    
    glch::AStringList fn_assign(glch::AString v1, glch::AString v2, AliasList& aData);
    
    glch::AStringList fn_assign(glch::AStringList& aArgs, AliasList& aData);
    
    
    glch::AStringList fn_tern(glch::AStringList& aArgs, AliasList& aData);
    
    glch::AStringList fn_colon(glch::AStringList& aArgs, AliasList& aData);
    
    Evaluator();
    
    glch::AString evaluate(glch::AString aInput);

    glch::AString evaluate(glch::AString aInput, glch::Parser& aParser, AliasList& aData);

    glch::AString evaluate(glch::AString aInput, AliasList& aData);

    glch::AString evaluate(glch::AString aInput, LenList& aData){
        AliasList lData;
        lData.vData = aData;
        
        
        
        glch::AString lEquation = lData.fix_equation(aInput);
        //lData.print();
        
        glch::AString lRet = evaluate(lEquation,lData);
        aData = lData.vData;
        
        return lRet;
    }
    
    glch::AString evaluate( SPNode  aNode);
    
    glch::AString evaluate( SPNode  aNode, AliasList& aData);
    
    glch::AStringList evaluate_top( SPNode  aNode, AliasList& aData);
    
    glch::AStringList evaluate_right( SPNode  aNode, AliasList& aData);
    
    
    
    glch::AString evaluate_float( SPNode  aNode);
    
    glch::AString evaluate_ident( SPNode  aNode);
};


}


    
#endif /* GLCH_PARSER_H */

