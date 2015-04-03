//
//  ImageLoad.cpp
//  GraphicsProject
//
//  Created by Natalie Agus on 3/4/15.
//  Copyright (c) 2015 Natalie Agus. All rights reserved.
//

#include "ImageLoad.h"
#include <vector>
using namespace std;

Image::Image(char* ps, int w, int h): pixels(ps), width(w), height(h) {
    
}

Image::Image() {
    
}

namespace{
    int toInt(const char* bytes) {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }
    
    
    int readInt(ifstream &input) {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }
}


Image* Image::loadBMP(const char* FilePath) {
    int width = 0;
    int height = 0;
    short BitsPerPixel = 0;
    vector<unsigned char> Pixels;
    
    
    std::fstream hFile(FilePath, std::ios::in | std::ios::binary);
    if (!hFile.is_open()) throw std::invalid_argument("Error: File Not Found.");
    
    hFile.seekg(0, std::ios::end);
    int Length = hFile.tellg();
    hFile.seekg(0, std::ios::beg);
    std::vector<std::uint8_t> FileInfo(Length);
    hFile.read(reinterpret_cast<char*>(FileInfo.data()), 54);
    
    if(FileInfo[0] != 'B' && FileInfo[1] != 'M')
    {
        cout << "FILE INFO IS: " <<FileInfo[0] << FileInfo[1]<<endl;
        hFile.close();
        throw std::invalid_argument("Error: Invalid File Format. Bitmap Required.");
    }
    
    if (FileInfo[28] != 24 && FileInfo[28] != 32)
    {
        hFile.close();
        throw std::invalid_argument("Error: Invalid File Format. 24 or 32 bit Image Required.");
    }
    
    BitsPerPixel = FileInfo[28];
    width = FileInfo[18] + (FileInfo[19] << 8);
    height = FileInfo[22] + (FileInfo[23] << 8);
    std::uint32_t PixelsOffset = FileInfo[10] + (FileInfo[11] << 8);
    std::uint32_t size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
    Pixels.resize(size);
    
    hFile.seekg (PixelsOffset, std::ios::beg);
    hFile.read(reinterpret_cast<char*>(Pixels.data()), size);
    hFile.close();
    
    return new Image((char*)Pixels.data(), width, height);
}

GLuint Image::loadTextureFromImage(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId);
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 image->width, image->height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 
                 image->pixels);
    return textureId;
}