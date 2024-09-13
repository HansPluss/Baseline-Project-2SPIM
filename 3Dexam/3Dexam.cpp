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
void processInput(GLFWwindow* window, Draw &cube, Draw &cube1, Draw &cube2);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;


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
    Cube0.DrawSphere(glm::vec3(23, 100, 145), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
    Draw Cube1;
    Cube1.DrawSphere(glm::vec3(23, 100, 145), glm::vec3(2, 0, -8), glm::vec3(1, 1, 1));

    Draw Cube2;
    Cube2.DrawSphere(glm::vec3(23, 100, 145), glm::vec3(-4, 0, -4), glm::vec3(1, 1, 1));
    
    Draw BoundingBox0;
    BoundingBox0.DrawBoundingBox(glm::vec3(1, 1, 1), glm::vec3(-5, 0, -5), glm::vec3(10, 1, 10));

    Collision collision; 

    Cube0.speed = 0.01; 
    
   

    Cube0.SetNormalVector(glm::vec3(0.0f, 0.0f, 1.0f));
    Cube1.SetNormalVector(glm::vec3(1.0f, 0.0f, 0.0f));
    Cube2.SetNormalVector(glm::vec3(1.0f, 0.0f, 0.0f));

    BoundingBox0.SetMass(10000.0f);

    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(-5.0f, 25.0f, -5.0f));

    Texture texture("Resources/Textures/icon.jpg", shaderProgram);


    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
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
 
        processInput(window, Cube0, Cube1, Cube2);

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


        // UNCOMMENT FOR ROTATION
        Cube0.RotateCube(dt);
        Cube1.RotateCube(dt);
        Cube2.RotateCube(dt);
        Cube0.Update(dt);
        Cube1.Update(dt);
        Cube2.Update(dt);



        Cube0.Render(shaderProgram, viewproj); 
        Cube1.Render(shaderProgram, viewproj);
        Cube2.Render(shaderProgram, viewproj);

        BoundingBox0.Render(shaderProgram, viewproj);

        //wall collision
        collision.InvAABBCollision(BoundingBox0, Cube0, dt);
        collision.InvAABBCollision(BoundingBox0, Cube1, dt);
        collision.InvAABBCollision(BoundingBox0, Cube2, dt);

        //spheres collision
        collision.SphereCollison(Cube0, Cube1, dt);
        collision.SphereCollison(Cube0, Cube2, dt);
        collision.SphereCollison(Cube1, Cube2, dt);


    
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
void processInput(GLFWwindow* window, Draw &cube, Draw& cube1, Draw &cube2)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {

        glm::vec3 force(20.0f, 0.0f, 10.0f);
      
        cube.ApplyForce(force);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {

        glm::vec3 force(-10.0f, 0.0f, 10.0f);
        cube1.ApplyForce(force);
        cube2.ApplyForce(force);
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
