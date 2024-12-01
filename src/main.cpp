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
#include "color.hpp"
#include "Sofa.h"
#include "Cylinder.h"
#include "Torus.h"

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
    
    TextureClass tableTex("../resources/textures/wood2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    TextureClass tableSpecTex("../resources/textures/wood2.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    TextureClass sofaTex("../resources/textures/rubber.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    TextureClass sofaSpecTex("../resources/textures/rubber.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    TextureClass triaTex("../resources/textures/tv-box.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    TextureClass triaSpecTex("../resources/textures/white.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //shapes:
    //Tria:
    Cylinder triaBar(0.01f, 0.01f, 0.1f, 16, 1, true, 2);
    Cylinder tria(0.2f, 0.11f, 0.1f, 32, 1, true, 2);
    //VBOs:

    //for Living Room:
    VBO livingRoomVBO(LivingRoom::vertices, sizeof(LivingRoom::vertices));
    VBO roomVBO(Room::vertices, sizeof(Room::vertices));
    VBO cubeVBO(Cube::vertices, sizeof(Cube::vertices));
    VBO sofaVBO(Sofa::vertices, sizeof(Sofa::vertices));
    VBO triaBarVBO(triaBar.getInterleavedVertices(), triaBar.getInterleavedVertexSize());
    VBO triaVBO(tria.getInterleavedVertices(), tria.getInterleavedVertexSize());

    //VAOs:
	VAO livingRoomVAO; livingRoomVAO.init(livingRoomVBO);
	VAO roomVAO; roomVAO.init(roomVBO);
    VAO cubeVAO; cubeVAO.init(cubeVBO);
    VAO sofaVAO; sofaVAO.init(sofaVBO);
    VAO triaBarVAO; triaBarVAO.init(triaBarVBO);
    VAO triaVAO; triaVAO.init(triaVBO);
    
    //EBOs:
    EBO triaBarEBO(triaBar.getIndices(), triaBar.getIndexSize());
    EBO triaEBO(tria.getIndices(), tria.getIndexSize());

    //postions:
    //Rooms:
    vector<pair<glm::vec3, glm::vec3>> rooms; // {position, scale}
    rooms.push_back({glm::vec3(5.27f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.55f)});
    rooms.push_back({glm::vec3(3.5f, -1.05f, 0.0f), glm::vec3(3.0f, 1.0f, 0.55f)});
    rooms.push_back({glm::vec3(-1.0f, -1.05f, 0.0f), glm::vec3(1.5f, 1.0f, 0.55f)});

    //SofaLegs:
    vector<glm::vec3> sofaLegs;
    sofaLegs.push_back(glm::vec3(0.7f, -0.45f, 0.0f));
    sofaLegs.push_back(glm::vec3(0.5f, -0.45f, 0.0f));
    sofaLegs.push_back(glm::vec3(0.6f, -0.45f, -0.05f));
    sofaLegs.push_back(glm::vec3(0.6f, -0.45f, 0.1f));


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
        Light light(mainShader, false, 2, false, camera.Position, camera.Front);
        light.pointLightPosition[0] = glm::vec3(4.0f, 0.0f, 2.0f);
        light.pointLightPosition[1] = glm::vec3(0.990622, 0.414369, -0.0452774);
        light.pointLightColor[1] = Color::Yellow;
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

        //table:
        //material:
        tableTex.Bind();
        tableSpecTex.Bind();
        tableTex.texUnit(mainShader, "texture.diffuse1", 0);
        tableSpecTex.texUnit(mainShader, "texture.specular1", 1);
        
        //surface:
        //model:
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.7f, -0.35f, 0.0f));
        model = glm::rotate(model, glm::radians(-25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.01f, 0.5f));
        mainShader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, sizeof(Cube::vertices)/8);
        //legs:
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.78f, -0.42f, 0.1f));
        model = glm::rotate(model, glm::radians(-25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.07f, 0.15f, 0.05f));
        mainShader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, sizeof(Cube::vertices)/8);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.7f, -0.42f, -0.1f));
        model = glm::rotate(model, glm::radians(-25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.07f, 0.15f, 0.05f));
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

        //Sofa:
        //Seat && Backrest:
        //material:
        sofaTex.Bind();
        sofaSpecTex.Bind();
        sofaTex.texUnit(mainShader, "texture.diffuse1", 0);
        sofaSpecTex.texUnit(mainShader, "texture.specular1", 1);
        //model
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.6f, -0.4f, 0.0f));
        model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.6f, 0.3f));
        mainShader.setMat4("model", model);
        
        sofaVAO.Bind();

        glDrawArrays(GL_TRIANGLES, 0, sizeof(Sofa::vertices)/8);

        //ARMREST:
        cubeVAO.Bind();
        //model:
        //right armrest:
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.67f, -0.25f, 0.08f));
        model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.15f));
        mainShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(Cube::vertices)/8);
        //left armrest:
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.52f, -0.25f, -0.08f));
        model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.15f));
        mainShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(Cube::vertices)/8);
        //legs:
        //material:
        tableTex.Bind();
        tableSpecTex.Bind();
        tableTex.texUnit(mainShader, "texture.diffuse1", 0);
        tableSpecTex.texUnit(mainShader, "texture.specular1", 1);
        
        //model:
        for(int i=0; i<(int)sofaLegs.size(); i++){
            model = glm::mat4(1.0f);
            model = glm::translate(model, sofaLegs[i]);
            model = glm::rotate(model, glm::radians(-25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.02f, 0.1f, 0.02f));
            mainShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, sizeof(Cube::vertices)/8);
        }

        //Tria:
        //TriaBar:
        //material:
        triaTex.Bind();
        triaSpecTex.Bind();
        triaTex.texUnit(mainShader, "texture.diffuse1", 0);
        triaSpecTex.texUnit(mainShader, "texture.specular1", 1);
        
        //model:
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 0.45f, 0.0f));
        mainShader.setMat4("model", model);

        triaBarVAO.Bind(); triaBarEBO.Bind();
        glDrawElements(GL_TRIANGLES, triaBar.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

        //tria:
        //model:
        model = glm::translate(model, glm::vec3(0.0f, -0.1f, 0.0f));
        mainShader.setMat4("model", model);

        triaVAO.Bind(); triaEBO.Bind();
        glDrawElements(GL_TRIANGLES, tria.getIndexCount(), GL_UNSIGNED_INT, (void*)0);





        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(controller.getWindow());
        glfwPollEvents();
    }

	// EBO1.Delete();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
