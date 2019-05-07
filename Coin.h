//
// Created by Jonah Rubin on 2019-02-21.
//

#include "Object.h"

#ifndef SHAPES_CIRCLE_H
#define SHAPES_CIRCLE_H

class Coin : public Object {
private:
    double radius;
    point center;
    color col;
    int hover = 0;
    bool up = true;
    int scale = 0;
public:

    Coin(point center, color col, double radius);

    virtual void draw() override;


    double getRadius() const;

    void setRadius(double radius);

    const point &getCenter() const;

    void setCenter(const point &center);

    bool isCollected() const;

    virtual void moveBox(int x, int y) override;

};

#endif //SHAPES_CIRCLE_H
