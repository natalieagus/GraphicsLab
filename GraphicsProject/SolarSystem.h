//
//  SolarSystem.h
//  GraphicsProject
//
//  Created by Crystal Tee on 25/3/15.
//  Copyright (c) 2015 Natalie Agus. All rights reserved.
//

#ifndef __GraphicsProject__SolarSystem__
#define __GraphicsProject__SolarSystem__

#include <stdio.h>
#include "Planet.h"

#endif /* defined(__GraphicsProject__SolarSystem__) */



class SolarSystem{
    
public:
    
    SolarSystem(char*);
    void draw();
    void toString();
    vector<Vector3f>evalF();
    vector<Planet> planets;
    vector<Vector3f> state;
    int sysSize;    //no. of planets
    
private:

    
    
};