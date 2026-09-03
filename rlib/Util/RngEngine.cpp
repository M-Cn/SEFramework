#include "RngEngine.h"

namespace rlib
{    
    RngEngineImpl::RngEngineImpl()
    {
        m_engine = pseudo_random_engine_from_device();
    }

    real_t RngEngineImpl::getRandomReal(real_t lower, real_t upper)
    {
        std::uniform_real_distribution<real_t> dist(lower, upper);
        return dist(m_engine);
    }

    int RngEngineImpl::getRandomInt(int lower, int upper)
    {
        std::uniform_int_distribution<int> dist(lower, upper);
        return dist(m_engine);
    }
} // namespace rlib