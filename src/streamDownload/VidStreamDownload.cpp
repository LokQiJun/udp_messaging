#include "streamDownload/VidStreamDownload.h"

#include <boost/array.hpp>
#include <opencv2/opencv.hpp>

VidStreamDownload::VidStreamDownload(Server* server)
    : StreamDownload(server)
{
}


VidStreamDownload::~VidStreamDownload()
{
}

void VidStreamDownload::download()
{
    std::vector<char> buffer(STREAM_SIZE);

    cv::Mat frame;
    std::vector<char> frameBuffer;
    int frameCount = 0;
    cv::namedWindow("StreamDownload");
    while (true)
    {
        buffer.clear();
        buffer.resize(STREAM_SIZE);   
        int bytesReceived = server -> receive_handler(buffer);

        frameBuffer.clear();
        frameBuffer.resize(bytesReceived);
        std::copy(buffer.begin(), buffer.begin()+bytesReceived, frameBuffer.begin());

        if (!frameBuffer.empty()){
            frameCount++;
            std::cout << frameCount << std::endl;
            frame = cv::imdecode(frameBuffer, cv::IMREAD_COLOR);
            cv::imshow("StreamDownload", frame);
            
            if(cv::waitKey(200) != -1)
            {
                break;
            }
        }
    }
}