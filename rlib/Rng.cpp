#include "Rng.h"

namespace rlib
{    
    DefaultRng::DefaultRng()
    {
        m_engine = pseudo_random_engine_from_device();
    }

    real_t DefaultRng::getRandomReal(real_t lower, real_t upper)
    {
        std::uniform_real_distribution<real_t> dist(lower, upper);
        return dist(m_engine);
    }

    int DefaultRng::getRandomInt(int lower, int upper)
    {
        std::uniform_int_distribution<int> dist(lower, upper);
        return dist(m_engine);
    }
} // namespace rlib