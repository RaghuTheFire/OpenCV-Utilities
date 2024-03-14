#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
/*************************************************************************************/
void listFiles(const std::string& path, std::vector<std::string>& lstFiles) 
{
    for (const auto& entry : fs::recursive_directory_iterator(path)) 
	{
        if (entry.is_regular_file()) 
		{
            lstFiles.push_back(entry.path().string());
        }
    }
}
/*************************************************************************************/
void remove(const std::string& path) 
{
    if (fs::is_regular_file(path) || fs::is_symlink(path)) 
	{
        fs::remove(path);
    }
    else if (fs::is_directory(path)) 
	{
        fs::remove_all(path);
    }
    else 
	{
        throw std::invalid_argument("file " + path + " is not a file or dir.");
    }
}
/*************************************************************************************/
void savePng(const cv::Mat& image, const std::string& path, const std::string& name) 
{
    if (!fs::exists(path)) 
	{
        fs::create_directories(path);
    }
    cv::imwrite(path + "/" + name + ".png", image);
}
/*************************************************************************************/
int main() 
{
    std::vector<std::string> DirsNames = { "IMG" };
    int framerate = 30;
    int bitrate = 20000;
    std::string codec = "h264";

    for (const auto& dirN : DirsNames) 
	{
        if (!fs::exists(dirN)) 
		{
            continue;
        }
        std::string DirName = dirN;
        std::vector<std::string> listFls;
        listFiles(DirName, listFls);
        std::string outputPath = DirName + "_aux_tmp";
        int numImages = listFls.size();
        for (int i = 0; i < numImages; i++) 
		{
            std::cout << listFls[i] << std::endl;
            cv::Mat img = cv::imread(listFls[i]);
            savePng(img, outputPath, "IMG" + std::to_string(i + 1));
        }
        std::string cmd1 = "ffmpeg -framerate " + std::to_string(framerate) + " -i " + outputPath + "/IMG%05d.png -codec copy " + outputPath + "/video_aux.mp4";
        std::string cmd2 = "ffmpeg -i " + outputPath + "/video_aux.mp4 -vcodec " + codec + " -b:v " + std::to_string(bitrate) + "k " + DirName + "/Result_video.mp4";
        system(cmd1.c_str());
        system(cmd2.c_str());
        remove(outputPath);
    }

    return 0;
}
/*************************************************************************************/

