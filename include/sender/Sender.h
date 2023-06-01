#ifndef SENDER_H
#define SENDER_H 

#include <string>
#include <vector>

class Sender 
{
    public:
        Sender();
        virtual ~Sender();

        virtual std::vector<char> send(std::string content) = 0;
};

#endif
