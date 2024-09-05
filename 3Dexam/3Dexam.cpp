#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include "glm/mat4x3.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib> 
#include <stb/stb_image.h>
#include "Resources/Shaders/shaderClass.h"
#include "Texture.h"
#include "Draw.h"
#include "Camera.h"
#include "Collision.h"
#include <chrono>
// Some of the code for the spotlight is from the following repo
// https://github.com/VictorGordan/opengl-tutorials.git
//

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Draw &cube, Draw &cube1);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Test Win", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    gladLoadGL();

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    Shader shaderProgram("default.vert", "default.frag");
    shaderProgram.Activate(); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    Shader lightShader("light.vert", "light.frag");
    lightShader.Activate();



    
    Draw Cube0; 
    Cube0.DrawCube(glm::vec3(23, 100, 145), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
    Draw Cube1;
    Cube1.DrawCube(glm::vec3(23, 100, 145), glm::vec3(10, 0, 0), glm::vec3(1, 1, 1));
    Draw Wall0;
    Wall0.DrawCube(glm::vec3(1, 1, 1), glm::vec3(20, 0, 0), glm::vec3(1, 1, 20));
    Draw Wall1;
    Wall1.DrawCube(glm::vec3(0.1, 0.1, 0.1), glm::vec3(-10, 0, 0), glm::vec3(1, 1, 20));
    Draw Wall2;
    Wall2.DrawCube(glm::vec3(1, 1, 1), glm::vec3(5, 0, -10), glm::vec3(20, 1, 1));
    Draw Wall3;
    Wall3.DrawCube(glm::vec3(0.1, 0.1, 0.1), glm::vec3(5, 0, 10), glm::vec3(20, 1, 1));

    Collision collision; 

    Cube0.speed = 0.01; 
    Cube0.ApplyForce(glm::vec3(10.0f, 0.0f, 0.0f));
   

    Cube0.SetNormalVector(glm::vec3(1.0f, 0.0f, 1.0f));
    Cube1.SetNormalVector(glm::vec3(0.0f, 0.0f, 1.0f));


    Wall0.SetMass(10000.0f);
    Wall1.SetMass(10000.0f);
    Wall2.SetMass(10000.0f);
    Wall3.SetMass(10000.0f);
    
    Wall0.SetNormalVector(glm::vec3(1.0f, 0.0f, 0.0f));
    Wall1.SetNormalVector(glm::vec3(-1.0f, 0.0f, 0.0f));
    Wall2.SetNormalVector(glm::vec3(0.0f, 0.0f, -1.0f));
    Wall3.SetNormalVector(glm::vec3(0.0f, 0.0f, 1.0f));

    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(-10.0f, 10.0f, 50.0f));

    Texture texture("Resources/Textures/icon.jpg", shaderProgram);
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(10.0f, 20.0f, 10.0f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 objectModel = glm::mat4(1.0f);
    objectModel = glm::translate(objectModel, objectPos);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    
   
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    int timeSinceStart = 0;

    auto previousTime = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window))
    {
 
        processInput(window, Cube0,Cube1);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto currentTime = std::chrono::high_resolution_clock::now();

        // Calculate delta time (in seconds)
        std::chrono::duration<float> deltaTime = currentTime - previousTime;

        // Update previousTime for the next frame
        previousTime = currentTime;

        // Now you can use deltaTime.count() which gives you the delta time in seconds
        float dt = deltaTime.count();
        camera.Inputs(window);

        //Set render distance and FOV
        glm::mat4 viewproj = camera.Matrix(45.0f, 0.1f, 1000.0f, shaderProgram, "camMatrix");

        
        Cube0.Update(dt);
        Cube1.Update(dt);
        
        //Cube1.MoveXdir();

        //cube collision
        collision.AABBCollision(Cube0, Cube1); 
       

        //wall collision
        collision.AABBCollision(Wall0, Cube0);
        collision.AABBCollision(Wall0, Cube1);
        collision.AABBCollision(Wall1, Cube0);
        collision.AABBCollision(Wall1, Cube1);

        collision.AABBCollision(Wall2, Cube0);
        collision.AABBCollision(Wall2, Cube1);
        collision.AABBCollision(Wall3, Cube0);
        collision.AABBCollision(Wall3, Cube1);

        Cube0.Render(shaderProgram, viewproj); 
        Cube1.Render(shaderProgram, viewproj);

        Wall0.Render(shaderProgram, viewproj);
        Wall1.Render(shaderProgram, viewproj);
        Wall2.Render(shaderProgram, viewproj);
        Wall3.Render(shaderProgram, viewproj);

    
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
 

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window, Draw &cube, Draw& cube1)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {

        glm::vec3 force(20.0f, 0.0f, 20.0f);
        cube.ApplyForce(force);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {

        glm::vec3 force(-10.0f, 0.0f, 20.0f);
        cube1.ApplyForce(force);
    }
       
   
    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
