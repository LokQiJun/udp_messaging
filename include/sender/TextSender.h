#ifndef TEXTSENDER_H
#define TEXTSENDER_H 

#include "Sender.h"

class TextSender : public TextSender
{
    public:
        TextSender();
        ~TextSender();

        std::vector<char> send(std::string content) override;
}
#endif
