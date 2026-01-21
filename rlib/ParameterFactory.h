#ifndef PARAMETER_FACTORY_H
#define PARAMETER_FACTORY_H

#include "Parameter.h"
#include <map>
#include <string>

namespace rlib
{
    class ParameterFactory
    {
    public:
        ParameterFactory();
        ~ParameterFactory() = default;

        /*
        Registers a new parameter type with its corresponding name.
        Parameters:
        - typeName: The name of the parameter type.
        - type: The ParameterType enum value.
        */
        void registerParameterType(const std::string& typeName, ParameterType type) { m_typeMap[typeName] = type; }

        /*
        Unregisters a parameter type.
        Parameters:
        - typeName: The name of the parameter type to unregister.
        */
        void unregisterParameterType(const std::string& typeName) { m_typeMap.erase(typeName); }

        /*
        Gets the ParameterType enum value for a given parameter type name.
        Parameters:
        - typeName: The name of the parameter type.
        Returns:
        - The corresponding ParameterType enum value.
        */
        ParameterType getParameterType(const std::string& typeName) const;

        /*
        Creates a Parameter object based on the provided type name.
        Parameters:
        - typeName: The name of the parameter type.
        Returns:
        - A pointer to the created Parameter object.
        */
        Parameter* makeParameter(const std::string& typeName, const std::string& name) const;

    private:
        /*
        Registers the default parameter types.
        */
        void registerDefaultTypes();

        std::map<std::string, ParameterType> m_typeMap;
    };
} // namespace rlib

#endif // PARAMETER_FACTORY_H