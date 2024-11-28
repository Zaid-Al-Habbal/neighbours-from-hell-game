#ifndef Light_CLASS_H
#define Light_CLASS_H

#include<glad/glad.h>
#include<iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shader.h"
#include"TextureClass.h"
#include "camera.h"

#include <vector>



class Light
{
public:
    // directional light:
    glm::vec3 dirLightColor, dirLightDirection, dirLightAmbient, dirLightDiffuse, dirLightSpecular;
    // Point light:
    glm::vec3 pointLightColor[10], pointLightAmbient[10], pointLightDiffuse[10], pointLightSpecular[10], pointLightPosition[10];
    float pointLightConstant[10], pointLightLinear[10], pointLightQuadratic[10];
    // Spot light:
    glm::vec3 spotLightColor, spotLightPosition, spotLightDirection, spotLightAmbient, spotLightDiffuse, spotLightSpecular;
    float spotLightConstant, spotLightLinear, spotLightQuadratic, spotLightCutOff,spotLightOuterCutOff;
    
    //for turning Lights on and off
    bool enableDir, enableSpot;
    int numOfPoints;
    //shader
    Shader myShader;
    //comera position:
    glm::vec3 viewPos;
    //Material:
    
    Light(Shader myShader, bool enableDir, int numOfPoints, bool enableSpot, glm::vec3 cameraPos, glm::vec3 cameraFront);

    void turnOnTheLights();
	
};
#endif