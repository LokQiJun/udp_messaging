#ifndef STREAMDOWNLOAD_H
#define STREAMDOWNLOAD_H

#include "../entities/Server.h"

class StreamDownload
{
    protected:
        Server* server;
    public:
        StreamDownload(Server* server) : server(server) {}
        virtual ~StreamDownload() {}

        virtual void download() = 0;
};

#endif
