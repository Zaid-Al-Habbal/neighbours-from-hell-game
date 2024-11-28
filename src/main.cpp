#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include <bits/stdc++.h>

#include "model.h"
#include "shader.h"
#include "filesystem.h"
#include "camera.h"
#include "TextureClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Light.h"
#include "Cube.h"
#include <Room.h>

using namespace std;

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float vis = 0.01, red = 0.3, blue = 0.2, green = 0.4;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL){ std::cout << "Failed to create GLFW window" << std::endl; glfwTerminate();return -1;}
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback); 

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);
    // configure global opengl state
    // -----------------------------
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
    VBO roomVBO(Room::vertices, sizeof(Room::vertices));


    //VAOs:
	VAO roomVAO; roomVAO.init(roomVBO);
    

    // render loop:
    while(!glfwWindowShouldClose(window)){

        // per-frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

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
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	// EBO1.Delete();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}  

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}   