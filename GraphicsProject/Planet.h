//
//  Planet.h
//  GraphicsProject
//
//  Created by Crystal Tee on 25/3/15.
//  Copyright (c) 2015 Natalie Agus. All rights reserved.
//

#ifndef __GraphicsProject__Planet__
#define __GraphicsProject__Planet__

#include <stdio.h>
#include "vecmath.h"
#include <vector>
#include <string>

using namespace std;

class Planet{

public:
    
    Planet( string name, float R, float r, float m, float ang_v);
    float getRadius();
    float getDist();
    float getMass();
    void draw();
    void toString();
    
    
    
private:

    float r;    //radius of Planet
    float m;    //mass of Planet
    float ang_v;    //angular velocity
    float R;    //distance from sun
    string name;
    
};


#endif /* defined(__GraphicsProject__Planet__) */
