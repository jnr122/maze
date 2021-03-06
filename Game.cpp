#include "graphics.h"
#include "collectible/Coin.h"
#include "texture/Player.h"
#include <time.h>
#include <vector>
#include "Object.h"
#include <iostream>
#include "texture/Enemy.h"
#include "texture/Scene.h"
#include "collectible/Heal.h"

using namespace std;

GLdouble width, height;
int play = 0;
int wd;

// block sizes of 45
int H = 765;
int W = 1125;
bool start = true;
bool playGame = false;
string finalScore = "";
string highScore = "0";

std::vector<std::vector<shared_ptr<Scene>>> scenes;
//[Y][X], Y = row, X = column (consider renaming)
int sceneIndexY = 0;
int sceneIndexX = 0;

int numScenesY = 5; //YX.txt, max(Y)-1
int numScenesX = 5; //YX.txt, max(X)-1

vector<string> visited;

int totalLevels = 5;
int level = 1; //sets current level

bool map = false;
bool hud = true;

bool endScreen = false;

bool dead = false;
Player p1(5);


Quad restart({0.5,.8,.2}, {570, 350}, 200, 60);
Object restartButton(restart, "Restart");

Quad cont({0.5,.8,.2}, {570, 450}, 200, 60);
Object contButton(cont, "Continue");

Quad startScreen({1,0,1}, {560, 350}, 100, 60);
Object startButton(startScreen, "Start");

Quad finalScreen({1,0,1}, {550, 350}, 50, 30);
Object winBanner(startScreen, "Congrats!");

Quad enemyQ({.7,.3,.4}, {350, 610}, 50, 30);
Enemy enemy(enemyQ, "", horizontalR);

void visit(string area){
    for(int i = 0; i< visited.size(); i++){
        if(visited[i] == area){
            return;
        }
    }
    visited.push_back(area);
}

void init() {
    width = W;
    height = H;
    srand(time(0));
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, W, H);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, W, H, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    /*
     * Draw here
     */

    if(start){
        startScreen.draw();
        startButton.draw();
    }else if(playGame){
        p1.drawPlayer();
        scenes[sceneIndexY][sceneIndexX]->draw();
        //**** lives *****
        if(hud) {
            Quad lifeBack({1, 1, 1}, {255, 15}, 504, 17);
            Object liveCounterBack(lifeBack, "");
            liveCounterBack.draw();
            Quad coinBack({1, 1, 1}, {25, 22}, 45, 30);
            Object coinCounterBack(coinBack, "");
            coinCounterBack.draw();
            for (int i = 0; i < p1.getLives() / 2; i++) {
                Quad life({1, 0, 0}, {10 + (10 * i), 15}, 10, 15);
                Object liveCounter(life, "");
                liveCounter.draw();
            }
            for (int i = 0; i < 3; i++) {
                Coin counter({10 + 15 * i, 30}, {.5, .5, .5}, 5);
                counter.draw();
            }
            for (int i = 0; i < p1.getCoins(); i++) {
                Coin counter({10 + 15 * i, 30}, {1, .8, 0}, 5);
                counter.draw();
            }
        }
        if(map){
            Quad boardBack({1, 1, 1}, {550, 400}, (numScenesX*100)+20, (numScenesY*68)+20);
            Object mapDisplayBack(boardBack, "");
            mapDisplayBack.draw();
            Quad board({0, 0, 0}, {550, 400}, numScenesX*100, numScenesY*68);
            Object mapDisplay(board, "");
            mapDisplay.draw();
            for(int i = 0; i < visited.size(); i++){
                Scene mapScene("../level"+to_string(level)+"/" + visited[i] + ".txt",visited[i][1],visited[i][0], 550-numScenesX*50, 400-numScenesY*34);
                mapScene.draw();
            }

        }
        if(p1.getLives() == 0){
            playGame = false;
            sceneIndexX = 0;
            sceneIndexY = 0;
        }
    }

    if(dead){
        restartButton.draw();
        contButton.draw();
    }
    if(endScreen){
        winBanner.draw();
    }
    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    if (key == 109){
        map = !map;
    }
    if (key == 104){
        hud = !hud;
    }
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            p1.movePlayer(0,3);
            p1.fastFall();
            for (int i = 0; i < scenes[sceneIndexY][sceneIndexX]->getObjects().size(); i++) {
                if(p1.isTouching(*scenes[sceneIndexY][sceneIndexX]->getObjects()[i])){
                    if(scenes[sceneIndexY][sceneIndexX]->getObjects()[i]->getType() == "C"){
                        scenes[sceneIndexY][sceneIndexX]->getObjects()[i]->contact();
                    }
                    if(scenes[sceneIndexY][sceneIndexX]->getObjects()[i]->getType() == "H"){
                        scenes[sceneIndexY][sceneIndexX]->getObjects()[i]->contact();
                    }
                }
            }
            break;
        case GLUT_KEY_LEFT:
            if (p1.getBody().getLeftX()>=0) {
                p1.setPlayerMovement(-2,0);
            }
            break;
        case GLUT_KEY_RIGHT:
            if (p1.getBody().getRightX()<=1125) {
                p1.setPlayerMovement(2,0);
            }
            break;
        case GLUT_KEY_UP:
            if(p1.isAlive()) {
                p1.setPlayerMovement(0,1);
            }
            break;
    }

    glutPostRedisplay();
}

//void keyUp(unsigned char key, int x, int y) {

//}


void cursor(int x, int y) {


    if (restartButton.isOverlapping(x, y)) {
        restartButton.hover();
    } else {
        restartButton.release();
    }

    if (contButton.isOverlapping(x, y)) {
        contButton.hover();
    } else {
        contButton.release();
    }

    if (startButton.isOverlapping(x, y)) {
        startButton.hover();
    } else {
        startButton.release();
    }



    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    if (start) {
        if (state == GLUT_DOWN &&
            button == GLUT_LEFT_BUTTON &&
            startButton.isOverlapping(x, y)) {
            startScreen.move(50, 0);
            startScreen.setColor(1,1,1);
            startButton.pressDown();
            start = true;

        } else {
            restartButton.release();
        }

    }
    if( x > restartButton.getBox().getLeftX() &&
        x < restartButton.getBox().getRightX() &&
        y > restartButton.getBox().getTopY() &&
        y < restartButton.getBox().getBottomY() and dead)

    {
        start = true;
        endScreen = false;
        dead = false;
    }

    if( x > contButton.getBox().getLeftX() &&
        x < contButton.getBox().getRightX() &&
        y > contButton.getBox().getTopY() &&
        y < contButton.getBox().getBottomY() and dead)
    {
        playGame = true;
        endScreen = false;
        dead = false;
        start = false;
        p1.nextLevel();
        p1.resetLives();
        visited.clear();
        sceneIndexY = 0;
        sceneIndexX = 0;
        if(level == 4)
        {
            sceneIndexY = 4;
            sceneIndexX = 0;
        }
        else if(level == 5){
            sceneIndexY = 0;
            sceneIndexX = 1;
        }
        scenes.clear();

        for(int y= 0; y < numScenesY; y++) {
            std::vector<shared_ptr<Scene>> temp;
            for (int x = 0; x < numScenesX; x++) {
                auto scene = make_shared<Scene>("../level"+to_string(level)+"/" + to_string(y) + to_string(x) + ".txt");
                temp.push_back(scene);
            }
            scenes.push_back(temp);
        }
    }

    if( x > startButton.getBox().getLeftX() &&
        x < startButton.getBox().getRightX() &&
        y > startButton.getBox().getTopY() &&
        y < startButton.getBox().getBottomY() and start)
    {
        playGame = true;
        endScreen = false;
        dead = false;
        start = false;
        p1.nextLevel();
        p1.resetLives();
        level = 1; //set to test
        visited.clear();
        sceneIndexY = 0; //set to test
        sceneIndexX = 0; //set to test
        scenes.clear();

        for(int y= 0; y < numScenesY; y++) {
            std::vector<shared_ptr<Scene>> temp;
            for (int x = 0; x < numScenesX; x++) {
                auto scene = make_shared<Scene>("../level"+to_string(level)+"/" + to_string(y) + to_string(x) + ".txt");
                temp.push_back(scene);
            }
            scenes.push_back(temp);
        }
    }

    glutPostRedisplay();
}

void timer(int dummy) {
    if(p1.isAlive() and !endScreen){
        visit(to_string(sceneIndexY) + to_string(sceneIndexX));
        if (p1.getBody().getBottomY() > 765) {
            sceneIndexY++;
            p1.movePlayer(0, -p1.getBody().getTopY());
        }
        if (p1.getBody().getTopY() < 0) {
            sceneIndexY--;
            p1.movePlayer(0, 765 - p1.getBody().getBottomY());
        }
        if (p1.getBody().getRightX() > 1125 and sceneIndexX < numScenesX - 1) {
            p1.movePlayer(-p1.getBody().getLeftX(), 0);
            ++sceneIndexX;
        }
        if (p1.getBody().getLeftX() < 0 and sceneIndexX > 0) {
            p1.movePlayer(1125 - p1.getBody().getRightX(), 0);
            --sceneIndexX;
        }
        p1.playerMovement();
        p1.reset();
        p1.movePlayer(0, 3);
        for (int i = 0; i < scenes[sceneIndexY][sceneIndexX]->getObjects().size(); i++) {
            scenes[sceneIndexY][sceneIndexX]->getObjects()[i]->moveBox(0, 0);
            if (p1.isTouching(*scenes[sceneIndexY][sceneIndexX]->getObjects()[i])) {
                if (scenes[sceneIndexY][sceneIndexX]->getObjects()[i]->getType() == "C") {
                    scenes[sceneIndexY][sceneIndexX]->getObjects()[i]->contact();
                }
                if (scenes[sceneIndexY][sceneIndexX]->getObjects()[i]->getType() == "H") {
                    scenes[sceneIndexY][sceneIndexX]->getObjects()[i]->contact();
                }
            }
        }
    }
    if(p1.getCoins() == 3 and level< totalLevels){
        //cout << level;
        level++;
        p1.nextLevel();
        visited.clear();
        sceneIndexY = 0;
        sceneIndexX = 0;
        scenes.clear();

        //level start areas here
        if(level == 4)
        {
            sceneIndexY = 4;
            sceneIndexX = 0;
        }
        else if(level == 5){
            sceneIndexY = 0;
            sceneIndexX = 1;
        }

        for(int y= 0; y < numScenesY; y++) {
            std::vector<shared_ptr<Scene>> temp;
            for (int x = 0; x < numScenesX; x++) {
                auto scene = make_shared<Scene>("../level"+to_string(level)+"/" + to_string(y) + to_string(x) + ".txt");
                temp.push_back(scene);
            }
            scenes.push_back(temp);
        }

    }
    if(p1.getCoins() == 3 and level == totalLevels and p1.isAlive()){
        endScreen = true;
    }
    if(!p1.isAlive() and !dead){
        dead = true;
    }
    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    for(int y= 0; y < numScenesY; y++) {
        std::vector<shared_ptr<Scene>> temp;
        for (int x = 0; x < numScenesX; x++) {
                auto scene = make_shared<Scene>("../level"+to_string(level)+"/" + to_string(y) + to_string(x) + ".txt");
                temp.push_back(scene);
        }
        scenes.push_back(temp);
    }

    init();
    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)W, (int)H);
    glutInitWindowPosition(200, 0); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Dodge!!!" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
