#ifndef TEXTSENDER_H
#define TEXTSENDER_H 

#include "Sender.h"

class TextSender : public Sender
{
    public:
        TextSender(Client* client);
        ~TextSender() override;

        void send(std::string content) override;
};

#endif
