#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <string>
#include <opencv2/opencv.hpp>

class VideoPlayer
{
    private:
        static VideoPlayer* videoPlayerInstance;
        VideoPlayer();
        ~VideoPlayer();

        std::mutex mapMutex;
        std::map<std::string, std::queue<cv::Mat> > filenameFramesMap;
    public:
        static VideoPlayer* getInstance();
        void newFrame(const std::string& filename, const cv::Mat& frame);
        void playback();
};

#endif
