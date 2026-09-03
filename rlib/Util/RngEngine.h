#ifndef RNG_H
#define RNG_H

#include "Singleton.inl"
#include "../../mocc/mocc.hpp"

namespace rlib
{
    class IRngEngine
    {
    public:
        /*
        Returns a random real number in the range [lower, upper).
        Returns:
        - A random real number between lower (inclusive) and upper (exclusive).
        */
        virtual real_t getRandomReal(real_t lower = 0.0, real_t upper = 1.0) = 0;

        /*
        Returns a random integer in the range [lower, upper).
        Returns:
        - A random integer between lower (inclusive) and upper (exclusive).
        */
        virtual int getRandomInt(int lower, int upper) = 0;
    };

    class RngEngineImpl final : public Singleton<RngEngineImpl>, public IRngEngine
    {
        friend class Singleton<RngEngineImpl>;
    private:
        urng_t m_engine;

        RngEngineImpl();
        ~RngEngineImpl() = default;
    public:
        virtual real_t getRandomReal(real_t lower = 0.0, real_t upper = 1.0) override;
        virtual int getRandomInt(int lower, int upper) override;
    };
} // namespace rlib

#endif // RNG_H