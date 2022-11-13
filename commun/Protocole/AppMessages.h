#pragma once
#include "stdint.h"

typedef enum AppMsgBit_t{

    ELE4205_DEFAULT     = 0,
    ELE4205_OK          = 1<<0,
    ELE4205_QUIT        = 1<<1,
    ELE4205_RES1        = 1<<2,
    ELE4205_RES2        = 1<<3,
    ELE4205_RES3        = 1<<4,
    ELE4205_RES4        = 1<<5,
    ELE4205_PNG         = 1<<6,
    ELE4205_JPEG        = 1<<7,
    ELE4205_ASK_IMAGE   = 1<<8,
    ELE4205_READY       = 1<<9,
    ELE4205_IDOWN       = 1<<10,
    ELE4205_PUSHB       = 1<<11
}AppMsgBit_t;

typedef uint32_t AppMsg_t;