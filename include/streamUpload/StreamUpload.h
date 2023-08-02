#ifndef STREAMUPLOAD_H
#define STREAMUPLOAD_H

#include "../entities/Client.h"

#include <string>
#include <vector>

// Parent class for all stream uploading classes
class StreamUpload
{
    protected:
        Client* client;

    public:
        StreamUpload(Client* client) : client(client) {}
        virtual ~StreamUpload() {}

        virtual void upload(std::string filepath) = 0; 
};

#endif
