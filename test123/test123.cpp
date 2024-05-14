#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <iostream>
#include <string>

#include "road.h"
#include"tree.h"
#include "ship.h"
#include "misc.h"

#include <random>

#include <Windows.h>

//audio
#include <tchar.h>
#include <Mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")


//opengl
#include <GL/stb_image.h>
#include <GL/glut.h>


//texture variable
unsigned int texture;
int width, height, nrChannels;
unsigned char* data = NULL;


//
float ratio;
bool fullscreen = true;
int i = 0;
//
float FPS = 1;
int gv = 0, score = 0, hight_score = 0;
bool pause = false;



//camera
const float PLUS_Z = 13;
const float EYEX_DEFAULT = 0;
const float EYEY_DEFAULT = 0;
const float EYEZ_DEFAULT = 50 + PLUS_Z;
const float UPZ_DEFAULT = -1;




//environment
const float X_MIN = -10;
const float X_MAX = 10;
const float Y_MIN = -5.5;
const float Y_MAX = 5.5;
const float Z_MIN = -50;
const float Z_MAX = 50;



//location of the cars in the game
const float Z_DEFAULT = 0;
const float Z1_DEFAULT = 0;
const float Z2_DEFAULT = Z_MAX + abs(Z_MIN);


//player_ship and enviromnet posetioning
const float LR_INDEX_DEFAULT = 0; //location on x for player player_ship.
const float CAR_DEFAULT = 0; //location on z for player player_ship.
const float LR_INDEX0_DEFAULT = 0;  //location of the player player_ship on z axis
const float INCRE1_DEFAULT = 0;   //tree position for parallax effect
const float INCRE_DEFAULT = -500;



float plus_z = PLUS_Z;
float eyex = EYEX_DEFAULT, eyey = EYEY_DEFAULT, eyez = EYEZ_DEFAULT, upz = UPZ_DEFAULT;

float xMin = X_MIN, xMax = X_MAX, yMin = Y_MIN, yMax = Y_MAX, zMin = Z_MIN, zMax = Z_MAX;

float  z1 = Z1_DEFAULT, z2 = Z2_DEFAULT;

float lrIndex = LR_INDEX_DEFAULT;

float speedCar = 0.5;

float player_ship = CAR_DEFAULT, lrIndex0 = LR_INDEX0_DEFAULT;

float ship1, lrIndex1, ship2, lrIndex2, ship3, lrIndex3;


//experimental
float nos = 0; //number of cars
float* cars_r = new float[nos];
float* lrIndexes = new float[nos];
char s[50];


float incre1 = INCRE1_DEFAULT;

float incre = INCRE_DEFAULT;




float randXmin = 2.5 * xMin / 5;
float randXmax = 2.5 * xMax / 5;



//Funcations
void spe_key(int, int, int);
void processKeys(unsigned char, int, int);
void timer(int);
void init();
void reshape(int, int);

void start();

void sky();

void Race();


void load(int);
void check(unsigned char*);

void initLighting()
{
    //glEnable(RGB_GAMMA_MAX);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    //glEnable(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    /*glEnable(GL_LIGHTING0);
    glEnable(GL_LIGHTING1);*/

    GLfloat ambiantlight[] = { 1, 1, 1, 1 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiantlight);

    //Add positioned light
    GLfloat lightcolor0[] = { 0.2f, 0.2f, 0.2f, 0 }; //C010r (0.5, 0.5, 0.5)
    GLfloat lightpos0[] = { 0.0f , 0, 0, 0 }; //P03itioned at (4, O, 8)

    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, lightcolor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
}
float randomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}


int main(int argc, char* argv[])
{
    
    if (FPS >= 1) FPS = 1;
    if (FPS <= 0.1) FPS = 0.1;

    if (speedCar>= 1) speedCar= 1;
    if (speedCar <= 0.1) speedCar = 0.1;
    glutInit(&argc, argv);
    //if (PlaySound(TEXT("music.mp3"), NULL, SND_LOOP | SND_ASYNC) ==false ) std::cout<<"failed to load audio";
    //mciSendString(_T("play music.mp3"), NULL, 0, NULL);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 650);
    glutInitWindowPosition(200, 20);
    glutCreateWindow("Racing player_ship");
    glutFullScreen();
    initLighting();
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
    glClearColor(0.5, 00.4, 0.8, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
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



//
void timer(int) {
    glutPostRedisplay();
    //sets the fps of the game
    glutTimerFunc((100)  / (FPS * 10 ), timer, 0);

    //if game is running (gv==1) and not pause, the speed of the cars are handled by the fps of the game
    if (gv == 1 && !pause) {
        // if (FPS < 0.5)FPS += 0.01;
        if (speedCar >= 0.5) score += speedCar * 20;
        else if (speedCar >= 0.7) score += speedCar * 40;
        else
        {
            score += speedCar * 10;
        }



        ship1 += speedCar ;

        
        
        //every time the player_ship passes zmax , it's z will return to 0, and a new lr index will be assigned
        if (ship1 > z2) {
            ship1 = 0;
            lrIndex1 = randomFloat(randXmin, randXmax);
        }

        ship2 += speedCar ;
        

        //if the player_ship gets beyond the 100 mark, or it's position passes 100 respawn it in the back again.
        if (ship2 > z2) {

            ship2 = 0; //z position of the player_ship
            lrIndex2 = randomFloat(randXmin, randXmax);
        }


        ship3 += speedCar ;

        
        if (ship3 > z2) {
            ship3 = 0;
            lrIndex3 = randomFloat(randXmin, randXmax);
        }

        incre1 += speedCar / 2;
        if (incre1 > z2)
        {
            nos += 1;
           // lrIndexes[(int)nos] = randomFloat(randXmin, randXmax);

            //cars_r[(int)nos] = 0;
            //std::cout << nos;
            incre1 = 0;
        }

        incre += speedCar;
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


//keys that controls the game flow
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
        if (gv == 1 && !pause && speedCar < 1) {
            //FPS += 0.05;
            speedCar += 0.05;
        }
        break;
    case 'S':
    case 's': // back
        if (gv == 1 && !pause &&speedCar > 0.2) {
            speedCar -= 0.01;
            //FPS -= 0.1; 
        }
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
        FPS = 1;
        score = 0;
        //defaults main values, incre defines the amount of traversal
        incre1 = INCRE1_DEFAULT;
        incre = INCRE_DEFAULT;
        lrIndex = LR_INDEX_DEFAULT;
        float randXmin = 2.5 * xMin / 5;
        float randXmax = 2.5 * xMax / 5;
        ship1 = 0;
        lrIndex1 =  randomFloat (randXmin, randXmax);
        ship2 = -35;
        lrIndex2 = randomFloat(randXmin, randXmax);
        ship3 = -70;
        lrIndex3 = randomFloat(randXmin, randXmax);
    }
}

void Race() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    
    gluLookAt(eyex, eyey, eyez, 0, 0, upz, 0, 1, 0); 

    sky();
    road(xMin, yMin, zMin, xMax, yMax, zMax);


    BoundingBox playercar = ship_controller(0);
    BoundingBox ship1 = ship_controller_t(1);
    BoundingBox ship2 = ship_controller_t(2);
    BoundingBox ship3 = ship_controller_t(3);
    
    //std::cout << incre1 << std::endl;

    if (checkCollision(playercar , ship1)) {
        gv = 3;
        nos = 0;
        if (score > hight_score) hight_score = score;
    }
    else if (checkCollision(playercar, ship2)) {
        gv = 3;
        nos = 0;
        if (score > hight_score) hight_score = score;
    }
    else if (checkCollision(playercar, ship3)) {
        gv = 3;
        nos = 0;
        if (score > hight_score) hight_score = score;
    }

    else if (incre > z2 - 2) {
        gv = 2;
        if (score > hight_score) hight_score = score;
    }

    renderTrees(incre1);
    renderTrees(incre1 - z2);
    score_board();
    flag();
    glutSwapBuffers();
}

void sky() {

   // load(2);

    //sky right
    
    glBegin(GL_QUADS);
    glColor3f(0.5, 00.4, 0.8);
    glNormal3f(-1, 0, 0);
    glTexCoord2d(0, 0);
    glVertex3f(xMax, yMin, zMax);
    glTexCoord2d(1, 0);
    glVertex3f(xMax, yMin, zMin);
    glTexCoord2d(1, 1);
    glVertex3f(xMax, yMax, zMin);
    glTexCoord2d(0, 1);
    glVertex3f(xMax, yMax, zMax);

    //sky left
    glNormal3f(1, 0, 0);
    glTexCoord2d(0, 0);
    glVertex3f(xMin, yMin, zMax);
    glTexCoord2d(1, 0);
    glVertex3f(xMin, yMin, zMin);
    glTexCoord2d(1, 1);
    glVertex3f(xMin, yMax, zMin);
    glTexCoord2d(0, 1);
    glVertex3f(xMin, yMax, zMax);

    //sky top
    glNormal3f(0, -1, 0);
    glVertex3f(xMin, yMax, zMax);
    glVertex3f(xMax, yMax, zMax);
    glVertex3f(xMax, yMax, zMin);
    glVertex3f(xMin, yMax, zMin);

    glEnd();
}




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

        (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
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
