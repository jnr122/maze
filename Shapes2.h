//
//

#ifndef CS205FINAL_SHAPES_H
#define CS205FINAL_SHAPES_H


//#include <cmath>
#include <iostream>
#include <memory>
#include <vector>
#include "Object.h"
//#include <math.h>

using namespace std;

/*struct color {
    double red;
    double green;
    double blue;
};*/

/*struct point {
    int x;
    int y;
};*/

enum triangleDirection {Up, Right, Down, Left};

class Shape {
public:
    // Constructors
    Shape();
    Shape(color f);
    Shape(point p);
    Shape(int xIn, int yIn);
    Shape(color f, point p);
    Shape(color f, int xIn, int yIn);
    Shape(const Shape &s); // copy constructor

    // Destructor
    ~Shape();

    // getters
    double getArea() const;
    double getPerimeter() const;
    color getFill() const;
    point getPosition() const;
    double getX() const;
    double getY() const;

    // setters
    void setFill(color f);
    void setFill(double r, double g, double b);
    void setPosition(point p);
    void setPosition(int xIn, int yIn);

    void move(int delta_x, int delta_y);

    // will add canvas parameter when we learn graphics
    // pure virtual (class is abstract)
    virtual void draw() const = 0;

protected:
    color fill;
    point position;
    // helper methods
    // pure virtual
    virtual double get_area() const = 0;
    virtual double get_perimeter() const = 0;
};



#endif //CS205FINAL_SHAPES_H
