//
// Created by Jonah Rubin on 2019-02-21.
//

#include "Object.h"

#ifndef SHAPES_CIRCLE_H
#define SHAPES_CIRCLE_H

class Coin : public Object {
private:
    double radius;
    Point center;
    Color col;
    int hover = 0;
    bool up = true;
    int scale = 0;
public:

    Coin(Point center, Color col, double radius);

    virtual void draw() override;


    double getRadius() const;

    void setRadius(double radius);

    const Point &getCenter() const;

    void setCenter(const Point &center);

    bool isCollected() const;

    virtual void moveBox(int x, int y) override;

};

#endif //SHAPES_CIRCLE_H
