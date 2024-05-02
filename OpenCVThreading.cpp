//Usage: g++ OpenCVThreading.cpp -o OpenCVThreading `pkg-config --cflags --libs opencv4`
#include <opecv2/opencv.hpp>
#include <iostream>
#include <sched.h>

int main()
{
  int numThreads = cv::getNumThreads();
  std::cout << "cv::getNumThreads: " << numThreads << std::endl;
  cpu_set_t cpu_set;
  sched_getaffinity(0, sizeof(cpu_set_t), &cpu_set);
  cv::setNumThreads(std::max(1, CPU_COUNT(&cpu_set)-1));
  std::cout << "cv::getNumThreads: " << cv::getNumThreads() << std::endl;  
}
