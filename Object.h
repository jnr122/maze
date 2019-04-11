

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

class Object {
private:
    /* Assume Quad includes color, center, width, height */
    Quad box;
    std::string label;
    color originalFill, hoverFill, pressFill;
    bool touched = false;
public:

    Object(Quad box, std::string label);
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

    void moveBox(int x, int y);

    Quad getBox();

    void setNew();

    std::string getLabel();

    void setLabel(std::string message);
};

class Player{
private:
    /* Assume Quad includes color, center, width, height */
    Object body;
    color originalFill, hoverFill, pressFill;
    bool inAir = false;
    bool hasJump = true;
    int jumpLeft = 0;
public:

    Player(int x);


    /* Uses OpenGL to draw the Player*/
    void drawPlayer();

    void movePlayer(int x, int y);

    void jump();

    Quad getBody();

    bool isJumping();

    int getJumpLeft();
    
    bool isTouching(Object hazard);
};
#endif //GRAPHICS_STARTER_BUTTON_H

