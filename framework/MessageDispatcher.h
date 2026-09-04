#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H

#include "Message.h"
#include "MessageReceiver.h"

#include <vector>
#include <map>

class IMessageDispatcher
{
public:
    virtual void sendMessage(const Message& _msg) = 0;
};

class MessageDispatcher : public IMessageDispatcher
{
public:
    MessageDispatcher() = default;
    virtual ~MessageDispatcher() = default;

    virtual void sendMessage(const Message& _msg) override;

    void registerReceiver(Message::MessageId _messageId, IMessageReceiver* _receiver);
    void unregisterReceiver(Message::MessageId _messageId);
protected:
    void _dispatchMessages();

    std::map<Message::MessageId, IMessageReceiver*> m_receivers;
    std::vector<Message> m_messageQueue;
};

#endif // MESSAGE_DISPATCHER_H