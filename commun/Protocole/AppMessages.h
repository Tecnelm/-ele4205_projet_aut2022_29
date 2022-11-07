#pragma once
#include "stdint.h"

typedef enum AppMsgBit_t{

    ELE4205_DEFAULT = 0x0,
    ELE4205_OK = 0x1,
    ELE4205_QUIT = 0x2,

    ELE4205_RES1 = 0x4,
    ELE4205_RES2 = 0x8,
    ELE4205_RES3 = 0x10,
    ELE4205_RES4 = 0x20,

    ELE4205_PNG = 0x40,
    ELE4205_JPEG = 0x80,
}AppMsgBit_t;

typedef uint32_t AppMsg_t;