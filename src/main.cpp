#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#define M_SQRT3 1.73205080756887729353

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "mesh.h"
#include "glwindow.h"
#include "colors.h"
#include "camera.h"
#include "texture.h"

#define ASSETS_PATH "./assets"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Window dimensions
GLWindow mainWindow;
const GLint WIDTH = 512, HEIGHT = 512;

// Shader program
ShaderProgram computeShader;
ShaderProgram fragmentShader;

// Textures
Texture brickTexture;

// List of meshes
std::vector<Mesh*> meshList;

// List of shaders
std::string vertexShaderPath   = "./assets/shaders/vertex.vert";
std::string fragmentShaderPath = "./assets/shaders/fragment.frag";
std::string computeShaderPath  = "./assets/shaders/compute.comp";


int main(){

    std::cout<<"\t Initializing window...\n";
    mainWindow = GLWindow(WIDTH,HEIGHT);  
    // version 4.3 for compute shaders
    mainWindow.Initialize(4,3);

    std::cout<<"\t Creating objects...\n";
    Mesh *rectangle = new Mesh();

    float vertices[] = {
    // x      y     z    u     v
      1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
      1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
      -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, 0.0f, 0.0f, 0.0f
    };

    /*
      2 ---- 1
      |      |
      |      |
      3 ---- 0
    */

    unsigned int indices[] = {
      0, 1, 3,
      1, 2, 3
    };

    rectangle->CreateMesh(vertices, indices, 4*5, 2*3);
    meshList.push_back(rectangle);

    // Initialize shaders
    std::cout<<"\t Initializing shaders...\n";
    computeShader = ShaderProgram(computeShaderPath, ShaderType::COMPUTE);
    fragmentShader = ShaderProgram(vertexShaderPath, fragmentShaderPath);

    // Initialize texture where we output the results
    // of compute shader
    std::cout<<"\t Initializing textures...\n";
    
    unsigned int computeTexture;

    glGenTextures(1, &computeTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, computeTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glBindImageTexture(0, computeTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);


    // Loop until window is closed.
    while(!mainWindow.getShouldClose())
    {
        // Get and handle user input events
        glfwPollEvents();

        // Clear window
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        computeShader.use();
        glDispatchCompute((unsigned int)WIDTH, (unsigned int)HEIGHT, 1);
        // Make sure writing has finished before read
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        fragmentShader.use();
        fragmentShader.setInt("theTexture", 0);
        glBindTexture(GL_TEXTURE_2D, computeTexture);
        meshList[0]->RenderMesh();

        glUseProgram(0);
        mainWindow.swapBuffers();
    }

    return 0;
}
