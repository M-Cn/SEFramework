#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H

#include "Message.h"
#include "MessageReceiver.h"

#include <vector>
#include <map>

class MessageDispatcher
{
public:
    MessageDispatcher() = default;
    virtual ~MessageDispatcher() = default;

    virtual bool initialize() { return true; }
    virtual void finalize();
    virtual void update(float _dt);

    virtual void sendMessage(const Message& _msg);

    void registerReceiver(Message::ReceiverId _id, IMessageReceiver* _receiver);
    void unregisterReceiver(Message::ReceiverId _id);
    IMessageReceiver* getReceiver(Message::ReceiverId _id) const;
    bool hasReceiver(Message::ReceiverId _id) const { return getReceiver(_id) != nullptr; }
protected:
    void _dispatchMessages();

    std::map<Message::ReceiverId, IMessageReceiver*> m_receivers;
    std::vector<Message> m_messageQueue;
};

#endif // MESSAGE_DISPATCHER_H