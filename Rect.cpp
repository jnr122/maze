//
// Created by Jonah Rubin on 2019-02-21.
//

#include "Rect.h"
#include "graphics.h"

#include <iostream>
//
//using namespace std;
//
//Rect::Rect(Point center, Color col, double length, double width) : Shapes(center, col), length(length), width(width) {
//
//}
//
//void Rect::draw() const {
//
//    glColor3f(col.r, col.g, col.b);
//    glBegin(GL_QUADS);
//    glVertex2i(center.x - length, center.y - width);
//    glVertex2i(center.x - length, center.y + width);
//    glVertex2i(center.x + length, center.y + width);
//    glVertex2i(center.x + length, center.y - width);
//    glEnd();
//}
//
//double Rect::get_area() const {
//    return length * width;
//}
//
//double Rect::get_perimeter() const {
//    return 2 * length + 2 * width;
//}
//
//void Rect::set_l_and_w(double l, double w) {
//    length = l;
//    width = w;
//}
//
//// getters and setters
//double Rect::getLength() const {
//    return length;
//}
//void Rect::setLength(double length) {
//    Rect::length = length;
//}
//double Rect::getWidth() const {
//    return width;
//}
//void Rect::setWidth(double width) {
//    Rect::width = width;
//}
