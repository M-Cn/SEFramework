#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <cstdint>

struct Message 
{
    typedef uint32_t MessageId;
    typedef float Timestamp;

    MessageId id;
    enum class Type { REQUEST, RESPONSE } type;
    Timestamp timestamp;
};

#endif // MESSAGE_H