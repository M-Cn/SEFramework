#include "Message.h"

const std::string Message::toString() const
{
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s:<uint32>receiverId=%u\n<Timestamp>timestamp=%zu\n", getTypeName(), m_receiverId, m_timestamp);
    return std::string(buffer);
}