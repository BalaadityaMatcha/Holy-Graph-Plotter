#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "RubiksCube.h"
#include <iostream>
#include <fstream>
#include <sstream>

OrbitCamera camera(glm::vec3(0.0f), 8.0f); // View from distance 8
float deltaTime = 0.0f;	
float lastFrame = 0.0f;
RubiksCube rubiks;

bool isDragging = false;
float lastX = 400.0f;
float lastY = 300.0f;

std::string readShaderCode(const char* filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) return "";
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, true);
        
        if (key == GLFW_KEY_SPACE) {
            rubiks = RubiksCube(); // Re-initializing the RubiksCube object
            camera.SetPositionAngles(-45.0f, 30.0f); // Resetting camera to starting angle
        }
        
        float dir = (mods & GLFW_MOD_SHIFT) ? -1.0f : 1.0f;
        
        if (key == GLFW_KEY_L) rubiks.RotateFace(0, -1, -90.0f * dir); // Left face
        if (key == GLFW_KEY_R) rubiks.RotateFace(0,  1,  90.0f * dir); // Right face
        if (key == GLFW_KEY_U) rubiks.RotateFace(1,  1, -90.0f * dir); // Up face
        if (key == GLFW_KEY_D) rubiks.RotateFace(1, -1,  90.0f * dir); // Down face
        if (key == GLFW_KEY_F) rubiks.RotateFace(2,  1, -90.0f * dir); // Front face
        if (key == GLFW_KEY_B) rubiks.RotateFace(2, -1,  90.0f * dir); // Back face
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            isDragging = true;
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            lastX = xpos;
            lastY = ypos;
        } else if (action == GLFW_RELEASE) {
            isDragging = false;
        }
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (isDragging) {
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;
        camera.ProcessMouseMovement(xoffset, yoffset);
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create Window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Week 4 - Rubiks Cube", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    camera.SetPositionAngles(-45.0f, 30.0f); // Look from an angled corner

    std::cout << "----------------Rubiks Cube Simulation----------------\n";
    std::cout << "Rubik's Cube Simulation Controls:\n\n";
    std::cout << "Click and Drag Left Mouse Button to adjust Camera\n\n";
    std::cout << "Press Shift to reverse direction of rotation\n";
    std::cout << "F : Rotate Front Face (clockwise)\n";
    std::cout << "B : Rotate Back Face (clockwise)\n";
    std::cout << "U : Rotate Up Face (clockwise)\n";
    std::cout << "D : Rotate Down Face (clockwise)\n";
    std::cout << "R : Rotate Right Face (clockwise)\n";
    std::cout << "L : Rotate Left Face (clockwise)\n\n";
    std::cout << "SPACE : Reset Cube and Camera\n";
    std::cout << "ESC : Quit simulation\n";

    std::string vertexCode = readShaderCode("shaders/cube.vert");
    std::string fragmentCode = readShaderCode("shaders/cube.frag");
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    float vertices[] = {
        // Back face (Red)
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

        // Front face (Orange)
        -0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,

        // Left face (Blue)
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        // Right face (Green)
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

        // Bottom face (Yellow)
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,

        // Top face (White)
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        int modelLoc = glGetUniformLocation(shaderProgram, "model");
        int viewLoc = glGetUniformLocation(shaderProgram, "view");
        int projLoc = glGetUniformLocation(shaderProgram, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        
        // Drawing 27 cubies
        float spacing = 1.05f; // Slight gap between cubies & slightly bigger
        for (const auto& cubie : rubiks.cubies) {
            glm::mat4 model = glm::mat4(1.0f);
            // Rotation of this cubie
            model = model * cubie.rotation;
            // Translation, scaled by spacing
            model = glm::translate(glm::mat4(1.0f), cubie.logicalPos * spacing) * cubie.rotation;
            
            // Scale down to make it look like a cubie
            model = glm::scale(model, glm::vec3(1.03f));

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
