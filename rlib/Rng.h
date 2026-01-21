#ifndef RNG_H
#define RNG_H

#include "Singleton.inl"
#include "../mocc/mocc.hpp"

namespace rlib
{
    class RngBase
    {
    public:
        virtual ~RngBase() = default;

        virtual real_t getRandomReal(real_t lower = 0.0, real_t upper = 1.0) = 0;
        virtual int getRandomInt(int lower, int upper) = 0;
    };

    class DefaultRng final : public Singleton<DefaultRng>, public RngBase
    {
        friend class Singleton<DefaultRng>;
    private:
        urng_t m_engine;

        DefaultRng();
        virtual ~DefaultRng() override = default;
    public:
        /*
        Returns a random real number in the range [lower, upper).
        Returns:
        - A random real number between lower (inclusive) and upper (exclusive).
        */
        virtual real_t getRandomReal(real_t lower = 0.0, real_t upper = 1.0) override;

        /*
        Returns a random integer in the range [lower, upper).
        Returns:
        - A random integer between lower (inclusive) and upper (exclusive).
        */
        virtual int getRandomInt(int lower, int upper) override;
    };
} // namespace rlib

#endif // RNG_H