//
// Created by Jonah Rubin on 2019-02-21.
//

#include "Coin.h"
#include "../graphics.h"
#include "math.h"
#include <iostream>

using namespace std;

// constructor
Coin::Coin(point center, color col, double radius) : Object(Quad(col, {center.x, center.y}, 10, 10),
                                                                ""), center(center), col(col), radius(radius)
                                                          {
    type = "C";
}

void Coin::draw() {
    // check if this is working
        float x1, y1, x2, y2;
        float angle;
        x1 = center.x, y1 = center.y-hover;

        glColor3f(col.red, col.green, col.blue);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x1, y1);

        for (angle = 1.0f; angle < 361.0f; angle += 0.2) {
            x2 = x1 + sin(angle) * radius;
            y2 = y1 + cos(angle) * radius;
            glVertex2f(x2, y2);
        }
    glEnd();

}


bool Coin::isCollected() const {
    return touched;
}


double Coin::getRadius() const {
    return radius;
}

void Coin::setRadius(double radius) {
    Coin::radius = radius;
}

const point &Coin::getCenter() const {
    return center;
}

void Coin::setCenter(const point &center) {
    Coin::center = center;
}

void Coin::moveBox(int x, int y) {
    scale = (scale+1) % 4;
    if(!touched and scale == 0) {
        if (hover == 0) {
            up = false;
            hover--;
        }
        else if(up == false and hover > -5){
            hover--;
        }
        else if(hover<0 and up == true){
            hover++;
        }
        else if(hover == -5){
            hover++;
            up = true;
        }
    }
}


