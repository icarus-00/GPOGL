#include "road.h"


//float xMin = -10, xMax = 10, yMin = -5.5, yMax = 5.5, zMin = -100, zMax = 50;


void road_midle(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) {
    //Road Midle
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(1 * xMin / 5, yMin, zMax);
    glVertex3f(.75 * xMin / 5, yMin, zMax);
    glVertex3f(.75 * xMin / 5, yMin, zMin);
    glVertex3f(1 * xMin / 5, yMin, zMin);

    glVertex3f(.75 * xMax / 5, yMin, zMax);
    glVertex3f(1 * xMax / 5, yMin, zMax);
    glVertex3f(1 * xMax / 5, yMin, zMin);
    glVertex3f(.75 * xMax / 5, yMin, zMin);
    glEnd();
}

//the miscs of the road
void road_backbround(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) {
    //Road side
    glBegin(GL_QUADS);
    glColor3f(0, 1, 0);
    glVertex3f(xMin, yMin, zMax);
    glVertex3f(3.25 * xMin / 5, yMin, zMax);
    glColor3f(.80, 1.00, 0.000);
    glVertex3f(3.25 * xMin / 5, yMin, zMin);
    glVertex3f(xMin, yMin, zMin);

    glColor3f(.5, .5, .5);
    glVertex3f(3.25 * xMin / 5, yMin, zMax);
    glVertex3f(3 * xMin / 5, yMin, zMax);
    glVertex3f(3 * xMin / 5, yMin, zMin);
    glVertex3f(3.25 * xMin / 5, yMin, zMin);

    glVertex3f(3 * xMax / 5, yMin, zMax);
    glVertex3f(3.25 * xMax / 5, yMin, zMax);
    glVertex3f(3.25 * xMax / 5, yMin, zMin);
    glVertex3f(3 * xMax / 5, yMin, zMin);

    glColor3f(0, 1, 0);
    glVertex3f(3.25 * xMax / 5, yMin, zMax);
    glVertex3f(xMax, yMin, zMax);
    glColor3f(1.000, 1.00, 0.000);
    glVertex3f(xMax, yMin, zMin);
    glVertex3f(3.25 * xMax / 5, yMin, zMin);
    glEnd();

}

void road(float xMin , float yMin , float zMin, float xMax, float yMax, float zMax) {
    //Road
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    /*glVertex3f(3 * xMin / 5, yMin, zMax);
    glVertex3f(1 * xMin / 5, yMin, zMax);
    glVertex3f(1 * xMin / 5, yMin, zMin);
    glVertex3f(3 * xMin / 5, yMin, zMin);

    glVertex3f(.75 * xMin / 5, yMin, zMax);
    glVertex3f(.75 * xMax / 5, yMin, zMax);
    glVertex3f(.75 * xMax / 5, yMin, zMin);
    glVertex3f(.75 * xMin / 5, yMin, zMin);

    glVertex3f(1 * xMax / 5, yMin, zMax);
    glVertex3f(3 * xMax / 5, yMin, zMax);
    glVertex3f(3 * xMax / 5, yMin, zMin);
    glVertex3f(1 * xMax / 5, yMin, zMin);*/
    glVertex3f(3*  xMin / 5, yMin, zMax);

    glVertex3f(3 * xMax / 5, yMin, zMax);

    glVertex3f(3 * xMax / 5, yMin, zMin);

    glVertex3f(3 * xMin / 5, yMin, zMin);
    
    
    glEnd();

    road_midle(xMin, yMin+ 0.1, zMin, xMax, yMax , zMax);
    road_backbround(xMin, yMin, zMin, xMax, yMax, zMax);
}

