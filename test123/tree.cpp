#include "tree.h"
#include <cmath> // for cos and sin functions
#include <GL/glut.h> // for OpenGL functions

extern float xMin, xMax, yMin, yMax, zMin, zMax; // Assuming these are declared globally elsewhere

void renderTree(float x, float z, int n) {
    glColor3f(0.871, 0.722, 0.529);
    glBegin(GL_QUADS);
    for (int i = 0; i < 360; i += 5) {
        glVertex3f(x + cos(i) / 4, yMin + (yMax / 4.6), n + z + sin(i) / 4);
        glVertex3f(x + cos(i) / 4, yMin, n + z + sin(i) / 4);
    }
    glEnd();

    glColor3f(0.133, 0.545, 0.133);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 360; i += 5) {
        glVertex3f(x + cos(i), yMin + (yMax / 4.6), n + z + sin(i));
        glVertex3f(x + cos(i + 6), yMin + (yMax / 4.6), n + z + sin(i + 6));
        glVertex3f(x, yMin + (yMax / 1.8), n + z);
    }
    glEnd();
}

void renderTrees(int incre) {
    float z1 = ((zMax + abs(zMin)) / 10);
    for (int side = -1; side <= 1; side += 2) { // -1 for left, 1 for right
        for (int i = 0; i < 10; i++) {
            renderTree(4 * xMax / 5 * side, zMax - i * z1, incre);
        }
    }
}