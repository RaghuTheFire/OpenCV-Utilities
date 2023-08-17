//Usage: g++ OpenCVConfigtest.cpp.cpp -o OpenCVConfigtest `pkg-config --cflags --libs opencv4`

#include <iostream>
#include <stdio.h>
#include <ctime>
#include <sys/timeb.h>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    cv::setNumThreads(4);
    printf("CPUs: %d, Threads: %d, Use optimizations: %s\n",cv::getNumberOfCPUs(),cv::getNumThreads(),cv::useOptimized() ? "yes" : "no");
    printf("%s\n", cv::getBuildInformation().c_str());
    return 0;
}
