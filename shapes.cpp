//
// Created by Lisa Dion on 10/3/18.
//

#include "shapes.h"
// struct constructors
Point::Point(int x, int y) : x(x), y(y){

}

Color::Color(double r, double g, double b) : r(r), g(g), b(b) {

}

// shape constructor
Shapes::Shapes(Point center, Color col) : center(center), col(col) {

}

Shapes::~Shapes() {

}

// move
void Shapes::move(int dx, int dy) {
    center.x += dx;
    center.y += dy;
}

// getters/ setters
const Point &Shapes::getCenter() const {
    return center;
}

void Shapes::setCenter(const Point &center) {
    Shapes::center = center;
}

const Color &Shapes::getCol() const {
    return col;
}

void Shapes::setCol(const Color &col) {
    Shapes::col = col;
}

