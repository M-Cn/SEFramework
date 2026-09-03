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
    printf("This test will output messages only if compiled in debug mode.\n");

    LOG_INFO("This is a log info message.\n");
    LOG_DEBUG("This is a log debug message.\n");
    LOG_WARNING("This is a log warning message.\n");
    LOG_ERROR("This is a log error message.\n");
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
        LOG_DEBUG("IntParameter parsed value: %d\n", intParam.getValue());
    }
    else
    {
        LOG_ERROR("Failed to parse IntParameter.\n");
    }

    RASSERT(intParam.getValue() == 42, "IntParameter value should be 42");

    rlib::DoubleParameter doubleParam("TestDouble");
    if (doubleParam.fromString("3.14159"))
    {
        LOG_DEBUG("DoubleParameter parsed value: %.5f\n", doubleParam.getValue());
    }
    else
    {
        LOG_ERROR("Failed to parse DoubleParameter.\n");
    }

    RASSERT(std::abs(doubleParam.getValue() - 3.14159) < 1e-5, "DoubleParameter value should be approximately 3.14159");

    rlib::StringParameter stringParam("TestString");
    if (stringParam.fromString("Hello, World!"))
    {
        LOG_DEBUG("StringParameter parsed value: %s\n", stringParam.getValue().c_str());
    }
    else
    {
        LOG_ERROR("Failed to parse StringParameter.\n");
    }

    RASSERT(stringParam.getValue() == "Hello, World!", "StringParameter value should be 'Hello, World!'");

    rlib::BoolParameter boolParam("TestBool");
    if (boolParam.fromString("true"))
    {
        LOG_DEBUG("BoolParameter parsed value: %s\n", boolParam.getValue() ? " true" : "false");
    }
    else
    {
        LOG_ERROR("Failed to parse BoolParameter.\n");
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
                LOG_DEBUG("Parameter %zu: (name='%s', type='%s', value='%s')\n", i, param->getName().c_str(), rlib::Parameter::parameterTypeAsString(param->getType()), param->getValueString().c_str());
        }
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("Failed to load parameters: %s\n", e.what());
    }
}

void panicTest()
{
    printf("------Panic test------\n");

    try 
    {
        rlib::setPanicMode(rlib::PanicMode::kPanicModeAbort);
        REPORT_PANIC("This is a test panic message.");
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("%s\n", e.what());
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