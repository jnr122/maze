//
// Created by Lisa Dion on 11/6/18.
//

#ifndef GRAPHICS_STARTER_BUTTON_H
#define GRAPHICS_STARTER_BUTTON_H

#include <string>
#include <functional>

struct color {
    double red;
    double green;
    double blue;
};

struct point {
    int x;
    int y;
};

class Quad {
private:
    color fill;
    point center;
    unsigned int width;
    unsigned int height;

public:
    Quad();
    Quad(color fill, point center, unsigned int width, unsigned int height);

    int getCenterX() const;
    int getLeftX() const;
    int getRightX() const;
    int getCenterY() const;
    int getTopY() const;
    int getBottomY() const;
    point getCenter() const;

    double getRed() const;
    double getGreen() const;
    double getBlue() const;
    color getFill() const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;

    void setColor(double red, double green, double blue);
    void setColor(color fill);
    void move(int deltaX, int deltaY);
    void resize(unsigned int width, unsigned int height);

    void draw() const;
};

class Button { 
private:
    /* Assume Quad includes color, center, width, height */
    Quad box;
    std::string label;
    color originalFill, hoverFill, pressFill;

public:
    Button(Quad box, std::string label);
    /* Uses OpenGL to draw the box with the label on top */
    virtual void draw();

    /* Returns true if the coordinate is inside the box */
    bool isOverlapping(int x, int y) const;

    /* Change color of the box when the user is hovering over it */
    void hover();

    /* Change color of the box when the user is clicking on it */
    void pressDown();

    /* Change the color back when the user is not clicking/hovering */
    void release();

    /* Execute whatever the Button is supposed to do */
    virtual void click(std::function<void()> callback);
};


#endif //GRAPHICS_STARTER_BUTTON_H
