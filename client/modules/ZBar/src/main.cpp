#include "ZBar.hpp"
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{

    // Read image
    Mat im = imread("test.png");

    // Variable for decoded objects
    vector<ZBar::decodedObject> decodedObjects;

    // Find and decode barcodes and QR codes
    ZBar::decode(im, decodedObjects);

    // Display location
    ZBar::addBarcodeLocation(im, decodedObjects);
    imshow("Image", im);
    waitKey(0);

    return EXIT_SUCCESS;
}