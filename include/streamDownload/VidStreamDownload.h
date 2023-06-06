#ifndef VIDSTREAM_H
#define VIDSTREAM_H

#include "StreamDownload.h"

class VidStreamDownload : public StreamDownload
{
    public:
        VidStreamDownload(Server* server);
        ~VidStreamDownload() override;

        void download() override;
        
};

#endif
