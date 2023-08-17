#include <opecv2/opencv.hpp>
#include <iostream>
int main()
{
  int64 t1 = cv::getCPUTickCount();
  //Perform Some Opeartion
  int64 t2 = cv::getCPUTickCount();

  double elapsed_time = (t2-t1)/cv::getTickFrequency();
  std::cout<<"Elapsed Time:"<<elapsed_time<<"Seconds."<<std::endl;
  return 0;
}
