#ifndef PARAMETER_MANAGER_H
#define PARAMETER_MANAGER_H

#include "ParameterFactory.h"
#include <vector>

namespace rlib
{
    class ParameterManager
    {
    public:
        ParameterManager();
        ~ParameterManager();

        /*
        Gets a parameter by its index.
        Parameters:
        - index: The index of the parameter.
        Returns:
        - A pointer to the Parameter object.
        */
        Parameter* getParameter(size_t index) const;

        /*
        Gets a parameter by its type name.
        Parameters:
        - typeName: The name of the parameter type.
        Returns:
        - A pointer to the Parameter object, or nullptr if not found.
        */
        Parameter* getParameter(const std::string& name) const;

        Parameter* getFirstParameterOfTypeName(const std::string& typeName) const;

        /*
        Gets the number of parameters.
        Returns:
        - The number of parameters.
        */
        size_t getNumParameters() const { return m_parameters.size(); }

        /*
        Registers a new parameter type with its corresponding name.
        Parameters:
        - typeName: The name of the parameter type.
        - type: The ParameterType enum value.
        */
        void registerParameterType(const std::string& typeName, ParameterType type) { m_factory->registerParameterType(typeName, type); }

        /*
        Unregisters a parameter type by its name.
        Parameters:
        - typeName: The name of the parameter type to unregister.
        */
        void unregisterParameterType(const std::string& typeName) { m_factory->unregisterParameterType(typeName); }

        /*
        Registers a new parameter by its type name and string value.
        Parameters:
        - typeName: The name of the parameter type.
        - valueStr: The string representation of the parameter value.
        Returns:
        - A pointer to the registered Parameter object.
        */
        Parameter* registerParameter(const std::string& typeName, const std::string& valueStr);

        /*
        Unregisters a parameter by its index.
        Parameters:
        - index: The index of the parameter to unregister.
        */
        void unregisterParameter(size_t index);

        /*
        Loads parameters from a configuration file.
        Parameters:
        - filename: The path to the configuration file.
        Returns:
        - true if loading was successful, false otherwise.
        */
        bool loadFromFile(const std::string& filename);

        /*
        Gets all parameters of a specific ParameterType.
        Parameters:
        - type: The ParameterType to filter by.
        - outParameters: A vector to store the pointers to the parameters of the specified type.
        */
        void getParametersOfType(ParameterType type, std::vector<Parameter*>& outParameters) const;

        /*
        Counts the number of parameters with the given type name.
        Parameters:
        - typeName: The name of the parameter type to count.
        Returns:
        - The number of parameters with the given type name.
        */
        uint32_t getNumParametersOfTypeName(const std::string& typeName) const;

        /*
        Counts the number of parameters with the given ParameterType.
        Parameters:
        - type: The ParameterType to count.
        Returns:
        - The number of parameters with the given ParameterType.
        */
        uint32_t getNumParametersOfType(ParameterType type) const;
    private:
        /*
        Checks if a parameter with the given type name already exists.
        Parameters:
        - typeName: The name of the parameter type to check.
        Returns:
        - true if a parameter with the given type name exists, false otherwise.
        */
        bool hasDuplicateParameter(const std::string& name) const { return getParameter(name) != nullptr; }

        std::vector<Parameter*> m_parameters;
        ParameterFactory* m_factory;
    };
} // namespace rlib
#endif