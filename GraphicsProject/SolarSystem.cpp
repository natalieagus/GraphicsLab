//
//  SolarSystem.cpp
//  GraphicsProject
//
//  Created by Crystal Tee on 25/3/15.
//  Copyright (c) 2015 Natalie Agus. All rights reserved.
//

#include "SolarSystem.h"
#include "Planet.h"
#include <string>
#include <cmath>

#define GRAV_C 6.67*pow(10,-11)


SolarSystem::SolarSystem(){

    //initialise Solar System here
    Planet earth("earth", 1.0, 1.0, 1.0, 1.0);
    this->planets.push_back(earth);
    
    vector<Vector3f> pos,vel;
    pos.push_back(Vector3f(earth.getDist(),0,0));
    vel.push_back(Vector3f(0,0,0));
    
    
    this->state.insert(this->state.end(), pos.begin(),pos.end());
    this->state.insert(this->state.end(), vel.begin(),vel.end());
    this->sysSize = planets.size();
    
    
    //keep states as x1,x2,x3,x4...,v1,v2,v3,v4...
    
};

void SolarSystem::parseCSV(char* filepath){
    
}

void SolarSystem::draw(){
    
};

vector<Vector3f> SolarSystem::evalF(){
    
    vector<Vector3f> acc;
    vector<Vector3f> pos(this->state.begin(),this->state.begin()+this->sysSize);
    vector<Vector3f> vel(this->state.begin()+this->sysSize,this->state.end());
  
    for(int i=0; i<this->sysSize;i++){
        
        Vector3f a(0,0,0);
        Vector3f loc_i = pos[i];
        for(int j=0; j<this->sysSize;j++){
            
            if (i==j){
                continue;
            }
            else{
                
                //calculate accel vector here
                float m = planets[j].getMass();
                Vector3f dist = pos[j] - loc_i;
                
                float k = (GRAV_C * m) /pow(dist.abs(),3);
                
                a = a + (k * dist);     //sum up for all planets
                
                
            }
            
        }
        
        acc.push_back(a);
        
        
    }
    vel.insert(vel.end(),acc.begin(),acc.end());
    return vel;
}

void SolarSystem::toString(){
    
    for(int i=0;i<this->planets.size();i++){
        this->planets[i].toString();
    }
}
