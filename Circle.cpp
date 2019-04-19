//
// Created by Jonah Rubin on 2019-02-21.
//

#include "Circle.h"
#include "graphics.h"
#include "math.h"
#include <iostream>

using namespace std;

// constructor
Circle::Circle(Point center, Color col, double radius) : Shapes(center, col), radius(radius){

}


void Circle::draw() const {
    float x1,y1,x2,y2;
    float angle;

    x1 = center.x, y1=center.y;

    glColor3f(col.r,col.g,col.b);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1,y1);

    for (angle=1.0f; angle<361.0f; angle+=0.2)
    {
        x2 = x1+sin(angle)*radius;
        y2 = y1+cos(angle)*radius;
        glVertex2f(x2,y2);
    }

    glEnd();
}

double Circle::get_area() const {
    return 3.14 * radius * radius;
}

double Circle::get_perimeter() const {
    return 2 * 3.14 * radius;
}

double Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(double radius) {
    Circle::radius = radius;
}
