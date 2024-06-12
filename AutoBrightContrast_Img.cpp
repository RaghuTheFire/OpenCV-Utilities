//Automatic contrast and brightness adjustment of a image with OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

// Automatic brightness and contrast optimization with optional histogram clipping
cv::Mat automatic_brightness_and_contrast(const cv::Mat& image, double clip_hist_percent = 1.0) 
{
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Calculate grayscale histogram
    std::vector<float> hist(256, 0.0);
    for (int i = 0; i < gray.rows; i++) 
    {
        for (int j = 0; j < gray.cols; j++) 
        {
            hist[gray.at<uchar>(i, j)]++;
        }
    }

    // Calculate cumulative distribution from the histogram
    std::vector<float> accumulator(256, 0.0);
    accumulator[0] = hist[0];
    for (int i = 1; i < 256; i++) 
    {
        accumulator[i] = accumulator[i - 1] + hist[i];
    }

    // Locate points to clip
    float maximum = accumulator[255];
    float clip_hist_percent_value = clip_hist_percent * (maximum / 100.0) / 2.0;

    // Locate left cut
    int minimum_gray = 0;
    while (accumulator[minimum_gray] < clip_hist_percent_value) 
    {
        minimum_gray++;
    }

    // Locate right cut
    int maximum_gray = 255;
    while (accumulator[maximum_gray] >= (maximum - clip_hist_percent_value)) 
    {
        maximum_gray--;
    }

    // Calculate alpha and beta values
    double alpha = 255.0 / (maximum_gray - minimum_gray);
    double beta = -minimum_gray * alpha;

    cv::Mat auto_result;
    cv::convertScaleAbs(image, auto_result, alpha, beta);
    return auto_result;
}

int main() 
{
    cv::Mat image = cv::imread("image.jpg");
    cv::Mat auto_result = automatic_brightness_and_contrast(image);

    double alpha, beta;
    cv::minMaxLoc(auto_result, nullptr, &beta, nullptr, nullptr, cv::noArray());
    alpha = 255.0 / (beta - (-beta));

    std::cout << "alpha: " << alpha << std::endl;
    std::cout << "beta: " << beta << std::endl;

    cv::imshow("original", image);
    cv::imshow("auto_result", auto_result);
    cv::waitKey();

    return 0;
}
