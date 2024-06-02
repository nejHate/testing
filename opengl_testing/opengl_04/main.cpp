#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

// Constants
const int WIDTH = 800;
const int HEIGHT = 600;
const float CAMERA_SPEED = 0.05f;
const float MOUSE_SENSITIVITY = 0.1f;

// Camera variables
float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 3.0f;
float cameraYaw = -90.0f;
float cameraPitch = 0.0f;
float lastMouseX = WIDTH / 2.0f;
float lastMouseY = HEIGHT / 2.0f;

// Function to handle mouse movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    float xOffset = xpos - lastMouseX;
    float yOffset = lastMouseY - ypos;
    lastMouseX = xpos;
    lastMouseY = ypos;

    xOffset *= MOUSE_SENSITIVITY;
    yOffset *= MOUSE_SENSITIVITY;

    cameraYaw += xOffset;
    cameraPitch += yOffset;

    if (cameraPitch > 89.0f) cameraPitch = 89.0f;
    if (cameraPitch < -89.0f) cameraPitch = -89.0f;

    float yawRad = (cameraYaw) * (3.14159f / 180.0f);
    float pitchRad = (cameraPitch) * (3.14159f / 180.0f);
}

// Function to handle keyboard input
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = CAMERA_SPEED;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraSpeed *= 2.5;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraZ -= cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraZ += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraX -= cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraX += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraY += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraY -= cameraSpeed;
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Minecraft-like Game", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);
    // Set the required callback functions
    glfwSetCursorPosCallback(window, mouse_callback);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Process input
        processInput(window);

        // Render here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Camera transformation
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(cameraX, cameraY, cameraZ, cameraX + cos(cameraYaw), cameraY + sin(cameraPitch), cameraZ + sin(cameraYaw), 0.0f, 1.0f, 0.0f);

        // Draw your blocks here

        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }
    // Terminate GLFW
    glfwTerminate();
    return 0;
}
