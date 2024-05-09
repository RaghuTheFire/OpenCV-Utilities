
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

bool drawing = false; // true if mouse is pressed
int pt1_x, pt1_y;

// mouse callback function
static void line_drawing(int event, int x, int y, int flags, void* param)
{
    static cv::Mat& img = *(cv::Mat*)param;

    if (event == cv::EVENT_LBUTTONDOWN)
    {
        drawing = true;
        pt1_x = x;
        pt1_y = y;
    }
    else if (event == cv::EVENT_MOUSEMOVE)
    {
        if (drawing)
        {
            cv::line(img, cv::Point(pt1_x, pt1_y), cv::Point(x, y), cv::Scalar(255, 255, 255), 3);
            pt1_x = x;
            pt1_y = y;
        }
    }
    else if (event == cv::EVENT_LBUTTONUP)
    {
        drawing = false;
        cv::line(img, cv::Point(pt1_x, pt1_y), cv::Point(x, y), cv::Scalar(255, 255, 255), 3);
    }
}

int main()
{
    cv::Mat img(512, 512, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::namedWindow("test draw");
    cv::setMouseCallback("test draw", line_drawing, &img);

    while (true)
    {
        cv::imshow("test draw", img);
        if (cv::waitKey(1) == 27)
            break;
    }

    cv::destroyAllWindows();
    return 0;
}

