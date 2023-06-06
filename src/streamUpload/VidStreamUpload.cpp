#include "streamUpload/VidStreamUpload.h"
#include "utils.h"

#include <iostream>
#include <fstream> 
#include <opencv2/opencv.hpp> 
#include <chrono>
#include <thread> 

VidStreamUpload::VidStreamUpload(Client* client)
    : StreamUpload(client)
{
}

VidStreamUpload::~VidStreamUpload()
{
}

void VidStreamUpload::upload(std::string filepath)
{
    // Check filetype 
    std::string filetype = filepath.substr(filepath.length()-4);
    if (filetype.compare(".mp4") != 0)
    {
        std::cerr << "Input file needs to be an mp4 file" << std::endl;
        return;
    }

    // Open video file
    cv::VideoCapture video(filepath);
    
    // //Open webcam
    // cv::VideoCapture video;
    // video.open(0);
    
    if (!video.isOpened())
    {
        std::cerr << "Unable to open video file." << std::endl;
        return;
    }

    // Read frames and send
    std::vector<char> videoBuffer;
    cv::Mat frame;
    int frameCount = 0;
    cv::Size newSize(360, 270);
    
    while(video.read(frame))
    {   
        cv::resize(frame, frame, newSize);
        std::vector<int> compressionParams;
        compressionParams.push_back(cv::IMWRITE_JPEG_QUALITY);
        compressionParams.push_back(20);

        std::vector<uchar> frameBuffer;
        cv::imencode(".jpg", frame, frameBuffer, compressionParams);
        videoBuffer.insert(videoBuffer.end(), frameBuffer.begin(), frameBuffer.end());

        client -> send_handler(videoBuffer);
        std::cout << "Frame " << frameCount << ": " << videoBuffer.size() << " bytes" << std::endl;

        frame.release();
        frameBuffer.clear();
        videoBuffer.clear();

        frameCount++;

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
    }

    video.release();
    cv::destroyAllWindows();
}
