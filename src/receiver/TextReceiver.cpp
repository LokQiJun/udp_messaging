#include "receiver/TextReceiver.h"

#include <iostream>
#include <fstream>

TextReceiver::TextReceiver()
{
}

TextReceiver::~TextReceiver()
{
}

void TextReceiver::handleData(boost::array<char, PACKET_SIZE>& buffer, int bytesReceived, std::string filepath)
{
    std::cout << "\n" << buffer.data() << std::endl;
    std::ofstream outputFile(filepath, (std::ios::binary | std::ios::app));
    outputFile << getCurrTime() + ": " + buffer.data();

    outputFile.close();
}