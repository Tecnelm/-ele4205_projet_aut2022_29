/**
 * @file Alphabet.cpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief Implementation of the alphabet morse
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Alphabet.hpp"
namespace Morse {


const std::map<char, std::vector<MorseElement>> morseAlphabet {
    
    //Letters
    {'A', {MorseElement::DOT,MorseElement::DASH}},
    {'B', {MorseElement::DASH,MorseElement::DOT,MorseElement::DOT,MorseElement::DOT}},
    {'C', {MorseElement::DASH,MorseElement::DOT,MorseElement::DASH,MorseElement::DOT}},
    {'D', {MorseElement::DASH,MorseElement::DOT,MorseElement::DOT}},
    {'E', {MorseElement::DOT}},
    {'F', {MorseElement::DOT,MorseElement::DOT,MorseElement::DASH,MorseElement::DOT}},
    {'G', {MorseElement::DASH,MorseElement::DASH,MorseElement::DOT}},
    {'H', {MorseElement::DOT,MorseElement::DOT,MorseElement::DOT,MorseElement::DOT}},
    {'I', {MorseElement::DOT,MorseElement::DOT}},
    {'J', {MorseElement::DOT,MorseElement::DASH,MorseElement::DASH,MorseElement::DASH}},
    {'K', {MorseElement::DASH,MorseElement::DOT,MorseElement::DASH}},
    {'L', {MorseElement::DOT,MorseElement::DASH,MorseElement::DOT,MorseElement::DOT}},
    {'M', {MorseElement::DASH,MorseElement::DASH}},
    {'N', {MorseElement::DASH,MorseElement::DOT}},
    {'O', {MorseElement::DASH,MorseElement::DASH,MorseElement::DASH}},
    {'P', {MorseElement::DOT,MorseElement::DASH,MorseElement::DASH,MorseElement::DOT}},
    {'Q', {MorseElement::DASH,MorseElement::DASH,MorseElement::DOT,MorseElement::DASH}},
    {'R', {MorseElement::DOT,MorseElement::DASH,MorseElement::DOT}},
    {'S', {MorseElement::DOT,MorseElement::DOT,MorseElement::DOT}},
    {'T', {MorseElement::DASH}},
    {'U', {MorseElement::DOT,MorseElement::DOT,MorseElement::DASH}},
    {'V', {MorseElement::DOT,MorseElement::DOT,MorseElement::DOT,MorseElement::DASH}},
    {'W', {MorseElement::DOT,MorseElement::DASH,MorseElement::DASH}},
    {'X', {MorseElement::DASH,MorseElement::DOT,MorseElement::DOT,MorseElement::DASH}},
    {'Y', {MorseElement::DASH,MorseElement::DOT,MorseElement::DASH,MorseElement::DASH}},
    {'Z', {MorseElement::DASH,MorseElement::DASH,MorseElement::DOT,MorseElement::DOT}},
    
    //Numbers
    {'1', {MorseElement::DOT,MorseElement::DASH,MorseElement::DASH,MorseElement::DASH,MorseElement::DASH}},
    {'2', {MorseElement::DOT,MorseElement::DOT,MorseElement::DASH,MorseElement::DASH,MorseElement::DASH}},
    {'3', {MorseElement::DOT,MorseElement::DOT,MorseElement::DOT,MorseElement::DASH,MorseElement::DASH}},
    {'4', {MorseElement::DOT,MorseElement::DOT,MorseElement::DOT,MorseElement::DOT,MorseElement::DASH}},
    {'5', {MorseElement::DOT,MorseElement::DOT,MorseElement::DOT,MorseElement::DOT,MorseElement::DOT}},
    {'6', {MorseElement::DASH,MorseElement::DOT,MorseElement::DOT,MorseElement::DOT,MorseElement::DOT}},
    {'7', {MorseElement::DASH,MorseElement::DASH,MorseElement::DOT,MorseElement::DOT,MorseElement::DOT}},
    {'8', {MorseElement::DASH,MorseElement::DASH,MorseElement::DASH,MorseElement::DOT,MorseElement::DOT}},
    {'9', {MorseElement::DASH,MorseElement::DASH,MorseElement::DASH,MorseElement::DASH,MorseElement::DOT}},
    {'0', {MorseElement::DASH,MorseElement::DASH,MorseElement::DASH,MorseElement::DASH,MorseElement::DASH}}, 
    
    //Ponctuation 
    {'.', {MorseElement::DOT,MorseElement::DASH,MorseElement::DOT,MorseElement::DASH,MorseElement::DOT,MorseElement::DASH}}, 
    {',', {MorseElement::DASH,MorseElement::DASH,MorseElement::DOT,MorseElement::DOT,MorseElement::DASH,MorseElement::DASH}}, 
    {'?', {MorseElement::DOT,MorseElement::DOT,MorseElement::DASH,MorseElement::DASH,MorseElement::DOT,MorseElement::DOT}}, 
    {'\'', {MorseElement::DOT,MorseElement::DASH,MorseElement::DASH,MorseElement::DASH,MorseElement::DASH,MorseElement::DOT}}, 
    {'!', {MorseElement::DASH,MorseElement::DOT,MorseElement::DASH,MorseElement::DOT,MorseElement::DASH,MorseElement::DASH}}, 
    {'/', {MorseElement::DASH,MorseElement::DOT,MorseElement::DOT,MorseElement::DASH,MorseElement::DOT}}, 
    {'(', {MorseElement::DASH,MorseElement::DOT,MorseElement::DASH,MorseElement::DASH,MorseElement::DOT}}, 
    {')', {MorseElement::DASH,MorseElement::DOT,MorseElement::DASH,MorseElement::DASH,MorseElement::DOT,MorseElement::DASH}}, 
    {'&', {MorseElement::DOT,MorseElement::DASH,MorseElement::DOT,MorseElement::DOT,MorseElement::DOT}}, 
    {':', {MorseElement::DASH,MorseElement::DASH,MorseElement::DASH,MorseElement::DOT,MorseElement::DOT,MorseElement::DOT}}, 
    {';', {MorseElement::DASH,MorseElement::DOT,MorseElement::DASH,MorseElement::DOT,MorseElement::DASH,MorseElement::DOT}}, 
    {'=', {MorseElement::DASH,MorseElement::DOT,MorseElement::DOT,MorseElement::DOT,MorseElement::DASH}}, 
    {'+', {MorseElement::DOT,MorseElement::DASH,MorseElement::DOT,MorseElement::DASH}}, 
    {'-', {MorseElement::DASH,MorseElement::DOT,MorseElement::DOT,MorseElement::DOT,MorseElement::DOT,MorseElement::DASH}}, 
    {'_', {MorseElement::DOT,MorseElement::DOT,MorseElement::DASH,MorseElement::DASH,MorseElement::DOT,MorseElement::DASH}}, 
    {'\"',{MorseElement::DOT,MorseElement::DASH,MorseElement::DOT,MorseElement::DOT,MorseElement::DASH,MorseElement::DOT}}, 
    {'$', {MorseElement::DOT,MorseElement::DOT,MorseElement::DOT,MorseElement::DASH,MorseElement::DOT,MorseElement::DOT,MorseElement::DASH}}, 
    {'@', {MorseElement::DOT,MorseElement::DASH,MorseElement::DASH,MorseElement::DOT,MorseElement::DASH,MorseElement::DOT}} 
};

} // namespace Morse
