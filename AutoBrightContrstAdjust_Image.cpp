//https://www.dfstudios.co.uk/articles/programming/image-programming-algorithms/image-processing-algorithms-part-5-contrast-adjustment/
//https://www.dfstudios.co.uk/articles/programming/image-programming-algorithms/image-processing-algorithms-part-4-brightness-adjustment/
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int truncate(int value) 
{
  if (value < 0) 
	{
    return 0;
  } 
  else 
  if (value > 255) 
	{
    return 255;
  } 
  else 
	{
    return value;
  }
}

Vec3b adjustContrast(Vec3b pixel, int contrast) 
{
    int b = pixel[0], g = pixel[1], r = pixel[2];
    double f = (259 * (contrast + 255)) / (255 * (259 - contrast));
    int bNew = truncate(static_cast<int>(f * (b - 128) + 128));
    int gNew = truncate(static_cast<int>(f * (g - 128) + 128));
    int rNew = truncate(static_cast<int>(f * (r - 128) + 128));
    return Vec3b(bNew, gNew, rNew);
}

Vec3b adjustBrightness(Vec3b pixel, int brightness) 
{
    int b = pixel[0], g = pixel[1], r = pixel[2];
    int bNew = truncate(b + brightness);
    int gNew = truncate(g + brightness);
    int rNew = truncate(r + brightness);
    return Vec3b(bNew, gNew, rNew);
}

int main() 
{
    Mat image = imread("image.jpg", IMREAD_COLOR);
    if (image.empty()) 
	  {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    cvtColor(image, image, COLOR_BGR2RGB);

    vector<int> clist = {-128, 128};
    vector<int> blist = {-50, 50};
    vector<Mat> imageContrasts(clist.size());
    vector<Mat> imageBrightness(blist.size());

    namedWindow("Original", WINDOW_AUTOSIZE);
    imshow("Original", image);

    for (int i = 0; i < clist.size(); i++) 
	  {
        imageContrasts[i] = image.clone();
        for (int y = 0; y < image.rows; y++) 
		    {
            for (int x = 0; x < image.cols; x++) 
			      {
                imageContrasts[i].at<Vec3b>(y, x) = adjustContrast(image.at<Vec3b>(y, x), clist[i]);
            }
        }

        string windowName = "Contrast: " + to_string(clist[i]);
        namedWindow(windowName, WINDOW_AUTOSIZE);
        imshow(windowName, imageContrasts[i]);
    }

    for (int i = 0; i < blist.size(); i++) 
	  {
        imageBrightness[i] = image.clone();
        for (int y = 0; y < image.rows; y++) 
		    {
            for (int x = 0; x < image.cols; x++) 
			      {
                imageBrightness[i].at<Vec3b>(y, x) = adjustBrightness(image.at<Vec3b>(y, x), blist[i]);
            }
        }

        string windowName = "Brightness: " + to_string(blist[i]);
        namedWindow(windowName, WINDOW_AUTOSIZE);
        imshow(windowName, imageBrightness[i]);
    }

    waitKey(0);
    return 0;
}


