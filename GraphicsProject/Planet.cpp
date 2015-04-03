//
//  Planet.cpp
//  GraphicsProject
//
//  Created by Crystal Tee on 25/3/15.
//  Copyright (c) 2015 Natalie Agus. All rights reserved.
//

#include "Planet.h"
#include <stdio.h>
#include "vecmath.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
    
Planet::Planet(string name, float R, float r, float m, float ang_v){
    this->r = r;
    this->R = R;
    this->m = m;
    this->ang_v = ang_v;
    this->name = name;
    
}

float Planet::getDist(){
    
    return this->R;
}

float Planet::getRadius(){
    
    return this->r;
}

float Planet::getMass(){
    
    return this->m;
    
}

void Planet::toString(){
    
    cout<< "Planet: "<< this->name<<" Radius: "<<this->r<<" Mass: "<< this->m<< " Angular Vel: "<<this->ang_v<<endl;
    
}

