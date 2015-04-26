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
    
Planet::Planet(string name, double R, double r, double m, double ang_v, string tex_file){
    this->r = r;
    this->R = R;
    this->m = m;
    this->ang_v = ang_v;
    this->name = name;
    this->tex_file = tex_file;

}

double Planet::getDist(){
    
    return this->R;
}

double Planet::getRadius(){
    
    return this->r;
}

void Planet::setDist(double new_R){
    
    this->R = new_R;
}
void Planet::setRadius(double new_r){
    
    this->r = new_r;
}

double Planet::getMass(){
    
    return this->m;
    
}

string Planet::getTexFile(){
    
    return tex_file;
    
}

void Planet::toString(){
    
    cout<< "Planet: "<< this->name<<" Radius: "<<this->r<<" Mass: "<< this->m<< " Angular Vel: "<<this->ang_v<<endl;
    
}

