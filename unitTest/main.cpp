#include "../rlib/rlib.h"
#include <stdio.h>
#include <stdlib.h>

void reportTestResultTest()
{
    printf("------Report test result test------\n");

    RASSERT(1 + 1 == 2, "This test is supposed to pass");
    RASSERT(2 * 2 == 5, "This test is supposed to fail");
}

void logTest()
{
    printf("------Log test------\n");
    
#ifndef DEBUG
    printf("This test will output messages only if compiled in debug mode.\n");
#endif

    LOG_INFO("This is a log info message.");
    LOG_DEBUG("This is a log debug message.");
    LOG_WARNING("This is a log warning message.");
    LOG_ERROR("This is a log error message.");
}

void mdpTest()
{
    printf("------MDP test------\n");
}

void parameterTest()
{
    printf("------Parameter test------\n");

    rlib::IntParameter intParam("TestInt");
    if (intParam.fromString("42"))
    {
        LOG_DEBUG("IntParameter parsed value: %d", intParam.getValue());
    }
    else
    {
        LOG_ERROR("Failed to parse IntParameter.");
    }

    RASSERT(intParam.getValue() == 42, "IntParameter value should be 42");

    rlib::DoubleParameter doubleParam("TestDouble");
    if (doubleParam.fromString("3.14159"))
    {
        LOG_DEBUG("DoubleParameter parsed value: %.5f", doubleParam.getValue());
    }
    else
    {
        LOG_ERROR("Failed to parse DoubleParameter.");
    }

    RASSERT(std::abs(doubleParam.getValue() - 3.14159) < 1e-5, "DoubleParameter value should be approximately 3.14159");

    rlib::StringParameter stringParam("TestString");
    if (stringParam.fromString("Hello, World!"))
    {
        LOG_DEBUG("StringParameter parsed value: %s", stringParam.getValue().c_str());
    }
    else
    {
        LOG_ERROR("Failed to parse StringParameter.");
    }

    RASSERT(stringParam.getValue() == "Hello, World!", "StringParameter value should be 'Hello, World!'");

    rlib::BoolParameter boolParam("TestBool");
    if (boolParam.fromString("true"))
    {
        LOG_DEBUG("BoolParameter parsed value: %s", boolParam.getValue() ? " true" : "false");
    }
    else
    {
        LOG_ERROR("Failed to parse BoolParameter.");
    }

    RASSERT(boolParam.getValue() == true, "BoolParameter value should be true");
}

void parameterLoadTest()
{
    printf("------Parameter load test------\n");

    rlib::ParameterManager paramManager;

    try 
    {
        paramManager.registerParameterType("N", rlib::ParameterType::kParamInt);
        paramManager.registerParameterType("A", rlib::ParameterType::kParamMdpStateTransitionDef);
        
        paramManager.loadFromFile("parameters.txt");
        size_t numParams = paramManager.getNumParameters();

        for (size_t i = 0; i < numParams; ++i)
        {
            rlib::Parameter* param = paramManager.getParameter(i);

            if (param != nullptr)
                LOG_DEBUG("Parameter %zu: (name='%s', type='%s', value='%s')", i, param->getName().c_str(), rlib::Parameter::parameterTypeAsString(param->getType()), param->getValueString().c_str());
        }
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("Failed to load parameters: %s", e.what());
    }
}

void panicTest()
{
    printf("------Panic test------\n");

    try 
    {
        rlib::setPanicMode(rlib::PanicMode::kPanicModeThrowException);
        RPANIC("This is a test panic message.");
    }
    catch (const rlib::PanicException& e)
    {
        LOG_INFO("Panic test completed successfully (%s).", e.what());
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("Unexpected exception: %s", e.what());
    }
}

int main() 
{
    reportTestResultTest();
    logTest();
    mdpTest();
    parameterTest();
    parameterLoadTest();
    panicTest();
    
    return EXIT_SUCCESS;
}