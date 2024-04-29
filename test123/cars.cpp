// cars.cpp
#include "cars.h"
#include <GL/glut.h>
#include <vector>
extern float yMin, zMin, zMax; // Assuming these are defined elsewhere globally
extern float lrIndex , lrIndex0, lrIndex1, lrIndex2, lrIndex3;
extern float car1, car2, car3;
extern float z;



BoundingBox calculateBoundingBox(float lrIndex, float yMin, float z) {
    BoundingBox box;
    box.minX = lrIndex - 0.4;
    box.maxX = lrIndex + 0.4;
    box.minY = yMin + 0.25;
    box.maxY = yMin + 1;
    box.minZ = z - 2.4;
    box.maxZ = z - 0.6;
    return box;
}

bool checkCollision(const BoundingBox& box1, const BoundingBox& box2) {
    return (box1.minX <= box2.maxX && box1.maxX >= box2.minX) &&
        (box1.minY <= box2.maxY && box1.maxY >= box2.minY) &&
        (box1.minZ <= box2.maxZ && box1.maxZ >= box2.minZ);
}


bool checkAllCollisions() {
    std::vector<BoundingBox> boxes;
    for (int i = 0; i < 4; i++) {  // Assuming there are 4 cars
        boxes.push_back(cars(i));
    }

    for (int i = 0; i < boxes.size(); i++) {
        for (int j = i + 1; j < boxes.size(); j++) {
            if (checkCollision(boxes[i], boxes[j])) {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}


BoundingBox  cars(int n) {
    //the z of player car is the zmax
    float zLocal;
    float lrIndexLocal;

    if (n == 0) { z = zMax; lrIndex0 = lrIndex; glColor3f(0, 0, 1); }
    else if (n == 1) { z = car1 + zMin; lrIndex0 = lrIndex1; glColor3f(1, 0.1, 0.9); }
    else if (n == 2) { z = car2 + zMin; lrIndex0 = lrIndex2; glColor3f(1, 0.7, 0.5); }
    else if (n == 3) { z = car3 + zMin; lrIndex0 = lrIndex3; glColor3f(1, 0.9, 0.1); }
    zLocal = z; 
    lrIndexLocal = lrIndex0;
    /*
    if (n == 0) { z = zMax; lrIndex0 = lrIndex; glColor3f(0, 0, 1); }
    //the z of other cars is 0 at the beginning + zmin to appear from begind the zmin. 
    else if (n == 1) { z = car1 + zMin; lrIndex0 = lrIndex1; glColor3f(1, 0.1, 0.9); }
    else if (n == 2) { z = car2 + zMin; lrIndex0 = lrIndex2; glColor3f(1, 0.7, 0.5); }
    else if (n == 3) { z = car3 + zMin; lrIndex0 = lrIndex3; glColor3f(1, 0.9, 0.1); }*/


    //right
    glBegin(GL_POLYGON);
    glVertex3f(lrIndex0 + .4, yMin + .25, z - 2.4);
    glVertex3f(lrIndex0 + .4, yMin + .5, z - 2.4);
    glVertex3f(lrIndex0 + .4, yMin + .75, z - 2);
    glVertex3f(lrIndex0 + .4, yMin + 1, z - 1.95);
    glVertex3f(lrIndex0 + .4, yMin + 1, z - 1.05);
    glVertex3f(lrIndex0 + .4, yMin + .75, z - 1);
    glVertex3f(lrIndex0 + .4, yMin + .75, z - .6);
    glVertex3f(lrIndex0 + .4, yMin + .25, z - .6);
    glEnd();

    //left
    glBegin(GL_POLYGON);
    glVertex3f(lrIndex0 - .4, yMin + .25, z - .6);
    glVertex3f(lrIndex0 - .4, yMin + .25, z - 2.4);
    glVertex3f(lrIndex0 - .4, yMin + .5, z - 2.4);
    glVertex3f(lrIndex0 - .4, yMin + .75, z - 2);
    glVertex3f(lrIndex0 - .4, yMin + 1, z - 1.95);
    glVertex3f(lrIndex0 - .4, yMin + 1, z - 1.05);
    glVertex3f(lrIndex0 - .4, yMin + .75, z - 1);
    glVertex3f(lrIndex0 - .4, yMin + .75, z - .6);
    glEnd();

    glBegin(GL_QUADS);

    //back
    glVertex3f(lrIndex0 - .4, yMin + .25, z - .6);
    glVertex3f(lrIndex0 + .4, yMin + .25, z - .6);
    glVertex3f(lrIndex0 + .4, yMin + .75, z - .6);
    glVertex3f(lrIndex0 - .4, yMin + .75, z - .6);

    if (n == 0) { z = zMax; lrIndex0 = lrIndex; glColor3f(0, 0.3, 1); }
    else if (n == 1) { z = car1 + zMin; lrIndex0 = lrIndex1; glColor3f(1, 0.1, 0.5); }
    else if (n == 2) { z = car2 + zMin; lrIndex0 = lrIndex2; glColor3f(1, 0.2, 0.5); }
    else if (n == 3) { z = car3 + zMin; lrIndex0 = lrIndex3; glColor3f(1, 0.2, 0.5); }
    zLocal = z;
    lrIndexLocal = lrIndex0;
    
    //top car
    glVertex3f(lrIndex0 - .4, yMin + 1, z - 1.05);
    glVertex3f(lrIndex0 + .4, yMin + 1, z - 1.05);
    glVertex3f(lrIndex0 + .4, yMin + 1, z - 1.95);
    glVertex3f(lrIndex0 - .4, yMin + 1, z - 1.95);

    //back top
    glVertex3f(lrIndex0 - .4, yMin + .75, z - .6);
    glVertex3f(lrIndex0 + .4, yMin + .75, z - .6);
    glVertex3f(lrIndex0 + .4, yMin + .75, z - 1);
    glVertex3f(lrIndex0 - .4, yMin + .75, z - 1);

    //back glass
    glColor3f(0.4, 0.4, 0.4);
    glVertex3f(lrIndex0 - .4, yMin + .75, z - 1);
    glVertex3f(lrIndex0 + .4, yMin + .75, z - 1);
    glVertex3f(lrIndex0 + .4, yMin + 1, z - 1.05);
    glVertex3f(lrIndex0 - .4, yMin + 1, z - 1.05);
    glEnd();

    //wheels
    glPushMatrix();
    glColor3f(0.2, 0.2, 0.2);
    //back right wheel
    glTranslatef(lrIndex0 + .4, yMin + .25, z - 1);
    glRotatef(90, 0, 1, 0);
    glutSolidTorus(0.07, 0.13, 10, 25);
    glPopMatrix();

    glPushMatrix();
    //back left wheel
    glTranslatef(lrIndex0 - .4, yMin + .25, z - 1);
    glRotatef(90, 0, 1, 0);
    glutSolidTorus(0.07, 0.13, 10, 25);
    glPopMatrix();

    glPushMatrix();
    //front right wheel
    glTranslatef(lrIndex0 + .4, yMin + .25, z - 2);
    glRotatef(90, 0, 1, 0);
    glutSolidTorus(0.07, 0.13, 10, 25);
    glPopMatrix();

    glPushMatrix();
    //front left wheel
    glTranslatef(lrIndex0 - .4, yMin + .25, z - 2);
    glRotatef(90, 0, 1, 0);
    glutSolidTorus(0.07, 0.13, 10, 25);
    glPopMatrix();

    BoundingBox box = calculateBoundingBox(lrIndexLocal, yMin, zLocal);
    return box;
}