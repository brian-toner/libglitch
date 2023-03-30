/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.cpp
 * Author: brian
 * 
 * Created on June 17, 2018, 9:46 AM
 */

#include "Parser.h"

namespace glch{
    
    std::string replace_floats(std::string aSrc, std::map<glch::AString, glch::AString>& aDst){
        
        std::string lFloat = "";
        size_t lPos = 0;
        std::string lRet = aSrc;
        
        do {
            
            
            lFloat = find_float(lRet,lPos);
            
            
            if(!lFloat.empty()){
                lPos = lRet.find(lFloat,lPos);
            } else {
                lPos = std::string::npos;
            }
            
            //std::cout << lFloat << " : " << lPos << endl;
            
            if(lPos != std::string::npos && glch::is_float(lFloat)){
                
                std::string lRand = glch::random_string(10);
                aDst[lRand] = lFloat;
                lRet = lRet.replace(lPos,lFloat.size(),lRand);
                lPos += lRand.size();
            } else {
                lPos += lFloat.size();
            }
            
        } while(lPos != std::string::npos && lPos < lRet.size());
        
        
        
//        for(std::map<glch::AString, glch::AString>::iterator it = aDst.begin(); it != aDst.end(); it++){
//            size_t lFind = lRet.find(it->second);
//            
//            lRet = lRet.replace(lFind,it->second.size(),it->first);
//        }
        
        return lRet;
    }
    
    std::string find_float(glch::AString aEquation, size_t aPosition){

        size_t lExp = aEquation.find("e",aPosition);
        std::string lNumbs = "0123456789.-+";
        std::string lSymbols = "!&|=><+-*/%^:?[(";
        size_t lCheckI = lExp;
        size_t lCheckJ = lExp;
        size_t i = lExp;
        size_t j = lExp+1;
        
        if(lExp == aEquation.size()-1 || lExp == 0){
            return "e";
        }
        
        if(lExp != std::string::npos){

            //lCheckI = lNumbs.find(aEquation.substr(i,1));
            lCheckJ = lNumbs.find(aEquation.substr(j,1));

            //std::cout << lExp << " : " << lCheckI << " : " << lCheckJ << endl;
            
            
            while(lCheckI != std::string::npos && i>0){
                i--;
                std::string lSearchVal = aEquation.substr(i,1);
                lCheckI = lNumbs.find(lSearchVal);

                if(lSymbols.find(lSearchVal) == std::string::npos && lNumbs.find(lSearchVal) == std::string::npos){
                    return "e";
                }
                
                //std::cout << "i: " << i << " || " << lCheckI << " || " << aEquation.substr(i,1) << endl;
                
                if(aEquation.substr(i,1) == "+" || aEquation.substr(i,1) == "-"){

                    if(i!=0){
                        //cout << "Find Symbol: " << lSymbols.find(aEquation.substr(i-1,1)) << " : " << aEquation.substr(i-1,1) << endl;
                        
                        
                        if(lSymbols.find(aEquation.substr(i-1,1)) == std::string::npos){
                            i++;
                        }
                        
                    }
                    
                    break;
                    
                }
            }

            if(lCheckJ != std::string::npos){
                lNumbs = lNumbs.substr(0,11);
                j++;
                lCheckJ = lNumbs.find(aEquation.substr(j,1));

                //std::cout << "j: " << j << " || " << lCheckJ << endl;
                
                while(lCheckJ != std::string::npos && j<aEquation.size()){
                    j++;
                    std::string lSearchVal = aEquation.substr(j,1);
                    lCheckJ = lNumbs.find(lSearchVal);

                    if(lSymbols.find(lSearchVal) == std::string::npos && lNumbs.find(lSearchVal) == std::string::npos){
                        return "e";
                    }
                    
                }

                
            }

            //std::cout << i << " : " << j << endl;
//            if(j == aEquation.size()){
//                j--;
//            }
//                
            std::string lRet = aEquation.substr(i,j-i);
            
            //if(glch::is_float(lRet)){
            return aEquation.substr(i,j-i);
            //}
            
        }

        //std::cout << i << " : " << j << endl;
        
        return "";
    }
    
    std::vector<std::string> split_equation(glch::AString aEquation){
        
        
        std::map<glch::AString,glch::AString> lDst;
        std::string lNewEqn = replace_floats(aEquation,lDst);
        
        
        std::vector<std::string> lSymbols = glch::AString("!,&,|,=,>,<,+,-,*,/,%,^,(,),:,?,[,]").to_vector<string>(",");
        std::vector<std::string> lSplits = glch::split_string(lNewEqn,lSymbols);
        std::vector<std::string> lRet;
        
        for(size_t i = 0; i < lSplits.size(); i++){
            
            //std::cout << "Splits: " << lSplits.at(i) << endl;
            
            if(lDst.find(lSplits.at(i)) != lDst.end()){
                lRet.push_back(lDst[lSplits.at(i)]);
            } else {
                lRet.push_back(lSplits.at(i));
            }
            
        }
        
        return lRet;
    }
    
    Node::Node(const Node& orig){
        vKey = orig.vKey;
        vLeft = orig.vLeft;
        vRight = orig.vRight;
        vParent = orig.vParent;
        vUID = orig.vUID;
        
    }
    
    Node::Node(){
        vKey = "NULL";
        vUID = glch::random_string(10);
    }
    
    Node::Node(string aKey){
        vKey = aKey;
        vUID = glch::random_string(10);
    }
    
    Node::~Node(){
        delete_tree();
    }
    
    void Node::delete_tree(){
        
        if(!vLeft.is_null()){
            vLeft->delete_tree();
        }
        
        if(!vRight.is_null()){
            vRight->delete_tree();
        }
        
        vLeft.clear();
        vRight.clear();
        
    }
    
    void Node::print(){
        
        system_out_println("\""+ vUID + "\" [label=\"" + vKey + "\"]");
        
        if(vParent.is_null()){
            //System.out.println(vKey);
        } else {
            system_out_println("\"" + vParent->vUID + "\"->\"" + vUID + "\"");
        }
        
        if(!vLeft.is_null()){
            vLeft->print();
        }
        
        if(!vRight.is_null()){
            vRight->print();
        }
        
    }
    
    BinaryTree::BinaryTree(string aKey){
        vRoot = SPNode(new Node(aKey));
    }
    
    BinaryTree::BinaryTree(){
        vRoot = SPNode(new Node());
    }
    
    BinaryTree::~BinaryTree(){
        //delete vRoot;
        //vRoot->delete_tree();
        
    }
    
    BinaryTree::BinaryTree(const BinaryTree& orig){
        vRoot = orig.vRoot;
    }
    
    void BinaryTree::print(){
        if(vRoot){
            system_out_println("digraph G {");
            vRoot->print();
            system_out_println("}");
        } else {
            cout << "No tree to print\n";
        }
        
    }
    
    
    
    Tuple::Tuple(){
        first = 0;
        second = 0;
    }

    Tuple::Tuple(long first, long second){
        Tuple::first = first;
        Tuple::second = second;
    }

    Tuple::Tuple(long first, long second, string name){
        Tuple::first = first;
        Tuple::second = second;
        Tuple::name = name;
    }
    
    Tuple::Tuple(const Tuple& orig) : first(orig.first), second(orig.second), name(orig.name){}

    bool Tuple::operator ==(const Tuple& RHS) const {
        return first==RHS.first&&second==RHS.second;
    }

    bool Tuple::operator<(const Tuple& RHS) const {
        
        return (first*1000+second)<(RHS.first*1000+RHS.second);
    }
    
    
    
    
    
    Connections::Connections(){
        vConnections.resize(0,0);
    }

    Connections::Connections(const Connections& orig) : vConnections(orig.vConnections),
                                                 vRowNames(orig.vRowNames),
                                                 vColNames(orig.vColNames),
                                                 vStateMap(orig.vStateMap),
                                                 vTerminalMap(orig.vTerminalMap),
                                                 vStartRule(orig.vStartRule){

    }

    void Connections::push_statemap(Tuple aTuple, long aState){
        vector<long>& lStates = vStateMap[aTuple];
        if(std::find(lStates.begin(),lStates.end(),aState) == lStates.end()){
            lStates.push_back(aState);
        }

    }

    void Connections::push_terminals(string aKey, long aState){
        vector<long>& lStates = vTerminalMap[aKey];
        if(std::find(lStates.begin(),lStates.end(),aState) == lStates.end()){
            lStates.push_back(aState);
        }

    }

    bool Connections::has_row(string aValue){
        //return (vRows.find(aValue)!=vRows.end());
        return glch::value_in_vector(vRowNames,aValue);
    }

    bool Connections::has_col(string aValue){
        //return (vCols.find(aValue)!=vCols.end());
        return glch::value_in_vector(vColNames,aValue);
    }

    void Connections::check_row_col_index(string aRow, string aCol){

        if(!has_row(aRow) && !has_col(aCol)){
            //vRows[aRow] = vConnections.rows;
            //vCols[aCol] = vConnections.cols;
            vRowNames.push_back(aRow);
            vColNames.push_back(aCol);
            vConnections.resize_clone(vConnections.rows+1,vConnections.cols+1);

        }

    }

    int Connections::row_index(string aValue){

        if(!has_row(aValue)){
            //vRows[aValue] = vConnections.rows;
            vConnections.resize_clone(vConnections.rows+1,vConnections.cols);
            vRowNames.push_back(aValue);
        }

        //return vRows[aValue];
        return glch::index_of(vRowNames,aValue);
    }

    int Connections::col_index(string aValue){

        if(!has_col(aValue)){
            //vCols[aValue] = vConnections.cols;
            vConnections.resize_clone(vConnections.rows,vConnections.cols+1);
            vColNames.push_back(aValue);
        }

        //return vCols[aValue];
        return glch::index_of(vColNames,aValue);
    }

    void Connections::add_variable(string aVariable){
        col_index(aVariable);
    }

    void Connections::add_rule(string aLHS, string aRHS){

        check_row_col_index(aRHS,aLHS);

        int lRow = row_index(aRHS);
        int lCol = col_index(aLHS);

        vConnections.at(lCol,lRow) = 1;

        if(vStartRule.empty()){
            vStartRule = aLHS;
        }

    }


    
    
    /**
     * Finds the columns where the symbol gets it's inputs from
     * @return Returns the column names.
     */
    vector<string> Connections::get_symbol_inputs(string aRow){

        vector<string> lRet;

        //cout << "get_symbol_inputs" << endl;
        
        if(std::find(vRowNames.begin(),vRowNames.end(),aRow) == vRowNames.end()){
            return lRet;
        }
        
        int lRow = row_index(aRow);
        //cout << lRow << " : " << aRow << endl;
        
        
        
        for(size_t i = 0; i < vConnections.cols; i++){
            if(vConnections.at(i,lRow) == 1){
                lRet.push_back( vColNames.at(i) );
                
                //cout << vColNames.at(i) << endl;
                
                vector<string> lTemp = get_symbol_inputs(vColNames.at(i));
                
                lRet.insert(lRet.end(),lTemp.begin(),lTemp.end());
                
                
            }
        }

        //cout << "get_symbol_inputs_end" << endl;
        return lRet;
    }

    string Connections::find_lineage(string aKey, string aSearch){
        
        if(vLineage.find(aKey) != vLineage.end()){
            
            std::vector<Lineage>& lLine = vLineage[aKey];
            
            for(size_t i = 0; i < lLine.size(); i++){
                if(lLine.at(i).name == aSearch){
                    return lLine.at(i).parent;
                }
            }
            
        }
        
        return "";
        
    }

    Connections::Lineage Connections::get_lineage(string aKey, string aSearch){
        
        if(vLineage.find(aKey) != vLineage.end()){
            
            std::vector<Lineage>& lLine = vLineage[aKey];
            
            for(size_t i = 0; i < lLine.size(); i++){
                if(lLine.at(i).name == aSearch){
                    return lLine.at(i);
                }
            }
            
        }
        
        Lineage lRet;
        return lRet;
        
    }
    
    void Connections::gen_lineage_list(string aKey, string aSearch, vector< SPNode >& aNodeList){
        
        //cout << "Gen Lineage... " << aKey << " : " << aSearch << endl;
        
         SPNode  lRet = SPNode(new Node(aKey));
        //lRet->vLeft = aChild;
        
        
        
        Lineage lLine = get_lineage(aKey,aSearch);
        
        if(aKey == aSearch){
            return;
        }
        
        aNodeList.push_back(lRet);
        
        if(!lLine.name.empty()){
            gen_lineage_list(lLine.parent,aSearch,aNodeList);
            
        }
        
        
        //return lRet;
    }
    
    vector< SPNode > Connections::gen_lineage(string aKey, string aSearch){
        vector< SPNode > lNodeList;
        
        gen_lineage_list(aKey,aSearch,lNodeList);
        
        if(lNodeList.size() == 0){
            lNodeList.push_back(SPNode(new Node(aKey)) );
            return lNodeList;
            //return new Node(aKey);
        }
        
        if(lNodeList.size() == 1){
            return lNodeList;
        }
        
        for(size_t i = 0; i < lNodeList.size()-1; i++){
            lNodeList.at(i)->vParent = lNodeList.at(i+1);
            lNodeList.at(i+1)->vLeft = lNodeList.at(i);
            
            //cout << "P/C: " << lNodeList.at(i+1)->vKey << " | " << lNodeList.at(i+1)->vUID << " : " << lNodeList.at(i)->vKey << " | " << lNodeList.at(i)->vUID << endl;
        }
        
        //cout << lNodeList.back()->vKey << " : " << lNodeList.back()->vUID << endl;
        
        return lNodeList;
        
        
    }
    
    void Connections::print_lineage(){
        
        cout << "=====================================================\n";
        cout << "Printing Lineage: \n";
        for(std::map<string,vector<Lineage> >::iterator it = vLineage.begin(); it != vLineage.end(); it++){
            std::cout << it->first << ":\n";
            std::vector<Lineage>& lTemp = it->second;
            for(size_t i = 0; i < lTemp.size(); i++){
                cout << "(" << lTemp.at(i).name << ", " << lTemp.at(i).orig << ", " << lTemp.at(i).parent << ")\n";
            }
            
        }
        cout << "=====================================================\n";
    }
    
    void Connections::map_lineage(){
        
        for(size_t i = 0; i < vRowNames.size(); i++){
            std::vector<string> lSplits = glch::split_string(vRowNames.at(i)," ");

            if(lSplits.size() == 1){
                
                vector<string> lTempOrig;
                vector<string> lTempDstName;
                vector<string> lTempDstParent;
                get_symbol_inputs_parent(vRowNames.at(i),"",lTempOrig,lTempDstName,lTempDstParent);
                
                for(size_t j = 0; j < lTempDstName.size(); j++){
                    Lineage lTemp;
                    lTemp.name = lTempDstName.at(j);
                    lTemp.orig = lTempOrig.at(j);
                    lTemp.parent = lTempDstParent.at(j);
                    
                    vLineage[vRowNames.at(i)].push_back(lTemp);
                }
            }
            

        }
        
    }
    
    
    /**
     * Finds the columns where the symbol gets it's inputs from
     * @return Returns the column names.
     */
    void Connections::get_symbol_inputs_parent(string aRow, string aParent, vector<string>& aOrig, vector<string>& aDstName, vector<string>& aDstParent){

        //vector<string> lRet;

        //cout << "get_symbol_inputs" << endl;
        
        if(std::find(vRowNames.begin(),vRowNames.end(),aRow) == vRowNames.end()){
            return;
        }
        
        int lRow = row_index(aRow);
        //cout << lRow << " : " << aRow << endl;
        
        bool lPushOrig = false;
        string lParent = aParent;
        
        if(aOrig.size() == 0){
            lPushOrig = true;
        }
        
        for(size_t i = 0; i < vConnections.cols; i++){
            if(vConnections.at(i,lRow) == 1){
                //lRet.push_back( vColNames.at(i) );
                
                //cout << vColNames.at(i) << endl;
                
                if(lPushOrig){
                    aOrig.push_back(vColNames.at(i));
                    lParent = vColNames.at(i);
                } else {
                    aOrig.push_back(aRow);
                }
                
                aDstName.push_back(vColNames.at(i));
                aDstParent.push_back(lParent);
                
                get_symbol_inputs_parent(vColNames.at(i),lParent,aOrig,aDstName,aDstParent);
                
                //lRet.insert(lRet.end(),lTemp.begin(),lTemp.end());
                
                
            }
        }

        //cout << "get_symbol_inputs_end" << endl;
        return;
    }
    
    /**
     * Finds the rows where the symbol outputs to (if it is a Variable)
     * @param aCol
     * @return
     */
    vector<string> Connections::get_symbol_outputs(string aCol){

        vector<string> lRet;
        int lCol = col_index(aCol);

        for(size_t i = 0; i < vConnections.rows; i++){
            if(vConnections.at(lCol,i) == 1){
                lRet.push_back( vRowNames.at(i) );
            }
        }

        return lRet;
    }
    

    
    
    void Connections::map_inputs(){

        vStateMap.clear();
        vTerminalMap.clear();

        //cout << "=============================================\n";
        //cout << "Mapping inputs...\n";

        for(vector<string>::iterator itr = vRowNames.begin(); itr != vRowNames.end(); itr++){

            std::vector<string> lSplits = glch::split_string(*itr," ");
            //cout << "Splits:" << endl;
            //glch::print_vect(lSplits);
            //cout << endl;

            if(lSplits.size() > 1){
                Tuple lPair;
                lPair.first = col_index(lSplits.at(0));
                lPair.second = col_index(lSplits.at(1));

                //cout << lPair.first << " : " << lPair.second << endl;

                vector<string> lInputs = get_symbol_inputs((*itr));

                for(vector<string>::iterator itc = lInputs.begin(); itc != lInputs.end(); itc++){
                    int lColSrc = col_index((*itc));

                    push_statemap(lPair,lColSrc);
                    //vStateMap[lPair].push_back(lColSrc);

                    //cout << "pushing back: " << lColSrc << endl;
                }



            } else {

//                if(std::find(vColNames.begin(),vColNames.end(),*itr) != vColNames.end()){
//                    Tuple lPair;
//                    lPair.first = col_index(lSplits.at(0));
//                    lPair.second = -1;
//
//                    vector<string> lInputs = get_symbol_inputs((*itr));
//
//                    for(vector<string>::iterator itc = lInputs.begin(); itc != lInputs.end(); itc++){
//                        int lColSrc = col_index((*itc));
//
//                        push_statemap(lPair,lColSrc);
//
//                    }
//                } //else {
                
                    vector<string> lInputs = get_symbol_inputs((*itr));

                    //cout << "Pushing terminals: " << lInputs.size() << endl;
                    for(vector<string>::iterator itc = lInputs.begin(); itc != lInputs.end(); itc++){
                        int lColSrc = col_index((*itc));

                        push_terminals((*itc),lColSrc);
                        //vTerminalMap[*itc].push_back(lColSrc);

                        //cout << (*itc) << " : " << lColSrc << endl;

                        vector<string> lLayerInputs = get_symbol_inputs((*itc));
                        for(vector<string>::iterator itk = lLayerInputs.begin(); itk != lLayerInputs.end(); itk++){
                            int lColLayerSrc = col_index((*itk));
                            push_terminals((*itk),lColLayerSrc);
                            
                            //cout << (*itk) << " : " << lColSrc << endl;
                        }
                        
                    }
                
                //}
            }
        }

        //std::cout << "Printing..." << endl;
        //std::map<Tuple, vector<long> > vStateMap;
        //std::map<string, vector<long> > vTerminalMap;

//        cout << "====================================" << endl;
//        cout << "Printing StateMap\n";
//        for(std::map<Tuple, vector<long> >::iterator it = vStateMap.begin();
//            it != vStateMap.end();
//            it++){

//            cout << (*it).first.first << " : " << (*it).first.second << endl;

//            glch::print_vect((*it).second);
//            cout << endl;
//        }

//        cout << "====================================" << endl;

//        cout << "Printing Terminals\n";
//        for(std::map<string, vector<long> >::iterator it = vTerminalMap.begin();
//            it != vTerminalMap.end();
//            it++){

//            cout << (*it).first << " : " << endl;

//            glch::print_vect((*it).second);
//            cout << endl;
//        }

//        cout << "====================================" << endl;
//        cout << "Mapping inputs end...\n";

    }

    void Connections::print_maps(){
        
        cout << "====================================" << endl;
        cout << "Printing StateMap\n";
        for(std::map<Tuple, vector<long> >::iterator it = vStateMap.begin();
            it != vStateMap.end();
            it++){

            cout << (*it).first.first << " : " << (*it).first.second << endl;

            glch::print_vect((*it).second);
            cout << endl << endl;
        }

        cout << "====================================" << endl;

        cout << "Printing Terminals\n";
        for(std::map<string, vector<long> >::iterator it = vTerminalMap.begin();
            it != vTerminalMap.end();
            it++){

            cout << (*it).first << " : " << endl;

            glch::print_vect((*it).second);
            cout << endl << endl;
        }
        
    }
    
    


    /**
     * Finds the columns where the symbol gets it's inputs from and clears the value.
     * @return Returns the column names.
     */
    void Connections::clear_symbol_inputs(string aRow){

        int lRow = row_index(aRow);

        for(size_t i = 0; i < vConnections.cols; i++){
            if(vConnections.at(i,lRow) == 1){
                vConnections.at(i,lRow) = 0;
            }
        }

    }

    bool Connections::has_connection(string aRowName, string aColName){
        return(vConnections.at(col_index(aColName),row_index(aRowName)) == 1);
    }

    void Connections::set_connection(string aRowName, string aColName, int aVal){
        vConnections.at(col_index(aColName),row_index(aRowName)) = aVal;
    }

    void Connections::print(int aColWidth){

        system_out_print(" ");
        for(size_t c = 0; c < vColNames.size(); c++){
            system_out_print(vColNames.at(c)+",");
        }
        system_out_print("\n");

        for(size_t r = 0; r < vRowNames.size(); r++){
            string itj = vRowNames.at(r);
            system_out_print(itj+",");

            for(size_t c = 0; c < vColNames.size(); c++){
                string iti = vColNames.at(c);

                if(has_connection(itj,iti)){
                    system_out_print("1,");
                } else {
                    system_out_print(",");
                }
            }

            system_out_print("\n");
        }

        system_out_print("\n");
    }

    vector<string> Connections::generate_terminals(){
        set<string> lTerminals;// = new Treeset<>();
        vector<string> lRet;// = new vector<>();

        for(size_t i = 0; i < vRowNames.size(); i++){

            glch::AStringList lRules = glch::AString(vRowNames.at(i)).split(" ");

            for(size_t j = 0; j < lRules.size(); j++){
                string lRule = lRules.at(i);
                if(glch::value_in_vector(vColNames,lRule)){
                    lTerminals.insert(lRules.at(i));
                }

            }

        }

        lRet.insert(lRet.begin(),lTerminals.begin(),lTerminals.end());
        return lRet;
    }



    vector<string> Connections::generate_grammar(){

        vector<string> lRet;

        for(size_t i = 0; i < vRowNames.size(); i++){

            for(size_t j = 0; j < vColNames.size(); j++){

                if(vConnections.at(j,i) == 1){
                    lRet.push_back(vColNames.at(j) + " -> " + vRowNames.at(i));
                }


            }
        }

        return lRet;
    }
    
    
    Trace::Trace(){}

    Trace::Trace(const Trace& orig) :
        vRuleName(orig.vRuleName),
        vTerminalName(orig.vTerminalName),
        vRule(orig.vRule),
        vFirstRule(orig.vFirstRule),
        vSecondRule(orig.vSecondRule),
        vFirstPos(orig.vFirstPos),
        vSecondPos(orig.vSecondPos) {

    }

    bool Trace::operator==(const Trace& rhs){
        
        bool lMatch = true;
        
        lMatch &= (vRule == rhs.vRule);
        
        if(vFirstRule != -1){
            lMatch &= (vFirstRule == rhs.vFirstRule);
            lMatch &= (vFirstPos == rhs.vFirstPos);
        }
        
        if(vSecondRule != -1){
            lMatch &= (vSecondRule == rhs.vSecondRule);
            lMatch &= (vSecondPos == rhs.vSecondPos);
        }
        

        
        return lMatch;
    }
    
    Trace& Trace::operator=(const Trace& orig){

        vRuleName = (orig.vRuleName);
        vTerminalName = (orig.vTerminalName);
        vRule = (orig.vRule);
        vFirstRule = (orig.vFirstRule);
        vSecondRule = (orig.vSecondRule);
        vFirstPos = (orig.vFirstPos);
        vSecondPos = (orig.vSecondPos);

        return *this;
    }


    std::string Trace::to_string(){
        
        std::string lRet;
        
        if(vFirstRule == -1){
            lRet = glch::AString("[%1 | %2]").arg(vRule)
                .arg(vTerminalName);
            
        } else {
            lRet = glch::AString("[%1 | %2:(%3,%4) -- %5:(%6,%7)]").arg(vRule)
                .arg(vFirstRule)
                .arg(vFirstPos.x)
                .arg(vFirstPos.y)
                .arg(vSecondRule)
                .arg(vSecondPos.x)
                .arg(vSecondPos.y);
        }
        


        return lRet;
    }
    
    
    

    TraceList::TraceList(const TraceList& orig) {

        vColStart = orig.vColStart;
        vConnections = orig.vConnections;

        vDataNew = orig.vDataNew;
        vDiagStartC = orig.vDiagStartC;
        vDiagStartR = orig.vDiagStartR;
        vDim = orig.vDim;
        vRowStart = orig.vRowStart;

    }

    BinaryTree TraceList::construct_single_tree(){
        BinaryTree lTree;
        
        vector<Trace>& lTraceList = vDataNew.at(Point(0,0));
        
        bool lSetMin = true;
        int lMin = 0;
        long lIndex = -1;
        
        
        for(size_t i = 0; i < lTraceList.size(); i++){
            
            //cout << lTraceList.at(i).to_string() << endl;
            
            if(lTraceList.at(i).vRuleName == vConnections.vStartRule  ){
                if(lSetMin){
                    
                    lMin = lTraceList.at(i).vFirstRule+lTraceList.at(i).vSecondRule;
                    lSetMin = false;
                    lIndex = i;
                } else {
                    
                    if(lTraceList.at(i).vFirstRule+lTraceList.at(i).vSecondRule < lMin){
                        lMin = lTraceList.at(i).vFirstRule+lTraceList.at(i).vSecondRule;
                        lIndex = i;
                    }
                    
                }
                
               // break;

            }
        }
        
        if(lIndex != -1){
            Trace& lTrace = lTraceList.at(lIndex);
            string& lName = lTraceList.at(lIndex).vRuleName;
            lTree.vRoot = SPNode(new Node(lName));
            lTree.vRoot->vParent.clear();

            //lTree.vRoot->vLeft = new Node(lTraceList.at(lIndex).vTerminalName);
            lTree.vRoot->vRight.clear();
            
            vector< SPNode > lList = vConnections.gen_lineage(lTraceList.at(lIndex).vTerminalName,lTree.vRoot->vKey);
            
            //for(size_t i = 0; i < lList.size(); i++){
            //    std::cout << lList.at(i)->vKey << endl;
            //}
            
            lTree.vRoot->vLeft = lList.back();
            lTree.vRoot->vLeft->vParent = lTree.vRoot;
            
            
            
            //fix_tree(lTree.vRoot);
        }

        return lTree;
        
    }
    
    BinaryTree TraceList::construct_tree_new(){
        BinaryTree lTree;

        
        vector<Trace>& lTraceList = vDataNew.at(Point(0,vDim-1));
        long lIndex = -1;

        //cout << "Constructing tree...\n";

        bool lSetMin = true;
        int lMin = 0;
        int lSum = 0;
        
        
        for(size_t i = 0; i < lTraceList.size(); i++){
            
            //cout << lTraceList.at(i).to_string() << endl;
            
            if(lTraceList.at(i).vRuleName == vConnections.vStartRule  ){
                int lTempMin = std::min(lTraceList.at(i).vFirstRule,lTraceList.at(i).vSecondRule);
                int lTempSum = lTraceList.at(i).vFirstRule+lTraceList.at(i).vSecondRule;


                if(lSetMin){

                    lSum = lTempSum;
                    lMin = lTempMin;
                    lSetMin = false;
                    lIndex = i;
                } else {


                    if(lTempMin==lMin && lTempSum < lSum){
                        lIndex = i;
                    } else if(lTempMin < lMin){
                        lMin = lTempMin;
                        lSum = lTempSum;
                        lIndex = i;
                    }

                }
                
               // break;

            }
        }

        //cout << "Found: " << lIndex << endl;
        
        if(lIndex != -1){
            Trace& lTrace = lTraceList.at(lIndex);
            string& lName = lTraceList.at(lIndex).vRuleName;
            lTree.vRoot = SPNode(new Node(lName));
            lTree.vRoot->vParent.clear();

            lTree.vRoot->vLeft = get_children_new(lTrace.vFirstRule,lTrace.vFirstPos, lTree.vRoot);
            lTree.vRoot->vRight = get_children_new(lTrace.vSecondRule,lTrace.vSecondPos, lTree.vRoot);


        }

        return lTree;
    }

    bool TraceList::fix_tree( SPNode  aNode){
        
        bool lRet = false;
        
        if(!aNode->vLeft.is_null()){
            string lLeftLine = vConnections.find_lineage(aNode->vLeft->vKey,aNode->vKey);
            if(!lLeftLine.empty()){
                aNode->vKey = lLeftLine;
                lRet = true;
            }
            
            fix_tree(aNode->vLeft);
        }
        
        if(!aNode->vRight.is_null()){
            string lRightLine = vConnections.find_lineage(aNode->vRight->vKey,aNode->vKey);
            if(!lRightLine.empty()){
                aNode->vKey = lRightLine;
                lRet = true;
            }
            
            fix_tree(aNode->vRight);
        }
        
        
        return false;
        
    }
    
    
     SPNode  TraceList::get_children_new(long aRule, const glch::Point& aIndex,  SPNode  aParent){

        vector<Trace>& lTraceList = vDataNew.at(aIndex);
        Trace lTrace;
        
        bool lSetMin = true;
        int lMin = 0;
        int lSum = 0;
        long lIndex = -1;
        
        for(size_t i = 0; i < lTraceList.size(); i++){
            //cout << lTraceList.at(i).to_string() << endl;;
            
            int lTempMin = std::min(lTraceList.at(i).vFirstRule,lTraceList.at(i).vSecondRule);
            int lTempSum = lTraceList.at(i).vFirstRule+lTraceList.at(i).vSecondRule;
                
                
            if(lSetMin){

                lSum = lTempSum;
                lMin = lTempMin;
                lSetMin = false;
                lIndex = i;
            } else {

                
                if(lTempMin==lMin && lTempSum < lSum){
                    lIndex = i;
                } else if(lTempMin < lMin){
                    lMin = lTempMin;
                    lSum = lTempSum;
                    lIndex = i;
                }

            }
            
//            if(lTraceList.at(i).vRule == aRule){
//                lTrace = lTraceList.at(i);
//                break;
//            }
        }
        
        if(lIndex != -1){
            lTrace = lTraceList.at(lIndex);
            
        } else {
            return SPNode(new Node("NULL"));
            
        }
        
        //cout << "========================\n";
        
        
        string lName = lTrace.vRuleName;

        //cout << "Printing Trace...\n";
        //cout << lTrace.to_string() << endl;
        
        //glch::AString lFirst = vConnections.vColNames.at(aRule);
        //vector< SPNode > lList = vConnections.gen_lineage(lFirst,aParent->vKey);
        // SPNode  lRet;
        
        //cout << "Figuringout..." << aParent->vKey << " : " << lFirst << " : " << lName << endl;
        
         SPNode  lRet = SPNode(new Node(lName));
        lRet->vParent = aParent;
        
        
//        cout << "F/B: " << lList.size() << " :: " << lList.front()->vKey << " : " << lList.back()->vKey << " : " << endl;
//        
//        if(lList.size() > 1){
//            lRet = lList.front();
//            
//            lList.back()->vParent = aParent;
//            //aParent->vLeft = lList.back();
//        
//            //return lRet;
//            
//        } else {
//            lRet = new Node(lName);
//            lRet->vParent = aParent;
//        }
        
        string lLine = vConnections.find_lineage(lName,lRet->vParent->vKey);
        if(!lLine.empty()){
            lRet->vParent->vKey = lLine;
        }
        
        if(lTrace.vFirstRule == -1 && lTrace.vSecondRule == -1){
            
            string lFirstRule = lTrace.vTerminalName;
            //string lLine = vConnections.find_lineage(lFirstRule,lName);
            //if(!lLine.empty()){
            //    lRet->vKey = lLine;
            //}
            
            
            lRet->vLeft = SPNode(new Node(lFirstRule));
            lRet->vLeft->vParent = lRet;
            
            lRet->vRight.clear();

            ////vector< SPNode > lChildList = vConnections.gen_lineage(lFirstRule,lName);
            ////lRet->vLeft = lChildList.back();
            ////lRet->vLeft->vParent = lRet;
            //lRet->vLeft->vKey = lFirstRule;
            //lChildList.front()->vKey = lFirstRule;
            
        } else if (lTrace.vFirstRule == -1) {
            
            
            lRet->vLeft = get_children_new(lTrace.vFirstRule,lTrace.vFirstPos, lRet);
            lRet->vRight.clear();
            
        } else {
            //glch::AString lFirst = vConnections.vColNames.at(lTrace.vFirstRule);
            //lRet->vLeft = vConnections.gen_lineage(lFirst,lName);
            

            //vector< SPNode > lList = vConnections.gen_lineage(lFirst,aParent->vKey);
            // SPNode  lRet = lList.front();
            //lList.back()->vParent = aParent;
            //aParent->vLeft = lList.back();
            
        
            lRet->vLeft = get_children_new(lTrace.vFirstRule,lTrace.vFirstPos, lRet);
            lRet->vRight = get_children_new(lTrace.vSecondRule,lTrace.vSecondPos, lRet);
        }

//        if(lList.size() > 1){
//            lRet = lList.back();
//            
//        }
        
        
        return lRet;
    }


    void TraceList::print(){

        std::cout << "Printing Tracelist:\n";
        std::cout << "Dim: " << vDim << std::endl;

        for(int i = 0; i < vDim; i++){
            for(int j = 0; j < vDim; j++){

                cout << "(" << j << "," << i << "): " << endl;
                vector<Trace>& lTraceList = vDataNew.at(Point(j,i));
                for(size_t k = 0; k < lTraceList.size(); k++){
                    std::cout << lTraceList.at(k).to_string();
                    
                    if(k != lTraceList.size()-1){
                        std::cout << " || ";
                    }
                    
                }

                system_out_print("\n");
            }
         
            system_out_print("\n");
        }
        
        system_out_print("\n");

    }



    vector<long> TraceList::get_terminal_map(string aTerminal){

        vector<long> lRet;
        vector<string> lInputs = vConnections.get_symbol_inputs(aTerminal);

        //cout << "Pushing terminals: " << lInputs.size() << endl;
        for(vector<string>::iterator itc = lInputs.begin(); itc != lInputs.end(); itc++){
            int lColSrc = vConnections.col_index((*itc));

            if(std::find(lRet.begin(), lRet.end(), lColSrc) == lRet.end()){
                lRet.push_back(lColSrc);
            }

            
            
            
            //cout << (*itc) << " : " << lColSrc << endl;

        }

        return lRet;
    }

    TraceList::TraceList(std::vector<string> aInput, const Connections& aConnections){
        vConnections = aConnections;
        vDim = aInput.size();
        vDataNew.resize(aInput.size(),aInput.size());
        

        //cout << "Constructing TraceList:\n";

        for(size_t i = 0; i < aInput.size(); i++){
            vector<Trace> lStartList;

            string lInsert = aInput.at(i);
            //vector<string> lConn = vConnections.get_symbol_inputs(lInsert);
            vector<long> lInputs = get_terminal_map(lInsert);//vConnections.vTerminalMap[lInsert];
            vector<string> lSymbols = vConnections.get_symbol_inputs(lInsert);
            //vector<long> lInputs = vConnections.vTerminalMap[lInsert];


            cout << "Inserting terminals for: " << lInsert << " : \n";
            glch::print_vect(lInputs);
            cout << endl;

            for(size_t j = 0; j < lInputs.size(); j++){
                cout << j << " : " << lInputs.size() << endl;

                Trace lTemp;
                lTemp.vRuleName = lSymbols.at(j);
                lTemp.vTerminalName = lInsert;
                lTemp.vRule = lInputs.at(j);
                lTemp.vFirstRule = -1;
                lTemp.vSecondRule = -1;
                lTemp.vFirstPos = glch::Point(-1,-1);
                lTemp.vSecondPos = glch::Point(-1,-1);

                if(std::find(lStartList.begin(), lStartList.end(), lTemp) == lStartList.end()){
                    lStartList.push_back(lTemp);

                    cout << "Adding:\n";
                    cout << lTemp.vRuleName << " : " << lTemp.vTerminalName << endl;
                    cout << lTemp.to_string() << endl;
                    
                   
                }// else {
                    //cout << "Skipping:\n";
                    //cout << lTemp.to_string() << endl;
                            
                //}
            }

            vDataNew.at(Point(i,0) ) = lStartList;

            //cout << "=======================\n";
            //cout << "Printing...\n";
            //print();
            //cout << endl;
        }

        //cout << "=======================\n";
        //cout << "Final Printing...\n";
        //print();
        //cout << endl;
        //cout << "Constructing TraceList End\n";

    }
    
    TraceList::TraceList(string aInput, const Connections& aConnections){
        vConnections = aConnections;
        vDim = aInput.length();
        vDataNew.resize(aInput.length(),aInput.length());
        

        //cout << "Constructing TraceList:\n";

        for(size_t i = 0; i < aInput.length(); i++){
            vector<Trace> lStartList;

            string lInsert = aInput.substr(i,1);
            //vector<string> lConn = vConnections.get_symbol_inputs(lInsert);
            vector<long> lInputs = get_terminal_map(lInsert);//vConnections.vTerminalMap[lInsert];
            vector<string> lSymbols = vConnections.get_symbol_inputs(lInsert);
            //vector<long> lInputs = vConnections.vTerminalMap[lInsert];


            //cout << "Inserting terminals for: " << lInsert << " : \n";
            //glch::print_vect(lInputs);
            //cout << endl;

            for(size_t j = 0; j < lInputs.size(); j++){
                //cout << j << " : " << lInputs.size() << endl;

                Trace lTemp;
                lTemp.vRuleName = lSymbols.at(j);
                lTemp.vTerminalName = lInsert;
                lTemp.vRule = lInputs.at(j);
                lTemp.vFirstRule = -1;
                lTemp.vSecondRule = -1;
                lTemp.vFirstPos = glch::Point(-1,-1);
                lTemp.vSecondPos = glch::Point(-1,-1);

                if(std::find(lStartList.begin(), lStartList.end(), lTemp) == lStartList.end()){
                    lStartList.push_back(lTemp);

                    //cout << "Adding:\n";
                    //cout << lTemp.vRuleName << " : " << lTemp.vTerminalName << endl;
                    //cout << lTemp.to_string() << endl;
                    
                   
                }// else {
                    //cout << "Skipping:\n";
                    //cout << lTemp.to_string() << endl;
                            
                //}
            }

            vDataNew.at(Point(i,0) ) = lStartList;

            //cout << "=======================\n";
            //cout << "Printing...\n";
            //print();
            //cout << endl;
        }

        //cout << "=======================\n";
        //cout << "Final Printing...\n";
        //print();
        //cout << endl;
        //cout << "Constructing TraceList End\n";

    }


    vector<Trace> TraceList::build_pairs_new(Point aFirst, Point aSecond, vector<Trace>& aDst){

        vector<Trace>& lFirst = vDataNew.at(aFirst);
        vector<Trace>& lSecond = vDataNew.at(aSecond);
        //vector<TraceNew> lRet;

        //cout << lFirst.size() << " : " << lSecond.size() << endl;

        //cout << "Building pairs:\n";

        
        
        
        for(size_t i = 0; i < lFirst.size(); i++ ){
            long lFirstRule = lFirst.at(i).vRule;
            //cout << i << " : " << lFirstRule << " : " << lFirst.size() << endl;
            
            
            for(size_t j = 0; j < lSecond.size(); j++){
                long lSecondRule = lSecond.at(j).vRule;
                vector<long>& lRules = vConnections.vStateMap[Tuple(lFirstRule,lSecondRule)];
                
                
                
                //cout << "Rules for: " << endl;
                //cout << lFirstRule << " : " << lSecondRule << endl;

                for(size_t k = 0; k < lRules.size(); k++){

                    Trace lTemp;
                    lTemp.vRuleName = vConnections.vColNames.at(lRules.at(k));
                    lTemp.vRule = lRules.at(k);
                    lTemp.vFirstRule = lFirstRule;
                    lTemp.vSecondRule = lSecondRule;
                    lTemp.vFirstPos = aFirst;
                    lTemp.vSecondPos = aSecond;

                    if(std::find(aDst.begin(),aDst.end(),lTemp) == aDst.end()){
                        aDst.push_back(lTemp);

                        //cout << "Pushing pair...\n";
                        //cout << lTemp.to_string() << endl;
                    }
                }


                
                
            }

        }

        //cout << "End Building Pairs\n";

        return aDst;

    }

    
    
    vector<Trace> TraceList::build_singles(Point aFirst, vector<Trace>& aDst){

        vector<Trace>& lFirst = vDataNew.at(aFirst);

        
        for(size_t i = 0; i < lFirst.size(); i++ ){
            long lFirstRule = lFirst.at(i).vRule;
            //cout << i << " : " << lFirstRule << " : " << lFirst.size() << endl;
            
            
                long lSecondRule = -1;
                vector<long>& lRules = vConnections.vStateMap[Tuple(lFirstRule,lSecondRule)];
                
                
                
                //cout << "Rules for: " << endl;
                //cout << lFirstRule << " : " << lSecondRule << endl;

                for(size_t k = 0; k < lRules.size(); k++){

                    Trace lTemp;
                    lTemp.vRuleName = vConnections.vColNames.at(lRules.at(k));
                    lTemp.vRule = lRules.at(k);
                    lTemp.vFirstRule = lFirstRule;
                    lTemp.vSecondRule = lSecondRule;
                    lTemp.vFirstPos = aFirst;
                    lTemp.vSecondPos = Point(-1,-1);

                    if(std::find(aDst.begin(),aDst.end(),lTemp) == aDst.end()){
                        aDst.push_back(lTemp);

                        //cout << "Pushing pair...\n";
                        //cout << lTemp.to_string() << endl;
                    }
                }

        }

        //cout << "End Building Pairs\n";

        return aDst;

    }    
    
    void TraceList::find_branches_new(int aRow, int aCol){

        int lDiagStartC = aRow+aCol;
        int lDiagStartR = 0;
        int lRowStart = aRow-1;
        int lColStart = aCol;

        //build_pairs_new(Point(aCol,aRow-1),Point(aCol+1,aRow-1),vDataNew.at(Point(aCol,aRow)) );
        
        while(lDiagStartC != aCol){

            //vConnections.vStateMap[Tuple(aRow,)];
            Point lFirst = Point(lColStart,lRowStart);
            Point lSecond = Point(lDiagStartC, lDiagStartR);

            //cout << lDiagStartC << " : " << lDiagStartR << " : " << lRowStart << " : " << lColStart << endl;
            //lFirst.print();
            //cout << endl;
            //lSecond.print();
            //cout << endl;

            //vDataNew.at(Point(aCol,aRow)) 
            build_pairs_new(lFirst,lSecond,vDataNew.at(Point(aCol,aRow)) );
            //build_singles(lFirst,vDataNew.at(Point(aCol,aRow)));
            
            lRowStart--;
            lDiagStartC--;
            lDiagStartR++;

        }

    }



    void TraceList::scan_row(int aRow){

        for(int i = 0; i < vDim-aRow; i++){
            find_branches_new(aRow, i);
        }

    }

    void TraceList::scan_rows(){

        for(int i = 1; i < vDim; i++){
            scan_row(i);
        }

    }

    Parser::Parser(){
        vConnections = Connections();

    }
    
    Parser::Parser(const Parser& orig){
        vConnections = orig.vConnections;
    }
        
    void Parser::add_variable(string aVariable){
        vConnections.add_variable(aVariable);
    }
    
    void Parser::add_rule(string aLHS, string aRHS){
        vConnections.add_rule(aLHS,aRHS);

    }
    
    vector<string> Parser::get_symbol_inputs(string aRow){
        return vConnections.get_symbol_inputs(aRow);
    }
    
    vector<string> Parser::get_symbol_outputs(string aCol){
        return vConnections.get_symbol_outputs(aCol);
    }
    
    void Parser::clear_symbol_inputs(string aRow){
        vConnections.clear_symbol_inputs(aRow);
    }
    
    void Parser::print_cols(){
        
        for(size_t i = 0; i < vConnections.vColNames.size(); i++){
            
            cout << i << ": " << vConnections.vColNames.at(i) << endl;
            
        }
        
    }
    
    void Parser::print_rules(){
        vector<string> lRules = generate_grammar();
        cout << "Printing rules\n";
        system_out_println("Start Rule: " + vConnections.vStartRule);
        
        
        for(size_t i = 0; i < lRules.size(); i++){
            system_out_println(lRules.at(i));
            
        }

    }
    
    vector<string> Parser::generate_terminals(){
        return vConnections.generate_terminals();
    }
    
    vector<string> Parser::generate_grammar(){
        return vConnections.generate_grammar();
    }
    
    void Parser::map_inputs(){
        vConnections.map_inputs();
        vConnections.map_lineage();
        
        vConnections.print_lineage();
        
        
        vConnections.print_maps();
    }

    Parser Parser::copy(){
        
        Parser lRet;
        lRet.vConnections = vConnections;
        
        return lRet;
    }
    
    void Parser::clear(){
        vConnections = Connections();
    }
    
    
    BinaryTree Parser::build_parse_matrix(string aInput){
        
        //system_out_println("BPM: " + aInput);
        
        BinaryTree lRet;
        TraceList lTrace = TraceList(aInput, vConnections);

        //cout << "===================================="<<endl;
        //cout << "===================================="<<endl;
        //cout << "===================================="<<endl;
        //cout << "Scanning rows" << endl;
        

        lTrace.scan_rows();

        //cout << "Finished Scanning rows" << endl;

        //vConnections.print();
        
        //cout << "====================================" << endl;
        //system_out_print("\n");
        //lTrace.print();
        //system_out_print("\n");
        //cout << "====================================" << endl;
        
        if(aInput.size() > 1){
            lRet = lTrace.construct_tree_new();
        } else {
            lRet = lTrace.construct_single_tree();
        }
        
//        lTrace.fix_tree(lRet.vRoot);
//        while(lTrace.fix_tree(lRet.vRoot)){
//            std::cout << "Fixing tree..." << endl;
//        }
        
        return lRet;
    }

    BinaryTree Parser::build_parse_matrix(std::vector<string> aInput){
        
        //system_out_println("BPM: " + aInput);
        
        BinaryTree lRet;
        TraceList lTrace = TraceList(aInput, vConnections);

        //cout << "===================================="<<endl;
        //cout << "===================================="<<endl;
        //cout << "===================================="<<endl;
        //cout << "Scanning rows" << endl;
        

        lTrace.scan_rows();

        //cout << "Finished Scanning rows" << endl;

        //vConnections.print();
        
        //cout << "====================================" << endl;
        //system_out_print("\n");
        //lTrace.print();
        //system_out_print("\n");
        //cout << "====================================" << endl;
        
        if(aInput.size() > 1){
            lRet = lTrace.construct_tree_new();
        } else {
            lRet = lTrace.construct_single_tree();
        }
        
//        lTrace.fix_tree(lRet.vRoot);
//        while(lTrace.fix_tree(lRet.vRoot)){
//            std::cout << "Fixing tree..." << endl;
//        }
        
        return lRet;
    }

    LenPair::LenPair(){
    
    }
    
    LenPair::LenPair(glch::AString aFirst){
        first = aFirst;
        second = "0";
    }
    
    LenPair::LenPair(glch::AString aFirst, glch::AString aSecond){
        first = aFirst;
        second = aSecond;
        
    }
    
    LenPair::LenPair(const glch::LenPair& orig) : first(orig.first), second(orig.second){
        
    }
    
    glch::LenPair& LenPair::operator=(const glch::LenPair& orig){
        first = orig.first;
        second = orig.second;
        
        return *this;
    }
    
    bool LenPair::operator>(const glch::LenPair& aComp) const{

        if(first.length() == aComp.first.length()){
            
            if(first.compare(aComp.first) < 0){
                return true;
            }
            
            return false;
        }
        
        return first.length()<aComp.first.length();
    }
    
    bool LenPair::operator<(const glch::LenPair& aComp) const{
        
        if(first.length() == aComp.first.length()){
            
            if(first.compare(aComp.first) < 0){
                return true;
            }
            
            return false;
        }
        
        return first.length()>aComp.first.length();
    }
    
    bool LenPair::operator==(const glch::LenPair& aComp){
        return first==aComp.first;
    }
    
    bool LenPair::operator==(const glch::AString& aComp){
        return first==aComp;
    }    
    
    void LenPair::print(std::string aDelim){
        cout << glch::AString("(%1|%2)").arg(first).arg(second) << aDelim;
    }
    
    
    
    
    LenList::LenList(){
        
        insert("UNKNOWN","NULL");
        
    }
    
    LenList::LenList(const LenList& orig) : data(orig.data){
        
    }
    
    size_t LenList::size(){
        return data.size();
    }

    std::vector<LenPair>::iterator LenList::begin(){
        return data.begin();
    }

    std::vector<LenPair>::iterator LenList::end(){
        return data.end();
    }

    void LenList::erase(glch::AString aKey){
        erase(LenPair(aKey));
    }

    void LenList::erase(LenPair aInput){
        std::vector<LenPair>::iterator it = find(aInput);
        data.erase(it);
    }
    
    std::vector<LenPair>::iterator LenList::insert_sorted( LenPair aInput ){
        
        std::vector<LenPair>::iterator it = std::upper_bound( data.begin(), data.end(), aInput );
        return data.insert(it, aInput);
    }
    
    std::vector<LenPair>::iterator LenList::find(glch::AString aKey){
        return find(LenPair(aKey));
    }
    
    std::vector<LenPair>::iterator LenList::find(LenPair aInput){
        return std::find(data.begin(), data.end(), aInput);
    }
    
    std::vector<LenPair>::iterator LenList::insert(LenPair aInput){
        
        std::vector<LenPair>::iterator it = find(aInput);
        
        if(it == data.end()){
            if(glch::is_decimal(aInput.first)){
            //if(glch::is_float(aInput.first)){
                return find("UNKNOWN");
            }
            
            return insert_sorted(aInput);
            
        } else {
            (*it).second = aInput.second;
            
        }
        
        return it;
    }
    
    std::vector<LenPair>::iterator LenList::insert(glch::AString aKey, glch::AString aVal){       
        return insert(LenPair(aKey,aVal));
    }
    

    LenPair& LenList::at(size_t aKey){
        return data.at(aKey);
    }

    
    
    bool LenList::contains(glch::AString aKey){

        if(find(aKey) == data.end()){
            return false;
        }
        
        return true;
    }
    
    void LenList::print(){
        
        glch::print_vect_fn(data,"\n");
        
    }

    
    
    
    
    
    void Evaluator::load_data(glch::AString aFileData){

        glch::AStringList lInput = aFileData.split("\n");

        for(size_t i = 0; i < lInput.size()-1; i++){
            glch::AStringList lRules = lInput.at(i).split(" ");
            vParser.add_variable(lRules.at(0));
        }

        for(size_t i = 0; i < lInput.size()-1; i++){

            glch::AStringList lRules = lInput.at(i).split(" ");
            glch::AString lRule = "";
            if(lRules.size() == 3){
                lRule = glch::AString("%1 %2").arg(lRules.at(1)).arg(lRules.at(2));
            } else {
                lRule = lRules.at(1);
            }

            vParser.add_rule(lRules.at(0),lRule);

        }

        vParser.map_inputs();

    }

    void Evaluator::load_file(glch::AString aFileName){
        
        glch::AString lFile = glch::load_text_file(aFileName);
        glch::AStringList lInput = lFile.split("\n");

        for(size_t i = 0; i < lInput.size()-1; i++){
            glch::AStringList lRules = lInput.at(i).split(" ");
            vParser.add_variable(lRules.at(0));
        }

        for(size_t i = 0; i < lInput.size()-1; i++){

            glch::AStringList lRules = lInput.at(i).split(" ");
            glch::AString lRule = "";
            if(lRules.size() == 3){
                lRule = glch::AString("%1 %2").arg(lRules.at(1)).arg(lRules.at(2));
            } else {
                lRule = lRules.at(1);
            }

            vParser.add_rule(lRules.at(0),lRule);

        }

        vParser.map_inputs();
        
    }
    
    
    glch::AStringList Evaluator::fn_equal(glch::AString v1, glch::AString v2, AliasList& aData){
        double lV1 = aData.at_cp(v1).toDouble();
        double lV2 = aData.at_cp(v2).toDouble();
        glch::AStringList lRet;
        lRet.push_back(lV1==lV2);
        return lRet;
        //return v1.toDouble()==v2.toDouble();
    }
    
    glch::AStringList Evaluator::fn_equal(glch::AStringList& aArgs, AliasList& aData){
        return fn_equal(aArgs.at(0),aArgs.at(1),aData);
    }
    
    glch::AStringList Evaluator::fn_gt(glch::AString v1, glch::AString v2, AliasList& aData){
        double lV1 = aData.at_cp(v1).toDouble();
        double lV2 = aData.at_cp(v2).toDouble();
        glch::AStringList lRet;
        lRet.push_back(lV1>lV2);
        return lRet;
        //return v1.toDouble()>v2.toDouble();
    }
    
    glch::AStringList Evaluator::fn_gt(glch::AStringList& aArgs, AliasList& aData){
        return fn_gt(aArgs.at(0),aArgs.at(1),aData);
    }
    
    glch::AStringList Evaluator::fn_lt(glch::AString v1, glch::AString v2, AliasList& aData){
        double lV1 = aData.at_cp(v1).toDouble();
        double lV2 = aData.at_cp(v2).toDouble();
        glch::AStringList lRet;
        lRet.push_back(lV1<lV2);
        return lRet;
        //return v1.toDouble()<v2.toDouble();
    }
    
    glch::AStringList Evaluator::fn_lt(glch::AStringList& aArgs, AliasList& aData){
        return fn_lt(aArgs.at(0),aArgs.at(1),aData);
    }
    
    glch::AStringList Evaluator::fn_gte(glch::AString v1, glch::AString v2, AliasList& aData){
        double lV1 = aData.at_cp(v1).toDouble();
        double lV2 = aData.at_cp(v2).toDouble();
        glch::AStringList lRet;
        lRet.push_back(lV1>=lV2);
        return lRet;
        //return v1.toDouble()>=v2.toDouble();
    }
    
    glch::AStringList Evaluator::fn_gte(glch::AStringList& aArgs, AliasList& aData){
        return fn_gte(aArgs.at(0),aArgs.at(1),aData);
    }
    
    glch::AStringList Evaluator::fn_lte(glch::AString v1, glch::AString v2, AliasList& aData){
        double lV1 = aData.at_cp(v1).toDouble();
        double lV2 = aData.at_cp(v2).toDouble();
        glch::AStringList lRet;
        lRet.push_back(lV1<=lV2);
        return lRet;
        //return v1.toDouble()<=v2.toDouble();
    }
    
    glch::AStringList Evaluator::fn_lte(glch::AStringList& aArgs, AliasList& aData){
        return fn_lte(aArgs.at(0),aArgs.at(1),aData);
    }
    
    glch::AStringList Evaluator::fn_and(glch::AString v1, glch::AString v2, AliasList& aData){
        bool lV1 = aData.at_cp(v1).toBool();
        bool lV2 = aData.at_cp(v2).toBool();
        glch::AStringList lRet;
        lRet.push_back(lV1&&lV2);
        return lRet;
        //return v1.toBool()&&v2.toBool();
    }
    
    glch::AStringList Evaluator::fn_and(glch::AStringList& aArgs, AliasList& aData){
        return fn_and(aArgs.at(0),aArgs.at(1),aData);
    }
    
    glch::AStringList Evaluator::fn_or(glch::AString v1, glch::AString v2, AliasList& aData){
        bool lV1 = aData.at_cp(v1).toBool();
        bool lV2 = aData.at_cp(v2).toBool();
        glch::AStringList lRet;
        lRet.push_back(lV1||lV2);
        return lRet;
        //return v1.toBool()||v2.toBool();
    }
    
    glch::AStringList Evaluator::fn_or(glch::AStringList& aArgs, AliasList& aData){
        return fn_or(aArgs.at(0),aArgs.at(1),aData);
    }
    
    glch::AStringList Evaluator::fn_pow(glch::AString v1, glch::AString v2, AliasList& aData){
        double lV1 = aData.at_cp(v1).toDouble();
        double lV2 = aData.at_cp(v2).toDouble();
        glch::AStringList lRet;
        lRet.push_back(pow(lV1,lV2));
        return lRet;
        //return pow(v1.toDouble(),v2.toDouble());
    }
    
    glch::AStringList Evaluator::fn_pow(glch::AStringList& aArgs, AliasList& aData){
        return fn_pow(aArgs.at(0),aArgs.at(1),aData);
    }
    
    glch::AStringList Evaluator::fn_mul(glch::AString v1, glch::AString v2, AliasList& aData){
        double lV1 = aData.at_cp(v1).toDouble();
        double lV2 = aData.at_cp(v2).toDouble();
        glch::AStringList lRet;
        lRet.push_back(lV1*lV2);
        return lRet;
        //return v1.toDouble()*v2.toDouble();
    }
    
    glch::AStringList Evaluator::fn_mul(glch::AStringList& aArgs, AliasList& aData){
        return fn_mul(aArgs.at(0),aArgs.at(1),aData);
    }
    
    glch::AStringList Evaluator::fn_div(glch::AString v1, glch::AString v2, AliasList& aData){
        //cout << "Dividing..." << endl;
        //cout << v1.toDouble()/v2.toDouble() << endl;
        double lV1 = aData.at_cp(v1).toDouble();
        double lV2 = aData.at_cp(v2).toDouble();
        glch::AStringList lRet;
        lRet.push_back(lV1/lV2);
        return lRet;
        //return v1.toDouble()/v2.toDouble();
    }
    
    glch::AStringList Evaluator::fn_div(glch::AStringList& aArgs, AliasList& aData){
        return fn_div(aArgs.at(0),aArgs.at(1),aData);
    }
    
    glch::AStringList Evaluator::fn_mod(glch::AString v1, glch::AString v2, AliasList& aData){
        long lV1 = aData.at_cp(v1).toLong();
        long lV2 = aData.at_cp(v2).toLong();
        glch::AStringList lRet;
        lRet.push_back(lV1%lV2);
        return lRet;
        //return v1.toLong()%v2.toLong();
    }
    
    glch::AStringList Evaluator::fn_mod(glch::AStringList& aArgs, AliasList& aData){
        return fn_mod(aArgs.at(0),aArgs.at(1),aData);
    }
    
    glch::AStringList Evaluator::fn_add(glch::AString v1, glch::AString v2, AliasList& aData){
        double lV1 = aData.at_cp(v1).toDouble();
        double lV2 = aData.at_cp(v2).toDouble();
        
        //cout << "ADD Vars: " << v1 << " : " << v2 << endl;
        //cout << "ADD: " << lV1 << " : " << lV2 << endl;
        glch::AStringList lRet;
        lRet.push_back(lV1+lV2);
        return lRet;
        //return v1.toDouble()+v2.toDouble();
    }
    
    glch::AStringList Evaluator::fn_add(glch::AStringList& aArgs, AliasList& aData){
        return fn_add(aArgs.at(0),aArgs.at(1),aData);
    }
    
    glch::AStringList Evaluator::fn_sub(glch::AString v1, glch::AString v2, AliasList& aData){
        double lV1 = aData.at_cp(v1).toDouble();
        double lV2 = aData.at_cp(v2).toDouble();
        glch::AStringList lRet;
        lRet.push_back(lV1-lV2);
        return lRet;
        //return v1.toDouble()-v2.toDouble();
    }
    
    glch::AStringList Evaluator::fn_sub(glch::AStringList& aArgs, AliasList& aData){
        return fn_sub(aArgs.at(0),aArgs.at(1),aData);
    }
    
    glch::AStringList Evaluator::fn_assign(glch::AString v1, glch::AString v2, AliasList& aData){
        double lV2 = aData.at_cp(v2).toDouble();
        
        aData[v1]=lV2;
        glch::AStringList lRet;
        lRet.push_back(aData[v1]);
        
        return aData[v1];
    }
    
    glch::AStringList Evaluator::fn_assign(glch::AStringList& aArgs, AliasList& aData){
        return fn_assign(aArgs.at(0),aArgs.at(1),aData);
    }
    
    
    glch::AStringList Evaluator::fn_tern(glch::AStringList& aArgs, AliasList& aData){
        bool lV0 = aData.at_cp(aArgs.at(0)).toBool();
        double lV1 = aData.at_cp(aArgs.at(1)).toDouble();
        double lV2 = aData.at_cp(aArgs.at(2)).toDouble();
        
        glch::AStringList lRet;
        
        //cout << "Tern..." << endl;
       // cout << lV0 << " : " << lV1 << " : " << lV2 << endl;
        
        if(lV0){
            lRet.push_back(lV1);
        } else {
            lRet.push_back(lV2);
        }
        
        return lRet;
    }
    
    glch::AStringList Evaluator::fn_colon(glch::AStringList& aArgs, AliasList& aData){
        //cout << "Colon:" << endl;
        //glch::print_vect(aArgs);
        return aArgs;
    }
    
    Evaluator::Evaluator(){
        vCommands["<AND>"] = &Evaluator::fn_and;
        vCommands["<OR>"] = &Evaluator::fn_or;
        vCommands["<EQUAL>"] = &Evaluator::fn_equal;
        vCommands["<GT>"] = &Evaluator::fn_gt;
        vCommands["<LT>"] = &Evaluator::fn_lt;
        vCommands["<LTE>"] = &Evaluator::fn_lte;
        vCommands["<GTE>"] = &Evaluator::fn_gte;
        vCommands["<ADD>"] = &Evaluator::fn_add;
        vCommands["<SUB>"] = &Evaluator::fn_sub;
        vCommands["<MUL>"] = &Evaluator::fn_mul;
        vCommands["<DIV>"] = &Evaluator::fn_div;
        vCommands["<MOD>"] = &Evaluator::fn_mod;
        vCommands["<POW>"] = &Evaluator::fn_pow;
        vCommands["<LARROW>"] = &Evaluator::fn_assign;
        vCommands["<QM>"] = &Evaluator::fn_tern;
        vCommands["<COLON>"] = &Evaluator::fn_colon;
    }
    
    glch::AString Evaluator::evaluate(glch::AString aInput){
        glch::BinaryTree lTree = vParser.build_parse_matrix(aInput);
        return evaluate(lTree.vRoot);
    }

    glch::AString Evaluator::evaluate(glch::AString aInput, glch::Parser& aParser, AliasList& aData){

        glch::BinaryTree lTree = aParser.build_parse_matrix(aInput);
        //lTree.print();
        return evaluate(lTree.vRoot,aData);

    }

    glch::AString Evaluator::evaluate(glch::AString aInput, AliasList& aData){

        
        //cout << "Evaluating..." << endl;
        //cout << aInput << endl;
        //vParser.vConnections.print();
        //vParser.vConnections.print_maps();
        
        //aData.print();
        
        //cout << "Evaluate: " << endl;

        //cout << "Time: " << time(NULL) << endl;
        glch::BinaryTree lTree = vParser.build_parse_matrix(aInput);
        //cout << "Time: " << time(NULL) << endl;
        //auto end = std::chrono::steady_clock::now();
        //auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        lTree.print();
        glch::AString lRet = evaluate(lTree.vRoot,aData);
        //std::cout << lRet << endl;
        //cout << "Time: " << time(NULL) << endl;
        return aData.at_cp(lRet);

    }

    glch::AString Evaluator::evaluate( SPNode  aNode){
        AliasList lData;
        return evaluate(aNode, lData);
    }
    
    glch::AString Evaluator::evaluate( SPNode  aNode, AliasList& aData){
        
        glch::AString lRet = evaluate_top(aNode, aData).at(0);
        //cout << "Output: " << lRet << endl;
        return lRet;
        
    }
    
    glch::AStringList Evaluator::evaluate_top( SPNode  aNode, AliasList& aData){
        
        glch::AString lLeft;
        glch::AStringList lRight;
        glch::AStringList lTemp;
        //cout << "Eval top\n";
        
        //cout << aNode->vLeft->vKey << " : " << aNode->vRight->vKey << endl;
        

        if(aNode->vLeft->vKey == "<FLOAT>" && aNode->vRight.is_null()){
            //cout << "Checking..." << 2781 << endl;
            return evaluate_float(aNode);
        }
        
        if(aNode->vLeft->vKey == "<DIGIT>" && aNode->vRight.is_null()){
            //cout << "Checking..." << 2785 << endl;
            return evaluate_float(aNode);
        }
        
        if(aNode->vLeft->vKey == "<IDENT>" && aNode->vRight.is_null()){
            //cout << "Checking..." << 2791 << endl;
            return evaluate_ident(aNode);
        }
        
        if(aNode->vLeft->vKey == "<IDENT>" && aNode->vRight->vKey == "<FACT>"){
            //cout << "Checking..." << 2791 << endl;
            return evaluate_ident(aNode);
        }
        
        if(aNode->vLeft->vKey == "<IDENT>" && aNode->vRight->vKey == "<ARRAYINT>"){
            glch::AString lArrayIdent = evaluate_ident(aNode->vLeft);
            glch::AString lIndex = evaluate_top(aNode->vRight,aData).at(0);
            glch::AStringList lRet;
            lRet.push_back(glch::AString("%1[%2]").arg(lArrayIdent).arg(lIndex));
            return lRet;
            
        }
        
//        if(aNode->vRight->vKey == "<TERNEXPR>"){
//            glch::AStringList lRet;
//            lRight = evaluate_top(aNode->vLeft, aData);
//            lRight = evaluate_top(aNode->vRight, aData);
//        }
        
//        if(aNode->vLeft->vKey == "<QM>" && aNode->vRight->vKey == "<TERNOPTS>"){
//            lRight = evaluate_right(aNode->vRight, aData);
//        }
        
        if(aNode->vLeft->vKey == "<FLOAT>" && aNode->vRight->vKey == "<FLOAT>"){
            return evaluate_float(aNode);
        }
        
        if(aNode->vLeft->vKey == "<DIGIT>" && aNode->vRight->vKey == "<DIGIT>"){
            return evaluate_float(aNode);
        }
        
        if(aNode->vLeft->vKey == "<DIGIT>" && aNode->vRight->vKey == "<FLOAT>"){
            return evaluate_float(aNode);
        }
        
        if(aNode->vLeft->vKey == "<FLOAT>" && aNode->vRight->vKey == "<DIGIT>"){
            return evaluate_float(aNode);
        }
        
        if(aNode->vLeft->vKey == "<IDENT>" && aNode->vRight->vKey == "<IDENT>"){
            return evaluate_ident(aNode);
        }
        
        if(!aNode->vLeft.is_null()){
            //cout << "Eval top left: " << aNode->vLeft->vKey << endl;
            
            
            if(aNode->vLeft->vKey == "<FLOAT>"){
                //cout << "Eval Float:\n";
                lLeft = evaluate_float(aNode->vLeft);
                //cout << lLeft << endl;
            }

            if(aNode->vLeft->vKey == "<DIGIT>"){
                //cout << "Checking..." << 2825 << endl;
                //cout << "Eval Digit:\n";
                lLeft = evaluate_float(aNode->vLeft);
                //cout << lLeft << endl;
            }

            if(aNode->vLeft->vKey == "<IDENT>"){
                lLeft = evaluate_ident(aNode->vLeft);
                //lLeft = aData[lLeft];
            }        

            if(aNode->vLeft->vKey == "<ARRAY>"){
                lTemp = evaluate_top(aNode->vLeft, aData);
            }
            
            
            if(aNode->vLeft->vKey == "<TERNARY>"){
                lTemp = evaluate_top(aNode->vLeft, aData);
            }
            
            if(aNode->vLeft->vKey == "<LOGICAL>"){
                lTemp = evaluate_top(aNode->vLeft, aData);
            }

            if(aNode->vLeft->vKey == "<CONDITIONAL>"){
                lTemp = evaluate_top(aNode->vLeft, aData);
            }

            if(aNode->vLeft->vKey == "<EXPR>"){
                lTemp = evaluate_top(aNode->vLeft, aData);
            }

            if(aNode->vLeft->vKey == "<TERM>"){
                lTemp = evaluate_top(aNode->vLeft, aData);
            }

            if(aNode->vLeft->vKey == "<EXPO>"){
                lTemp = evaluate_top(aNode->vLeft, aData);
            }

            if(aNode->vLeft->vKey == "<FACT>"){
                lTemp = evaluate_top(aNode->vLeft, aData);
            }

            if(aNode->vLeft->vKey == "<LEFT>"){
                lTemp = evaluate_top(aNode->vRight, aData);
            }

            if(aNode->vLeft->vKey == "<LEFTB>"){
                lTemp = evaluate_top(aNode->vRight, aData);
            }
            
            if(aNode->vLeft->vKey == "<NOT>"){
                lLeft = evaluate_top(aNode->vRight, aData).at(0);
                lLeft = !lLeft.toBool();
            }
            
            
            if(lTemp.size() > 0){
                //cout << "Printing Temp: \n";
                //glch::print_vect(lTemp);
                //cout << endl;
            
                lLeft = lTemp.front();
            }
        }
        
        if(!aNode->vRight.is_null()){
            //cout << "Eval top right: " << aNode->vRight->vKey << endl;
            
            if(aNode->vRight->vKey == "<ARRAY>"){
                lRight = evaluate_top(aNode->vRight, aData);
            }
            
            if(aNode->vRight->vKey == "<LOGICOPERCOND>"){
                lRight = evaluate_right(aNode->vRight, aData);
            }
            
            if(aNode->vRight->vKey == "<TERNEXPR>"){
                
                //lRight.push_back(aNode->vLeft->vKey);
                lRight = evaluate_right(aNode->vRight, aData);
                
            }

            if(aNode->vRight->vKey == "<TERNOPTS>"){
                lRight = evaluate_right(aNode->vRight, aData);
                
                
            }
            
            if(aNode->vRight->vKey == "<COLONLOG>"){
                lRight = evaluate_right(aNode->vRight, aData);
            }
            
            if(aNode->vRight->vKey == "<CONDOPERATOREXPR>"){
                lRight = evaluate_right(aNode->vRight, aData);
            }

            if(aNode->vRight->vKey == "<EXPROPTERM>"){
                lRight = evaluate_right(aNode->vRight, aData);
            }

            if(aNode->vRight->vKey == "<TERMOPEXPO>"){
                //cout << "Eval TERMOPEXPO" << endl;
                lRight = evaluate_right(aNode->vRight, aData);
            }

            if(aNode->vRight->vKey == "<EXPOOPFACT>"){
                lRight = evaluate_right(aNode->vRight, aData);
            }

            if(aNode->vRight->vKey == "<ASIGN>"){
                lRight = evaluate_right(aNode->vRight, aData);
            }
            

            
    //        if(aNode->vRight->vKey == "<FACT>"){
    //            lRight = evaluate_right(aNode->vRight, aData);
    //        }
        
        }
        
        //cout << "Right Size: " << lRight.size() << endl;
        if(lRight.size() >= 2){
            //cout << "Result Eval: " << lLeft << endl;
            //glch::print_vect(lRight);
            //cout << endl;
            std::vector<glch::AString> lArgs;
            lArgs.push_back(lLeft);
            for(size_t i = 1; i < lRight.size(); i++){
                lArgs.push_back(lRight.at(i));
            }
            
            glch::AStringList lRet = ((*this).*vCommands[lRight.at(0)])(lArgs, aData);
            return lRet;
            
        } //else if (lRight.size() == 1) {
            
        //if(lRight.size() == 1){
            //cout << "Right data...";
            //glch::print_vect(lRight);
            //cout << endl;
        //}
        
        //cout << "Result: " << aNode->vKey << " : " << aNode->vLeft->vKey << " : " << lLeft << endl;
        //glch::print_vect(lRight);
        lRight.push_back(lLeft);
        return lRight;
            
        //} else {
            
            
        //}
        
        
        //return lLeft;
    }
    
    glch::AStringList Evaluator::evaluate_right( SPNode  aNode, AliasList& aData){
        
        glch::AString lLeft;
        glch::AStringList lRight;
        glch::AStringList lRet;
        
//        if(aNode->vRight->vKey == "<FLOAT>"){
//            lRight = evaluate_float(aNode->vLeft);
//        }        
//        
//        if(aNode->vRight->vKey == "<DIGIT>"){
//            lRight = evaluate_float(aNode->vLeft);
//        }
        
        //cout << "Eval Right:" << endl;
        //cout << aNode->vLeft->vKey << " : " << aNode->vRight->vKey << endl;
        
        lLeft = aNode->vLeft->vKey;
        //cout << "Right Key:" << aNode->vRight->vKey << endl;
        
        if(aNode->vRight->vKey == "<FLOAT>"){
            //cout << "Eval Float Right:\n";
            glch::AString lTemp = evaluate_float(aNode->vRight);
            //cout << lTemp << endl;
            lRight.push_back(lTemp);
            
        } else if(aNode->vRight->vKey == "<DIGIT>"){
            //cout << "Eval Digit Right:\n";
            glch::AString lTemp = evaluate_float(aNode->vRight);
            //cout << lTemp << endl;
            lRight.push_back(lTemp);
            
        } else if(aNode->vRight->vKey == "<IDENT>"){
            //cout << "Eval Digit Right:\n";
            glch::AString lTemp = evaluate_ident(aNode->vRight);
            //cout << lTemp << endl;
            lRight.push_back(lTemp);
            
        } else {
            lRight = evaluate_top(aNode->vRight, aData);
        }
        
        
        
        //cout << "Right Result: " << endl;
        //glch::print_vect(lRight);
        //cout << endl;
        lRet.push_back(lLeft);
        lRet.insert(lRet.end(),lRight.begin(),lRight.end());
        //glch::print_vect(lRet);
        //cout << endl;
        //cout << "End Right Result..." << endl;
        //lRet.push_back(lRight);
        
        //cout << lLeft << " : " << lRight << endl;
        
        return lRet;
    }
    
    
    
    glch::AString Evaluator::evaluate_float( SPNode  aNode){
        
        if(!aNode->vLeft.is_null() && !aNode->vRight.is_null()){
            return evaluate_float(aNode->vLeft)+evaluate_float(aNode->vRight);
        }
        
        if(!aNode->vLeft.is_null()){
            return evaluate_float(aNode->vLeft);
        }
        
        if(!aNode->vRight.is_null()){
            return evaluate_float(aNode->vRight);
        }
        
        return aNode->vKey;
        
    }
    
    glch::AString Evaluator::evaluate_ident( SPNode  aNode){
        
        if(!aNode->vLeft.is_null() && !aNode->vRight.is_null()){
            return evaluate_ident(aNode->vLeft)+evaluate_ident(aNode->vRight);
        }
        
        if(!aNode->vLeft.is_null()){
            return evaluate_ident(aNode->vLeft);
        }
        
        if(!aNode->vRight.is_null()){
            return evaluate_ident(aNode->vRight);
        }
        
        return aNode->vKey;
        
    }
    
}



#if false


Parser::Parser() {
}

Parser::Parser(const Parser& orig) {
}

Parser::~Parser() {
}

#endif
