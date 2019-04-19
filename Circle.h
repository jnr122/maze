//
// Created by Jonah Rubin on 2019-02-21.
//
#include "shapes.h"

#ifndef SHAPES_CIRCLE_H
#define SHAPES_CIRCLE_H

class Circle : public Shapes {
private:
    double radius;

public:

    Circle(Point center, Color col, double radius);

    virtual void draw() const override;
    virtual double get_area() const override;
    virtual double get_perimeter() const override;

    double getRadius() const;
    void setRadius(double radius);

};

#endif //SHAPES_CIRCLE_H
