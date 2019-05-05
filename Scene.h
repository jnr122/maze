//
// Created by Christopher on 4/30/2019.
//

#ifndef JR_BA_BT_GRAPHICS_SCENE_H
#define JR_BA_BT_GRAPHICS_SCENE_H

#include "Object.h"
#include "Enemy.h"
#include "Coin.h"
#include "Heal.h"
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <ostream>

using namespace std;

class Scene {
private:
    std::vector<shared_ptr<Object>> objects;
public:
    Scene(string filename);
    Scene(string filename, int mx, int my, int bx, int by);
    Scene(std::vector<shared_ptr<Object>> objects);

    void draw() const;

    const vector<shared_ptr<Object>> &getObjects() const;

};


#endif //JR_BA_BT_GRAPHICS_SCENE_H
