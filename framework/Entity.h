#ifndef ENTITY_H
#define ENTITY_H

#include "Message.h"

class Entity 
{
public:
    Entity(uint32_t id) : m_id(id) {}
    virtual ~Entity() = default;

    virtual void initialize() = 0;
    virtual void update(float dt) = 0;
    virtual void receiveMessage(const Message& msg) = 0;

    uint32_t getId() const { return m_id; }

protected:
    uint32_t m_id;
};

#endif // ENTITY_H