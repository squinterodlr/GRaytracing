#include "camera.h"

Camera::Camera(glm::vec3 initPosition, glm::vec3 initUp, GLfloat initYaw, GLfloat initPitch)
{
    position = initPosition;
    worldUp = initUp;
    yaw = initYaw;
    pitch = initPitch;
    front = glm::vec3(0.0f, 0.0f, -1.0f);

    movementSpeed = 1.0f;
    turnSpeed = 5.0f;

    update();

}


void Camera::keyControl(bool* keys, GLfloat deltaTime)
{

    if(keys[GLFW_KEY_W])
    {
        position += front*movementSpeed*deltaTime;
    }


    if(keys[GLFW_KEY_S])
    {
        position -= front*movementSpeed*deltaTime;
    }


    if(keys[GLFW_KEY_A])
    {
        position -= right*movementSpeed*deltaTime;
    }


    if(keys[GLFW_KEY_D])
    {
        position += right*movementSpeed*deltaTime;
    }

}

void Camera::mouseControl(GLfloat mouseDeltaX, GLfloat mouseDeltaY, GLfloat deltaTime)
{

    mouseDeltaX *= turnSpeed*deltaTime;
    mouseDeltaY *= turnSpeed*deltaTime;

    yaw += mouseDeltaX;
    pitch -= mouseDeltaY; //Flip this sign to get inverted view
    pitch = glm::clamp(pitch,-89.0f,89.0f);
    
    //std::cout<<"yaw: "<<yaw<<"\t pitch: "<<pitch<<"\n";

    update();

}

glm::mat4 Camera::calculateViewMatrix()
{
    return glm::lookAt(position, position + front, up);

}

void Camera::update()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);


    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right,front));

}

Camera::~Camera()
{

}