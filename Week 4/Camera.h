#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OrbitCamera {
public:
    float radius;
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    OrbitCamera(glm::vec3 targetPos = glm::vec3(0.0f), float rad = 5.0f) 
        : target(targetPos), radius(rad) {
        SetPositionAngles(-90.0f, 0.0f);
    }

    void SetPositionAngles(float yaw, float pitch) {
        float camX = target.x + radius * cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        float camY = target.y + radius * sin(glm::radians(pitch));
        float camZ = target.z + radius * cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        position = glm::vec3(camX, camY, camZ);
        
        glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 forward = glm::normalize(target - position);
        glm::vec3 right = glm::cross(forward, worldUp);
        // Handling the case where forward is parallel to worldUp
        if (glm::length(right) < 0.001f) {
            right = glm::cross(forward, glm::vec3(1.0f, 0.0f, 0.0f));
        }
        right = glm::normalize(right);
        up = glm::normalize(glm::cross(right, forward));
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(position, target, up);
    }

    void ProcessMouseMovement(float xoffset, float yoffset) {
        float sensitivity = 0.3f;
        
        // Calculating the camera's local Right and Up vectors
        glm::vec3 forward = glm::normalize(target - position);
        glm::vec3 right = glm::normalize(glm::cross(forward, up));
        
        // Creating rotation matrices around the local axes
        glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(-xoffset * sensitivity), up);
        glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(yoffset * sensitivity), right);
        glm::mat4 rotation = rotY * rotX;

        // Applying rotation to position relative to target
        glm::vec3 dir = position - target;
        dir = glm::vec3(rotation * glm::vec4(dir, 1.0f));
        
        position = target + glm::normalize(dir) * radius;
        
        // Applying the same rotation to the Up vector
        up = glm::normalize(glm::vec3(rotation * glm::vec4(up, 0.0f)));
    }
};
