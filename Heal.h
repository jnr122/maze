//
// Created by btemk_mm3vcui on 5/4/2019.
//
#include "Object.h"

#ifndef JR_BA_BT_GRAPHICS_HEAL_H
#define JR_BA_BT_GRAPHICS_HEAL_H


class Heal : public Object {
private:
    double radius;
    point center;
    color col;
    int hover = 0;
    bool up = true;
    int scale = 0;
public:

    Heal(point center, color col, double radius);

    virtual void draw() override;

    double getRadius() const;

    void setRadius(double radius);

    const point &getCenter() const;

    void setCenter(const color &center);

    bool isCollected() const;

    virtual void moveBox(int x, int y) override;

};


#endif //JR_BA_BT_GRAPHICS_HEAL_H
