# OpenCV-Utilities

Programs to check the installation of OpenCV and configuration of GPU's including Optimization checks for the Hardware



# Performance Measurement and Improvement Techniques (OpenCVMeasurePerf.cpp)

1. cv::getCPUTickCount is a function in OpenCV which returns the number of clock-cycles that have passed since the start of the process. It can be used to measure the time elapsed between two parts of the code, which can help to identify the performance bottlenecks in the code. The value returned by this function is implementation-dependent and is typically obtained using the CPU’s time-stamp counter (TSC) register.

2. cv::getTickFrequency() is a function in OpenCV that returns the frequency of the high-resolution performance counter in Hertz (cycles per second). The function is commonly used to calculate the duration of a particular OpenCV operation by counting the number of ticks before and after the operation and then dividing the difference by the frequency to obtain the duration in seconds. 
