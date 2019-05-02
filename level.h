//
// Created by jaker_000 on 4/30/2019.
//

#ifndef JR_BA_BT_GRAPHICS_LEVEL_H
#define JR_BA_BT_GRAPHICS_LEVEL_H
#include "Object.h"
#include <vector>
#include <string>
#include <ostream>
#include <fstream>

class Level {
private:
    std::vector<Quad> drawable = std::vector<Quad>();

public:
    Level(std::string fileName);

    void draw();

    std::vector<Quad> getVec() const;
};


#endif //JR_BA_BT_GRAPHICS_LEVEL_H
