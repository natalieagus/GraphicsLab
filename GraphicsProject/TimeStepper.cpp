#include "TimeStepper.hpp"
#include <iostream>

float TimeStepper::updatedStepsize = 0.0f;


//TODO: Implement RK4 rule here

void RK4::takeStep(SolarSystem* solarSystem, float stepSize)
{
    
    vector<Vector3f> nextState;
    
    vector<Vector3f> k2;
    vector<Vector3f> k3;
    vector<Vector3f> k4;
    
    vector<Vector3f> s2;
    vector<Vector3f> s3;
    vector<Vector3f> s4;
    
    vector<Vector3f> s1 = solarSystem->getState();
    
    vector<Vector3f> k1 = solarSystem->evalF(s1);
    
   // unsigned size = s1.size();
    
    for (int i =0 ; i<s1.size(); i++){
        Vector3f s = s1[i] + 0.5f * stepSize * k1[i];
        s2.push_back(s);
    }
    
    k2 = solarSystem->evalF(s2);
    
    for (int i = 0; i<s1.size(); i++){
        Vector3f s = s1[i] + 0.5f  * stepSize * k2[i];
        s3.push_back(s);
    }
    
    k3 = solarSystem->evalF(s3);
    
    for (int i =0 ;i<s1.size(); i++){
        Vector3f s = s1[i] + stepSize * k3[i];
        s4.push_back(s);
    }
    
    k4 = solarSystem->evalF(s4);
    
    for (int i = 0; i<s1.size(); i++){
        Vector3f sFinal = s1[i] + (1.0f/6.0f) * stepSize * (k1[i]+2*k2[i]+2*k3[i]+k4[i]);
        nextState.push_back(sFinal);
    }
    
    solarSystem->setState(nextState, s1);
    
}
