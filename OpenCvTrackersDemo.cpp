#include <opencv2/opencv.hpp>
#include <iostream>
#include <random>

int main() 
{
  std::vector < std::string > tracker_types = 
  {
    "BOOSTING",
    "MIL",
    "KCF",
    "TLD",
    "MEDIANFLOW",
    "MOSSE",
    "CSRT"
  };
  std::string tracker_type = tracker_types[5];
  std::cout << tracker_type << std::endl;

  cv::Ptr < cv::legacy::Tracker > tracker;
  if (tracker_type == "BOOSTING") 
  {
    tracker = cv::legacy::TrackerBoosting::create();
  } 
  else 
  if (tracker_type == "MIL") 
  {
    tracker = cv::legacy::TrackerMIL::create();
  } 
  else 
  if (tracker_type == "KCF") 
  {
    tracker = cv::legacy::TrackerKCF::create();
  } 
  else 
  if (tracker_type == "TLD") 
  {
    tracker = cv::legacy::TrackerTLD::create();
  } 
  else 
  if (tracker_type == "MEDIANFLOW") 
  {
    tracker = cv::legacy::TrackerMedianFlow::create();
  } 
  else 
  if (tracker_type == "MOSSE") 
  {
    tracker = cv::legacy::TrackerMOSSE::create();
  } 
  else
  if (tracker_type == "CSRT") 
  {
    tracker = cv::legacy::TrackerCSRT::create();
  }

  std::cout << tracker << std::endl;

  cv::VideoCapture video("race.mp4");
  if (!video.isOpened()) 
  {
    std::cout << "Error while loading the video!" << std::endl;
    return -1;
  }

  cv::Mat frame;
  bool ok = video.read(frame);
  if (!ok) 
  {
    std::cout << "Error while loading the frame!" << std::endl;
    return -1;
  }
  std::cout << ok << std::endl;

  cv::Rect bbox = cv::selectROI(frame);
  std::cout << bbox << std::endl;

  ok = tracker -> init(frame, bbox);
  std::cout << ok << std::endl;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution < > dis(0, 255);
  cv::Scalar colors(dis(gen), dis(gen), dis(gen));
  std::cout << colors << std::endl;

  while (true) 
  {
    ok = video.read(frame);
    if (!ok) 
    {
      break;
    }

    ok = tracker->update(frame, bbox);
    if (ok) 
    {
      cv::rectangle(frame, bbox, colors, 2);
    } 
    else 
    {
      cv::putText(frame, "Tracking failure!", cv::Point(100, 80), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 255));
    }

    cv::putText(frame, tracker_type, cv::Point(100, 20), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 255));

    cv::imshow("Tracking", frame);
    if (cv::waitKey(1) == 27) // esc
    { 
      break;
    }
  }

  return 0;
}
