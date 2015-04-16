//
//  asteroidSystem.cpp
//  GraphicsProject
//
//  Created by Crystal Tee on 10/4/15.
//  Copyright (c) 2015 Natalie Agus. All rights reserved.
//

#include "asteroidSystem.h"

#define GRAV_C 6.67*pow(10,-11)
#define SCALE_F 0.1289
#define m_E 5.972 * pow(10,24)
#define AU 1.496 * pow(10,11)


AsteroidSystem::AsteroidSystem(SolarSystem solSys){

    this->solSys = solSys;
};
void AsteroidSystem::addAsteroid(Vector3f pos){
    this->asteroids.push_back(Asteroid());
    
    //scale pos
    
    double scale = pow(pos.abs() * solSys.min_dist,3.0);
    this->state.push_back(scale*(pos.normalized()));
    sysSize++;
};
void AsteroidSystem::delAsteroid(Asteroid ast){
    //yet to implement
};
void AsteroidSystem::draw(){
    
};
void AsteroidSystem::toString(){
    
};
    vector<Asteroid> asteroids;
    vector<Vector3f> state;
    vector<Vector3f> oldstate;
    
    int sysSize;    //no. of asteroids

vector<Vector3f> AsteroidSystem::evalF(vector<Vector3f> currentState){
    
    vector<Vector3f> vel;
    
    vector<Planet> planets = solSys.planets;
    
    for(int i=0; i<sysSize;i++){ //calc v for all asteroids
        
        Vector3f pos = state[i],v;
        
        //adjust for negative 0 because using double
        if(pos.x()==0){
            
            v = Vector3f(pos.z(),pos.y(),pos.x());
        }
        else{
            v = Vector3f(pos.z(),pos.y(),pos.x()*-1.0);
        }
        
        double sum=0.0;
        
        for(int j=0; j<solSys.sysSize;j++){     //loop thru all planet
                
                //calculate v
                
                //double dist = abs(planets[j].getDist()*1000 - asteroids[i].getDist());
                
                double dist = (solSys.state[j] - currentState[i]).abs();
                
                sum+=(planets[j].getMass()* (double) m_E /dist);
            
        }
        
        for(int j=0; j<solSys.sysSize;j++){     //loop thru all asteroid
            
            
            if (i==j){
                continue;
            }
            else{
                
                //calculate v
                
                //double dist = abs(planets[j].getDist()*1000 - asteroids[i].getDist());
                
                double dist = (currentState[j] - currentState[i]).abs();
                
                sum+=(asteroids[j].getMass()* (double) m_E /dist);
                
            }
            
        }
        
        
        //float k = sqrt(sum*(double)GRAV_C)*SCALE_F;
        float k = sqrt(sum*(double)GRAV_C);
        vel.push_back(k*v.normalized());
        //vel.push_back(v);
        
    }
    
    
    return vel;
};

vector<Vector3f> AsteroidSystem::getState(){
    return state;
}

void AsteroidSystem::setState(vector<Vector3f> nextState, vector<Vector3f> currentState){
    state = nextState;
    oldstate = currentState;
    
};