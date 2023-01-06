#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLWindow
{

public:
    GLWindow();
    GLWindow(GLuint windowWidth, GLuint windowHeight);
    ~GLWindow();

    int Initialize();
    int Initialize(int GLVersionMajor, int GLVersionMinor);

    void swapBuffers();

    bool getShouldClose() { return glfwWindowShouldClose(window); }
    bool getKeyPressed(unsigned int keyID) { return keys[keyID]; }

    GLfloat getXChange();
    GLfloat getYChange();

    bool *getKeys() { return keys; }

private:
    GLFWwindow *window;
    GLuint width, height;
    int bufferWidth, bufferHeight;

    // 1024 covers all ASCII characters. When key is pressed, bool is true.
    bool keys[1024];

    GLfloat lastMouseX, lastMouseY, mouseDeltaX, mouseDeltaY;
    bool mouseFirstMoved; // We want to avoid the camera jumping when we make the window active

    void createCallbacks();
    // A callback can't take a member function of class, that's why we have to make it static
    static void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow *window, double xPos, double yPos);
};

#endif