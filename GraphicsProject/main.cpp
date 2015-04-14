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
#include "camera.h"
#include "asteroidSystem.h"


using namespace std;

//Solar system set up variables
int screenWidth, screenHeight;
SolarSystem* SolSys;
TimeStepper* timestepper;
float stepSize;

//For camera variables
Camera camera;
GLUquadricObj *sphere = NULL;
float _angle = 0;
GLfloat zoom;
GLfloat side;
GLfloat updown;

//Texture Ids for texture binding
vector<GLuint> texIds;
GLuint bgId;


//Initializing solar system
void initialize(char* dataFile){
    SolSys = new SolarSystem(dataFile);
    
    //initialise AsteroidSystem
    astSys = new AsteroidSystem(*SolSys);
    
    timestepper = new RK4();
    stepSize = 3.f;
}

//Initializing rendering (lights, and texture loading)
void initRendering() {
    
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
    
    
    //Texture Loading
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    
    Image* imgBG = Image::loadBMP("stars.bmp");
    bgId = Image::loadTexture(imgBG);
    delete imgBG;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    Image* img = Image::loadBMP("sun.bmp");
//    GLuint td = Image::loadTexture(img);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    texIds.push_back(td);
//    delete img;
//    
//    Image* img2 = Image::loadBMP("mercury.bmp");
//    GLuint td2 = Image::loadTexture(img2);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    texIds.push_back(td2);
//    delete img2;
//    
//    Image* img3 = Image::loadBMP("venus.bmp");
//    GLuint td3 = Image::loadTexture(img3);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    texIds.push_back(td3);
//    delete img3;
//    
//    Image* img4 = Image::loadBMP("earth.bmp");
//    GLuint td4 = Image::loadTexture(img4);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    texIds.push_back(td4);
//    delete img4;
//    
//    Image* img5 = Image::loadBMP("mars.bmp");
//    GLuint td5 = Image::loadTexture(img5);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    texIds.push_back(td5);
//    delete img5;
//    
//    Image* img6 = Image::loadBMP("jupiter.bmp");
//    GLuint td6 = Image::loadTexture(img6);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    texIds.push_back(td6);
//    delete img6;
//    
//    Image* img7 = Image::loadBMP("saturn.bmp");
//    GLuint td7 = Image::loadTexture(img7);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    texIds.push_back(td7);
//    delete img7;
//    
//    Image* img8 = Image::loadBMP("uranus.bmp");
//    GLuint td8 = Image::loadTexture(img8);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    texIds.push_back(td8);
//    delete img8;
//    
//    Image* img9 = Image::loadBMP("neptune.bmp");
//    GLuint td9 = Image::loadTexture(img9);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    texIds.push_back(td9);
//    delete img9;
//    
//    Image* img10 = Image::loadBMP("pluto.bmp");
//    GLuint td10 = Image::loadTexture(img10);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    texIds.push_back(td10);
//    delete img10;
    
    SolSys->setTextures();
    texIds = SolSys->textures;

    //create new quadric sphere for drawing
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    
}


//Resizing function
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    screenWidth = w;
    screenHeight = h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(1,w, h,1,-100,100);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0f, (float)screenWidth / (float)screenHeight, 0.001f, 500.0f);
   }

//Planet rendering function
void drawPlanets(SolarSystem* solsys){
    vector<Planet> p = solsys->planets;
    vector<Vector3f> states = solsys->getState();
    double minDist = solsys->min_dist;
    
    float drawDistance = 0;
    float prevRad = 0;
    for (int i = 0; i<solsys->sysSize; i++){
        glBindTexture(GL_TEXTURE_2D, texIds[i]);
        glPushMatrix();
        Vector3f pos;
        vector<double>pos_xyz;
        
        if (i!=0){
        double scale = pow(states[i].abs()/minDist,1.0/3.0);
            
        pos = scale*states[i].normalized();
        }
        else{
            pos = states[i];
        }
        
        double rad = pow(p[i].getRadius()/minDist, 1.0/3.0);
        glTranslatef(pos[0], pos[1], pos[2]);
        
        if(i != 0){ //self rotation
              glRotatef(_angle, 0, 1, 0);
        }
        
        glRotatef(90, 1, 0, 0);//rotate for orientation

        if (i == 0){ //if sun, then its the source of light, off lighting
            glDisable(GL_LIGHTING);
            gluSphere(sphere, rad, 20, 20);
            glEnable(GL_LIGHTING);
        }
      
        else{
            glEnable(GL_LIGHTING);
            gluSphere(sphere, rad, 20, 20);
            glDisable(GL_LIGHTING);
        }
        
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
    }
}

//Background cube for rendering stars
void drawCube(void)
{
    glBegin(GL_QUADS);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
    
    glEnd();
}

//Update draw function
void drawScene() {
    
    //Setup background with orthographic camera
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(1,1,1,1,-100,100);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, bgId);
    drawCube();
    
    
    //Setup perspective camera for solar system rendering
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0, (float)screenWidth / (float)screenHeight, 0.001f, 400.0f);
    glMatrixMode(GL_MODELVIEW);


    glLoadIdentity();
    //If using openGL camera, use gluLookAt
   // gluLookAt(0.0, 20.0, 100.0, //eye is at 0,0,100 so that sun is at origin
              //0.0, 0.0, 0.0, //look at origin
              //0.0, 1.0, -0.2); //upwards
    glLoadMatrixf(camera.viewMatrix());
    glScalef(1.0f+zoom, 1.0f+zoom, 1.0f+zoom);
    glTranslatef(0+side, 0+updown, 0);
  
    GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    
    //Rendering solar system
    //glEnable(GL_DEPTH_TEST);
 
    drawPlanets(SolSys);
    //glDisable(GL_LIGHTING);
    

    //FOR DEBUGGING
//    glPushMatrix();
//    glTranslatef(0.0f, 0.0f, 0.0f);
//    glPushMatrix();
//    glRotatef(_angle, 0, 1, 0);
//    gluSphere(sphere, 8.45, 20, 20);
//    glPopMatrix();
//    glPopMatrix();
    
////
   // glLoadIdentity();
//    glPushMatrix();
//    glTranslatef(-97.47, 0.0f, 0.0f);
//    glRotatef(_angle, 0, 1, 0);
//    gluSphere(sphere, 1, 20,20);
//   // glutSwapBuffers();
//    glPopMatrix();
//    glPopMatrix();
    
//    glPushMatrix();
//    glTranslatef(-49.6, 0.0f, 0.0f);
//    glRotatef(_angle, 0, 1, 0);
//    gluSphere(sphere, 3.96, 20,20);
    
    glutSwapBuffers();
    
}

//Updating planet position every timestep
void stepSystem()
{

    if (timestepper != 0 && SolSys != 0){
        timestepper->takeStep(SolSys, stepSize);
    }
    
}

//Update function, calling stepsystem every 20ms and updating planet's self rotation
void update(int value) {
    _angle += 1.5f;
    if (_angle > 360) {
        _angle -= 360;
        
    }
    stepSystem();
    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}


//Mouse drag function for orientation
void motionFunc(int x, int y)
{
    camera.MouseDrag(x, y);
    
    glutPostRedisplay();
}

//Mouse click function
void mouseFunc(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        switch (button)
        {
            case GLUT_LEFT_BUTTON:
                camera.MouseClick(Camera::LEFT, x, y);
//                break;
//            case GLUT_MIDDLE_BUTTON:
//                camera.MouseClick(Camera::MIDDLE, x, y);
//                break;
//            case GLUT_RIGHT_BUTTON:
//                camera.MouseClick(Camera::RIGHT, x, y);
            default:
                break;
        }
    }
    else
    {
        camera.MouseRelease(x, y);
    }
    glutPostRedisplay();
}

//Keyboard key function
void keyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: // Escape key
            exit(0);
            break;
        case 'i':
            zoom+=0.2;
            break;
        case 'o':
            zoom-=0.2;
            break;
        case 'w':
            updown+=0.2;
            break;
        case 's':
            updown-=0.2;
            break;
        case 'a':
            side+=0.2;
            break;
        case 'd':
            side -=0.2;
            break;
        default:
            break;
    }
    glutPostRedisplay();
 
}

//Main function
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

    initialize(dataFile);
 
    
    //Setting up window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 1024);
    camera.SetDimensions(1280, 1024);
    camera.SetDistance(80);
    camera.SetCenter(Vector3f(0,0,0));
    glutCreateWindow("Solar System");
    initRendering();
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutKeyboardFunc(keyboardFunc);
    glutDisplayFunc(drawScene);
    glutReshapeFunc(handleResize);
    glutTimerFunc(20, update, 0);
    glutMainLoop();

}
