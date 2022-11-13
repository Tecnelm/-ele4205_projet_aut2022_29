#include "opencv2/opencv.hpp"
#include <string>
#include <vector>
namespace ZBar {
typedef struct
{
    std::string type;
    std::string data;
    std::vector<cv::Point> location;
} decodedObject;

// Find and decode barcodes and QR codes
void decode(cv::Mat& im, std::vector<decodedObject>& decodedObjects);

// Display barcode and QR code location
void addBarcodeLocation(cv::Mat& im, std::vector<decodedObject>& decodedObjects);

}