//
//  ImageLoad.h
//  GraphicsProject
//
//  Created by Natalie Agus on 3/4/15.
//  Copyright (c) 2015 Natalie Agus. All rights reserved.
//

#ifndef __GraphicsProject__ImageLoad__
#define __GraphicsProject__ImageLoad__

#include <stdio.h>


#include <iostream>
#include <fstream>
#include <GLUT/glut.h>

using namespace std;

class Image{
public:
    Image(char* ps, int w, int h);
    
    Image();
    
    char* pixels;
    int width;
    int height;
    
    static Image* loadBMP(const char* filename) ;
    static GLuint loadTextureFromImage(Image* image);
    //Converts a four-character array to an integer, using little-endian form
    
};
#endif /* defined(__GraphicsProject__ImageLoad__) */
