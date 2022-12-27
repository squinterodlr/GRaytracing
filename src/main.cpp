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

float degree = M_PI/180.0;

// Window dimensions
GLWindow mainWindow;
const GLint WIDTH = 800, HEIGHT = 600;

// Shader program
ShaderProgram shaderProgram;

// Camera
Camera camera;

// Textures

Texture brickTexture;


// Time!
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;


// List of meshes
std::vector<Mesh*> meshList;

// List of shaders
std::string vertexShaderPath   = "./assets/shaders/vertex.vert";
std::string fragmentShaderPath = "./assets/shaders/fragment.frag";
std::string computeShaderPath  = "./assets/shaders/compute.comp";

// Camera properties:
glm::vec3 cameraPos(0.0f,0.0f,-5.0f);
glm::vec3 cameraDir(0.0f,0.0f,1.0f);

/* Ortho properties
float cameraOrthoDepth = 100.0f;
float cameraOrthoWidth = 2.0f;
float cameraOrthoHeight = 2.0f;
*/

float cameraDepth  = 100.0f;
float cameraAspect = (float)WIDTH/(float)HEIGHT;
float cameraFOV = 45.0*degree;

void CreateObjects(){

    /* Hexahedron:

                0
               /|\
             /  |  \
           /    |    \
         /     |      \
       2_- - - | - - -  1
         \¯__  |   __¯ /
           \ ¯ 3 ¯   /
             \  |  /
               \|/
                4
    
    0: (  0.0,   0.0,   √2)
    1: (  1.0,   0.0,  0.0)
    2: ( -0.5,  √3/2,  0.0)
    3: ( -0.5, -√3/2,  0.0)
    4: (  0.0,   0.0,  -√2)

    If we set ±√2 for the z value of the 0th and 4th vertices, we get
    two regular tetrahedra stuck together. However, if we set z value
    to ±1, then we get an octahedron whose vertices lie on the unit
    sphere, so it looks rounder.

    
    */

    // I'm just randomly choosing the positions of the texture coordinates because yeah
    GLfloat vertices[] = {
///         x,             y,     z,  u,       v,         
         0.0f,          0.0f,  1.0f,  0.0f, 0.0f,
         1.0f,          0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f*M_SQRT3,  0.0f,  0.5f, 0.0f,
        -0.5f,  0.5f*M_SQRT3,  0.0f,  1.0f, 1.0f,
         0.0f,          0.0f, -1.0f,  1.0f, 0.0f,
         };

    unsigned int indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 3, 1,
        4, 1, 3,
        4, 2, 1,
        4, 3, 2
    };

    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices,indices,5*5,6*3);
    meshList.push_back(obj1);

}

int main(){

    std::cout<<"\t Initializing window...\n";
    mainWindow = GLWindow(WIDTH,HEIGHT);  
    mainWindow.Initialize();

    std::cout<<"\t Creating objects...\n";
    CreateObjects();
    
    Color vertexColor = colors["nadeshikopink"];
    //std::cout<<"Color: "<<vertexColor.r<<" "<<vertexColor.g<<" "<<vertexColor.b<<"\n";


    // Initialize shaders
    std::cout<<"\t Initializing shaders...\n";
    shaderProgram = ShaderProgram(vertexShaderPath,fragmentShaderPath);

    // Initialize camera
    std::cout<<"\t Initializing camera...\n";
    camera = Camera(glm::vec3(0.0f,0.0f,-2.0f),glm::vec3(0.0f,1.0f,0.0f),90.0f, 0.0f);
    camera.setMovementSpeed(5.0f);
    camera.setTurnSpeed(10.0f);

    // Initialize texture
    std::cout<<"\t Initializing textures...\n";
    brickTexture = Texture("assets/textures/brick.png");
    brickTexture.LoadTexture();
    

    // View matrix: transforms everything so that camera is at the origin looking in the -z direction
    glm::mat4 view = camera.calculateViewMatrix();

    // Projection matrix
    glm::mat4 projection = glm::perspective(cameraFOV,cameraAspect,0.1f,0.1f+cameraDepth);

    // Wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glm::mat4 model = glm::rotate(glm::mat4(1.0f),(float)M_PI_2,glm::vec3(0.0f,0.0f,1.0f));
    //float dAngle = 0.00f;


    // Loop until window is closed.
    while(!mainWindow.getShouldClose())
    {
        // Get and handle user input events
        glfwPollEvents();

        GLfloat currentTime = glfwGetTime(); // Time in seconds
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        GLfloat mousedx = mainWindow.getXChange();
        GLfloat mousedy = mainWindow.getYChange();

        camera.keyControl(mainWindow.getKeys(), deltaTime);
        camera.mouseControl(mousedx, mousedy, deltaTime);
        view = camera.calculateViewMatrix();

        // Clear window
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        shaderProgram.use();

        
        // model = glm::rotate(model, dAngle, glm::vec3(1.0f,1.0f,0.0f));

        shaderProgram.setMat4("model",model);
        shaderProgram.setMat4("view",view);
        shaderProgram.setMat4("projection",projection);
        shaderProgram.setVec3("inColor",glm::vec3(vertexColor.r,vertexColor.g,vertexColor.b));


        // TODO: Add textures to meshes!
        brickTexture.UseTexture();
        meshList[0]->RenderMesh();

        glUseProgram(0);

        mainWindow.swapBuffers();
    }

    return 0;
}
