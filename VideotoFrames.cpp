#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) 
{
    if (argc < 3) 
	{
        std::cout << "Please provide video file and save directory" << std::endl;
        return 0;
    }

    std::string video_file = argv[1];
    std::string save_dir = argv[2];

    cv::VideoCapture video(video_file);
    if (!video.isOpened()) 
	{
        std::cout << "Could not open video file" << std::endl;
        video.release();
        return 0;
    }

    int frame_count = 0;
    while (video.isOpened()) 
	{
        cv::Mat frame;
        bool status = video.read(frame);
        if (!status) 
		{
            break;
        }
        frame_count++;

        std::string out_file = save_dir + "/" + "frame_" + std::to_string(frame_count) + ".jpg";
        std::cout << "writing file to .. " << out_file << std::endl;
        cv::imwrite(out_file, frame);
    }

    video.release();

    return 0;
}

