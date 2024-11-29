#ifndef LIVINGROOM_H
#define LIVINGROOM_H

#include<iostream>

using namespace std;
class LivingRoom {
public:
    
    static inline float vertices[] = {
        // Floor (Y = -0.5)
        -1.0f, -0.5f, -1.0f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left
        4.25f, -0.5f, -1.0f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,  // Bottom-right
        4.25f, -0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,  // Top-right
        4.25f, -0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,  // Top-right
        -1.0f, -0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f,  // Top-left
        -1.0f, -0.5f, -1.0f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left

        // Ceiling (Y = 0.5)
        -1.0f,  0.5f, -1.0f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left
        4.25f,  0.5f, -1.0f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,  // Bottom-right
        4.25f,  0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,  // Top-right
        4.25f,  0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,  // Top-right
        -1.0f,  0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,  // Top-left
        -1.0f,  0.5f, -1.0f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left

        // left Back Wall (Z = -1.0)
        -1.0f, -0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Bottom-left
        1.0f, -0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,  // Bottom-right
        1.0f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,  // Top-right
        1.0f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,  // Top-right
        -1.0f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,  // Top-left
        -1.0f, -0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Bottom-left

        // left-center Back Wall (Z = -1.0)
        1.0f, 0.25f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Bottom-left
        1.5f, 0.25f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,  // Bottom-right
        1.5f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,  // Top-right
        1.5f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,  // Top-right
        1.0f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,  // Top-left
        1.0f, 0.25f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Bottom-left

        // center Back Wall (Z = -1.0)
        1.5f, -0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Bottom-left
        1.75f, -0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,  // Bottom-right
        1.75f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,  // Top-right
        1.75f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,  // Top-right
        1.5f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,  // Top-left
        1.5f, -0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Bottom-left
        
        // center-right Back Wall (Z = -1.0)
        1.75f, 0.25f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Bottom-left
        2.25f, 0.25f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,  // Bottom-right
        2.25f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,  // Top-right
        2.25f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,  // Top-right
        1.75f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,  // Top-left
        1.75f, 0.25f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Bottom-left

        // right Back Wall (Z = -1.0)
        2.25f, -0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Bottom-left
        4.25f, -0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,  // Bottom-right
        4.25f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,  // Top-right
        4.25f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,  // Top-right
        2.25f,  0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,  // Top-left
        2.25f, -0.5f, -1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Bottom-left

        // Left Wall (X = -1.0)
        -1.0f, -0.5f, -1.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left
        -1.0f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,  // Bottom-right
        -1.0f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Top-right
        -1.0f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Top-right
        -1.0f,  0.5f, -1.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,  // Top-left
        -1.0f, -0.5f, -1.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left

        // back Right Wall (X = 1.0)
        4.25f, -0.5f, -1.0f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left
        4.25f, -0.5f,  -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,  // Bottom-right
        4.25f,  0.5f,  -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Top-right
        4.25f,  0.5f,  -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Top-right
        4.25f,  0.5f, -1.0f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,  // Top-left
        4.25f, -0.5f, -1.0f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,   // Bottom-left

        // back-front Right Wall (X = 1.0)
        4.25f, 0.25f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left
        4.25f, 0.25f,  0.0f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,  // Bottom-right
        4.25f,  0.5f,  0.0f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Top-right
        4.25f,  0.5f,  0.0f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Top-right
        4.25f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,  // Top-left
        4.25f, 0.25f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,   // Bottom-left

        // front Right Wall (X = 1.0)
        4.25f, -0.5f, 0.0f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,  // Bottom-left
        4.25f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,  // Bottom-right
        4.25f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Top-right
        4.25f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,  // Top-right
        4.25f,  0.5f, 0.0f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,  // Top-left
        4.25f, -0.5f, 0.0f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f   // Bottom-left
    };

};



#endif