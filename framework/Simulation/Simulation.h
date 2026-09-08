#ifndef SIMULATION_H
#define SIMULATION_H

#include "../../rlib/rlib.h"

class Simulation
{
public:
    Simulation() = default;
    virtual ~Simulation() = default;
    
    virtual bool initialize() { return true; }
    virtual void finalize() {}
    virtual void update(float _dt) {}
    virtual bool isFinished() const = 0;
    virtual void onSimulationFinished() = 0;
};

#endif // SIMULATION_H