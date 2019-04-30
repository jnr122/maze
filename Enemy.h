//
// Created by Jonah Rubin on 2019-04-29.
//
#include "Object.h"

#ifndef JR_BA_BT_GRAPHICS_ENEMY_H
#define JR_BA_BT_GRAPHICS_ENEMY_H

enum movement {horizontal, vertical};


class Enemy : public Object {
protected:
    bool movingLeft;
    int distance;
    movement direction;
public:

    Enemy(Quad box, std::string label, movement direction);
    /* Uses OpenGL to draw the obstruction */
    virtual void draw();

    /* Returns true if the coordinate is inside the box */
    bool isOverlapping(int x, int y) const;

    /* Change color of the box when the user is hovering over it */
    void hover();

    /* Change color of the box when the user is clicking on it */
    void pressDown();

    /* Change the color back when the user is not clicking/hovering */
    void release();

    /* Execute whatever the Object is supposed to do */
    virtual void click(std::function<void()> callback);

    void moveBox();

    void moveCenter(int newX, int newY);

    class Quad getBox();

    void setNew();

    std::string getLabel();

    void setLabel(std::string message);

    bool wasTouched();

    void contact();

    void resize(unsigned int w, unsigned int h);
};

#endif //JR_BA_BT_GRAPHICS_ENEMY_H
