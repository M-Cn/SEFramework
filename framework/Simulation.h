#ifndef SIMULATION_H
#define SIMULATION_H

/*
 * Represents the result of a simulation.
 * Note: This class should be inherited from by specific simulation result types to provide additional data and functionality as needed.
 */
struct SimulationResult 
{
public:
    virtual ~SimulationResult() = default;
};

class Simulation
{
public:
    Simulation() = default;
    virtual ~Simulation() = default;
    
    virtual bool initialize() { return true; }
    virtual void finalize() {}
    virtual void update(float _dt) {}

    template<typename T>
    bool getResult(T& _outResult) 
    {
        return _getResultInternal(&_outResult);
    }

protected:
    /*
    Retrieves the result of the simulation and stores it in the provided pointer.
    Parameters:
    - _pResult: A pointer to an instance of SimulationResult.
    Note: The type of the result is determined by the specific implementation of the simulation. 
    As such, the actual result should be exposed by another user defined function that calls this function and casts the result to the appropriate type.
    */
    virtual bool _getResultInternal(SimulationResult* _pResult) = 0;
};

#endif // SIMULATION_H