#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <cstdint>

class Message 
{
public:
    typedef uint32_t ReceiverId;
    typedef size_t Timestamp;

    Message(ReceiverId _id) : m_receiverId(_id), m_timestamp(0) {}
    Message(ReceiverId _id, Timestamp _timestamp) : m_receiverId(_id), m_timestamp(_timestamp) {}
    
    virtual ~Message() = default;

    virtual const char* getTypeName() const { return "Message"; }
    virtual const std::string toString() const;

    ReceiverId receiverId() const { return m_receiverId; }
    Timestamp timestamp() const { return m_timestamp; }
protected:
    ReceiverId m_receiverId;
    Timestamp m_timestamp;
};

#endif // MESSAGE_H