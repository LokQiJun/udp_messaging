#ifndef UDP_HEADER
#define UDP_HEADER

#include <string>
#include <vector>

// Customer UDP Header struct that stores metadata for the UDP Packet it is attached to
struct UDPHeader
{
    std::string filename;
    std::string filetype;
    int numPackets;
    int packetOrder;
    int frameOrder; // Only for video streams
};

// Helper functions 
std::string stripBreadcrumb(std::string filepath);
std::string extractFiletype(std::string filename);

// Handles header read/write to their UDP packets
UDPHeader formatHeader(std::string filename, int filesize);
int attachHeader(const UDPHeader& udpHeader, std::vector<char>& buffer);
UDPHeader removeHeader(std::vector<char>& buffer);

#endif