#include "Light.h"

Light::Light(Shader myShader, bool enableDir, int numOfPoints, bool enableSpot, glm::vec3 cameraPos, glm::vec3 cameraFront)
{
    this->myShader = myShader;
    this->enableDir = enableDir;
    this->numOfPoints = numOfPoints;
    this->enableSpot = enableSpot;
    //DirLight:
    this->dirLightColor = glm::vec3(1.0f);
    this->dirLightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
    this->dirLightSpecular = glm::vec3(1.0f);
    //PointLight:
    for(int i=0; i<numOfPoints; i++){
        this->pointLightColor[i]= glm::vec3(1.0f);
        this->pointLightSpecular[i]=glm::vec3(1.0f);
        this->pointLightConstant[i] =1.0f;
        this->pointLightLinear[i]=0.09f;
        this->pointLightQuadratic[i] = 0.032f;
        this->pointLightPosition[i] = glm::vec3( 0.7f,  0.2f,  2.0f); 
        
    }
    //SpotLight:
    this->spotLightColor = glm::vec3(1.0f);
    
    this->spotLightSpecular = glm::vec3(1.0f);
    this->spotLightConstant = 1.0f;
    this->spotLightLinear = 0.09f;
    this->spotLightQuadratic = 0.032f;
    this->spotLightPosition = cameraPos,
    this->spotLightCutOff = 12.5f;
    this->spotLightOuterCutOff = 17.5f;
    this->spotLightDirection = cameraFront;
    //viewPos:
    this->viewPos = cameraPos;

}

void Light::turnOnTheLights(){
    myShader.use();
    myShader.setVec3("viewPos", viewPos);

    //lights:
    // directional light
    myShader.setBool("enableDir", enableDir);
    this->dirLightDiffuse = this->dirLightColor * glm::vec3(0.8f);
    this->dirLightAmbient = this->dirLightDiffuse * glm::vec3(0.2f);
    myShader.setVec3("dirLight.direction", dirLightDirection);
    myShader.setVec3("dirLight.specular", dirLightSpecular);
    myShader.setVec3("dirLight.ambient", dirLightAmbient);
    myShader.setVec3("dirLight.diffuse", dirLightDiffuse);
    // point light 
    myShader.setInt("numOfPoints", numOfPoints);
    for(int i=0; i<numOfPoints; i++){
        this->pointLightDiffuse[i] = this->pointLightColor[i] * glm::vec3(0.8f);
        this->pointLightAmbient[i] = this->pointLightDiffuse[i] * glm::vec3(0.2f);
    }
    for(char x = '0'; x-'0'<numOfPoints; x++){
        std::string ch; ch += x;
        myShader.setVec3("pointLights["+ch+"].position", pointLightPosition[x-'0']);
        myShader.setVec3("pointLights["+ch+"].ambient", pointLightAmbient[x-'0']);
        myShader.setVec3("pointLights["+ch+"].diffuse", pointLightDiffuse[x-'0']);
        myShader.setVec3("pointLights["+ch+"].specular", pointLightSpecular[x-'0']);
        myShader.setFloat("pointLights["+ch+"].constant", pointLightConstant[x-'0']);
        myShader.setFloat("pointLights["+ch+"].linear", pointLightLinear[x-'0']);
        myShader.setFloat("pointLights["+ch+"].quadratic", pointLightQuadratic[x-'0']);
    }
    // spotLight
    myShader.setBool("enableSpot", enableSpot);
    this->spotLightDiffuse = this->spotLightColor * glm::vec3(0.8f);
    this->spotLightAmbient = this->spotLightDiffuse * glm::vec3(0.2f);
    myShader.setVec3("spotLight.position", spotLightPosition);
    myShader.setVec3("spotLight.direction", spotLightDirection);
    myShader.setVec3("spotLight.ambient", spotLightAmbient);
    myShader.setVec3("spotLight.diffuse", spotLightDiffuse);
    myShader.setVec3("spotLight.specular", spotLightSpecular);
    myShader.setFloat("spotLight.constant", spotLightConstant);
    myShader.setFloat("spotLight.linear", spotLightLinear);
    myShader.setFloat("spotLight.quadratic", spotLightQuadratic);
    myShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(spotLightCutOff)));
    myShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(spotLightOuterCutOff)));
    //material:
    // materialDiffuse.texUnit(myShader, "material.diffuse", 0);
    // materialSpecular.texUnit(myShader, "material.specular", 1);
    // myShader.setFloat("material.shininess", materialShininess);
    
}
