#include <GL/glut.h> // Include the GLUT header file

GLuint texture[3]; // Array to hold texture IDs

void loadTexture() {
    glGenTextures(3, texture); // Generate texture IDs

    // Load top texture
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glutInit(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, "dirt_top.png");

    // Load side texture
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glutInit(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, "dirt_side.png");

    // Load bottom texture
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glutInit(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, "dirt_bottom.png");
}

void drawCube() {
    glBegin(GL_QUADS);

    // Top face
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

    // Bottom face
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

    // Front face
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

    // Back face
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

    // Left face
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

    // Right face
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity(); // Reset the view

    glTranslatef(0.0f, 0.0f, -5.0f); // Move back a bit to view the cube

    drawCube(); // Draw the cube

    glutSwapBuffers(); // Swap the front and back frame

void init() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set the clear color to black

    loadTexture(); // Load textures
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height); // Set the viewport to the entire window
    glMatrixMode(GL_PROJECTION); // Switch to projection matrix mode
    glLoadIdentity(); // Reset the projection matrix
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f); // Set the perspective
    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix mode
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Set display mode
    glutInitWindowSize(800, 600); // Set window size
    glutCreateWindow("Textured Cube"); // Create a window with the given title

    init(); // Initialize OpenGL

    glutDisplayFunc(display); // Register display callback function
    glutReshapeFunc(reshape); // Register reshape callback function

    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}
