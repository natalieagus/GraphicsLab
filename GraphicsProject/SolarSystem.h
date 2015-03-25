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
    
    SolarSystem();
    void draw();
    void toString();
    
    
private:
    vector<Planet> planets;
    
    
};