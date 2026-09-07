#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <cstdint>

struct Message 
{
    typedef uint32_t ReceiverId;
    typedef size_t Timestamp;

    ReceiverId receiverId;
    Timestamp timestamp;

    Message(ReceiverId _id) : receiverId(_id), timestamp(0) {}
    Message(ReceiverId _id, Timestamp _timestamp) : receiverId(_id), timestamp(_timestamp) {}
    std::string toString() const;
};

#endif // MESSAGE_H