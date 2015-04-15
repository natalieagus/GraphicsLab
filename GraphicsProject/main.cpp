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
#include "asteroid.h"

using namespace std;

//Solar system set up variables
int screenWidth, screenHeight;
SolarSystem* SolSys;
AsteroidSystem* AstSys;
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
    AstSys = new AsteroidSystem(*SolSys);
    AstSys->sysSize = 0;
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

void drawAsteroids(AsteroidSystem* asteroidSystem){
    double minDist = SolSys->min_dist;
    for (int i = 0; i<asteroidSystem->sysSize; i++){
        vector<Asteroid> asts = asteroidSystem->asteroids;
        vector<Vector3f> states = asteroidSystem->state;
        glPushMatrix();
        Asteroid a = asts[i];
        double scale = pow(states[i].abs()/minDist,1.0/3.0);
        Vector3f pos = scale*states[i].normalized();
    //    cout << "Asteroid " << i << " pos x " << pos[0] << " pos y "<< pos[1]<< " pos z" <<pos[2]<<endl;
        glTranslatef(pos[0], pos[1], pos[2]);
        glEnable(GL_COLOR);
        glColor3f(1 , 0, 0);
        double rad = pow(asts[i].getRadius()/minDist, 1.0/3.0);
       // cout <<"Radius is: "<<rad<<endl;
        gluSphere(sphere, rad, 20, 20);
        glDisable(GL_COLOR);
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
    gluPerspective(100.0, (float)screenWidth / (float)screenHeight, 0.001f, 500.0f);
    glMatrixMode(GL_MODELVIEW);


    glLoadIdentity();
    //If using openGL camera, use gluLookAt
  //  gluLookAt(40.0, 0.0, 80.0, //eye is at 0,0,100 so that sun is at origin
    //          0.0, 0.0, 0.0, //look at origin
      //        0.0, 1.0, 0.0); //upwards
   glLoadMatrixf(camera.viewMatrix());
    
   // gluLookAt(0, 0, 100, 0, 20, 0, 0, 1, 0);
    glScalef(1.0f+zoom, 1.0f+zoom, 1.0f+zoom);
    glTranslatef(0+side, 0+updown, 0);
  
    GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    
    //Rendering solar system
    //glEnable(GL_DEPTH_TEST);
 
    drawPlanets(SolSys);
    drawAsteroids(AstSys);
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
       // timestepper->takeStepAsteroid(AstSys, stepSize/1000);
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
    
    float xcoord = float(x)/(float)1280 * (float) 1400000000 -( float)700000000;
    float ycoord = (1024-float(y))/(float)1024 * (float) 1400000000 -( float)700000000;
    
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
            case GLUT_RIGHT_BUTTON:
               // camera.MouseClick(Camera::RIGHT, x, y);
                //range is -700000000 to 700000000 on all axes

                AstSys->addAsteroid(Vector3f(xcoord ,ycoord,7000000));
                cout<<"X is: "<< x << "Y is: " << y << endl;
                cout <<"new x is: "<<xcoord << "new y is" <<ycoord<<endl;
                break;
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
   // camera.SetCenter(Vector3f(100, 0, 0));
    camera.SetCenter(Vector3f(0,0,0)); //this is the camera center, change this to location of planet
    
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
