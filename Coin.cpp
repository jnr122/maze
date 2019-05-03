//
// Created by Jonah Rubin on 2019-02-21.
//

#include "Coin.h"
#include "graphics.h"
#include "math.h"
#include <iostream>

using namespace std;

Point::Point(int x, int y) : x(x), y(y) {

}

Color::Color(double r, double g, double b) : r(r), g(g), b(b) {

}

// constructor
Circle::Circle(Point center, Color col, double radius) : Object(Quad({col.r, col.g, col.b}, {center.x, center.y}, 1, 1),
                                                                ""), center(center), col(col), radius(radius),
                                                         collected(false) {

}

void Circle::draw() {
    if (!collected) {
        float x1, y1, x2, y2;
        float angle;
        x1 = center.x, y1 = center.y;

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

bool Circle::isCollected() const {
    return collected;
}

void Circle::setCollected(bool collected) {
    Circle::collected = collected;
}

bool Circle::wasTouched() {
    return false;
}

double Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(double radius) {
    Circle::radius = radius;
}

const Point &Circle::getCenter() const {
    return center;
}

void Circle::setCenter(const Point &center) {
    Circle::center = center;
}



