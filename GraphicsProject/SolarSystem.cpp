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
#include <random>
#include "ImageLoad.h"

#define GRAV_C 6.67*pow(10,-11)
#define SCALE_F 0.1289
#define m_E 5.972 * pow(10,24)
#define AU 1.496 * pow(10,11)

//#define GRAV_C 1.99*pow(10,-44)    //defined in AU^3 / (M_e *s^2)

using namespace std;

SolarSystem::SolarSystem(){
    
}
SolarSystem::SolarSystem(char* filePath){
    
    //read and parse file
    
    vector<Vector3f> pos;
    vector<double> all_rad;
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
            
            Planet p(toks[0],atof(toks[1]),atof(toks[2]),atof(toks[3]),atof(toks[4]),toks[5],atof(toks[6]));
            this->planets.push_back(p);
            cout <<"Planet tex file is: "<<p.getTexFile()<< endl;
            float rdm = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2));
//            pos.push_back(Vector3f(
//                                   p.getDist()*cos(rdm*M_PI)*sin(p.getIncl()),
//                                   p.getDist()*cos(p.getIncl()),
//                                   p.getDist()*sin(rdm*M_PI))*sin(p.getIncl())
//                          );
            pos.push_back(Vector3f(
                                   p.getDist()*cos(rdm*M_PI),
                                   0,
                                   p.getDist()*sin(rdm*M_PI))
                          );
            all_rad.push_back(p.getRadius());
            
            
        }
    }
    this->sysSize = planets.size();
    //this->min_dist = 1150;
    this->min_dist = *min_element(all_rad.begin(), all_rad.end());
    
    cout<<"min dist: "<<this->min_dist<<endl;
    //initialise Solar System here
    this->state = pos;
    cout << "state size is "<<state.size()<<endl;

    cout<<"Solar system initializaton done"<<endl;
    
    //keep states as x1,x2,x3,x4...,v1,v2,v3,v4...
    
};

void SolarSystem::draw(){
    
};


vector<Vector3f> SolarSystem::evalF(vector<Vector3f> state){
    
    vector<Vector3f> vel;
    vel.push_back(Vector3f(0,0,0)); //sun always 0
    for(int i=1; i<sysSize;i++){
        
        Vector3f pos = state[i],v;
        
        //adjust for negative 0 because using double
        if(pos.x()==0){
            
            v = Vector3f(pos.z(),pos.y(),pos.x());
        }
        else{
            v = Vector3f(pos.z(),pos.y(),pos.x()*-1.0);
        }
        
        double sum=0.0;
        
        for(int j=0; j<this->sysSize;j++){
            
            
            if (i==j){
                continue;
            }
            else{
                
                //calculate v
                
                //double dist = abs(planets[j].getDist() - planets[i].getDist())*1000;
                
                double dist = (state[j]-state[i]).abs();
                
                sum+=(planets[j].getMass()* (double) m_E /dist);
                
            }
            
        }
        //float k = sqrt(sum*(double)GRAV_C)*SCALE_F;
        float k = sqrt(sum*(double)GRAV_C);
        vel.push_back(-1.0*k*v.normalized());
        //vel.push_back(v);
        if(i==0){
            
            cout<<"Sun: "<<v[0]<<" "<<v[1]<<" "<<v[2]<<" ";
            cout<<endl;
        }
        
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


void SolarSystem::setTextures(){
    
    for (int i = 0; i<planets.size(); i++){
        string filename = planets[i].getTexFile();
        const char* filenameChar = filename.c_str();
        Image* img = Image::loadBMP(filenameChar);
        GLuint td = Image::loadTexture(img);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        textures.push_back(td);
        delete img;
    }
}
