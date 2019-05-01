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
    int oldX = 0;
    int oldY = 0;
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
    int getOldX();
    int getOldY();
    double getRed() const;
    double getGreen() const;
    double getBlue() const;
    color getFill() const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;

    void setColor(double red, double green, double blue);
    void setColor(color fill);
    void setOld(int x, int y);
    void move(int deltaX, int deltaY);
    void resize(unsigned int width, unsigned int height);
    void moveCenter(int newX, int NewY);
    void draw() const;
};

class Object {
protected:
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

    void moveCenter(int newX, int newY);

    Quad getBox();

    void setNew();

    std::string getLabel();

    void setLabel(std::string message);

    bool wasTouched();

    void contact();

    void resize(unsigned int w, unsigned int h);
};

class Player{
private:
    /* Assume Quad includes color, center, width, height */
    Object body;
    bool hasJump = true;
    bool crouched = false;
    int lives = 3;
    int extraLives = 2;
    std::string score = "0";
    bool contact = false;
    int moveX = 0;
    int moveY= 0;
    int acceleration = 1;
public:

    Player(int x);

    void moved();
    /* Uses OpenGL to draw the Player*/
    void drawPlayer();

    void movePlayer(int x, int y);
    void reset();

    Quad getBody();


    bool isTouching(Object object);

    void gotHit();

    bool isAlive();

    void resetLives();

    void resetPosition();

    void setScore(std::string points);

    int getLives();


    void playerMovement();

    void setPlayerMovement(int x, int y);

    int getVertical();
};
#endif //GRAPHICS_STARTER_BUTTON_H