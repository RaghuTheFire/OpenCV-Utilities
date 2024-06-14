
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int truncate(int value) 
{
    if (value < 0) 
       return 0; 
    else 
    if (value > 255) 
        return 255; 
    else 
        return value;
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
    VideoCapture cap;
    cap.open("rtsp://your_rtsp_stream_url");

    if (!cap.isOpened()) 
    {
        cout << "Could not open the video stream" << endl;
        return -1;
    }

    Mat frame;
    vector<int> clist = {-128, 128};
    vector<int> blist = {-50, 50};
    vector<Mat> imageContrasts(clist.size());
    vector<Mat> imageBrightness(blist.size());

    namedWindow("Original", WINDOW_AUTOSIZE);

    while (true) 
    {
        cap >> frame;
        if (frame.empty()) 
        {
            cout << "No more frames" << endl;
            break;
        }

        cvtColor(frame, frame, COLOR_BGR2RGB);
        imshow("Original", frame);

        for (int i = 0; i < clist.size(); i++) 
        {
            imageContrasts[i] = frame.clone();
            for (int y = 0; y < frame.rows; y++) 
            {
                for (int x = 0; x < frame.cols; x++) 
                {
                    imageContrasts[i].at<Vec3b>(y, x) = adjustContrast(frame.at<Vec3b>(y, x), clist[i]);
                }
            }

            string windowName = "Contrast: " + to_string(clist[i]);
            namedWindow(windowName, WINDOW_AUTOSIZE);
            imshow(windowName, imageContrasts[i]);
        }

        for (int i = 0; i < blist.size(); i++) 
        {
            imageBrightness[i] = frame.clone();
            for (int y = 0; y < frame.rows; y++) 
            {
                for (int x = 0; x < frame.cols; x++) 
                {
                    imageBrightness[i].at<Vec3b>(y, x) = adjustBrightness(frame.at<Vec3b>(y, x), blist[i]);
                }
            }

            string windowName = "Brightness: " + to_string(blist[i]);
            namedWindow(windowName, WINDOW_AUTOSIZE);
            imshow(windowName, imageBrightness[i]);
        }

        int key = waitKey(1);
        if (key == 27) // Press 'Esc' to exit
        { 
            break;
        }
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
