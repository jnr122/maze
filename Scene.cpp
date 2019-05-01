//
// Created by Christopher on 4/30/2019.
//

#include "Scene.h"

Scene::Scene(std::vector<Object*> objects) {
    this->objects = objects;
}

void Scene::draw() const {
    for(Object *obj : objects){
        obj->draw();
    }
}

void Scene::addObject(Object *object){
    objects.push_back(object);
}
