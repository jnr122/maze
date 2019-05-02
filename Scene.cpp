//
// Created by Christopher on 4/30/2019.
//

#include "Scene.h"

using std::string;
using std::vector;

Scene::Scene(std::vector<Object*> objects) {
    this->objects = objects;
}

Scene::Scene(String filename) {
    int y = 0;

    this->objects = vector<Object*>;

    ofstream file;
    file.open(fileName);

    while (getline(file, line)) {
        for(int x = 0; x < line.length(); ++x) {
            switch(line[x])
                case '0':
                    break;
                case '1':
                    Quad b({1, 1, 1}, {(x * 50 + 25),(y * 50 + 25) }, 50, 50);
                    Object block(b, "")
                    this->objects.push_back(block)
                    break;
        }
        ++y;
    }
}

void Scene::draw() const {
    for(Object *obj : objects){
        obj->draw();
    }
}

void Scene::addObject(Object *object){
    objects.push_back(object);
}
