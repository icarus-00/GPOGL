// misc.cpp
#include "misc.h"
#include <GL/glut.h>
#include <cmath> // For cos and sin functions
#include <cstdio> // For sprintf_s if needed
#include <GL/stb_image.h>
extern float xMin, xMax, yMin, yMax, zMin, zMax, incre;
extern int i, score, gv, hight_score;
extern float FPS;
extern char s[50];
extern float plus_z;
extern bool pause; 
extern float width, height;

void renderBitmapString(float x, float y, float z, void* font, const char* string) {
    const char* c;
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void flag() {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f((3.5 * xMin / 5), 0, (zMin + incre));
    glVertex3f((3.5 * xMax / 5), 0, (zMin + incre));
    glVertex3f((3.5 * xMax / 5), 0.5, (zMin + incre));
    glVertex3f((3.5 * xMin / 5), 0.5, (zMin + incre));

    glColor3f(0, 0, 0);
    glVertex3f((3.5 * xMin / 5), 0.5, (zMin + incre));
    glVertex3f((3.5 * xMax / 5), 0.5, (zMin + incre));
    glVertex3f((3.5 * xMax / 5), 1, (zMin + incre));
    glVertex3f((3.5 * xMin / 5), 1, (zMin + incre));

    glColor3f(1, 1, 1);
    glVertex3f((3.5 * xMin / 5), 1, (zMin + incre));
    glVertex3f((3.5 * xMax / 5), 1, (zMin + incre));
    glVertex3f((3.5 * xMax / 5), 1.5, (zMin + incre));
    glVertex3f((3.5 * xMin / 5), 1.5, (zMin + incre));

    glColor3f(0, 0, 0);
    glVertex3f((3.5 * xMin / 5), 1.5, (zMin + incre));
    glVertex3f((3.5 * xMax / 5), 1.5, (zMin + incre));
    glVertex3f((3.5 * xMax / 5), 2, (zMin + incre));
    glVertex3f((3.5 * xMin / 5), 2, (zMin + incre));
    glEnd();

    //bottom left
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i < 360; i += 5) {
        glVertex3f((3.5 * xMin / 5) + (cos(i) / 4), 2, (zMin + incre) + (sin(i) / 4));
        glVertex3f((3.5 * xMin / 5) + (cos(i) / 4), yMin, (zMin + incre) + (sin(i) / 4));
    }
    glEnd();

    //bottom right
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i < 360; i += 5) {
        glVertex3f((3.5 * xMax / 5) + (cos(i) / 4), 2, (zMin + incre) + (sin(i) / 4));
        glVertex3f((3.5 * xMax / 5) + (cos(i) / 4), yMin, (zMin + incre) + (sin(i) / 4));
    }
    glEnd();

}


void score_board() {
    //Text Information in Frist Page
    if (gv == 0) {
        glColor3f(1, 1, 0);
        renderBitmapString(xMin / 1.7, -1, zMin + plus_z, GLUT_BITMAP_TIMES_ROMAN_24, "START");
    }
    else if (gv == 1 && !pause) {
        //Print Score
        glColor3f(0, 1, 0);
        sprintf_s(s, "SCORE: %d", score);
        renderBitmapString(xMin, yMax - yMax / 10, zMax - 1, (void*)GLUT_BITMAP_HELVETICA_18, s);
        sprintf_s(s, "SPEED:%dKm/h", int(FPS * 50));
        renderBitmapString(xMin, yMax - yMax / 5, zMax - 1, (void*)GLUT_BITMAP_HELVETICA_18, s);
    }
    else if (gv == 1 && pause) {
        //Print Score
        glColor3f(0, 1, 0);
        renderBitmapString(xMin / 1.7, -1, zMin + plus_z, (void*)GLUT_BITMAP_TIMES_ROMAN_24, "Paused");
    }
    else if (gv == 2) {
        glColor3f(1, 1, 0);
        renderBitmapString(xMin / 1.2, -1, zMin + plus_z, GLUT_BITMAP_HELVETICA_12, "Play Again");

        glColor3f(1, 0, 0);
        renderBitmapString(xMin, yMax - yMax / 10, zMax - 1, (void*)GLUT_BITMAP_TIMES_ROMAN_24, "Win");

        glColor3f(1, 0, 1);
        sprintf_s(s, "Your Score: %d", (score));
        renderBitmapString(xMin, yMax - yMax / 5, zMax - 1, GLUT_BITMAP_HELVETICA_18, s);
        sprintf_s(s, "High Score: %d", hight_score);
        renderBitmapString(xMin, yMax - yMax / 3.3, zMax - 1, GLUT_BITMAP_HELVETICA_18, s);
    }
    else if (gv == 3) {
        glColor3f(1, 1, 0);
        renderBitmapString(xMin / 1.2, -1, zMin + plus_z, GLUT_BITMAP_HELVETICA_12, "Play Again");

        glColor3f(1, 0, 0);
        renderBitmapString(xMin, yMax - yMax / 10, zMax - 1, (void*)GLUT_BITMAP_HELVETICA_18, "GAME OVER");

        glColor3f(1, 0, 1);
        sprintf_s(s, "Your Score: %d", (score));
        renderBitmapString(xMin, yMax - yMax / 5, zMax - 1, GLUT_BITMAP_HELVETICA_18, s);
        sprintf_s(s, "High Score: %d", hight_score);
        renderBitmapString(xMin, yMax - yMax / 3.3, zMax - 1, GLUT_BITMAP_HELVETICA_18, s);
    }
}