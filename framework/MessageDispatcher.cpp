#include "MessageDispatcher.h"

void MessageDispatcher::registerReceiver(Message::MessageId _messageId, IMessageReceiver* _receiver)
{
    m_receivers[_messageId] = _receiver;
}

void MessageDispatcher::unregisterReceiver(Message::MessageId _messageId)
{
    m_receivers.erase(_messageId);
}

void MessageDispatcher::sendMessage(const Message& _msg)
{
    m_messageQueue.push_back(_msg);
}

void MessageDispatcher::_dispatchMessages()
{
    std::vector<Message> currentQueue = std::move(m_messageQueue);
    m_messageQueue.clear();

    for (const auto& msg : currentQueue)
    {
        auto it = m_receivers.find(msg.id);
        if (it != m_receivers.end())
        {
            IMessageReceiver* receiver = it->second;

            if (receiver) receiver->receiveMessage(msg);
        }
    }
}