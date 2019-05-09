//
// Created by Jonah Rubin on 2019-04-29.
//
#include "../Object.h"

#ifndef JR_BA_BT_GRAPHICS_ENEMY_H
#define JR_BA_BT_GRAPHICS_ENEMY_H

enum movement {horizontalR,horizontalL, verticalU, verticalD, none};


class Enemy : public Object {
protected:
    bool movingForward;
    int distance, range, speed;
    movement direction;
public:

    Enemy(Quad box, std::string label, movement direction);
    Enemy(Quad box, std::string label, movement direction, int variableDist);
    /* Uses OpenGL to draw the obstruction */
    virtual void draw();

    /* Execute whatever the Object is supposed to do */
    virtual void click(std::function<void()> callback);

    virtual void moveBox(int x, int y) override;
};

#endif //JR_BA_BT_GRAPHICS_ENEMY_H
