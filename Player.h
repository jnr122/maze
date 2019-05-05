//
// Created by Jonah Rubin on 2019-05-03.
//
#include "Object.h"

#ifndef JR_BA_BT_GRAPHICS_PLAYER_H
#define JR_BA_BT_GRAPHICS_PLAYER_H



class Player{
private:
    /* Assume Quad includes color, center, width, height */
    Object head;
    Object body;
    Object legs;
    Object chest;
    bool hasJump = true;
    int lives = 75;
    int extraLives = 2;
    std::string score = "0";
    bool contact = false;
    int moveX = 0;
    int moveY= 0;
    int acceleration = 1;
    int coins = 0;
    bool wallContact = false;
public:

    Player(int x);

    void moved();
    /* Uses OpenGL to draw the Player*/
    void drawPlayer();

    void movePlayer(int x, int y);
    void setCenter();

    void reset();

    Quad getBody();


    bool isTouching(Object object);

    void gotHit();

    bool isAlive();

    void resetLives();

    void resetPosition();

    void setScore(std::string points);

    int getLives();


    void playerMovement();

    void setPlayerMovement(int x, int y);

    int getVertical();

    int getCoins();

    void nextLevel();
};


#endif //JR_BA_BT_GRAPHICS_PLAYER_H
