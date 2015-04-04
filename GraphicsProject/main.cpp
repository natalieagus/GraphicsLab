//
//  main.cpp
//  GraphicsProject
//
//  Created by Natalie Agus on 23/3/15.
//  Copyright (c) 2015 Natalie Agus. All rights reserved.
//  Uploaded on GitHub

#include <iostream>
#include "SolarSystem.h"
#include "Planet.h"
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include "ImageLoad.h"
#include <cmath>
#include <sstream>
#include <vector>
#include "vecmath.h"
#include <fstream>
#include <chrono>
#include <thread>
#include "math.h"
#include "TimeStepper.hpp"

using namespace std;
int screenWidth, screenHeight;
SolarSystem* SolSys;
TimeStepper* timestepper;
float stepSize;

float distBuffer = -20;
const float SIZE = 10.0f;
#define M_PI    (3.14159265)
GLUquadricObj *sphere = NULL;
float _angle = 0;
GLuint texId;

void initialize(char* dataFile){
    SolSys = new SolarSystem(dataFile);
    cout <<"solarsystemsetup"<<endl;
    timestepper = new RK4();
    stepSize = 0.04;
    
}
void initRendering() {
    glEnable(GL_DEPTH_TEST);

    
    // set up lighting
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat matAmbience[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat matShininess[] = { 20.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);
    
    GLfloat lightAmbient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    Image* img = Image::loadBMP("Startup_screen.bmp");
    texId = Image::loadTextureFromImage(img);
    delete img;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    screenWidth = w;
    screenHeight = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0f, (float)screenWidth / (float)screenHeight, 0.001f, 500.0f);
   }
void drawPlanets(SolarSystem* solsys){
    vector<Planet> p = solsys->planets;
    float drawDistance = 0;
    float prevRad = 0;
    for (int i = 0; i<p.size(); i++){
        glPushMatrix();
        drawDistance += p[i].getDist() + prevRad;
        float rad = 0;
        if (p[i].getRadius() > 13){
            rad = 13;
        }
        else{
            rad = p[i].getRadius();
        }
        prevRad = rad;
        glTranslatef(-drawDistance, 0, 0.0f);
        if(rad <= 12.999){
              glRotatef(_angle, 0, 1, 0);
        }
        if (i == 0){
            glDisable(GL_LIGHTING);
            gluSphere(sphere, rad, 20, 20);
            glEnable(GL_LIGHTING);
        }
        else{
            gluSphere(sphere, rad, 20, 20);

        }
        
        glPopMatrix();
    }
}
//called every  time
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texId);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0, (float)screenWidth / (float)screenHeight, 0.001f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 100.0, //eye is at 0,0,100 so that sun is at origin
              0.0, 0.0, 0.0, //look at origin
              0.0, 1.0, 0.0); //upwards
    
    GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
//    // render the solar system
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    drawPlanets(SolSys);
    glDisable(GL_LIGHTING);
    

//    glPushMatrix();
// //   glTranslatef(0.0f, 0.0f, -100.0f);
//    glRotatef(_angle, 0, 1, 0);
//    gluSphere(sphere, 1, 20, 20);
//    glPopMatrix();
    
////
//    glLoadIdentity();
//    glPushMatrix();
//    glTranslatef(-30, 0.0f, -100.f);
//    glRotatef(_angle, 0, 1, 0);
//    gluSphere(sphere, 0.3, 50, 50);
    glutSwapBuffers();
    
}
void stepSystem()
{
    ///TODO The stepsize should change according to commandline arguments
    
    //if using RK45 then stepsize should change according to the timestepper's timestep
    
    //cout << "Printing" << endl;
    if (timestepper != 0){
        timestepper->takeStep(SolSys, stepSize);
    }
    
}

void update(int value) {
    _angle += 1.5f;
    
    if (_angle > 360) {
        
        _angle -= 360;
        
    }
    
    
    stepSystem();

    glutPostRedisplay();
    
    glutTimerFunc(25, update, 0);
    
}


int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    

    char* dataFile = nullptr;
    for (int argNum=1;argNum<argc; ++argNum){
        
     //read command line args
        cout<<argNum<<": "<<argv[argNum]<<endl;
        
        if (strcmp(argv[argNum], "-data")==0){
            
            dataFile = (char*) argv[argNum+1];
            cout<<"dataFile: "<<dataFile<<endl;
            
            //Specify data file with -data [dataFilePath]
        }
        
    }
    
    //SolarSystem solSys;
    initialize(dataFile);
 
    
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 700);
    glutCreateWindow("Solar System");
    initRendering();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);
    glutMainLoop();

    
    

}
