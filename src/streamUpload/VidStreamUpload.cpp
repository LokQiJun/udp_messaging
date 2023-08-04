#include "streamUpload/VidStreamUpload.h"
#include "UDPPacket/UDPPacket.h"
#include "utils.h"

#include <iostream>
#include <fstream> 
#include <sstream>
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
    std::string filetype = extractFiletype(filepath);
    std::string filename = stripBreadcrumb(filepath);
    
    // Check filetype 
    if (filetype.compare("mp4") != 0)
    {
        std::cerr << "Input file needs to be an mp4 file. Current file type: " << filetype << std::endl;
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
    cv::Mat frame;
    int frameCount = 0;
    int frameWidth = 480;
    int frameHeight = 360;
    
    while(video.read(frame))
    {   
        frameCount++;

        // Compress frame
        cv::resize(frame, frame, cv::Size(frameWidth, frameHeight));
        std::vector<int> compressionParams;
        compressionParams.push_back(cv::IMWRITE_JPEG_QUALITY); // image file read/write flag
        compressionParams.push_back(50); // image quality 

        std::vector<uchar> frameBuffer;
        cv::imencode(".jpg", frame, frameBuffer, compressionParams);
       

        //TODO: split frame 
        std::ostringstream oss;
        oss << filename << ".stream";
        std::string formattedUDPFilename = oss.str();
        int frameSize = frameBuffer.size();
        UDPHeader udpHeader = formatHeader(formattedUDPFilename, frameSize);
    
        // send frame in packets
        std::vector<char> packetBuffer(PACKET_SIZE);
        int packetCount = 0; // Number of packets sent
        int read = 0; // Number of bytes read from file
        while (read < frameSize)
        {
            // Prepare packetBuffer for next data packet
            packetBuffer.clear();
            packetBuffer.resize(PACKET_SIZE);

            // Attach header to UDP packet
            packetCount++;
            udpHeader.packetOrder = packetCount;
            udpHeader.frameOrder = frameCount;
            int headerSize = attachHeader(udpHeader, packetBuffer);
    
            // Calculate payload size
            std::size_t payloadSize = std::min(PACKET_SIZE-headerSize, frameSize-read); // payload size corresponds to amount of space left in a packet or the amount of data left in a file

            // Client sends packetBuffer
            std::cout << frameCount << "," << packetCount << ":" << packetBuffer.size() << std::endl;
            packetBuffer.insert(packetBuffer.begin()+headerSize, frameBuffer.begin()+read, frameBuffer.begin()+read+payloadSize);
            packetBuffer.resize(PACKET_SIZE);
            std::cout << frameCount << "," << packetCount << ":" << packetBuffer.size() << "(" << headerSize << ")" << std::endl;
            client -> sendHandler(packetBuffer);
            
            
            // Update variables for next iteration
            read += payloadSize;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        
        std::cout << "Frame " << frameCount << ": " << frameBuffer.size() << " bytes" << std::endl;
  
        frame.release();
        frameBuffer.clear();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        
    }

    video.release();
    cv::destroyAllWindows();
}
