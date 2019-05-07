

#include <iostream>
#include "Object.h"
#include "graphics.h"
using namespace std;

point::point(int x, int y) : x(x), y(y) {}

color::color(double red, double green, double blue) : red(red), green(green), blue(blue) {

}

color::color() {
    red = 0;
    green = 0;
    blue = 0;
}

point::point() {
    x = 0;
    y = 0;
}


/********** Quad *************/

Quad::Quad() {
    fill = {0, 0, 1};
    center = {0, 0};
    width = 45;
    height = 45;
}

Quad::Quad(color fill, point center, unsigned int width, unsigned int height) {
    this->fill = fill;
    this->center = center;
    this->width = width;
    this->height = height;
}

int Quad::getCenterX() const {
    return center.x;
}

int Quad::getLeftX() const {
    return center.x - (width / 2);
}

int Quad::getRightX() const {
    return center.x + (width / 2);
}

int Quad::getCenterY() const {
    return center.y;
}

int Quad::getTopY() const {
    return center.y - (height / 2);
}

int Quad::getBottomY() const {
    return center.y + (height / 2);
}

point Quad::getCenter() const {
    return center;
}

int Quad::getOldX() {
    return oldX;
}

int Quad::getOldY() {
    return oldY;
}

double Quad::getRed() const {
    return fill.red;
}

double Quad::getGreen() const {
    return fill.green;
}

double Quad::getBlue() const {
    return fill.blue;
}

color Quad::getFill() const {
    return fill;
}

unsigned int Quad::getWidth() const {
    return width;
}

unsigned int Quad::getHeight() const {
    return height;
}

void Quad::setColor(double red, double green, double blue) {
    fill = {red, green, blue};
}

void Quad::setColor(color fill) {
    this->fill = fill;
}

void Quad::setCenter(point center) {
    this->center = center;
}

void Quad::setOld(int x, int y) {
    oldX = x;
    oldY = y;
}
void Quad::move(int deltaX, int deltaY) {
    center.x += deltaX;
    center.y += deltaY;
}

void Quad::resize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}
void Quad::moveCenter(int newX, int newY) {
    center.x = newX;
    center.y = newY;
}
void Quad::draw() const {
    glColor3f(fill.red, fill.green, fill.blue);
//    glColor4f(1, fill.green, 1, .5);

    glBegin(GL_QUADS);
    glVertex2i(getLeftX(), getTopY());
    glVertex2i(getLeftX(), getBottomY());
    glVertex2i(getRightX(), getBottomY());
    glVertex2i(getRightX(), getTopY());
    glEnd();
}

/************ Button **************/



Object::Object(Quad box, string label) {
    this->box = box;
    this->label = label;
    originalFill = box.getFill();
    hoverFill = {box.getRed()+0.5, box.getGreen()+0.5, box.getBlue()+0.5};
    pressFill = {box.getRed()-0.5, box.getGreen()-0.5, box.getBlue()-0.5};
}

void Object::draw() {
    box.draw();
    glColor3f(1, 1, 1);
    glRasterPos2i(box.getCenterX()-(4*label.length()), box.getCenterY()+7);
    for (char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

/* Returns true if the coordinate is inside the box */
bool Object::isOverlapping(int x, int y) const {
    // TODO: Implement
    return !( x < box.getLeftX() or x > box.getRightX() or y < box.getTopY() or y > box.getBottomY());
}

/* Change color of the box when the user is hovering over it */
void Object::hover() {
    box.setColor(hoverFill);
}

/* Change color of the box when the user is clicking on it */
void Object::pressDown() {
    box.setColor(pressFill);
}

/* Change the color back when the user is not clicking/hovering */
void Object::release() {
    box.setColor(originalFill);
}

/* Execute whatever the Object is supposed to do */
void Object::click(function<void()> callback) {
    callback();
}
void Object::moveBox(int x, int y){
    box.move(x, y);
}

void Object::moveCenter(int newX, int newY) {
    box.moveCenter(newX, newY);
}
Quad Object::getBox() {
    return box;
}
void Object::setNew() {
    int type = rand() % 8;
    touched = false;
    box.setColor(1, 0, 0);
    box.move(box.getOldX(),box.getOldY());
    box.setOld(0,0);

    switch (type) {
        case 0:
            box.move(0,20);
            box.setOld(0,-20);
            box.resize(200, 20);
            break;
        case 1:
            box.resize(20, 150);
            break;
        case 2:
            box.resize(100, 100);
            break;
        case 3:
            box.move(0,-10);
            box.setOld(0,10);
            box.resize(20, 20);
            break;
        case 4:
            box.move(0,-250);
            box.setOld(0,250);
            box.resize(100, 500);
            break;
        case 5:
            box.move(0,10);
            box.setOld(0,-10);
            box.resize(20, 20);
            break;
        case 6:
            box.move(0,-250);
            box.setOld(0,250);
            box.resize(100, 500);
            break;
        case 7:
            box.move(0,-77);
            box.setOld(0,77);
            box.resize(20, 100);
            break;

    }
}

std::string Object::getLabel() {
    return label;
}

void Object::setLabel(std::string message){
    label = message;
}

bool Object::wasTouched() {
    return touched;
}
void Object::contact() {
    touched = true;
    box.setColor(0,0,0);
}

void Object::resize(unsigned int w, unsigned int h) {
    box.resize(w,h);
}

std::string Object::getType() {
    return type;
}

