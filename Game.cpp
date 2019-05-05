#include "graphics.h"
#include "Circle.h"
#include "shapes.h"
#include "Shapes2.h"
#include "Rect.h"
#include <time.h>
#include <vector>
#include "Object.h"
#include "Image.h"
#include <iostream>
#include "Enemy.h"
#include "Scene.h"

using namespace std;

GLdouble width, height;
int play = 0;
int wd;

// block sizes of 45
int H = 765;
int W = 1125;
bool start = true;
string finalScore = "";
string highScore = "0";

std::vector<shared_ptr<Scene>> scenes;
int sceneIndex = 0;
int numScenes = 2;



//
//
//Quad danger({1, 0, 0}, {700, 575}, 50, 50);
//Object obstruction(danger, "");
//Quad danger2({1, 0, 0}, {500, 490}, 100, 50);
//Object obstruction2(danger2, "");
//Quad danger3({1, 0, 0}, {700, 425}, 100, 50);
//Object obstruction3(danger3, "");
//Quad ground({0, 1, 0}, {500, 700}, 2000, 150);
//Object floor(ground, "");
//Quad board({1, 1, 1}, {900, 50}, 200, 100);
//Object score(board, "0");
Player p1(5);
//Quad screen({1, 1, 1}, {500, 250}, 1000, 1000);
//Object gameOver(screen, "");
//Quad highScoreBox({1,1,1}, {500, 300}, 100, 20);
//Object highScoreDisplay(highScoreBox, "");

Quad restart({0.5,.8,.2}, {500, 350}, 100, 30);
Object restartButton(restart, "Restart");

Quad startScreen({1,0,1}, {500, 250}, 50, 30);
Object startButton(startScreen, "Start");

Quad enemyQ({.7,.3,.4}, {350, 610}, 50, 30);
Enemy enemy(enemyQ, "", horizontal);



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


    if (start) {
        p1.drawPlayer();
        scenes[sceneIndex]->draw();
//        floor.draw();
//        //i.draw();
//        enemy.draw();
//        startButton.draw();
//        obstruction.draw();
//        obstruction2.draw();
//        obstruction3.draw();
        //**** lives *****
        for(int i = 0; i < p1.getLives(); i++){
            Quad life({1, 0, 0}, {10+10*i, 15}, 10, 15);
            Object liveCounter(life, "");
            liveCounter.draw();
        }
    } else {

        if (p1.isAlive()) {
            p1.drawPlayer();
            //obstruction.draw();
//            floor.draw();
//            score.draw();

        }
        if(!(p1.isAlive()) and finalScore.empty()){
//            finalScore =  score.getLabel();
            play = 1;
        }
        if(!(p1.isAlive())) {
            if (play == 1) {

//                gameOver.setLabel("Game Over, Score: " + finalScore);
                if ((std::stoi(finalScore)) > std::stoi(highScore)) {
                    highScore = finalScore;
                }
//                highScoreDisplay.setLabel("High score: " + highScore);
                play = 0;
            }
//            gameOver.draw();
//            highScoreDisplay.draw();
            restartButton.draw();

        }


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

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:

            break;
        case GLUT_KEY_LEFT:
            if (p1.getBody().getLeftX()>0) {
                p1.setPlayerMovement(-2,0);
                //p1.moved();
            } else if (sceneIndex > 0) {
                p1.movePlayer(1125-p1.getBody().getRightX(),0);
                --sceneIndex;
            }
            break;
        case GLUT_KEY_RIGHT:
            if (p1.getBody().getRightX()<200) {
                p1.setPlayerMovement(2,0);
                //p1.movePlayer(15, 0);
                //p1.moved();
            } else if (sceneIndex < numScenes - 1) {
                p1.movePlayer(-p1.getBody().getLeftX(),0);
                //p1.setCenter();
                ++sceneIndex;

            }
            break;
        case GLUT_KEY_UP:
            if(p1.isAlive()) {
                p1.setPlayerMovement(0,1);
            }
            //p1.standUp();
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
            start = false;

        } else {
            restartButton.release();
        }



    }

    glutPostRedisplay();
}

void timer(int dummy) {

    p1.playerMovement();
    p1.reset();
    p1.movePlayer(0, 3);

    for (int i = 0; i < scenes[sceneIndex]->getObjects().size(); i++) {
        scenes[sceneIndex]->getObjects()[i]->moveBox(0,0);
        p1.isTouching(*scenes[sceneIndex]->getObjects()[i]);
    }

//    p1.isTouching(floor);
//    p1.isTouching(obstruction);
//    p1.isTouching(obstruction2);
//    p1.isTouching(obstruction3);
//    p1.isTouching(enemy);
//    enemy.moveBox();
    //handles player jumps
    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    for (int i = 0; i < numScenes; i++) {
        auto scene = make_shared<Scene>("../levels/" + to_string(i) + ".txt");
        scenes.push_back(scene);
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
