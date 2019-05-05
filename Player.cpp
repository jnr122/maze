//
// Created by Jonah Rubin on 2019-05-03.
//

#include "Player.h"
#include "graphics.h"
#include "Coin.h"
#include <iostream>



Player::Player(int x):  body(Quad({0, 0, 0}, {100, 550}, 25, 27), ""),
                        head(Quad({0, 0, 0}, {101, 537}, 30, 10), "o"),
                        legs(Quad({0, 0, 0}, {101, 555}, 30, 10), "||"),
                        chest(Quad({0, 0, 0}, {101, 547}, 30, 5), "/0\\")
{
}
void Player::drawPlayer() {
    body.draw();
    legs.draw();
    chest.draw();
    head.draw();


    glColor3f(0, 0, 0);

}

Quad Player::getBody() {
    return body.getBox();
}

void Player::movePlayer(int x, int y) {
    body.moveBox(x,y);
    head.moveBox(x,y);
    legs.moveBox(x,y);
    chest.moveBox(x,y);
}

void Player::setCenter() {

    body.moveBox(-5,body.getBox().getCenterY());
    head.moveBox(-5,head.getBox().getCenterY());
    legs.moveBox(-5,legs.getBox().getCenterY());
    chest.moveBox(-5,chest.getBox().getCenterY());
    //std::cout << "here";

}


void Player::gotHit() {
    lives--;
    if(lives>0){
        lives--;
    }
}


bool Player::isTouching(Object hazard) {
    if(hazard.wasTouched()){
        return false;
    }
    point pl;
    pl.x = body.getBox().getLeftX();
    pl.y = (body.getBox().getTopY());
    point pr;
    pr.x = body.getBox().getRightX();
    pr.y = (body.getBox().getBottomY());
    point hl;
    hl.x = hazard.getBox().getLeftX();
    hl.y = hazard.getBox().getTopY();
    point hr;
    hr.x = hazard.getBox().getRightX();
    hr.y = hazard.getBox().getBottomY();
    if(hazard.getType() == "E"){
        if (pl.x > hr.x || hl.x > pr.x) {
            return false;
        }
        // If one rectangle is above other
        if (pl.y > hr.y || hl.y > pr.y  ) {
            return false;
        }
        gotHit();
        return true;
    }

    if(hazard.getType() == "C"){
        if (pl.x > hr.x || hl.x > pr.x) {
            return false;
        }
        // If one rectangle is above other
        if (pl.y > hr.y || hl.y > pr.y  ) {
            return false;
        }
        coins++;
        return true;
    }
    if(hazard.getType() == "H"){
        if (pl.x > hr.x || hl.x > pr.x) {
            return false;
        }
        // If one rectangle is above other
        if (pl.y > hr.y || hl.y > pr.y  ) {
            return false;
        }
        if(lives<=75){
            lives += 25;
        }
        else if(lives==100){
            return false;
        }
        else{
                lives = 100;
        }

        return true;
    }


    if(hl.y == pr.y-3 and pr.x > hl.x and pl.x < hr.x){
        contact = true;
        hasJump = true;
    }
    // If one rectangle is on left side of other
    if (pl.x >= hr.x || hl.x >= pr.x) {
        return false;
    }
    // If one rectangle is above other
    if (pl.y >= hr.y || hl.y >= pr.y  ) {
        return false;
    }else if(pr.y-3 <= hl.y or pl.y+3 >= hr.y){
        if(pr.y > hl.y and hl.y-pr.y >= -4){
            movePlayer(0,hl.y-pr.y);
        }
        if(pl.y < hr.y and hr.y-pl.y <= 4){
            movePlayer(0,hr.y-pl.y);
        }
        return false;
    }
    if(pr.y > hl.y and hl.y-pr.y >= -4){
        movePlayer(0,hl.y-pr.y);
    }
    if(pl.y < hr.y and hr.y-pl.y <= 4){
        movePlayer(0,hr.y-pl.y);
    }
    if(pr.x>hl.x and hl.x-pr.x >= -7){
        movePlayer(hl.x-pr.x,0);
    }
    if(pl.x<hr.x and hr.x-pl.x <= 7){
        movePlayer(hr.x-pl.x,0);
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

void Player::reset(){
    contact=false;
}

int Player::getLives() {
    return lives;
}



void Player::setPlayerMovement(int x, int y) {
    //cout << body.getBox().getCenterX() << " :: " << body.getBox().getCenterY()<< endl;
    if(moveY==0 and acceleration > 0) {
//        cout <<"accel: " <<acceleration;
        moveY += y*30;
    }
    if(moveX<12 and moveX>-12 and contact) {
        moveX += x;
    }else if(moveX<12 and moveX>-12){
        moveX = x;
    }
}
void Player::playerMovement() {
//    cout << "x: " << moveX << "y: " << moveY << endl;
    if(moveX == 1 or moveX == -1){
        moveX = 0;
        moveY = 0;
    }
    if(moveX>=3 or moveX <=-3){
        acceleration = 3;
    }else if(moveX>=2 or moveX <=-2){
        acceleration = 2;
    }else if(moveX == 0 and moveY == 0){
        acceleration = 1;
    }
    if(moveY>0 and hasJump){
        movePlayer(0,-6);
        moveY--;

        if(moveX > 0) {
            movePlayer(3+acceleration, 0);
        }else if(moveX < 0){
            movePlayer(-3-acceleration, 0);
        }

        if(moveY == 0){
            hasJump = false;
        }
    }else if(moveY>0 and moveX ==0 and !hasJump){
        moveY=0;
    }
    else if(moveX > 0){
        if(contact){
            moveX-=2;
        }
        movePlayer(4+acceleration,0);
    }else if(moveX < 0){
        if(contact) {
            moveX += 2;
        }
        movePlayer(-4-acceleration,0);
    }
}

int Player::getVertical() {
    return moveY;
}

int Player::getCoins() {
    return coins;
}