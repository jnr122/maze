//
// Created by Jonah Rubin on 2019-04-29.
//

#include "Enemy.h"
#include "graphics.h"
#include <string>
#include <iostream>


using namespace std;


Enemy::Enemy(Quad box, string label, movement direction) : Object(box, label), direction(direction) {
    movingForward = false;
    distance = 0;
    type = "E";
}
Enemy::Enemy(Quad box, string label, movement direction,int variableDist) : Object(box, label), direction(direction) {
    movingForward = false;
    distance = 0;
    range = variableDist;
    type = "E";

}

void Enemy::draw() {
    box.draw();
    glColor3f(50, 14, 6);
    glRasterPos2i(box.getCenterX()-(4*label.length()), box.getCenterY()+7);
    for (char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

/* Execute whatever the Enemy is supposed to do */
void Enemy::click(function<void()> callback) {
    callback();
}
void Enemy::moveBox(int x, int y){
    int dist = 270;
    if (direction == horizontalR) {
        if (!movingForward && distance < dist) {
            box.move(5, 0);
            distance += 5;
        } else {
            movingForward = true;
        }

        if (movingForward && distance > 0) {
            box.move(-5, 0);
            distance -= 5;
        } else {
            movingForward = false;
        }
    } else if(direction == verticalU){
        if (!movingForward && distance < dist) {
            box.move(0, -5);
            distance += 5;
        } else {
            movingForward = true;
        }

        if (movingForward && distance > 0) {
            box.move(0, 5);
            distance -= 5;
        } else {
            movingForward = false;
        }
    }
    else if (direction == horizontalL) {
        if (movingForward && distance < dist) {
            box.move(-5, 0);
            distance += 5;
        } else {
            movingForward = false;
        }

        if (!movingForward && distance > 0) {
            box.move(5, 0);
            distance -= 5;
        } else {
            movingForward = true;
        }
    }
    else if(direction == verticalD){
        if (!movingForward && distance < dist) {
            box.move(0, 5);
            distance += 5;
        } else {
            movingForward = true;
        }
        if (movingForward && distance > 0) {
            box.move(0, -5);
            distance -= 5;
        } else {
            movingForward = false;
        }
    }
}

