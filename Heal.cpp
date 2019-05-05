//
// Created by btemk_mm3vcui on 5/4/2019.
//

#include "Heal.h"
#include "graphics.h"
#include "math.h"
#include <iostream>

using namespace std;


// constructor
Heal::Heal(Point center, Color col, double radius) : Object(Quad({col.r, col.g, col.b}, {center.x, center.y}, 10, 10),
                                                            ""), center(center), col(col), radius(radius)
{
    type = "H";
}

void Heal::draw() {
    // check if this is working
    cout << touched;
    if (!touched) {
        float x1, y1, x2, y2;
        float angle;
        x1 = center.x, y1 = center.y-hover;

        glColor3f(col.r, col.g, col.b);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x1, y1);

        for (angle = 1.0f; angle < 361.0f; angle += 0.2) {
            x2 = x1 + sin(angle) * radius;
            y2 = y1 + cos(angle) * radius;
            glVertex2f(x2, y2);
        }
    }
    glEnd();

}


bool Heal::isCollected() const {
    return touched;
}


double Heal::getRadius() const {
    return radius;
}

void Heal::setRadius(double radius) {
    Heal::radius = radius;
}

const Point &Heal::getCenter() const {
    return center;
}

void Heal::setCenter(const Point &center) {
    Heal::center = center;
}

void Heal::moveBox(int x, int y) {
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
