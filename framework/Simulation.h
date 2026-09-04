#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation
{
public:
    Simulation() = default;
    virtual ~Simulation() = default;
    
    virtual bool initialize() { return true; }
    virtual void finalize() {}
    virtual void update(float _dt) {}

protected:
    /*
    Retrieves the result of the simulation and stores it in the provided pointer.
    Parameters:
    - _pResult: A pointer to the memory location where the result will be stored.
    Note: The type of the result is determined by the specific implementation of the simulation. 
    As such, the actual result should be exposed by another user defined function that calls this function and casts the result to the appropriate type.
    */
    virtual void _getResult(void* _pResult) = 0;
};

#endif // SIMULATION_H