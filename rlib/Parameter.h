#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
#include <vector>

#include "../mocc/mocc.hpp"

namespace rlib 
{
    enum class ParameterType
    {
        kParamInvalid,
        kParamInt,
        kParamUInt,
        kParamFloat,
        kParamDouble,
        kParamString,
        kParamBool,
        kParamIntArray,
        kParamFloatArray,
        kParamDoubleArray,
        kParamStringArray,
        kParamBoolArray,
        kParamMdpStateTransitionDef,

        kParamNumTypes
    };

    class Parameter
    {
    public:
        Parameter(const std::string& name, const std::string& typeName, ParameterType type) : m_name(name), m_typeName(typeName), m_type(type) {}
        virtual ~Parameter() = default;

        /*
        Parses the parameter value from a string representation.
        Returns:
        - true if parsing was successful, false otherwise.
        */
        virtual bool fromString(const std::string& string) = 0;

        /*
        Converts the parameter value to its string representation.
        Returns:
        - The string representation of the parameter value.
        */
        virtual std::string getValueString() const = 0;

        /*
        Checks if the parameter is valid.
        Returns:
        - true if the parameter is valid, false otherwise.
        */
        virtual bool isValid() const { return false; }

        std::string getName() const { return m_name; }
        std::string getTypeName() const { return m_typeName; }
        ParameterType getType() const { return m_type; }

        void rename(const std::string& newName) { m_name = newName; }

        /*
        Converts a ParameterType to its string representation.
        Returns:
        - The string representation of the ParameterType.
        */
        static const char* parameterTypeAsString(ParameterType type);

        /*
        Converts a string representation of a parameter type to its ParameterType enum.
        Returns:
        - The corresponding ParameterType enum value.
        */
        static ParameterType stringAsParameterType(const std::string& typeName);
    protected:
        std::string m_name;
        std::string m_typeName;
        ParameterType m_type;

        bool isOfType(ParameterType type) const { return m_type == type; }
    };

    class IntParameter : public Parameter
    {
    public:
        IntParameter(const std::string& name) : Parameter(name, "int", ParameterType::kParamInt), m_value(0) {}
        IntParameter(const std::string& name, const std::string& typeName) : Parameter(name, typeName, ParameterType::kParamInt), m_value(0) {}    
        
        virtual ~IntParameter() override = default;

        bool fromString(const std::string& string) override;
        std::string getValueString() const override;
        bool isValid() const override { return isOfType(ParameterType::kParamInt); }

        int getValue() const { return m_value; }
        void setValue(int value) { m_value = value; }
    private:
        int m_value;
    };

    class UIntParameter : public Parameter
    {
    public:
        UIntParameter(const std::string& name) : Parameter(name, "uint", ParameterType::kParamUInt), m_value(0) {}
        UIntParameter(const std::string& name, const std::string& typeName) : Parameter(name, typeName, ParameterType::kParamUInt), m_value(0) {}
        
        virtual ~UIntParameter() override = default;
        
        bool fromString(const std::string& string) override;
        std::string getValueString() const override;
        bool isValid() const override { return isOfType(ParameterType::kParamUInt); }

        uint32_t getValue() const { return m_value; }
        void setValue(uint32_t value) { m_value = value; } 
    private:
        uint32_t m_value;
    };

    class FloatParameter : public Parameter
    {
    public:
        FloatParameter(const std::string& name) : Parameter(name, "float", ParameterType::kParamFloat), m_value(0.0f) {}
        FloatParameter(const std::string& name, const std::string& typeName) : Parameter(name, typeName, ParameterType::kParamFloat), m_value(0.0f) {}
        
        virtual ~FloatParameter() override = default;

        bool fromString(const std::string& string) override;
        std::string getValueString() const override;
        bool isValid() const override { return isOfType(ParameterType::kParamFloat); }

        float getValue() const { return m_value; }
        void setValue(float value) { m_value = value; }
    private:
        float m_value;
    };

    class DoubleParameter : public Parameter
    {
    public:
        DoubleParameter(const std::string& name) : Parameter(name, "double", ParameterType::kParamDouble), m_value(0.0) {}
        DoubleParameter(const std::string& name, const std::string& typeName) : Parameter(name, typeName, ParameterType::kParamDouble), m_value(0.0) {}
        
        virtual ~DoubleParameter() override = default;

        bool fromString(const std::string& string) override;
        std::string getValueString() const override;
        bool isValid() const override { return isOfType(ParameterType::kParamDouble); }

        double getValue() const { return m_value; }
        void setValue(double value) { m_value = value; }
    private:
        double m_value;
    };

    class StringParameter : public Parameter
    {
    public:
        StringParameter(const std::string& name) : Parameter(name, "string", ParameterType::kParamString), m_value("") {}
        StringParameter(const std::string& name, const std::string& typeName) : Parameter(name, typeName, ParameterType::kParamString), m_value("") {}
        
        virtual ~StringParameter() override = default;

        bool fromString(const std::string& string) override;
        std::string getValueString() const override;
        bool isValid() const override { return isOfType(ParameterType::kParamString); }

        const std::string& getValue() const { return m_value; }
        void setValue(const std::string& value) { m_value = value; }
    private:
        std::string m_value;
    };

    class BoolParameter : public Parameter
    {
    public:
        BoolParameter(const std::string& name) : Parameter(name, "bool", ParameterType::kParamBool), m_value(false) {}
        BoolParameter(const std::string& name, const std::string& typeName) : Parameter(name, typeName, ParameterType::kParamBool), m_value(false) {}
        
        virtual ~BoolParameter() override = default;

        bool fromString(const std::string& string) override;
        std::string getValueString() const override;
        bool isValid() const override { return isOfType(ParameterType::kParamBool); }

        bool getValue() const { return m_value; }
        void setValue(bool value) { m_value = value; }
    private:
        bool m_value;
    };

    class IntArrayParameter : public Parameter
    {
    public:
        IntArrayParameter(const std::string& name) : Parameter(name, "intArray", ParameterType::kParamIntArray) {}
        IntArrayParameter(const std::string& name, const std::string& typeName) : Parameter(name, typeName, ParameterType::kParamIntArray) {}
        
        virtual ~IntArrayParameter() override = default;

        bool fromString(const std::string& string) override;
        std::string getValueString() const override;
        bool isValid() const override { return isOfType(ParameterType::kParamIntArray); }

        size_t getNumValues() const { return m_value.size(); }
        int getValue(int idx) const;
        void setValue(int idx, int value);
    private:
        std::vector<int> m_value;
    };

    class FloatArrayParameter : public Parameter
    {
    public:
        FloatArrayParameter(const std::string& name) : Parameter(name, "floatArray", ParameterType::kParamFloatArray) {}
        FloatArrayParameter(const std::string& name, const std::string& typeName) : Parameter(name, typeName, ParameterType::kParamFloatArray) {}
        
        virtual ~FloatArrayParameter() override = default;

        bool fromString(const std::string& string) override;
        std::string getValueString() const override;
        bool isValid() const override { return isOfType(ParameterType::kParamFloatArray); }

        size_t getNumValues() const { return m_value.size(); }
        float getValue(int idx) const;
        void setValue(int idx, float value);
    private:
        std::vector<float> m_value;
    };

    class DoubleArrayParameter : public Parameter
    {
    public:
        DoubleArrayParameter(const std::string& name) : Parameter(name, "doubleArray", ParameterType::kParamDoubleArray) {}
        DoubleArrayParameter(const std::string& name, const std::string& typeName) : Parameter(name, typeName, ParameterType::kParamDoubleArray) {}
        
        virtual ~DoubleArrayParameter() override = default;

        bool fromString(const std::string& string) override;
        std::string getValueString() const override;
        bool isValid() const override { return isOfType(ParameterType::kParamDoubleArray); }

        size_t getNumValues() const { return m_value.size(); }
        double getValue(int idx) const;
        void setValue(int idx, double value);
    private:
        std::vector<double> m_value;
    };

    class StringArrayParameter : public Parameter
    {
    public:
        StringArrayParameter(const std::string& name) : Parameter(name, "stringArray", ParameterType::kParamStringArray) {};
        StringArrayParameter(const std::string& name, const std::string& typeName) : Parameter(name, typeName, ParameterType::kParamStringArray) {};
        
        virtual ~StringArrayParameter() override = default;

        bool fromString(const std::string& string) override;
        std::string getValueString() const override;
        bool isValid() const override { return isOfType(ParameterType::kParamStringArray); }

        size_t getNumValues() const { return m_value.size(); }
        std::string getValue(int idx) const;
        void setValue(int idx, const std::string& value);
    private:
        std::vector<std::string> m_value;
    };

    class BoolArrayParameter : public Parameter
    {
    public:
        BoolArrayParameter(const std::string& name) : Parameter(name, "boolArray", ParameterType::kParamBoolArray) {};
        BoolArrayParameter(const std::string& name, const std::string& typeName) : Parameter(name, typeName, ParameterType::kParamBoolArray) {};
        
        virtual ~BoolArrayParameter() override = default;

        bool fromString(const std::string& string) override;
        std::string getValueString() const override;
        bool isValid() const override { return isOfType(ParameterType::kParamBoolArray); }

        size_t getNumValues() const { return m_value.size(); }
        bool getValue(int idx) const;
        void setValue(int idx, bool value);
    private:
        std::vector<bool> m_value;
    };

    class MdpStateTransitionDefParameter : public Parameter
    {
    public:
        MdpStateTransitionDefParameter(const std::string& name) : Parameter(name, "mdpStateTransitionDef", ParameterType::kParamMdpStateTransitionDef),
        m_stateID(-1), 
        m_nextStateID(-1),
        m_probability(0.0), 
        m_cost(0.0) {};

        MdpStateTransitionDefParameter(const std::string& name, const std::string& typeName) : Parameter(name, typeName, ParameterType::kParamMdpStateTransitionDef),
        m_stateID(-1), 
        m_nextStateID(-1),
        m_probability(0.0), 
        m_cost(0.0) {};
        
        virtual ~MdpStateTransitionDefParameter() override = default;

        bool fromString(const std::string& string) override;
        std::string getValueString() const override;
        bool isValid() const override { return isOfType(ParameterType::kParamMdpStateTransitionDef); }

        int getStateID() const { return m_stateID; }
        int getNextStateID() const { return m_nextStateID; }
        real_t getProbability() const { return m_probability; }
        real_t getCost() const { return m_cost; }

        void setStateID(int stateID) { m_stateID = stateID; }
        void setNextStateID(int stateID) { m_nextStateID = stateID; }
        void setProbability(real_t probability) { m_probability = probability; }
        void setCost(real_t cost) { m_cost = cost; }
    private:
        int m_stateID;
        int m_nextStateID;
        real_t m_probability;
        real_t m_cost;
    };
} // namespace rlib

#endif // PARAMETER_H