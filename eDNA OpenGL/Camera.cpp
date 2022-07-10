#include "Camera.h"




Camera::Camera()
{

    Position = glm::dvec3(0.0, 0.0, 0.0);
    WorldUp = glm::vec3(0.f, 0.f, 1.f);
    Yaw = 0.f;
    Pitch = 0.f;
    MovementSpeed = 2.5f;
    MouseSensitivity = 0.1f;
    Zoom = 45.0f;
    UpdateCameraVectors();
    UpdateViewMatrix();
}


void Camera::UpdateViewMatrix()
{
    //viewMatrix = glm::lookAt((glm::vec3)Position, (glm::vec3)Position + Front, Up);
    viewMatrix = glm::lookAt(glm::vec3(0.f), glm::vec3(0.f) + Front, Up);
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
    return viewMatrix;
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position.y += velocity;
    if (direction == BACKWARD)
        Position.y -= velocity;
    if (direction == LEFT)
        Position.x -= velocity;
    if (direction == RIGHT)
        Position.x += velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
    UpdateViewMatrix();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}


// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::UpdateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.y = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.x = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.z = sin(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}