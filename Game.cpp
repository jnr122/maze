#include "graphics.h"
#include "Object.h"
#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

GLdouble width, height;
int wd;
int H = 750;
int W = 1000;
Quad rect({1, 0, 0}, {1500, 600}, 100, 50);
Object spawn(rect, "");
Quad ground({0, 1, 0}, {500, 700}, 1000, 150);
Object floor(ground, "");
Quad board({1, 1, 1}, {900, 50}, 200, 100);
Object score(board, "0");
Player p1(5);

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
    glViewport(0, 0, width, height);
    
    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);
    
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    /*
     * Draw here
     */
    spawn.draw();
    floor.draw();
    score.draw();
    p1.drawPlayer();
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
                p1.movePlayer(-15, 0);
            }
            break;
        case GLUT_KEY_RIGHT:
            if (p1.getBody().getRightX()<1000) {
                p1.movePlayer(15, 0);
            }
            break;
        case GLUT_KEY_UP:
            p1.jump();
            break;
    }
    
    glutPostRedisplay();
}

void cursor(int x, int y) {
    if (spawn.isOverlapping(x, y)) {
        spawn.hover();
    } else {
        spawn.release();
    }
    
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN &&
        button == GLUT_LEFT_BUTTON &&
        spawn.isOverlapping(x, y)) {
        spawn.pressDown();
    } else {
        spawn.release();
    }

    if (state == GLUT_UP &&
        button == GLUT_LEFT_BUTTON &&
        spawn.isOverlapping(x, y)) {

    }
    
    glutPostRedisplay();
}

void timer(int dummy) {
    if(p1.isJumping()){
        p1.movePlayer(0, -10);
    }
    else if(p1.getBody().getBottomY()<floor.getBox().getTopY()) {
        p1.movePlayer(0, 10);
    }
    else if(p1.getBody().getBottomY()>floor.getBox().getTopY()){
        p1.movePlayer(0,-1);
    }
    score.setLabel(std::to_string(std::stoi(score.getLabel())+1));
    spawn.moveBox(-12,0);
    if(spawn.getBox().getRightX()< 0){
        spawn.setNew();
        spawn.moveBox(1100,0);
        score.setLabel(std::to_string(std::stoi(score.getLabel())+100));
    }
    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Fun with Drawing!" /* title */ );
    
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
