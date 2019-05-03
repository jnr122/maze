//
// Created by Jonah Rubin on 2019-04-29.
//

#include "Enemy.h"
#include "graphics.h"
#include <string>
#include <iostream>


using namespace std;


Enemy::Enemy(Quad box, string label, movement direction) : Object(box, label), direction(direction) {
    movingLeft = false;
    distance = 0;
    type = "E";
    range = 180;
    speed = 3;
}

void Enemy::draw() {
    box.draw();
    glColor3f(50, 14, 6);
    glRasterPos2i(box.getCenterX()-(4*label.length()), box.getCenterY()+7);
    for (char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }

    moveBox();
}

/* Execute whatever the Enemy is supposed to do */
void Enemy::click(function<void()> callback) {
    callback();
}
void Enemy::moveBox(){
    if (direction == horizontal) {
        if (!movingLeft && distance < range) {
            box.move(speed, 0);
            distance += speed;
        } else {
            movingLeft = true;
        }

        if (movingLeft && distance > 0) {
            box.move(-speed, 0);
            distance -= speed;
        } else {
            movingLeft = false;
        }
    } else {
        if (!movingLeft && distance < range) {
            box.move(0, -speed);
            distance += speed;
        } else {
            movingLeft = true;
        }

        if (movingLeft && distance > 0) {
            box.move(0, speed);
            distance -= speed;
        } else {
            movingLeft = false;
        }
    }
}

