#ifndef RECEIVER_H
#define RECEIVER_H

#include "utils.h"

#include <boost/asio.hpp>
#include <boost/array.hpp>

class Receiver
{
    public:
        Receiver();
        virtual ~Receiver();

        virtual boost::array<char, PACKET_SIZE> handleData() = 0;
};

#endif
