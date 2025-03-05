//drawing alpha blended overlay roi rectangle  using mouse without pausing the video
#include <opencv2/opencv.hpp>

cv::Rect roi;
bool drawing = false;

void drawRectangle(cv::Mat & image) 
{
  cv::Mat overlay;
  image.copyTo(overlay);
  cv::rectangle(overlay, roi, cv::Scalar(0, 255, 0), -1);
  cv::addWeighted(overlay, 0.5, image, 0.5, 0, image);
}

void mouseCallback(int event, int x, int y, int flags, void * param) 
{
  if (event == cv::EVENT_LBUTTONDOWN) 
  {
    drawing = true;
    roi = cv::Rect(x, y, 0, 0);
  } 
  else 
  if (event == cv::EVENT_MOUSEMOVE) 
  {
    if (drawing) 
    {
      roi.width = x - roi.x;
      roi.height = y - roi.y;
    }
  } 
  else 
  if (event == cv::EVENT_LBUTTONUP) 
  {
    drawing = false;
    roi.width = x - roi.x;
    roi.height = y - roi.y;
  }
}

int main() 
{
  cv::VideoCapture cap(0);
  if (!cap.isOpened()) 
  {
    return -1;
  }

  cv::namedWindow("Video");
  cv::setMouseCallback("Video", mouseCallback, nullptr);

  while (true) 
  {
    cv::Mat frame;
    cap >> frame;
    if (frame.empty()) break;

    if (drawing) 
    {
      drawRectangle(frame);
    }

    cv::imshow("Video", frame);
    if (cv::waitKey(30) >= 0) break;
  }

  cap.release();
  cv::destroyAllWindows();
  return 0;
}
