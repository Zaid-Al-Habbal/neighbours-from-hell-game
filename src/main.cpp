#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include <bits/stdc++.h>

#include "Controller.h"
#include "model.h"
#include "shader.h"
#include "filesystem.h"
#include "TextureClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Light.h"
#include "Cube.h"
#include "Room.h"

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    //Controller:
    Controller controller;
    if (!controller.initializeWindow("Neighbours From Hell")) return -1;
    
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);
    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Shaders:
    Shader mainShader("../src/shaders/mainShader.vs", "../src/shaders/mainShader.fs");

    //Models:


    //Textures:
    TextureClass containerTex("../resources/textures/container2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    TextureClass containerSpecTex("../resources/textures/container2_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    TextureClass fireTex("../resources/textures/fire.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    
    //VBOs:

    //for Living Room:
    VBO roomVBO(Room::vertices, sizeof(Room::vertices));


    //VAOs:
	VAO roomVAO; roomVAO.init(roomVBO);
    
    // render loop:
    while(!controller.shouldClose()){
        controller.updateDeltaTime();
        controller.processInput();
        Camera camera = controller.getCamera();
        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        
        //start drawing process:
        mainShader.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        mainShader.setMat4("projection", projection);
        mainShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        mainShader.setMat4("model", model);

        //Light:
        Light light(mainShader, true, 3, false, camera.Position, camera.Front);
        light.pointLightPosition[0] = glm::vec3(5.0f, 5.0f, 0.0f);
        light.pointLightColor[0] = glm::vec3(0.0f, 1.0f, 1.0f);
        light.pointLightPosition[1] = glm::vec3(2.0f, 0.0f, 12.0f);
        light.pointLightColor[1] = glm::vec3(0.0f, 0.0f, 0.0f);
        light.pointLightPosition[2] = glm::vec3(2.0f, 5.0f, 3.0f);
        light.pointLightColor[2] = glm::vec3(0.0f, 0.0f, 0.0f);
        light.turnOnTheLights();
        mainShader.setFloat("shininess", 64.0f);

        containerTex.Bind();
        containerSpecTex.Bind();

        containerTex.texUnit(mainShader, "texture.diffuse1", 0);
        containerSpecTex.texUnit(mainShader, "texture.specular1", 1);

        roomVAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, sizeof(Room::vertices)/6);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(controller.getWindow());
        glfwPollEvents();
    }

	// EBO1.Delete();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
