//
//  asteroid.h
//  GraphicsProject
//
//  Created by Crystal Tee on 10/4/15.
//  Copyright (c) 2015 Natalie Agus. All rights reserved.
//

#ifndef __GraphicsProject__asteroid__
#define __GraphicsProject__asteroid__

#include <stdio.h>

class Asteroid{
    
public:
    
    Asteroid();
    double getRadius();
    double getMass();
    
    void setRadius(double new_r);
    void setMass(double new_m);
    void draw();
    void toString();
    
    
    
private:
    
    double r;    //radius of Planet
    double m;
    char* obj_filePath;
    
};



#endif /* defined(__GraphicsProject__asteroid__) */
