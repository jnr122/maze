

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
//************************************* Player *************************************

Player::Player(int x):  body(Quad({0, 0, 1}, {100, 550}, 25, 55), ""){
}
void Player::drawPlayer() {
    body.draw();
    glColor3f(0, 0, 0);

}

Quad Player::getBody() {
    return body.getBox();
}

void Player::movePlayer(int x, int y) {
    body.moveBox(x,y);
}

void Player::jump() {
    if(moving){
        body.moveBox(30, 0);
        moving = false;
    }
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
        contact = false;
        return false;
    }
    // If one rectangle is above other
    if (pl.y > hr.y || hl.y > pr.y) {
        contact = false;
        return false;
    }

    Quad p1 = body.getBox();
    Quad obj = hazard.getBox();
    if(obj.getTopY() == p1.getBottomY()){
        hasJump = true;
    }
    if(p1.getBottomY() > obj.getTopY() and obj.getTopY()-p1.getBottomY() >= -4){
        movePlayer(0,obj.getTopY()-p1.getBottomY());
        contact = true;
    }
    if(p1.getTopY() < obj.getBottomY() and obj.getBottomY()-p1.getTopY() <= 4){
        movePlayer(0,obj.getBottomY()-p1.getTopY());
        contact = true;
    }
    if(p1.getRightX()>obj.getLeftX() and obj.getLeftX()-p1.getRightX() >= -9){
        contact = true;
        movePlayer(obj.getLeftX()-p1.getRightX(),0);
    }
    if(p1.getLeftX()<obj.getRightX() and obj.getRightX()-p1.getLeftX() <= 9){
        contact = true;
        movePlayer(obj.getRightX()-p1.getLeftX(),0);
    }
    return true;
}

bool Player::isAlive(){
    if(stoi(score) > 30000 and extraLives ==2){
        lives++;
        extraLives--;
    }
    if(stoi(score) > 77777 and extraLives ==1){
        lives++;
        extraLives--;
    }
    if(lives >0){
        return true;
    }
    else{
        return false;
    }
}

void Player::resetLives() {
    lives = 3;
    extraLives = 2;
    score = "0";
}

void Player::resetPosition() {
    body.getBox().move(500, 0);

}

void Player::setScore(string points){
    score = points;
}

int Player::getLives() {
    return lives;
}

void Player::crouch() {
    moving = false;
    body.resize(50,25);
    crouched = true;
}
void Player::standUp() {
    body.resize(25,50);
    crouched = false;
}
bool Player::isCrouched() {
    ;
    return crouched;
}
void Player::moved(){
        moving = true;
}
void Player::setPlayerMovement(int x, int y) {
    if(moveY==0) {
        moveY += y*acceleration;
        if(moveX<12) {
            moveX += x;
        }
    }
}
void Player::playerMovement() {
    cout << "x: " << moveX << "y: " << moveY << endl;

    if(moveX == 1 or moveX == -1){
        moveX = 0;
    }
    if(moveX>=6 or moveX <=-6){
        acceleration = 6;
    }else if(moveX>=5 or moveX <=-5){
        acceleration = 5;
    }else if(moveX>=4 or moveX <=-4){
        acceleration = 4;
    }else if(moveX>=3 or moveX <=-3){
        acceleration = 3;
    }else if(moveX>=2 or moveX <=-2){
        acceleration = 2;
    }else if(moveX == 0 and moveY == 0){
        acceleration = 1;
    }
    if(moveY>0 and hasJump){
        movePlayer(0,-3);
        moveY--;
        if(acceleration > 1){
            if(moveX > 0) {
                movePlayer(3+acceleration, 0);
            }else{
                movePlayer(-3-acceleration, 0);
            }
        }
        if(moveY == 0){
            moveY = (-6*acceleration)-1;
            hasJump = false;
        }
    }else if(moveY < 0){
        moveY++;

        if(contact){
            moveX = 0;
            acceleration = 0;
        }
        if(acceleration > 1){
            if(moveX > 0) {
                movePlayer(3+acceleration, 0);
            }else{
                movePlayer(-3-acceleration, 0);
            }
        }
        if(moveY == 0){
            moveX = moveX/2;
        }
    }
    else if(moveX > 0){
        moveX-=2;
        movePlayer(3+acceleration,0);
    }else if(moveX < 0){
        moveX+=2;
        movePlayer(-3-acceleration,0);
    }
}

int Player::getVertical() {
    return moveY;
}