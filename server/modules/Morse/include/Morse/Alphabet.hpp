/**
 * @file Alphabet.hpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief Description of morse alphabet in c++ 
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <map>
#include <string>
#include <vector>
namespace Morse {
    /**
     * @brief Unit time correspond to morse dot 
     * 
     */
const int unit_time = 60; // unit time in ms
enum MorseElement {
    DOT = unit_time,
    DASH = 3 * unit_time,
    INTER_ELEM = unit_time, // gap between the dits and dahs within a character
    SHORT_GAP = 3 * unit_time, // between letters
    MEDIUM_GAP = 7 * unit_time // between words
};

/**
 * @brief const std::map containing alphabet in morse with ascii character as key and std::vector containing coresponding traduction
 * 
 */
extern const std::map<char, std::vector<MorseElement>> morseAlphabet;

}