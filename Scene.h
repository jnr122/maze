//
// Created by Christopher on 4/30/2019.
//

#ifndef JR_BA_BT_GRAPHICS_SCENE_H
#define JR_BA_BT_GRAPHICS_SCENE_H

#include "Object.h"
#include <vector>


class Scene {
private:
    std::vector<Object*> objects;
public:

    Scene(std::vector<Object*> objects);

    void draw() const;

};


#endif //JR_BA_BT_GRAPHICS_SCENE_H
