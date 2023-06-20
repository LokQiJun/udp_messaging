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
};



std::string stripBreadcrumb(std::string filepath);
std::string extractFiletype(std::string filename);

UDPHeader formatHeader(std::string filename, std::string filetype, int filesize);
int attachHeader(const UDPHeader& udpHeader, std::vector<char>& buffer);
UDPHeader removeHeader(std::vector<char>& buffer);

#endif