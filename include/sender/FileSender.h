#ifndef FILESENDER_H
#define FILESENDER_H

#include "Sender.h"

class FileSender : public Sender
{
    public:
        FileSender();
        ~FileSender();

        std::vector<char> send(std::string content) override;
}


#endif
