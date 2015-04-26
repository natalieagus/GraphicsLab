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
    
    Planet( string name, double R, double r, double m, double ang_v, string tex_file);
    double getRadius();
    double getDist();
    double getMass();
    string getTexFile();
    double ang_v;    //angular velocity, period is 2pi / angular vel
    
    
    void setRadius(double new_r);
    void setDist(double new_R);
    void toString();
    
private:

    double r;    //radius of Planet
    double m;    //mass of Planet
    double R;    //distance from sun
    string tex_file;
    string name;
    
};


#endif /* defined(__GraphicsProject__Planet__) */
