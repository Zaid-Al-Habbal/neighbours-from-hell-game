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
#include "LivingRoom.h"
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
    TextureClass wallTex("../resources/textures/wood.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    TextureClass wallSpecTex("../resources/textures/wood.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    TextureClass doorTex("../resources/textures/door.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    TextureClass doorSpecTex("../resources/textures/door.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    TextureClass tvBoxTex("../resources/textures/tv-box.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    TextureClass tvBoxSpecTex("../resources/textures/tv-box.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    TextureClass screenTex("../resources/textures/screen.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    TextureClass screenSpecTex("../resources/textures/screen.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //VBOs:

    //for Living Room:
    VBO livingRoomVBO(LivingRoom::vertices, sizeof(LivingRoom::vertices));
    VBO roomVBO(Room::vertices, sizeof(Room::vertices));
    VBO cubeVBO(Cube::vertices, sizeof(Cube::vertices));


    //VAOs:
	VAO livingRoomVAO; livingRoomVAO.init(livingRoomVBO);
	VAO roomVAO; roomVAO.init(roomVBO);
    VAO cubeVAO; cubeVAO.init(cubeVBO);
    
    //postions:
    vector<pair<glm::vec3, glm::vec3>> rooms; // {position, scale}
    rooms.push_back({glm::vec3(5.27f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.55f)});
    rooms.push_back({glm::vec3(3.5f, -1.05f, 0.0f), glm::vec3(3.0f, 1.0f, 0.55f)});
    rooms.push_back({glm::vec3(-1.0f, -1.05f, 0.0f), glm::vec3(1.5f, 1.0f, 0.55f)});
    // render loop:
    while(!controller.shouldClose()){
        controller.updateDeltaTime();
        controller.processInput();
        Camera camera = controller.getCamera();

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        
        //start mainShader:
        mainShader.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        mainShader.setMat4("projection", projection);
        mainShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);


        //set the lights:
        Light light(mainShader, true, 0, false, camera.Position, camera.Front);
        light.turnOnTheLights();

        //set material:
        mainShader.setFloat("shininess", 32.0f);
        wallTex.Bind();
        wallSpecTex.Bind();
        wallTex.texUnit(mainShader, "texture.diffuse1", 0);
        wallSpecTex.texUnit(mainShader, "texture.specular1", 1);

        //Living LivingRoom:
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.2f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.75f));
        mainShader.setMat4("model", model);
        
        livingRoomVAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, sizeof(LivingRoom::vertices)/8);

        //other rooms:
        for(int i=0; i<(int)rooms.size(); i++){
            model = glm::mat4(1.0f);
            model = glm::translate(model, rooms[i].first);
            model = glm::scale(model, rooms[i].second);
            mainShader.setMat4("model", model);
            roomVAO.Bind();
            glDrawArrays(GL_TRIANGLES, 0, sizeof(Room::vertices)/8);
        }

        //doors:

        //door1:
        //material:
        doorTex.Bind();
        doorSpecTex.Bind();
        doorTex.texUnit(mainShader, "texture.diffuse1", 0);
        doorSpecTex.texUnit(mainShader, "texture.specular1", 1);

        //model:
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.25f, -0.15f, -0.55f));
        model = glm::scale(model, glm::vec3(0.53f, 0.8f, 0.05f));
        mainShader.setMat4("model", model);

        cubeVAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, sizeof(Cube::vertices)/8);
        
        //door2:
        //model:
        model = glm::translate(model, glm::vec3(1.4f, 0.0f, 0.0f));

        mainShader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, sizeof(Cube::vertices)/8);

        //tv:
        //box
        //material:
        tvBoxTex.Bind();
        tvBoxSpecTex.Bind();
        tvBoxTex.texUnit(mainShader, "texture.diffuse1", 0);
        tvBoxSpecTex.texUnit(mainShader, "texture.specular1", 1);
        
        //model:
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.7f, -0.2f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
        model = glm::rotate(model, glm::radians(-25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        mainShader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, sizeof(Cube::vertices)/8);

        //screen
        //material:
        screenTex.Bind();
        screenSpecTex.Bind();
        screenTex.texUnit(mainShader, "texture.diffuse1", 0);
        screenSpecTex.texUnit(mainShader, "texture.specular1", 1);

        //model:
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.55f, -0.2f, 0.07f));
        model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.01f));
        mainShader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, sizeof(Cube::vertices)/8);
        


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(controller.getWindow());
        glfwPollEvents();
    }

	// EBO1.Delete();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
