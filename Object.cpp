

#include <iostream>
#include "Object.h"
#include "graphics.h"
using namespace std;

/********** Quad *************/

Quad::Quad() {
    fill = {0, 0, 0};
    center = {0, 0};
    width = 50;
    height = 50;
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

void Quad::move(int deltaX, int deltaY) {
    center.x += deltaX;
    center.y += deltaY;
}

void Quad::resize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

void Quad::draw() const {
    glColor3f(fill.red, fill.green, fill.blue);
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
    glColor3f(0, 0, 0);
    glRasterPos2i(box.getCenterX()-(4*label.length()), box.getCenterY()+7);
    for (char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

/* Returns true if the coordinate is inside the box */
bool Object::isOverlapping(int x, int y) const {
    // TODO: Implement
    return false; // Placeholder for compilation
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

Quad Object::getBox() {
    return box;
}
void Object::setNew() {
    box.resize(rand() % 200, rand() % 200);
    touched = false;
    box.setColor(1,0,0);
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
//************************************* Player *************************************

Player::Player(int x):  body(Quad({0, 0, 1}, {100, 600}, 25, 55), ""){
}
void Player::drawPlayer() {
        getBody().draw();
        glColor3f(0, 0, 0);

}

Quad Player::getBody() {
    return body.getBox();
}

void Player::movePlayer(int x, int y) {
    body.moveBox(x,y);
}

void Player::jump() {
    if ((body.getBox().getBottomY()>= 625)){
        hasJump = true;
        inAir = false;
        jumpLeft = 70;
    }
    if(inAir == false){
        body.moveBox(0,-30);
        inAir = true;
    }
    else if( inAir == true and hasJump == true){
        hasJump = false;
        body.moveBox(0,-30);
        jumpLeft+=70;
    }

}

bool Player::isJumping() {

    if(jumpLeft == 0){
        return false;
    }
    else{
        jumpLeft-= 10;
        return true;
    }
}

string Player::getScore() {
    return score;
}

void Player::gotHit() {
    lives--;

}


bool Player::isTouching(Object hazard) {
    if(hazard.wasTouched()){
        return false;
    }
    point pl;
    pl.x = body.getBox().getLeftX();
    pl.y = body.getBox().getTopY();
    point pr;
    pr.x = body.getBox().getRightX();
    pr.y = body.getBox().getBottomY();
    point hl;
    hl.x = hazard.getBox().getLeftX();
    hl.y = hazard.getBox().getTopY();
    point hr;
    hr.x = hazard.getBox().getRightX();
    hr.y = hazard.getBox().getBottomY();


    // If one rectangle is on left side of other
    if (pl.x > hr.x || hl.x > pr.x) {
        return false;
    }
    // If one rectangle is above other
    if (pl.y > hr.y || hl.y > pr.y) {
        return false;
    }
    return true;
}

bool Player::isAlive(){
    if(lives >0){
        return true;
    }
    else{
        return false;
    }
}

void Player::setScore(string points){
    score = points;
}