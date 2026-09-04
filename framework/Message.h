#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <cstdint>

struct Message 
{
    typedef float Timestamp;

    uint32_t senderId;
    uint32_t receiverId;
    uint32_t productId;
    enum class Type { REQUEST, RESPONSE } type;
    Timestamp timestamp;

    Message(uint32_t _senderId, uint32_t _receiverId, uint32_t _productId, Type _type, Timestamp _timestamp = 0.f)
        : senderId(_senderId), receiverId(_receiverId), productId(_productId), type(_type), timestamp(_timestamp) {}
};

#endif // MESSAGE_H