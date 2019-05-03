//
// Created by Christopher on 4/30/2019.
//

#include "Scene.h"

using std::string;
using std::vector;

Scene::Scene(std::vector<shared_ptr<Object>> objects) {
//    this->objects = objects;
}

Scene::Scene(string fileName) {
    int y = 0;
    string line;
    auto objects = vector<shared_ptr<Object>>();

    ifstream file;
    file.open(fileName);

    while (file) {
        getline(file, line);
        for(int x = 0; x < line.length(); ++x) {
            switch(line[x]) {
                case '0':
                    break;
                case '1':
                    Quad b({0, .5, 0}, {(x * 45 + 25), (y * 45 + 25)}, 45, 45);
                    auto block = make_shared<Object>(b, "");
                    objects.push_back(block);
                    break;
            }
        }
        ++y;
    }
    this->objects = objects;
}

void Scene::draw() const {
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->draw();
    }
//    for(shared_ptr<Object> & obj : objects){
//        obj->draw();
//    }
}

const vector<shared_ptr<Object>> &Scene::getObjects() const {
    return objects;
}

//void Scene::addObject(Object *object){
//    objects.push_back(object);
//}
