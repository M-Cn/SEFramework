#ifndef AGENT_BASED_SIMULATION_H
#define AGENT_BASED_SIMULATION_H

#include "Simulation.h"
#include "Message.h"
#include "Entity.h"

#include <vector>
#include <map>

class AgentBasedSimulation : public Simulation
{
public:
    virtual void sendMessage(const Message& msg);

protected:
    void _dispatchMessages();

    std::map<uint32_t, Entity*> m_entities;
    std::vector<Message> m_messageQueue;
};

#endif // AGENT_BASED_SIMULATION_H