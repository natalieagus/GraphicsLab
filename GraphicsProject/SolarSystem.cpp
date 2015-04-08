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
#include <fstream>
#include <sstream>
#include <iostream>
#include <istream>
#include <stdio.h>
#include <stdlib.h>


//#define GRAV_C 6.67*pow(10,-11)
#define GRAV_C 3.337*pow(10,-69)    //defined in AU^3 / (M_e *s^2)

using namespace std;

SolarSystem::SolarSystem(){
    
}
SolarSystem::SolarSystem(char* filePath){
    
    //read and parse file
    
    vector<Vector3f> pos,vel;
    cout<<"filePath: "<<filePath<<endl;
    
    FILE *fp = fopen(filePath,"r");
    //FILE *fp = fopen("sunEarthData.csv","r");
    char line[1024];
    
    if(fp == NULL){
        cerr<<"Failed to open file"<<endl;
    }
    else{
    
        
        while(fgets(line,1024,fp)){
           // cout<<line<<endl;
            char* tok;
            vector<char*> toks;
            
            
            tok = strtok(line,",");
            
            while (tok != NULL)
            {
               // printf ("%s\n",tok);
                toks.push_back(tok);
                tok = strtok (NULL, ",");
            }
            cout << atof(toks [1]) << " " << toks[2]<<endl;
            Planet p(toks[0],atof(toks[1]),atof(toks[2]),atof(toks[3]),atof(toks[4]));
            this->planets.push_back(p);
            pos.push_back(Vector3f(p.getDist(),0,0));
            vel.push_back(Vector3f(0,0,0));
            cout << "doing values" << pos.size() << vel.size()<<endl;
            
            
        }
    }
    
    //initialise Solar System here
    for (int i = 0; i<vel.size(); i++){
        pos.push_back(vel[i]);
    }
    this->state = pos;
    cout << "state size is "<<state.size()<<endl;
    this->sysSize = planets.size();
    
    cout<<"Solar system initializaton done"<<endl;
    
    //keep states as x1,x2,x3,x4...,v1,v2,v3,v4...
    
};

void SolarSystem::draw(){
    
};

vector<Vector3f> SolarSystem::evalF(vector<Vector3f> state){
    
    vector<Vector3f> acc;
    
    vector<Vector3f> pos;
    
    for (int i = 0; i<ceil(state.size()/2) ; i++){
        //printf("dist: %f",state[i][0]);
        pos.push_back(state[i]);
    }
    
    vector<Vector3f> vel;
    for (int i = ceil (state.size()/2); i< state.size(); i++){
        vel.push_back(state[i]);
    }
  
    for(int i=0; i<this->sysSize;i++){
        
        Vector3f a = Vector3f(0,0,0);
        
        Vector3f loc_i = pos[i];
        
        for(int j=0; j<this->sysSize;j++){
            
            if (i==j){
                continue;
            }
            else{
                
                //calculate accel vector here
                float m = planets[j].getMass();
                
                Vector3f dist = pos[j] - loc_i;
                
                double k = ((double)GRAV_C * m) /pow(dist.abs(),3);
                
                a = a + (k * dist);     //sum up for all planets
                
                
            }
            
        }
        
        acc.push_back(a/planets[i].getMass());
        
        
    }
    
    for (int k = 0; k<acc.size(); k++){
        vel.push_back(acc[k]);
    }
    return vel;
}
void SolarSystem::setState(vector<Vector3f> nextState, vector<Vector3f> currentState){
    this->state = nextState;
    this->oldstate = currentState;
}

vector<Vector3f> SolarSystem::getState(){
    return state;
}
              
void SolarSystem::toString(){
    
    for(int i=0;i<this->planets.size();i++){
        this->planets[i].toString();
    }
}
