//
// Created by Jonah Rubin on 2019-02-21.
//

#ifndef SHAPES_RECT_H
#define SHAPES_RECT_H

#include "shapes.h"

class Rect : public Shapes {
private:
    double length, width;

public:
    Rect(Point center, Color col, double length, double width);

    virtual void draw() const override;
    virtual double get_area() const override;
    virtual double get_perimeter() const override;

    void set_l_and_w(double length, double width);

    double getLength() const;
    void setLength(double length);
    double getWidth() const;
    void setWidth(double width);

};

#endif //SHAPES_RECT_H
