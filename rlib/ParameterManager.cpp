#include "ParameterManager.h"
#include <fstream>
#include <stdexcept>
#include "Debug.h"

namespace rlib
{
    ParameterManager::ParameterManager()
    {
        m_factory = new ParameterFactory();
    };

    ParameterManager::~ParameterManager()
    {
        for (Parameter* param : m_parameters)
            delete param;

        delete m_factory;
    }

    Parameter* ParameterManager::getParameter(size_t index) const
    {
        if (index < m_parameters.size())
            return m_parameters[index];

        REPORT_PANIC("ParameterManager::getParameter: index out of range");
    }

    Parameter* ParameterManager::getParameter(const std::string& name) const
    {
        for (Parameter* param : m_parameters)
        {
            if (param->getName() == name)
                return param;
        }

        return nullptr;
    }

    Parameter* ParameterManager::getFirstParameterOfTypeName(const std::string& typeName) const
    {
        for (Parameter* param : m_parameters)
        {
            if (param->getTypeName() == typeName)
                return param;
        }

        return nullptr;
    }

    Parameter* ParameterManager::registerParameter(const std::string& typeName, const std::string& valueStr)
    {
        std::string paramName = typeName + "_" + std::to_string(getNumParametersOfTypeName(typeName) + 1);

        Parameter* param = m_factory->makeParameter(typeName, paramName);
        if (!param->fromString(valueStr))
        {
            delete param;
            LOG_ERROR("Failed to parse parameter '%s' from string '%s'\n", paramName.c_str(), valueStr.c_str());
            
            return nullptr;
        }

        LOG_DEBUG("Registered parameter: name='%s', typeName='%s', type='%s', value='%s'\n", param->getName().c_str(), param->getTypeName().c_str(), Parameter::parameterTypeAsString(param->getType()), valueStr.c_str());
        m_parameters.push_back(param);

        return param;
    }

    void ParameterManager::unregisterParameter(size_t index)
    {
        if (index < m_parameters.size())
        {
            delete m_parameters[index];
            m_parameters.erase(m_parameters.begin() + index);

            return;
        }

        REPORT_PANIC("ParameterManager::unregisterParameter: index out of range");
    }

    bool ParameterManager::loadFromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            REPORT_PANIC("ParameterManager::loadFromFile: failed to open file " + filename);
            return false;
        }

        int numberOfLoadedParameters = 0;

        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty()) 
                continue;

            std::string typeName;
            std::string valueStr;
            
            size_t delimiterPos = line.find(' ');
            if (delimiterPos == std::string::npos)
            {
                LOG_WARNING("Skipping invalid line (no delimiter found): %s\n", line.c_str());
                continue;
            }

            typeName = line.substr(0, delimiterPos);
            valueStr = line.substr(delimiterPos + 1);

            registerParameter(typeName, valueStr);

            numberOfLoadedParameters++;
        }

        file.close();

        LOG_DEBUG("Successfully loaded %d parameters from file '%s'\n", numberOfLoadedParameters, filename.c_str());
        
        return true;
    }

    uint32_t ParameterManager::getNumParametersOfTypeName(const std::string& typeName) const
    {
        uint32_t count = 0;

        for (Parameter* param : m_parameters)
        {
            if (param->getTypeName() == typeName)
                count++;
        }

        return count;
    }

    uint32_t ParameterManager::getNumParametersOfType(ParameterType type) const
    {
        uint32_t count = 0;

        for (Parameter* param : m_parameters)
        {
            if (param->getType() == type)
                count++;
        }

        return count;
    }

    void ParameterManager::getParametersOfType(ParameterType type, std::vector<Parameter*>& outParameters) const
    {
        outParameters.clear();
        outParameters.reserve(getNumParametersOfType(type));
        
        for (Parameter* param : m_parameters)
        {
            if (param->getType() == type)
                outParameters.push_back(param);
        }
    }
} // namespace rlib