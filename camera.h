
#ifndef LEARNOGL_COURSE_CAMERA_H
#define LEARNOGL_COURSE_CAMERA_H

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using glm::radians;
using glm::vec3;
using glm::normalize;
using glm::cross;

enum Camera_Movements {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// default camera values
const float YAW         = -90.f;
const float PITCH       = 0.0f;
const float SPEED       = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM        = 45.0f;

class Camera {

public:
    //camera attributes
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    //scalar constructor
    Camera(float posX, float posY, float posZ, float upX, float upY, float
    upZ, float pitch, float yaw) :  Front(vec3(0.0f, 0.0f, -1.0f)),
    MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        Up = glm::vec3(upX, upY, upZ);
        Pitch = pitch;
        Yaw = yaw;
        updateCameraVectors();
    }

    glm::mat4 GetMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void ProcessKeyboard(Camera_Movements direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if(direction == FORWARD)
            Position += Front * velocity;
        if(direction == BACKWARD)
            Position -= Front * velocity;
        if(direction == RIGHT)
            Position += Right * velocity;
        if(direction == LEFT)
            Position -= Right * velocity;
    }

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean
    constrainPitch=true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        if(constrainPitch)
        {
            if(Pitch < -89.0f)
                Pitch = 89.0f;
            if(Pitch > 89.0f)
                Pitch = 89.0f;
        }
        updateCameraVectors();
    }

    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if(Zoom < 1.0f)
            Zoom = 1.0f;
        if(Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:
    void updateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(radians(Yaw)) * cos(radians(Pitch));
        front.y = sin(radians(Pitch));
        front.z = sin(radians(Yaw)) * cos(radians(Pitch));
        Front = normalize(front);
        Right = normalize(cross(Front, WorldUp));
        Up = normalize(cross(Right, Front));
    }

};

#endif //LEARNOGL_COURSE_CAMERA_H


