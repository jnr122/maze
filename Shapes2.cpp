
//

#include "Shapes2.h"
#include "graphics.h"
//***************************************************************************************************************//
//                                            Beginning of Shape Class                                           //
//***************************************************************************************************************//
const double PI = 3.141592653589793;

Shape::Shape() {
    // default color: black
    fill = {0, 0, 0};
    position = {0, 0};
}

Shape::Shape(color f) : Shape() {
    fill = f;
    position = {0,0};
}

Shape::Shape(point p) : Shape() {
    setPosition(p);
}

Shape::Shape(color f, point p) : Shape(f) {
    setPosition(p);
}

Shape::Shape(color f, int x_in, int y_in) : Shape(f) {
    setPosition(x_in, y_in);
}

Shape::Shape(int x_in, int y_in) : Shape() {
    setPosition(x_in, y_in);
}

// copy constructor
Shape::Shape(const Shape &s) : fill(s.fill) , position(s.position){
}

Shape::~Shape() {
    // does nothing
}

double Shape::getArea() const {
    return calculateArea();
}

double Shape::getPerimeter() const {
    return calculatePerimeter();
}

color Shape::getFill() const {
    return fill;
}

point Shape::getPosition() const {
    return position;
}

double Shape::getX() const {
    return position.x;
}

double Shape::getY() const {
    return position.y;
}

void Shape::setFill(color f) {
    fill = f;
}

void Shape::setFill(double r, double g, double b) {
    fill = {r, g, b};
}

void Shape::setPosition(point p) {
    position = p;
}

void Shape::setPosition(int x_in, int y_in) {
    position.x = x_in;
    position.y = y_in;
}

void Shape::move(int delta_x, int delta_y) {
    // Note: if delta_x is negative, this will
    // in effect subtract from the x position.
    position.x += delta_x;
    // Note: if delta_y is negative, this will
    // in effect subtract from the y position.
    position.y += delta_y;
}

