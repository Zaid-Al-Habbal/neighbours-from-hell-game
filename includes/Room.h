#ifndef ROOM_H
#define ROOM_H

#include<iostream>

using namespace std;
class Room {
public:
    
    static inline float vertices[] = {
    // Floor (Y = -0.5)
    -1.0f, -0.5f, -1.0f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left
     1.0f, -0.5f, -1.0f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,  // Bottom-right
     1.0f, -0.5f,  1.0f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,  // Top-right
     1.0f, -0.5f,  1.0f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,  // Top-right
    -1.0f, -0.5f,  1.0f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f,  // Top-left
    -1.0f, -0.5f, -1.0f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left

    // Ceiling (Y = 0.5)
    -1.0f,  0.5f, -1.0f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left
     1.0f,  0.5f, -1.0f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,  // Bottom-right
     1.0f,  0.5f,  1.0f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,  // Top-right
     1.0f,  0.5f,  1.0f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,  // Top-right
    -1.0f,  0.5f,  1.0f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,  // Top-left
    -1.0f,  0.5f, -1.0f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left

    // Back Wall (Z = -1.0)
    -1.0f, -0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Bottom-left
     1.0f, -0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,  // Bottom-right
     1.0f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,  // Top-right
     1.0f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,  // Top-right
    -1.0f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,  // Top-left
    -1.0f, -0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Bottom-left

    // Left Wall (X = -1.0)
    -1.0f, -0.5f, -1.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left
    -1.0f, -0.5f,  1.0f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,  // Bottom-right
    -1.0f,  0.5f,  1.0f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Top-right
    -1.0f,  0.5f,  1.0f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Top-right
    -1.0f,  0.5f, -1.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,  // Top-left
    -1.0f, -0.5f, -1.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left

    // Right Wall (X = 1.0)
     1.0f, -0.5f, -1.0f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left
     1.0f, -0.5f,  1.0f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,  // Bottom-right
     1.0f,  0.5f,  1.0f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Top-right
     1.0f,  0.5f,  1.0f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Top-right
     1.0f,  0.5f, -1.0f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,  // Top-left
     1.0f, -0.5f, -1.0f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f   // Bottom-left
};


};



#endif