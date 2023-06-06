#ifndef VIDSTREAMUPLOAD
#define VIDSTREAMUPLOAD

#include "StreamUpload.h"

class VidStreamUpload : public StreamUpload
{
    public:
        VidStreamUpload(Client* client);
        ~VidStreamUpload() override;

        void upload(std::string filepath) override;
};

#endif
