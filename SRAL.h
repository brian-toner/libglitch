/* 
 * File:   SRAL.h
 * Author: brian
 *
 * Created on July 5, 2015, 1:13 PM
 */

#ifndef SRAL_H
#define	SRAL_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "stringconversion.h"
#include "StringAddress.h"

namespace glch{

    struct Bracket{
        char varLeft;               //Left bracket symbol
        char varRight;              //Right bracket symbol
    };

    struct BracketTrack{
        size_t varType;                //Bracket type id
        size_t varStart;               //Start position of the bracket in the string
        size_t varEnd;                 //End position of the bracket in the string
        size_t varBranch;
    };

    void string_to_sral(std::string argInput, std::vector<std::string> &argOutVect, std::vector<Bracket> *locBracket = NULL);
    bool has_brackets(std::string argInput, std::vector<Bracket> &argBracket);
    void build_bracket_list(std::vector<Bracket> &argBracketList);
    Bracket bracket(char argLeft, char argRight);
    BracketTrack bracket_track(size_t argType, size_t argStart, size_t argEnd, size_t argBranch);

    void split_brackets(std::string argInput, std::vector<BracketTrack> &argTracker);
    void inject_addresses(std::string argInput, const std::vector<BracketTrack> &argTracker, std::vector<BracketTrack> &argTrackerAdj, std::vector<std::string> &argAddressedStr);

}

#endif	/* SRAL_H */

