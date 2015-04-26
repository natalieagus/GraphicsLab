//
//  asteroid.cpp
//  GraphicsProject
//
//  Created by Crystal Tee on 10/4/15.
//  Copyright (c) 2015 Natalie Agus. All rights reserved.
//

#include "asteroid.h"
#include <random>

#define DENS 2000.0
    
Asteroid::Asteroid(){
    
    double rand_r = (float) rand()/RAND_MAX *5;
    //double rand_m = (float) rand()/RAND_MAX;
    
    this->r = rand_r*1000.0;
    double vol = pow(this->r,3)*M_PI * (4.0/3.0);
    this->m = vol*DENS;
    
};
double Asteroid::getRadius(){

    return this->r;
};

double Asteroid::getMass(){
    
    return this->m;
};

void Asteroid::setRadius(double new_r){
    
    this->r = new_r;
};
void Asteroid::setMass(double new_m){
    
    this->m = new_m;
    
};
void Asteroid::draw(){
    
};
void Asteroid::toString(){
    
    
};