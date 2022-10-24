/* boneCVtiming.cpp
 *
 * Copyright Derek Molloy, School of Electronic Engineering, Dublin City University
 * www.derekmolloy.ie
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that source code redistributions retain this notice.
 *
 * This software is provided AS IS and it comes with no warranties of any type.
 */

#include "Resolution/Resolution.hpp"
#include <Camera/Camera.hpp>
#include <PrimeNumber/PrimeNumber.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <time.h>

using namespace std;
using namespace cv;

int main()
{
    Camera camera;
    // std::cout << main_prime_number() << std::endl;
    //  Resolution::Resolution_t reso {0,0,0};
    //  std::cout << reso;
    std::cout << Resolution::resolutions.find("176x144")->second;
    return 0;
}