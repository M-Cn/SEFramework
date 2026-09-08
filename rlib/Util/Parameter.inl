#ifndef PARAMETER_INL
#define PARAMETER_INL

#include "Parameter.h"

namespace rlib
{
    template<>
    inline bool Parameter::getValue<bool>() const
    {
        if (!isValid()) throw std::runtime_error("Invalid BoolParameter");
        const BoolParameter* pBoolParam = dynamic_cast<const BoolParameter*>(this);
        if (!pBoolParam) throw std::runtime_error("Failed to cast Parameter to BoolParameter");
        return pBoolParam->getValue();
    }

    template<>
    inline int Parameter::getValue<int>() const
    {
        if (!isValid()) throw std::runtime_error("Invalid IntParameter");
        const IntParameter* pIntParam = dynamic_cast<const IntParameter*>(this);
        if (!pIntParam) throw std::runtime_error("Failed to cast Parameter to IntParameter");
        return pIntParam->getValue();
    }

    template<>
    inline uint32_t Parameter::getValue<uint32_t>() const
    {
        if (!isValid()) throw std::runtime_error("Invalid UIntParameter");
        const UIntParameter* pUIntParam = dynamic_cast<const UIntParameter*>(this);
        if (!pUIntParam) throw std::runtime_error("Failed to cast Parameter to UIntParameter");
        return pUIntParam->getValue();
    }

    template<>
    inline float Parameter::getValue<float>() const
    {
        if (!isValid()) throw std::runtime_error("Invalid FloatParameter");
        const FloatParameter* pFloatParam = dynamic_cast<const FloatParameter*>(this);
        if (!pFloatParam) throw std::runtime_error("Failed to cast Parameter to FloatParameter");
        return pFloatParam->getValue();
    }

    template<>
    inline double Parameter::getValue<double>() const
    {
        if (!isValid()) throw std::runtime_error("Invalid DoubleParameter");
        const DoubleParameter* pDoubleParam = dynamic_cast<const DoubleParameter*>(this);
        if (!pDoubleParam) throw std::runtime_error("Failed to cast Parameter to DoubleParameter");
        return pDoubleParam->getValue();
    }

    template<>
    inline std::string Parameter::getValue<std::string>() const
    {
        if (!isValid()) throw std::runtime_error("Invalid StringParameter");
        const StringParameter* pStringParam = dynamic_cast<const StringParameter*>(this);
        if (!pStringParam) throw std::runtime_error("Failed to cast Parameter to StringParameter");
        return pStringParam->getValue();
    }

    template<>
    inline std::vector<bool> Parameter::getValue<std::vector<bool>>() const
    {
        if (!isValid()) throw std::runtime_error("Invalid BoolArrayParameter");
        const BoolArrayParameter* pBoolArrayParam = dynamic_cast<const BoolArrayParameter*>(this);
        if (!pBoolArrayParam) throw std::runtime_error("Failed to cast Parameter to BoolArrayParameter");

        std::vector<bool> values;
        for (size_t i = 0; i < pBoolArrayParam->getNumValues(); ++i)
            values.push_back(pBoolArrayParam->getValue(i));

        return values;
    }

    template<>
    inline std::vector<int> Parameter::getValue<std::vector<int>>() const
    {
        if (!isValid()) throw std::runtime_error("Invalid IntArrayParameter");
        const IntArrayParameter* pIntArrayParam = dynamic_cast<const IntArrayParameter*>(this);
        if (!pIntArrayParam) throw std::runtime_error("Failed to cast Parameter to IntArrayParameter");

        std::vector<int> values;
        for (size_t i = 0; i < pIntArrayParam->getNumValues(); ++i)
            values.push_back(pIntArrayParam->getValue(i));

        return values;
    }

    template<>
    inline std::vector<float> Parameter::getValue<std::vector<float>>() const
    {
        if (!isValid()) throw std::runtime_error("Invalid FloatArrayParameter");
        const FloatArrayParameter* pFloatArrayParam = dynamic_cast<const FloatArrayParameter*>(this);
        if (!pFloatArrayParam) throw std::runtime_error("Failed to cast Parameter to FloatArrayParameter");

        std::vector<float> values;
        for (size_t i = 0; i < pFloatArrayParam->getNumValues(); ++i)
            values.push_back(pFloatArrayParam->getValue(i));

        return values;
    }

    template<>
    inline std::vector<double> Parameter::getValue<std::vector<double>>() const
    {
        if (!isValid()) throw std::runtime_error("Invalid DoubleArrayParameter");
        const DoubleArrayParameter* pDoubleArrayParam = dynamic_cast<const DoubleArrayParameter*>(this);
        if (!pDoubleArrayParam) throw std::runtime_error("Failed to cast Parameter to DoubleArrayParameter");

        std::vector<double> values;
        for (size_t i = 0; i < pDoubleArrayParam->getNumValues(); ++i)
            values.push_back(pDoubleArrayParam->getValue(i));

        return values;
    }

    template<>
    inline std::vector<std::string> Parameter::getValue<std::vector<std::string>>() const
    {
        if (!isValid()) throw std::runtime_error("Invalid StringArrayParameter");
        const StringArrayParameter* pStringArrayParam = dynamic_cast<const StringArrayParameter*>(this);
        if (!pStringArrayParam) throw std::runtime_error("Failed to cast Parameter to StringArrayParameter");

        std::vector<std::string> values;
        for (size_t i = 0; i < pStringArrayParam->getNumValues(); ++i)
            values.push_back(pStringArrayParam->getValue(i));

        return values;
    }
}

#endif