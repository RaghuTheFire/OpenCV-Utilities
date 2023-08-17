//Usage: g++ OpenCVOptimize.cpp -o OpenCVOptimize `pkg-config --cflags --libs opencv4`

#include <opecv2/opencv.hpp>
#include <iostream>
int main()
{
   // Read the optimization settings
  bool optimized_flag = cv::useOptimized();
  std::cout<<"Optimized Flag Setting :"<< optimized_flag<< std::endl;

  // Set the optimization to false
  cv::setUseOptimized(false);
  optimized_flag = cv::useOptimized();
  std::cout<<"Optimized Flag after setting false :"<< optimized_flag<< std::endl;
  
  // Set the optimization to true
  cv::setUseOptimized(true);
  optimized_flag = cv::useOptimized();
  std::cout<<"Optimized Flag after setting true :"<< optimized_flag<< std::endl;
  return 0;
}
