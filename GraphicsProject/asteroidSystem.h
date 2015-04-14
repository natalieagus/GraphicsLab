//
//  asteroidSystem.h
//  GraphicsProject
//
//  Created by Crystal Tee on 10/4/15.
//  Copyright (c) 2015 Natalie Agus. All rights reserved.
//

#ifndef __GraphicsProject__asteroidSystem__
#define __GraphicsProject__asteroidSystem__

#include <stdio.h>
#include "asteroid.h"
#include "vecmath.h"
#include <vector>
#include "SolarSystem.h"

using namespace std;

class AsteroidSystem{
    public:
        AsteroidSystem(SolarSystem solSys);
    void addAsteroid(Vector3f pos);
    void delAsteroid(Asteroid ast);
    void draw();
    void toString();
    vector<Asteroid> asteroids;
    vector<Vector3f> state;
    vector<Vector3f> oldstate;

    int sysSize;    //no. of asteroids
    vector<Vector3f> getState();
    vector<Vector3f> evalF(vector<Vector3f> currentState);
    void setState(vector<Vector3f> nextState, vector<Vector3f> currentState);
    SolarSystem solSys;

    private:
    
};


#endif /* defined(__GraphicsProject__asteroidSystem__) */
