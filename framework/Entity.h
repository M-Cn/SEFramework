#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>

class Entity 
{
public:
    Entity(uint32_t id) : m_id(id) {}
    virtual ~Entity() = default;

    virtual bool initialize() { return true; }
    virtual void update(float dt) {}

    uint32_t getId() const { return m_id; }

protected:
    uint32_t m_id;
};

#endif // ENTITY_H