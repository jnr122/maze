//
// Created by Jonah Rubin on 2019-02-21.
//

#include "Object.h"

#ifndef SHAPES_CIRCLE_H
#define SHAPES_CIRCLE_H

struct Point {
    // range constructor
    Point(int x, int y);
    int x, y;
};

// rgb struct
struct Color {
    Color(double r, double g, double b);
    double r, g, b;
};

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

    virtual void moveBox(int x, int y);

};

#endif //SHAPES_CIRCLE_H
