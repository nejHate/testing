#include <GL/glut.h>
#include <cmath>

// Constants
const int WIDTH = 800;
const int HEIGHT = 600;
const int CHUNK_SIZE = 16;

// Camera parameters
float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 5.0f;
float cameraYaw = 0.0f;
float cameraPitch = 0.0f;

// Array representing the chunk
int chunk[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

// Function to initialize the chunk
void initChunk() {
    // Initialize the chunk array with block types
    for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE; ++i) {
        // Assign block types based on your data
        chunk[i] = i % 3; // Just an example
    }
}

// Function to render a single block at position (x, y, z)
void renderBlock(float x, float y, float z, int blockType) {
    // Set color based on block type
    switch(blockType) {
        case 0:
            glColor3f(1.0f, 0.0f, 0.0f); // Red
            break;
        case 1:
            glColor3f(0.0f, 1.0f, 0.0f); // Green
            break;
        case 2:
            glColor3f(0.0f, 0.0f, 1.0f); // Blue
            break;
        // Add more cases for other block types
    }

    // Draw the cube
    glBegin(GL_QUADS);
    // Front face
    glVertex3f(x - 0.5f, y - 0.5f, z + 0.5f);
    glVertex3f(x + 0.5f, y - 0.5f, z + 0.5f);
    glVertex3f(x + 0.5f, y + 0.5f, z + 0.5f);
    glVertex3f(x - 0.5f, y + 0.5f, z + 0.5f);
    // Back face
    glVertex3f(x - 0.5f, y - 0.5f, z - 0.5f);
    glVertex3f(x - 0.5f, y + 0.5f, z - 0.5f);
    glVertex3f(x + 0.5f, y + 0.5f, z - 0.5f);
    glVertex3f(x + 0.5f, y - 0.5f, z - 0.5f);
    // Top face
    glVertex3f(x - 0.5f, y + 0.5f, z - 0.5f);
    glVertex3f(x - 0.5f, y + 0.5f, z + 0.5f);
    glVertex3f(x + 0.5f, y + 0.5f, z + 0.5f);
    glVertex3f(x + 0.5f, y + 0.5f, z - 0.5f);
    // Bottom face
    glVertex3f(x - 0.5f, y - 0.5f, z - 0.5f);
    glVertex3f(x + 0.5f, y - 0.5f, z - 0.5f);
    glVertex3f(x + 0.5f, y - 0.5f, z + 0.5f);
    glVertex3f(x - 0.5f, y - 0.5f, z + 0.5f);
    // Right face
    glVertex3f(x + 0.5f, y - 0.5f, z - 0.5f);
    glVertex3f(x + 0.5f, y + 0.5f, z - 0.5f);
    glVertex3f(x + 0.5f, y + 0.5f, z + 0.5f);
    glVertex3f(x + 0.5f, y - 0.5f, z + 0.5f);
    // Left face
    glVertex3f(x - 0.5f, y - 0.5f, z - 0.5f);
    glVertex3f(x - 0.5f, y - 0.5f, z + 0.5f);
    glVertex3f(x - 0.5f, y + 0.5f, z + 0.5f);
    glVertex3f(x - 0.5f, y + 0.5f, z - 0.5f);
    glEnd();
}

// Function to render the chunk of blocks
void renderChunk() {
    // Iterate through the chunk array and render each block
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                int index = x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE;
                int blockType = chunk[index];
                float posX = x - CHUNK_SIZE / 2.0f + 0.5f;
                float posY = y - CHUNK_SIZE / 2.0f + 0.5f;
                float posZ = z - CHUNK_SIZE / 2.0f + 0.5f;
                renderBlock(posX, posY, posZ, blockType);
            }
        }
    }
}

// Function to render the scene
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Set up camera
    glRotatef(-cameraPitch, 1.0f, 0.0f, 0.0f);
    glRotatef(-cameraYaw, 0.0f, 1.0f, 0.0f);
    glTranslatef(-cameraX, -cameraY, -cameraZ);
    
    // Render the chunk of blocks
    renderChunk();
    
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    // Handle key presses to move the camera
    switch(key) {
        case 'w':
            // Move camera forward
            cameraZ -= 0.1f * cos(cameraYaw);
            cameraX += 0.1f * sin(cameraYaw);
            break;
        case 's':
            // Move camera backward
            cameraZ += 0.1f * cos(cameraYaw);
            cameraX -= 0.1f * sin(cameraYaw);
            break;
        case 'a':
            // Strafe camera left
            cameraX -= 0.1f * cos(cameraYaw);
            cameraZ -= 0.1f * sin(cameraYaw);
            break;
        case 'd':
            // Strafe camera right
            cameraX += 0.1f * cos(cameraYaw);
            cameraZ += 0.1f * sin(cameraYaw);
            break;
        case 'q':
            // Move camera up
            cameraY += 0.1f;
            break;
        case 'e':
            // Move camera down
            cameraY -= 0.1f;
            break;
    }
}

// Function to handle mouse input
void mouse(int x, int y) {
    // Update camera yaw and pitch based on mouse movement
    cameraYaw += (x - WIDTH / 2) * 0.01f;
    cameraPitch += (y - HEIGHT / 2) * 0.01f;
    glutWarpPointer(WIDTH / 2, HEIGHT / 2); // Center mouse cursor
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("3D Block Game");

    // Set up OpenGL
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouse);

    // Initialize the chunk
    initChunk();

    // Start the main loop
    glutMainLoop();

    return 0;
}
