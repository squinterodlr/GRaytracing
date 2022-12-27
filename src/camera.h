#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

class Camera
{
public:
    Camera(glm::vec3 initPosition = glm::vec3(0.0f,0.0f,0.0f),
           glm::vec3 initUp = glm::vec3(0.0f,1.0f,0.0f),
           GLfloat initYaw = 0.0f,
           GLfloat initPitch = 0.0f);

    void keyControl(bool *keys, GLfloat deltaTime);
    void mouseControl(GLfloat mouseDeltaX, GLfloat mouseDeltaY, GLfloat deltaTime);

    glm::mat4 calculateViewMatrix();

    ~Camera();

    void setMovementSpeed(GLfloat speed){ movementSpeed = speed;}
    void setTurnSpeed(GLfloat speed){ turnSpeed = speed;}

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat movementSpeed;
    GLfloat turnSpeed;

    void update();
};



#endif