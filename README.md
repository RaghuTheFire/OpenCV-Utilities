# OpenCV-Utilities

Programs to check the installation of OpenCV and configuration of GPU's including Optimization checks for the Hardware

# Performance Measurement and Improvement Techniques (OpenCVMeasurePerf.cpp) (OpenCVOptimize.cpp)

1. **cv::getCPUTickCount()** is a function in OpenCV which returns the number of clock-cycles that have passed since the start of the process. It can be used to measure the time elapsed between two parts of the code, which can help to identify the performance bottlenecks in the code. The value returned by this function is implementation-dependent and is typically obtained using the CPU’s time-stamp counter (TSC) register.

2. **cv::getTickFrequency()** is a function in OpenCV that returns the frequency of the high-resolution performance counter in Hertz (cycles per second). The function is commonly used to calculate the duration of a particular OpenCV operation by counting the number of ticks before and after the operation and then dividing the difference by the frequency to obtain the duration in seconds.

3. **cv::useOptimized()** is a function in OpenCV that enables or disables the use of optimized code. By default, the optimized code is enabled. However, if you want to disable it to get more detailed error messages or to debug your code, you can use cv::useOptimized(false).

4. **cv::setUseOptimized()** is a function in the OpenCV library that can be used to enable or disable the usage of optimized functions. By default, the library uses optimized functions for performance. But in some cases, you might want to use the non-optimized version for debugging or testing purposes. In such cases, you can call cv::setUseOptimized(false) to disable the use of optimized functions. After that, all functions that have an optimized version will use the non-optimized version. To re-enable the optimized version, you can call cv::setUseOptimized(true). 

