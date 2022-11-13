#pragma once 
namespace Morse{
    const int unit_time = 10;
    enum MorseElement{
        DOT = unit_time,
        DASH = 3*unit_time,
        INTER_ELEM=unit_time, // gap between the dits and dahs within a character
        SHORT_GAP=3*unit_time, // between letters
        MEDIUM_GAP=7*unit_time //between words
    };

    

}