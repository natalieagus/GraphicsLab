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
#include "imageloader.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include "vecmath.h"
#include <fstream>
#include <chrono>
#include <thread>
#include "math.h"


using namespace std;


const float SIZE = 10.0f;
#define M_PI    (3.14159265)
GLUquadricObj *sphere = NULL;
float _angle = 0;
GLuint _textureId;

void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    Image* img = Image::loadBMP("Startup_screen.bmp");
    _textureId = Image::loadTextureFromImage(img);
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}


void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, -20.0f);
    glRotatef(_angle, 0, 1, 0);
    gluSphere(sphere, 5.0, 20, 20);
    
    glutSwapBuffers();
    
}

void update(int value) {
    _angle += 1.5f;
    
    if (_angle > 360) {
        
        _angle -= 360;
        
    }
    
    
    
    glutPostRedisplay();
    
    glutTimerFunc(25, update, 0);
    
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    
    // insert code here...
    cout << "Hello, World!\n";
    
    //hello natalie
    
    cout<<"Graphics is fun"<<endl;
    //on crystal branch
    
    SolarSystem solSys;
    
    solSys.toString();
    char ** argt;
    
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Sphery sky");
    initRendering();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);
    glutMainLoop();

    
    

}
