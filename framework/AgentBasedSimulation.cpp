#include "AgentBasedSimulation.h"

void AgentBasedSimulation::sendMessage(const Message& msg)
{
    m_messageQueue.push_back(msg);
}

void AgentBasedSimulation::_dispatchMessages()
{
    std::vector<Message> currentQueue = std::move(m_messageQueue);
    m_messageQueue.clear();

    for (const auto& msg : currentQueue)
    {
        auto it = m_entities.find(msg.receiverId);
        if (it != m_entities.end())
        {
            Entity* receiver = it->second;

            if (receiver) receiver->receiveMessage(msg);
        }
    }
}