//
// Created by jaker_000 on 4/30/2019.
//

#include "level.h"

using namespace std;

Level::Level(string fileName) {
    ofstream file;
    file.open(fileName);

}

void Level::draw() {

}

vector<Quad> Level::getVec() const {return drawable;}