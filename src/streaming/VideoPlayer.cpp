#include "streaming/VideoPlayer.h"
#include "utils.h"

#include <mutex> 
#include <boost/array.hpp>
#include <opencv2/opencv.hpp>

// Initalise singleton instance 
VideoPlayer* VideoPlayer::videoPlayerInstance = nullptr;

VideoPlayer::VideoPlayer()
{
}

VideoPlayer::~VideoPlayer()
{
}

VideoPlayer* VideoPlayer::getInstance()
{
    if (videoPlayerInstance == NULL)
    {
        videoPlayerInstance = new VideoPlayer(); 
    }
    return videoPlayerInstance;
}

void VideoPlayer::newFrame(const std::string& filename, const cv::Mat& frame)
{
    // Critical section
    {
        std::lock_guard<std::mutex> lock(mapMutex);

        // Create key-value pair for new video file
        if (filenameFramesMap.find(filename) == filenameFramesMap.end()) 
        {
            filenameFramesMap[filename] = std::queue<cv::Mat>();
        }

        filenameFramesMap[filename].push(frame);
    }
}

void VideoPlayer::playback()
{
    while (true)
    {
        {
            std::lock_guard<std::mutex> lock(mapMutex);
            for (auto& pair : filenameFramesMap)
            {
                if (!pair.second.empty())
                {
                    cv::Mat frame = pair.second.front();
                    pair.second.pop();
                    cv::imshow(pair.first, frame);

                    if(cv::waitKey(50) != -1)
                    {
                        break;
                    }
                }
            }
        }
    }
}