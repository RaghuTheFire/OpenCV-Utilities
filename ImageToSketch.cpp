#include <opencv2/opencv.hpp>

int main() 
{
    // Read the image
    cv::Mat image1 = cv::imread("image.jpg");
    std::string window_name = "Actual image";

    // Display the actual image
    cv::imshow(window_name, image1);

    // Convert the image to grayscale
    cv::Mat grey_img;
    cv::cvtColor(image1, grey_img, cv::COLOR_BGR2GRAY);

    // Invert the grayscale image
    cv::Mat invert;
    cv::bitwise_not(grey_img, invert);

    // Apply Gaussian blur to the inverted image
    cv::Mat blur;
    cv::GaussianBlur(invert, blur, cv::Size(21, 21), 0);

    // Invert the blurred image
    cv::Mat invertedblur;
    cv::bitwise_not(blur, invertedblur);

    // Create the sketch image
    cv::Mat sketch;
    cv::divide(grey_img, invertedblur, sketch, 256.0);

    // Save the sketch image
    cv::imwrite("sketch.jpeg", sketch);

    // Read the sketch image
    cv::Mat image = cv::imread("sketch.jpeg");
    window_name = "Sketch image";

    // Display the sketch image
    cv::imshow(window_name, image);
    cv::waitKey(0);

    return 0;
}


