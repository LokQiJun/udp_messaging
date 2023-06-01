#ifndef RECEIVER_H
#define RECEIVER_H

#include "utils.h"

#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

class Receiver
{
    public:
        Receiver();
        virtual ~Receiver();

        virtual void handleData(boost::array<char, PACKET_SIZE>& buffer, int bytesReceived, std::string filepath) = 0;
};

#endif
