#include "glwindow.h"

#include <GL/glew.h>

GLWindow::GLWindow()
{
    width = 800;
    height = 600;

    mouseDeltaX = 0.0f;
    mouseDeltaY = 0.0f;

    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
    

}
GLWindow::GLWindow(GLuint windowWidth, GLuint windowHeight){

    width = windowWidth;
    height = windowHeight;
    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
    

}
int GLWindow::Initialize(){
    return Initialize(3,3);
}
int GLWindow::Initialize(int GLVersionMajor, int GLVersionMinor){

    // Initialize GLFW and check that it works
    if (!glfwInit())
    {
        std::cerr<<"GLFW initialization failed"<<std::endl;
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties:
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLVersionMinor);

    // Core profile: don't allow deprecated features (no backwards compatibility)
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    // Create main window and check it was created properly
    window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);

    if (!window)
    {
        std::cout<<"GLFW window creation failed"<<std::endl;
        glfwTerminate();
        return 1;
    }

    // Get main monitor info and center window
    const GLFWvidmode *vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int screenWidth = vidMode->width;
    int screenHeight = vidMode->height;
    int windowX = (screenWidth - width)/2;
    int windowY = (screenHeight - height)/2;
    glfwSetWindowPos(window, windowX, windowY);

    // Get buffer size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(window,&bufferWidth, &bufferHeight);

    // Set context that GLEW will use
    glfwMakeContextCurrent(window);

    // Handle mouse + key input
    createCallbacks();
    // Capture the cursor
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    // Allow modern extension features
    glewExperimental = GL_TRUE;
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cout<<"GLEW Initialization failed"<<std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    // Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    // Enable z-buffer
    glEnable(GL_DEPTH_TEST);

    //This lets us assign user pointers to the window to set for callback functions
    glfwSetWindowUserPointer(window, this); 

    return 0;
}

void GLWindow::swapBuffers()
{
    glfwSwapBuffers(window);    
}

void GLWindow::createCallbacks()
{
    glfwSetKeyCallback(window, handleKeys);
    glfwSetCursorPosCallback(window, handleMouse);

}

GLfloat GLWindow::getXChange()
{
    GLfloat theChange = mouseDeltaX;
    mouseDeltaX = 0.0f;
    return theChange;

}

GLfloat GLWindow::getYChange()
{

    GLfloat theChange = mouseDeltaY;
    mouseDeltaY = 0.0f;
    return theChange;

    
}

void GLWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    GLWindow *theWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));


    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            theWindow->keys[key] = true;
            std::cout<<"Pressed "<<key<<" key.\n";
        }
        else if (action == GLFW_RELEASE)
        {
            theWindow->keys[key] = false;
            std::cout<<"Released "<<key<<" key.\n";
        }
        
    }

}

void GLWindow::handleMouse(GLFWwindow *window, double xPos, double yPos)
{
    GLWindow *theWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

    if (theWindow->mouseFirstMoved){
        theWindow->lastMouseX = xPos;
        theWindow->lastMouseY = yPos;
        theWindow->mouseFirstMoved = false;
    }

    theWindow->mouseDeltaX = xPos-theWindow->lastMouseX;
    theWindow->mouseDeltaY = yPos-theWindow->lastMouseY; //If we flip this sign we get inverted view (I think?)

    theWindow->lastMouseX = xPos;
    theWindow->lastMouseY = yPos;
}


GLWindow::~GLWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}