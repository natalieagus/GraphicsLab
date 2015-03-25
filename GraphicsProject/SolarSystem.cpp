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


SolarSystem::SolarSystem(){

    //initialise Solar System here
    Planet earth("earth", 1.0, 1.0, 1.0);
    this->planets.push_back(earth);
    
};



void SolarSystem::draw(){
    
};

void SolarSystem::toString(){
    
    for(int i=0;i<this->planets.size();i++){
        this->planets[i].toString();
    }
}
