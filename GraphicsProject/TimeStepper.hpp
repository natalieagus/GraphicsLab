#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "vecmath.h"
#include <vector>
#include "SolarSystem.h"

class TimeStepper
{
public:
	virtual void takeStep(SolarSystem* solarSystem,float stepSize)=0;
    static float updatedStepsize;
};

class RK4:public TimeStepper
{

  void takeStep(SolarSystem* solarSystem, float stepSize);
};

#endif
