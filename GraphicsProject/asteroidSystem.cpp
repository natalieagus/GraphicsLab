//
//  asteroidSystem.cpp
//  GraphicsProject
//
//  Created by Crystal Tee on 10/4/15.
//  Copyright (c) 2015 Natalie Agus. All rights reserved.
//

#include "asteroidSystem.h"


AsteroidSystem::AsteroidSystem(){};
void AsteroidSystem::addAsteroid(Asteroid ast){
    this->asteroids.push_back(ast);
};
void AsteroidSystem::delAsteroid(Asteroid ast){
    //yet to implement
};
void AsteroidSystem::draw(){
    
};
void AsteroidSystem::toString(){
    
};
    vector<Asteroid> asteroids;
    vector<Vector3f> state;
    vector<Vector3f> oldstate;
    
    int sysSize;    //no. of asteroids

vector<Vector3f> evalF(vector<Vector3f> currentState){
    
    vector<Vector3f> fX;
    
    return fX;
};
void setState(vector<Vector3f> nextState, vector<Vector3f> currentState){
    
};