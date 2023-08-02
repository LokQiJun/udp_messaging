#ifndef VIDSTREAMUPLOAD
#define VIDSTREAMUPLOAD

#include "StreamUpload.h"

// Reads a video file and split each frame into packets before passing it to Client class for stream transmission
class VidStreamUpload : public StreamUpload
{
    public:
        VidStreamUpload(Client* client);
        ~VidStreamUpload() override;

        void upload(std::string filepath) override;
};

#endif
