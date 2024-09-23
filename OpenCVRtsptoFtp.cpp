//Compilation command:
//g++ -o OpenCVRtsptoFtp OpenCVRtsptoFtp.cpp `pkg-config --cflags --libs opencv4` -lcurl

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <curl/curl.h>
#include <iostream>

int main() 
{
    std::string rtsp_url = "rtsp://your_rtsp_url";
    std::string ftp_url = "ftp://your_ftp_url/filename.avi";
    std::string ftp_user = "username";
    std::string ftp_password = "password";

    cv::VideoCapture cap(rtsp_url);
    if (!cap.isOpened()) 
    {
        std::cerr << "Error: Could not open video stream." << std::endl;
        return -1;
    }

    cv::Mat frame;
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, ftp_url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERPWD, (ftp_user + ":" + ftp_password).c_str());
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        while (true) 
        {
            cap >> frame;
            if (frame.empty()) 
              break;

            // Convert frame to a format suitable for uploading
            std::vector<uchar> buffer;
            cv::imencode(".avi", frame, buffer);
            curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_READDATA, buffer.data());
            curl_easy_setopt(curl, CURLOPT_INFILESIZE, buffer.size());

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) 
            {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            }
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}
