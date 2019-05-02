//
// Created by Christopher on 4/30/2019.
//

#ifndef JR_BA_BT_GRAPHICS_SCENE_H
#define JR_BA_BT_GRAPHICS_SCENE_H

#include "Object.h"
#include <vector>
#include <iostream>
#include <fstream>
#incldue <string>


class Scene {
private:
    std::vector<Object*> objects;
public:
    Scene(String filename);

    Scene(std::vector<Object*> objects);

    void draw() const;

    void addObject(Object *object);

};


#endif //JR_BA_BT_GRAPHICS_SCENE_H
