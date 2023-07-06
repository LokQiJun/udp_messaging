#ifndef UDP_HEADER
#define UDP_HEADER

#include <string>
#include <vector>

struct UDPHeader
{
    std::string filename;
    std::string filetype;
    int numPackets;
    int packetOrder;
    int frameOrder; // Only for video streams
};



std::string stripBreadcrumb(std::string filepath);
std::string extractFiletype(std::string filename);

UDPHeader formatHeader(std::string filename, int filesize);
int attachHeader(const UDPHeader& udpHeader, std::vector<char>& buffer);
UDPHeader removeHeader(std::vector<char>& buffer);

#endif