//
//  asteroid.cpp
//  GraphicsProject
//
//  Created by Crystal Tee on 10/4/15.
//  Copyright (c) 2015 Natalie Agus. All rights reserved.
//

#include "asteroid.h"
    
Asteroid::Asteroid(double r, double m, char* obj_filePath){
    
    this->r = r;
    this->m = m;
    this->obj_filePath = obj_filePath;
    
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



private:

double r;    //radius of Planet
double m;
char* obj_filePath;