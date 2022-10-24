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
#include <cstdlib>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <time.h>
using namespace std;
using namespace cv;

int main(int argc, char const* argv[])
{
    Camera camera(0);
    camera.setFourcc(CV_FOURCC('M', 'J', 'P', 'G'));
#ifdef DEBUG
    camera.changeResolution(Resolution::resolutions.at("1280x720"));
    camera.recordVideo(5, "capture-liv1.avi");
#else
    if (argc == 4) {
        camera.changeResolution(Resolution::resolutions.at(argv[2]));
        camera.recordVideo(atoi(argv[3]), (argv[1]));
    }

#endif
    return 0;
}