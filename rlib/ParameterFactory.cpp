#include "ParameterFactory.h"
#include "GeneralUtil.h"

namespace rlib
{
    ParameterFactory::ParameterFactory()
    {
        registerDefaultTypes();
    }

    ParameterType ParameterFactory::getParameterType(const std::string& typeName) const
    {
        auto it = m_typeMap.find(typeName);
        if (it != m_typeMap.end())
            return it->second;

        REPORT_PANIC("Unknown parameter type: " + typeName);
    }

    Parameter* ParameterFactory::makeParameter(const std::string& typeName, const std::string& name) const
    {
        ParameterType type = getParameterType(typeName);

        switch (type)
        {
        case ParameterType::kParamInt:                      return new IntParameter(name, typeName);
        case ParameterType::kParamUInt:                     return new UIntParameter(name, typeName);
        case ParameterType::kParamFloat:                    return new FloatParameter(name, typeName);
        case ParameterType::kParamDouble:                   return new DoubleParameter(name, typeName);
        case ParameterType::kParamString:                   return new StringParameter(name, typeName);
        case ParameterType::kParamBool:                     return new BoolParameter(name, typeName);
        case ParameterType::kParamIntArray:                 return new IntArrayParameter(name, typeName);
        case ParameterType::kParamFloatArray:               return new FloatArrayParameter(name, typeName);
        case ParameterType::kParamDoubleArray:              return new DoubleArrayParameter(name, typeName);
        case ParameterType::kParamStringArray:              return new StringArrayParameter(name, typeName);
        case ParameterType::kParamBoolArray:                return new BoolArrayParameter(name, typeName);
        case ParameterType::kParamMdpStateTransitionDef:    return new MdpStateTransitionDefParameter(name, typeName);
        }

        REPORT_PANIC("Unsupported parameter type: " + std::to_string(static_cast<int>(type)));
    }

    void ParameterFactory::registerDefaultTypes()
    {
        registerParameterType("int", ParameterType::kParamInt);
        registerParameterType("uint", ParameterType::kParamUInt);
        registerParameterType("float", ParameterType::kParamFloat);
        registerParameterType("double", ParameterType::kParamDouble);
        registerParameterType("string", ParameterType::kParamString);
        registerParameterType("bool", ParameterType::kParamBool);
        registerParameterType("intArray", ParameterType::kParamIntArray);
        registerParameterType("floatArray", ParameterType::kParamFloatArray);
        registerParameterType("doubleArray", ParameterType::kParamDoubleArray);
        registerParameterType("stringArray", ParameterType::kParamStringArray);
        registerParameterType("boolArray", ParameterType::kParamBoolArray);
        registerParameterType("mdpStateTransitionDef", ParameterType::kParamMdpStateTransitionDef);
    }
} // namespace rlib