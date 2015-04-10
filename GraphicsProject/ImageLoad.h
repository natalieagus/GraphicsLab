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
//Represents an image
class Image {
public:
    Image(char* ps, int w, int h);
    ~Image();
    static Image* loadBMP(const char* filename);
    static GLuint  loadTexture(Image* image);

    /* An array of the form (R1, G1, B1, R2, G2, B2, ...) indicating the
     * color of each pixel in image.  Color components range from 0 to 255.
     * The array starts the bottom-left pixel, then moves right to the end
     * of the row, then moves up to the next column, and so on.  This is the
     * format in which OpenGL likes images.
     */
    char* pixels;
    int width;
    int height;
};

//Reads a bitmap image from file.



#endif /* defined(__GraphicsProject__ImageLoad__) */
