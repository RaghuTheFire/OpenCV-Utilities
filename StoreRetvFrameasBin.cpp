#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

// Function to store OpenCV frame as binary file with token
void storeFrameWithToken(const cv::Mat& frame, const std::string& filename, const std::string& token) 
{
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) 
    {
        // Write token to the file
        file.write(token.c_str(), token.length());

        // Write frame data to the file
        std::vector<uchar> data(frame.isContinuous() ? frame.total() * frame.elemSize() : 1);
        if (frame.isContinuous()) 
        {
            memcpy(data.data(), frame.data, data.size() * sizeof(uchar));
        } 
        else 
        {
            uchar* ptr = data.data();
            const uchar* framePtr = frame.ptr<uchar>();
            size_t frameStep = frame.step;
            for (int i = 0; i < frame.rows; ++i) 
            {
                memcpy(ptr, framePtr, frame.cols * frame.elemSize());
                ptr += frame.cols * frame.elemSize();
                framePtr += frameStep;
            }
        }
        file.write(reinterpret_cast<char*>(data.data()), data.size() * sizeof(uchar));
        file.close();
        std::cout << "Frame stored successfully with token: " << token << std::endl;
    } 
    else 
    {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}

// Function to retrieve OpenCV frame from binary file using token
cv::Mat retrieveFrameWithToken(const std::string& filename, const std::string& token) 
{
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) 
    {
        // Read token from the file
        std::string fileToken(token.length(), '\0');
        file.read(&fileToken[0], token.length());

        // Check if the token matches
        if (fileToken == token) 
        {
            // Read frame data from the file
            std::vector<uchar> data(std::istreambuf_iterator<char>(file), {});
            cv::Mat frame(1, data.size() / sizeof(uchar), CV_8UC1, data.data());
            frame = cv::imdecode(frame, cv::IMREAD_UNCHANGED);
            file.close();
            std::cout << "Frame retrieved successfully with token: " << token << std::endl;
            return frame;
        } 
        else 
        {
            std::cout << "Invalid token for the file: " << filename << std::endl;
            file.close();
            return cv::Mat();
        }
    } 
    else 
    {
        std::cout << "Unable to open file: " << filename << std::endl;
        return cv::Mat();
    }
}

int main() 
{
    // Example usage
    cv::Mat frame = cv::imread("image.jpg");
    std::string filename = "frame.bin";
    std::string token = "mytoken";

    // Store frame with token
    storeFrameWithToken(frame, filename, token);

    // Retrieve frame with token
    cv::Mat retrievedFrame = retrieveFrameWithToken(filename, token);

    // Display retrieved frame
    if (!retrievedFrame.empty()) 
    {
        cv::imshow("Retrieved Frame", retrievedFrame);
        cv::waitKey(0);
    }

    return 0;
}
