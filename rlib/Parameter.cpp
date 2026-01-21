#include "Parameter.h"
#include <sstream>
#include <algorithm>

#include "GeneralUtil.h"

#define SEPARATOR ' '

namespace rlib
{
    const char* Parameter::parameterTypeAsString(ParameterType type)
    {
        switch (type)
        {
        case ParameterType::kParamInt:                      return "int";
        case ParameterType::kParamUInt:                     return "uint";
        case ParameterType::kParamFloat:                    return "float";
        case ParameterType::kParamDouble:                   return "double";
        case ParameterType::kParamString:                   return "string";
        case ParameterType::kParamBool:                     return "bool";
        case ParameterType::kParamIntArray:                 return "intArray";
        case ParameterType::kParamFloatArray:               return "floatArray";
        case ParameterType::kParamDoubleArray:              return "doubleArray";
        case ParameterType::kParamStringArray:              return "stringArray";
        case ParameterType::kParamBoolArray:                return "boolArray";
        case ParameterType::kParamMdpStateTransitionDef:    return "mdpStateTransitionDef";
        default:                                            return "unknown";
        }
    }

    ParameterType Parameter::stringAsParameterType(const std::string& typeName)
    {
        if (typeName == "int")                      return ParameterType::kParamInt;
        if (typeName == "uint")                     return ParameterType::kParamUInt;
        if (typeName == "float")                    return ParameterType::kParamFloat;
        if (typeName == "double")                   return ParameterType::kParamDouble;
        if (typeName == "string")                   return ParameterType::kParamString;
        if (typeName == "bool")                     return ParameterType::kParamBool;
        if (typeName == "intArray")                 return ParameterType::kParamIntArray;
        if (typeName == "floatArray")               return ParameterType::kParamFloatArray;
        if (typeName == "doubleArray")              return ParameterType::kParamDoubleArray;
        if (typeName == "stringArray")              return ParameterType::kParamStringArray;
        if (typeName == "boolArray")                return ParameterType::kParamBoolArray;
        if (typeName == "mdpStateTransitionDef")    return ParameterType::kParamMdpStateTransitionDef;

        return ParameterType::kParamInvalid;
    }

    bool IntParameter::fromString(const std::string& string)
    {
        if (!isValid()) REPORT_PANIC("Invalid IntParameter");

        try 
        {
            m_value = std::stoi(string);
        }
        catch (const std::invalid_argument&)
        {
            return false;
        }

        return true;
    }

    std::string IntParameter::getValueString() const
    {
        if (!isValid()) REPORT_PANIC("Invalid IntParameter");

        return std::to_string(m_value);
    }

    bool UIntParameter::fromString(const std::string& string)
    {
        if (!isValid()) REPORT_PANIC("Invalid UIntParameter");

        try 
        {
            m_value = static_cast<uint32_t>(std::stoul(string));
        }
        catch (const std::invalid_argument&)
        {
            return false;
        }

        return true;
    }

    std::string UIntParameter::getValueString() const
    {
        if (!isValid()) REPORT_PANIC("Invalid UIntParameter");

        return std::to_string(m_value);
    }

    bool FloatParameter::fromString(const std::string& string)
    {
        if (!isValid()) REPORT_PANIC("Invalid FloatParameter");

        try
        {
            m_value = std::stof(string);
        }
        catch (const std::invalid_argument&)
        {
            return false;
        }

        return true;
    }

    std::string FloatParameter::getValueString() const
    {
        if (!isValid()) REPORT_PANIC("Invalid FloatParameter");

        return std::to_string(m_value);
    }

    bool DoubleParameter::fromString(const std::string& string)
    {
        if (!isValid()) REPORT_PANIC("Invalid DoubleParameter");

        try 
        {
            m_value = std::stod(string);
        }
        catch (const std::invalid_argument&)
        {
            return false;
        }

        return true;
    }

    std::string DoubleParameter::getValueString() const
    {
        if (!isValid()) REPORT_PANIC("Invalid DoubleParameter");

        return std::to_string(m_value);
    }

    bool StringParameter::fromString(const std::string& string)
    {
        if (!isValid()) REPORT_PANIC("Invalid StringParameter");

        m_value = string;

        return true;
    }

    std::string StringParameter::getValueString() const
    {
        if (!isValid()) REPORT_PANIC("Invalid StringParameter");

        return m_value;
    }

    bool BoolParameter::fromString(const std::string& string)
    {
        if (!isValid()) REPORT_PANIC("Invalid BoolParameter");

        std::string lowerStr = string;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);

        if (lowerStr == "true" || lowerStr == "1")
        {
            m_value = true;
        }
        else if (lowerStr == "false" || lowerStr == "0")
        {
            m_value = false;
        }
        else
        {
            return false;
        }

        return true;
    }

    std::string BoolParameter::getValueString() const
    {
        if (!isValid()) REPORT_PANIC("Invalid BoolParameter");

        return m_value ? "true" : "false";
    }

    int IntArrayParameter::getValue(int idx) const
    {
        if (idx < 0 || static_cast<size_t>(idx) >= m_value.size())
            REPORT_PANIC("Index out of range in IntArrayParameter::getValue");

        return m_value[idx];
    }

    void IntArrayParameter::setValue(int idx, int value)
    {
        if (idx < 0 || static_cast<size_t>(idx) >= m_value.size())
            REPORT_PANIC("Index out of range in IntArrayParameter::setValue");

        m_value[idx] = value;
    }

    bool IntArrayParameter::fromString(const std::string& string)
    {
        if (!isValid()) REPORT_PANIC("Invalid IntArrayParameter");

        m_value.clear();

        std::istringstream ss(string);
        std::string item;
        while (std::getline(ss, item, SEPARATOR))
        {
            try 
            {
                m_value.push_back(std::stoi(item));
            }
            catch (const std::invalid_argument&)
            {
                return false;
            }
        }

        return true;
    }

    std::string IntArrayParameter::getValueString() const
    {
        if (!isValid()) REPORT_PANIC("Invalid IntArrayParameter");

        std::ostringstream ss;
        for (size_t i = 0; i < m_value.size(); ++i)
        {
            ss << m_value[i];
            if (i < m_value.size() - 1)
            {
                ss << SEPARATOR;
            }
        }

        return ss.str();
    }

    float FloatArrayParameter::getValue(int idx) const
    {
        if (idx < 0 || static_cast<size_t>(idx) >= m_value.size())
            REPORT_PANIC("Index out of range in FloatArrayParameter::getValue");

        return m_value[idx];
    }

    void FloatArrayParameter::setValue(int idx, float value)
    {
        if (idx < 0 || static_cast<size_t>(idx) >= m_value.size())
            REPORT_PANIC("Index out of range in FloatArrayParameter::setValue");

        m_value[idx] = value;
    }

    bool FloatArrayParameter::fromString(const std::string& string)
    {
        if (!isValid()) REPORT_PANIC("Invalid FloatArrayParameter");
        
        m_value.clear();

        std::istringstream ss(string);
        std::string item;

        while (std::getline(ss, item, SEPARATOR))
        {
            try 
            {
                m_value.push_back(std::stof(item));
            }
            catch (const std::invalid_argument&)
            {
                return false;
            }
        }

        return true;
    }

    std::string FloatArrayParameter::getValueString() const
    {
        if (!isValid()) REPORT_PANIC("Invalid FloatArrayParameter");

        std::ostringstream ss;
        for (size_t i = 0; i < m_value.size(); ++i)
        {
            ss << m_value[i];
            if (i < m_value.size() - 1)
            {
                ss << SEPARATOR;
            }
        }

        return ss.str();
    }

    double DoubleArrayParameter::getValue(int idx) const
    {
        if (idx < 0 || static_cast<size_t>(idx) >= m_value.size())
            REPORT_PANIC("Index out of range in DoubleArrayParameter::getValue");

        return m_value[idx];
    }

    void DoubleArrayParameter::setValue(int idx, double value)
    {
        if (idx < 0 || static_cast<size_t>(idx) >= m_value.size())
            REPORT_PANIC("Index out of range in DoubleArrayParameter::setValue");

        m_value[idx] = value;
    }

    bool DoubleArrayParameter::fromString(const std::string& string)
    {
        if (!isValid()) REPORT_PANIC("Invalid DoubleArrayParameter");

        m_value.clear();

        std::istringstream ss(string);
        std::string item;

        while (std::getline(ss, item, SEPARATOR))
        {
            try 
            {
                m_value.push_back(std::stod(item));
            }
            catch (const std::invalid_argument&)
            {
                return false;
            }
        }

        return true;
    }

    std::string DoubleArrayParameter::getValueString() const
    {
        if (!isValid()) REPORT_PANIC("Invalid DoubleArrayParameter");

        std::ostringstream ss;
        for (size_t i = 0; i < m_value.size(); ++i)
        {
            ss << m_value[i];

            if (i < m_value.size() - 1)
            {
                ss << SEPARATOR;
            }
        }

        return ss.str();
    }

    std::string StringArrayParameter::getValue(int idx) const
    {
        if (idx < 0 || static_cast<size_t>(idx) >= m_value.size())
            REPORT_PANIC("Index out of range in StringArrayParameter::getValue");

        return m_value[idx];
    }

    void StringArrayParameter::setValue(int idx, const std::string& value)
    {
        if (idx < 0 || static_cast<size_t>(idx) >= m_value.size())
            REPORT_PANIC("Index out of range in StringArrayParameter::setValue");

        m_value[idx] = value;
    }

    bool StringArrayParameter::fromString(const std::string& string)
    {
        if (!isValid()) REPORT_PANIC("Invalid StringArrayParameter");

        m_value.clear();
        std::istringstream ss(string);
        std::string item;

        while (std::getline(ss, item, SEPARATOR))
        {
            m_value.push_back(item);
        }

        return true;
    }

    std::string StringArrayParameter::getValueString() const
    {
        if (!isValid()) REPORT_PANIC("Invalid StringArrayParameter");

        std::ostringstream ss;
        for (size_t i = 0; i < m_value.size(); ++i)
        {
            ss << m_value[i];

            if (i < m_value.size() - 1)
            {
                ss << SEPARATOR;
            }
        }

        return ss.str();
    }

    bool BoolArrayParameter::getValue(int idx) const
    {
        if (idx < 0 || static_cast<size_t>(idx) >= m_value.size())
            REPORT_PANIC("Index out of range in BoolArrayParameter::getValue");

        return m_value[idx];
    }

    void BoolArrayParameter::setValue(int idx, bool value)
    {
        if (idx < 0 || static_cast<size_t>(idx) >= m_value.size())
            REPORT_PANIC("Index out of range in BoolArrayParameter::setValue");

        m_value[idx] = value;
    }
    
    bool BoolArrayParameter::fromString(const std::string& string)
    {
        if (!isValid()) REPORT_PANIC("Invalid BoolArrayParameter");

        m_value.clear();
        std::istringstream ss(string);
        std::string item;

        while (std::getline(ss, item, SEPARATOR))
        {
            std::string lowerItem = item;
            std::transform(lowerItem.begin(), lowerItem.end(), lowerItem.begin(), ::tolower);

            if (lowerItem == "true" || lowerItem == "1")
            {
                m_value.push_back(true);
            }
            else if (lowerItem == "false" || lowerItem == "0")
            {
                m_value.push_back(false);
            }
            else
            {
                return false;
            }
        }

        return true;
    }

    std::string BoolArrayParameter::getValueString() const
    {
        if (!isValid()) REPORT_PANIC("Invalid BoolArrayParameter");

        std::ostringstream ss;
        for (size_t i = 0; i < m_value.size(); ++i)
        {
            ss << (m_value[i] ? "true" : "false");

            if (i < m_value.size() - 1)
            {
                ss << SEPARATOR;
            }
        }

        return ss.str();
    }

    bool MdpStateTransitionDefParameter::fromString(const std::string& string)
    {
        if (!isValid()) REPORT_PANIC("Invalid MdpStateTransitionDefParameter");

        std::istringstream ss(string);
        std::string item;
        std::vector<std::string> tokens;

        while (std::getline(ss, item, SEPARATOR))
            tokens.push_back(item);

        if (tokens.size() != 4)
            return false;

        m_stateID = std::stoi(tokens[0]);
        m_nextStateID = std::stoi(tokens[1]);
        m_probability = std::stod(tokens[2]);
        m_cost = std::stod(tokens[3]);

        return true;
    }

    std::string MdpStateTransitionDefParameter::getValueString() const
    {
        if (!isValid()) REPORT_PANIC("Invalid MdpStateTransitionDefParameter");

        std::ostringstream ss;
        ss << m_stateID << SEPARATOR << m_nextStateID << SEPARATOR << m_probability << SEPARATOR << m_cost;

        return ss.str();
    }
} // namespace rlib