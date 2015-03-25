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
    
Planet::Planet(string name, float r, float m, float ang_v){
    this->r = r;
    this->m = m;
    this->ang_v = ang_v;
    this->name = name;
    
    vector<Vector3f> s;
    s.push_back(Vector3f(0,0,0));
    s.push_back(Vector3f(0,0,0));
    
    this->state =s;
    
}
    
vector<Vector3f> Planet::evalF(vector<Vector3f> state){
    
    vector<Vector3f> eval;
    
    //add code here to eval fx_t;
    
    return eval;
    
}

float Planet::getRadius(){
    
    return this->r;
}

float Planet::getMass(){
    
    return this->m;
    
}
vector<Vector3f> Planet::getState(){

    return this->state;
}

void Planet::toString(){
    
    cout<< "Planet: "<< this->name<<" Radius: "<<this->r<<" Mass: "<< this->m<< " Angular Vel: "<<this->ang_v<<endl;
    
}

