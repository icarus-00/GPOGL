#define STB_IMAGE_IMPLEMENTATION
//#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <GL/stb_image.h>
#include <GL/glut.h>
#include "road.h"
#include"tree.h"
#include "cars.h"
#include "misc.h"


#include <Windows.h>
#include <tchar.h>
#include <Mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")

unsigned int texture;
int width, height, nrChannels;
unsigned char* data = NULL;

float ratio;
bool fullscreen = true;
int i = 0;

float FPS = 1;
int gv = 0, score = 0, hight_score = 0;
bool pause = false;

const float PLUS_Z = 13;
const float EYEX_DEFAULT = 0;
const float EYEY_DEFAULT = 0;
const float EYEZ_DEFAULT = 50 + PLUS_Z;
const float UPZ_DEFAULT = -1;
const float X_MIN = -10;
const float X_MAX = 10;
const float Y_MIN = -5.5;
const float Y_MAX = 5.5;
const float Z_MIN = -100;
const float Z_MAX = 50;
const float Z_DEFAULT = 0;
const float Z1_DEFAULT = 0;
const float Z2_DEFAULT = Z_MAX + abs(Z_MIN);
const float LR_INDEX_DEFAULT = 0;
const float CAR_DEFAULT = 0;
const float LR_INDEX0_DEFAULT = 0;
const float INCRE1_DEFAULT = 0;
const float INCRE_DEFAULT = -500;

float plus_z = PLUS_Z;
float eyex = EYEX_DEFAULT, eyey = EYEY_DEFAULT, eyez = EYEZ_DEFAULT, upz = UPZ_DEFAULT;

float xMin = X_MIN, xMax = X_MAX, yMin = Y_MIN, yMax = Y_MAX, zMin = Z_MIN, zMax = Z_MAX;

float z = Z_DEFAULT, z1 = Z1_DEFAULT, z2 = Z2_DEFAULT;

float lrIndex = LR_INDEX_DEFAULT;

float car = CAR_DEFAULT, lrIndex0 = LR_INDEX0_DEFAULT;

float car1, lrIndex1, car2, lrIndex2, car3, lrIndex3;

float incre1 = INCRE1_DEFAULT;

float incre = INCRE_DEFAULT;

char s[50];



//Funcations
void spe_key(int, int, int);
void processKeys(unsigned char, int, int);
void timer(int);
void init();
void reshape(int, int);

void start();

void sky();

void Race();
void collision();

void load(int);
void check(unsigned char*);

int main(int argc, char* argv[])
{
    if (FPS >= 1) FPS = 1;
    if (FPS <= 0.1) FPS = 0.1;
    glutInit(&argc, argv);
    //if (PlaySound(TEXT("music.mp3"), NULL, SND_LOOP | SND_ASYNC) ==false ) std::cout<<"failed to load audio";
    mciSendString(_T("play music.mp3"), NULL, 0, NULL);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 650);
    glutInitWindowPosition(200, 20);
    glutCreateWindow("Racing Car");
    glutFullScreen();
    
    init();
    glutDisplayFunc(Race);
    glutReshapeFunc(reshape);
    glutTimerFunc(100, timer, 0);
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(spe_key);
    
    glutMainLoop();

    return 0;
}

void init() {
    glClearColor(1, 0.3, 0.3, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}

void reshape(int w, int h) {
    if (h == 0)h = 1;
    ratio = w / (float)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, ratio, 1, z2 + .1);
    glMatrixMode(GL_MODELVIEW);
}


//game overtime
void timer(int) {
    glutPostRedisplay();
    //sets the fps of the game
    glutTimerFunc(100 / (FPS * 80), timer, 0);

    //if game is running (gv==1) and not pause, the speed of the cars are handled by the fps of the game
    if (gv == 1 && !pause) {
       // if (FPS < 0.5)FPS += 0.01;
        score += FPS;
        


        car1 += FPS;
        
        //every time the car passes zmax , it's z will return to 0, and a new lr index will be assigned
        if (car1 > z2) {
            car1 = 0;
            lrIndex1 = ((rand() % 3 + 1) * 3) + xMin + 4;
        }

        car2 += FPS;
        if (car2 > z2) {
            car2 = 0;
            lrIndex2 = ((rand() % 3 + 1) * 3) + xMin + 4;
        }

        car3 += FPS;
        if (car3 > z2) {
            car3 = 0;
            lrIndex3 = ((rand() % 3 + 1) * 3) + xMin + 4;
        }

        incre1 += FPS / 2;
        if (incre1 > z2) incre1 = 0;

        incre += FPS;
    }
}

void spe_key(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_F1:
        fullscreen = !fullscreen;
        if (fullscreen) {
            glutFullScreen();
        }
        else {
            glutPositionWindow(100, 80);
            glutReshapeWindow(1000, 800);
        }
        break;
    case GLUT_KEY_DOWN:
        eyey--;
        break;
    case GLUT_KEY_UP:
        eyey++;
        break;
    case GLUT_KEY_LEFT:
        eyex--;
        break;
    case GLUT_KEY_RIGHT:
        eyex++;
        break;
    default:
        break;
    }
}

void processKeys(unsigned char key, int x, int y) {
    switch (key)
    {
    case 13: // Enter To Start
        start();
        break;
    case 32: // pause
        if (gv == 1) pause = !pause;
        break;
    case 'W':
    case 'w': // forward
        if (gv == 1 && !pause && FPS < 1) FPS += 0.05;
        break;
    case 'S':
    case 's': // back
        if (gv == 1 && !pause && FPS > 0.2) FPS -= 0.1;
        break;
    case 'A':
    case 'a': // left
        if (lrIndex > -3 && gv == 1 && !pause)lrIndex -= 0.1;
        break;
    case 'D':
    case 'd': // right
        if (lrIndex < 3 && gv == 1 && !pause)lrIndex += 0.1;
        break;
    case 'I':
    case 'i': // zoom in
        eyez--;
        break;
    case 'O':
    case 'o': // zoom out
        eyez++;
        break;
    case 'R':
    case 'r': // reset
        eyex = EYEX_DEFAULT; eyey = EYEY_DEFAULT; eyez = EYEZ_DEFAULT;
        break;
    case 27:  // Escape for exit
        exit(0);
        break;
    default:
        break;
    }
}

void start() {
    if (gv != 1) {
        gv = 1;
        FPS = 0.1;
        score = 0;

        //defaults main values, incre defines the amount of traversal
        incre1 = INCRE1_DEFAULT;
        incre = INCRE_DEFAULT;

        lrIndex = LR_INDEX_DEFAULT;


        //initializes randomly generated cars at specific locations
        car1 = 0;
        lrIndex1 = ((rand() % 3 + 1) * 3) + xMin + 4;
        car2 = -35;
        lrIndex2 = ((rand() % 3 + 1) * 3) + xMin + 4;
        car3 = -70;
        lrIndex3 = ((rand() % 3 + 1) * 3) + xMin + 4;
    }
}

void Race() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(eyex, eyey, eyez, 0, 0, upz, 0, 1, 0);

    sky();
    road(xMin, yMin, zMin, xMax, yMax, zMax);

    BoundingBox playercar =  cars(0);
    BoundingBox car1 = cars(1);
    BoundingBox car2 =  cars(2);
    BoundingBox car3 =  cars(3);
    if (checkCollision(playercar , car1)) {
        gv = 3;
        if (score > hight_score) hight_score = score;
    }
    else if (checkCollision(playercar, car2)) {
        gv = 3;
        if (score > hight_score) hight_score = score;
    }
    else if (checkCollision(playercar, car3)) {
        gv = 3;
        if (score > hight_score) hight_score = score;
    }
    /*
    if (checkAllCollisions()) {
        gv = 3;
        if (score > hight_score) hight_score = score;
    }*/
    renderTrees(incre1);
    renderTrees(incre1 - z2);

    score_board();

    collision();

    flag();

    glutSwapBuffers();
}

void sky() {

    load(2);

    //sky right
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2d(10, 3);
    glVertex3f(xMax, yMin, zMax);
    glTexCoord2d(0, 3);
    glVertex3f(xMax, yMin, zMin);
    glTexCoord2d(0, 0);
    glVertex3f(xMax, yMax, zMin);
    glTexCoord2d(10, 0);
    glVertex3f(xMax, yMax, zMax);

    //sky left
    glTexCoord2d(10, 3);
    glVertex3f(xMin, yMin, zMax);
    glTexCoord2d(0, 3);
    glVertex3f(xMin, yMin, zMin);
    glTexCoord2d(0, 0);
    glVertex3f(xMin, yMax, zMin);
    glTexCoord2d(10, 0);
    glVertex3f(xMin, yMax, zMax);

    //sky top
    glVertex3f(xMin, yMax, zMax);
    glVertex3f(xMax, yMax, zMax);
    glVertex3f(xMax, yMax, zMin);
    glVertex3f(xMin, yMax, zMin);

    glEnd();
}

void collision() {
    //KIll check car
    if (lrIndex == lrIndex1 && (car1 >= z2 - 2.4)) {
        gv = 3;
        if (score > hight_score) hight_score = score;
        car1 -= .5;
    }
    else if (lrIndex == lrIndex2 && (car2 >= z2 - 2.4)) {
        gv = 3;
        if (score > hight_score) hight_score = score;
        car2 -= .5;
    }
    else if (lrIndex == lrIndex3 && (car3 >= z2 - 2.4)) {
        gv = 3;
        if (score > hight_score) hight_score = score;
        car3 -= .5;
    }
    else if (incre > z2 - 2) {
        gv = 2;
        if (score > hight_score) hight_score = score;
    }
}
/*
bool check_collision()
{

}*/

void load(int imgnum) {
    if (imgnum == 1) {
        data = stbi_load("flag.png", &width, &height, &nrChannels, 0);
        check(data);
    }
    else if (imgnum == 2) {
        data = stbi_load("wall.bmp", &width, &height, &nrChannels, 0);
        check(data);
    }
}

void check(unsigned char* data) {
    if (data)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
