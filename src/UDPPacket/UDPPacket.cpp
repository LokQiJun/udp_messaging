#include <UDPPacket/UDPPacket.h>
#include <utils.h>

#include <cstring>


std::string stripBreadcrumb(std::string filepath)
{
    return substrRightOf(filepath, "\\/");
}

std::string extractFiletype(std::string filename)
{
    return substrRightOf(filename, ".");
}

// Util variables for header
int size_t_size  = sizeof(std::size_t);
int int_size = sizeof(int);

UDPHeader formatHeader(std::string filename, std::string filetype, int filesize)
{
    // Format filename and filetype 
    filename = stripBreadcrumb(filename);
    filetype = extractFiletype(filename);

    // Calculate sizes
    std::size_t headerSize = sizeof(size_t) * 2 + 
        filename.length() +
        filetype.length() +
        sizeof(int) * 2;
    std::size_t payloadSize = PACKET_SIZE - headerSize;
    
    // Format header
    UDPHeader udpHeader;
    udpHeader.filename = filename;
    udpHeader.filetype = filetype;
    udpHeader.numPackets = ceilDiv(filesize, payloadSize);
    udpHeader.packetOrder = 0;

    return udpHeader;
}



int attachHeader(const UDPHeader& udpHeader, std::vector<char>& buffer)
{
    std::size_t pos = 0;

    // Serialise filename
    std::size_t filenameLength = udpHeader.filename.length();
    memcpy(&buffer[pos], &filenameLength, size_t_size);
    pos += size_t_size;
    memcpy(&buffer[pos], udpHeader.filename.data(), filenameLength);
    pos += filenameLength;

    // Serialise filetype
    std::size_t filetypeLength = udpHeader.filetype.length();
    memcpy(&buffer[pos], &filetypeLength, size_t_size);
    pos += size_t_size;
    memcpy(&buffer[pos], udpHeader.filetype.data(), filetypeLength);
    pos += filetypeLength;

    // Serialise numPackets
    memcpy(&buffer[pos], &udpHeader.numPackets, int_size);
    pos += int_size;

    // Serialise packetOrder
    memcpy(&buffer[pos], &udpHeader.packetOrder, int_size);
    pos += int_size;
    
    return pos;
}

UDPHeader removeHeader(std::vector<char>& buffer)
{
    UDPHeader udpHeader;

    // Extract filename
    std::size_t filenameLength;
    memcpy(&filenameLength, buffer.data(), size_t_size);
    buffer.erase(buffer.begin(), buffer.begin()+size_t_size);

    memcpy(&udpHeader.filename, buffer.data(), filenameLength);
    buffer.erase(buffer.begin(), buffer.begin()+filenameLength);

    // Extract filetype
    std::size_t filetypeLength;
    memcpy(&filetypeLength, buffer.data(), size_t_size);
    buffer.erase(buffer.begin(), buffer.begin()+size_t_size);

    memcpy(&udpHeader.filetype, buffer.data(), filetypeLength);
    buffer.erase(buffer.begin(), buffer.begin()+filetypeLength);

    // Extract num packets
    memcpy(&udpHeader.numPackets, buffer.data(), int_size);
    buffer.erase(buffer.begin(), buffer.begin()+int_size);

    // Extract packet order
    memcpy(&udpHeader.packetOrder, buffer.data(), int_size);
    buffer.erase(buffer.begin(), buffer.begin()+int_size);

    return udpHeader;
}