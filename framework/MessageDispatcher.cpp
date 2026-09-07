#include "MessageDispatcher.h"
#include "../rlib/rlib.h"

void MessageDispatcher::registerReceiver(Message::ReceiverId _id, IMessageReceiver* _receiver)
{
    m_receivers[_id] = _receiver;
}

void MessageDispatcher::unregisterReceiver(Message::ReceiverId _id)
{
    m_receivers.erase(_id);
}

void MessageDispatcher::finalize()
{
    m_receivers.clear();
    m_messageQueue.clear();
}

void MessageDispatcher::update(float _dt)
{
    _dispatchMessages();
}

void MessageDispatcher::sendMessage(const Message& _msg)
{
    m_messageQueue.push_back(_msg);
}

IMessageReceiver* MessageDispatcher::getReceiver(Message::ReceiverId _id) const
{
    auto it = m_receivers.find(_id);

    if (it != m_receivers.end())
        return it->second;

    return nullptr;
}

void MessageDispatcher::_dispatchMessages()
{
    std::vector<Message> currentQueue = std::move(m_messageQueue);
    m_messageQueue.clear();

    for (const auto& msg : currentQueue)
    {
        IMessageReceiver* receiver = getReceiver(msg.receiverId);

        if (!receiver)
        {
            LOG_WARNING("MessageDispatcher: No receiver found for message with receiverId %d", msg.receiverId);
            continue;
        }

        receiver->receiveMessage(msg);
    }
}