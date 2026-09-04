#ifndef MESSAGE_RECEIVER_H
#define MESSAGE_RECEIVER_H

#include "Message.h"

class IMessageReceiver 
{
public:
    virtual void receiveMessage(const Message& _msg) = 0;
};

#endif