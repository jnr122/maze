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
                case '-':
                    break;
                case '0':
                    break;
                case '1': {
                    //block
                    Quad b({0, .5, 0}, {(x * 45 + 25), (y * 45 + 25)}, 45, 45);
                    auto block = make_shared<Object>(b, "");
                    objects.push_back(block);
                    break;
                }
                case '2': {
                    //enemy moving right, goes 6
                    Quad eH({.5, 0, 0}, {(x * 45 + 25), (y * 45 + 25)}, 45, 45);
                    auto enemyHorizontal = make_shared<Enemy>(eH, "", horizontalR);
                    objects.push_back(enemyHorizontal);
                    break;
                }
                case '3': {
                    //enemy moving left goes 6
                    Quad eH({.5, 0, 0}, {(x * 45 + 25), (y * 45 + 25)}, 45, 45);
                    auto enemyHorizontal = make_shared<Enemy>(eH, "", horizontalL);
                    objects.push_back(enemyHorizontal);
                    break;
                }
                case '4': {
                    //enemy moving right : starts behind block
                    Quad eH({.5, 0, 0}, {(x * 45 + 25), (y * 45 + 25)}, 45, 45);
                    auto enemyHorizontal = make_shared<Enemy>(eH, "", horizontalR);
                    objects.push_back(enemyHorizontal);
                    Quad b({0, .5, 0}, {(x * 45 + 25), (y * 45 + 25)}, 45, 45);
                    auto block = make_shared<Object>(b, "");
                    objects.push_back(block);
                    break;
                }
                case '5': {
                    //enemy moving left : starts behind block
                    Quad eH({.5, 0, 0}, {(x * 45 + 25), (y * 45 + 25)}, 45, 45);
                    auto enemyHorizontal = make_shared<Enemy>(eH, "", horizontalL);
                    objects.push_back(enemyHorizontal);
                    Quad b({0, .5, 0}, {(x * 45 + 25), (y * 45 + 25)}, 45, 45);
                    auto block = make_shared<Object>(b, "");
                    objects.push_back(block);
                    break;
                }
                case '6': {
                    //enemy moving down : goes 6
                    Quad eV({.5, 0, 0}, {(x * 45 + 25), (y * 45 + 25)}, 45, 45);
                    auto enemyVertical = make_shared<Enemy>(eV, "", verticalD);
                    objects.push_back(enemyVertical);
                    Quad b({0, .5, 0}, {(x * 45 + 25), (y * 45 + 25)}, 45, 45);
                    auto block = make_shared<Object>(b, "");
                    objects.push_back(block);
                    break;
                }
                case 'c': {
                    //coin
                    //Point center, Color col, double radius
                    auto coin = make_shared<Coin>(point((x * 45 + 25), (y * 45 + 25)), color(1, .8, 0), 10);
                    objects.push_back(coin);
                    break;
                }
                case '7':{
                    //enemy moving up : goes 6
                    Quad ev({.5, 0, 0}, {(x * 45 + 25), (y * 45 + 25)}, 45, 45);
                    auto enemyVertical = make_shared<Enemy>(ev, "", verticalU);
                    objects.push_back(enemyVertical);
                    break;
                }
                case '8': {
                    //enemy moving down : goes 6
                    Quad eV({.5, 0, 0}, {(x * 45 + 25), (y * 45 + 25)}, 45, 45);
                    auto enemyVertical = make_shared<Enemy>(eV, "", verticalD);
                    objects.push_back(enemyVertical);
                    break;
                }
                case '9':{
                    // stationary enemy
                    Quad eH({.5, 0, 0}, {(x * 45 + 25), (y * 45 + 25)}, 45, 45);
                    auto enemyVertical = make_shared<Enemy>(eH, "", none);
                    objects.push_back(enemyVertical);
                    break;
                }
                case 'h': {
                    //health pick-up
                    auto heal = make_shared<Heal>(point((x * 45 + 25), (y * 45 + 25)), color(0, 0, 1), 10);
                    objects.push_back(heal);
                    break;
                }
            }
        }
        ++y;
    }
    this->objects = objects;
}
//this is for map add cases but don't draw anything else except blocks(ie like 0 case)
Scene::Scene(string filename, int mx, int my, int bx, int by) {
    mx = mx-48;
    my = my -48;
    int y = 0;
    string line;
    auto objects = vector<shared_ptr<Object>>();
    ifstream file;
    file.open(filename);

    while (file) {
        getline(file, line);
        for(int x = 0; x < line.length(); ++x) {
            switch(line[x]) {
                case '-':
                    break;
                case '0':
                    break;
                case '1': {
                    Quad b({0, .5, 0}, {(x * 4 + bx+2+(100*mx)), (y * 4 + by+2+(68*my))}, 4, 4);
                    auto block = make_shared<Object>(b, "");
                    objects.push_back(block);
                    break;
                }
                case '2': {
                    //Quad eH({.5, 0, 0}, {(x * 4 + bx+2+(100*mx)), (y * 4 + by+2+(68*my))}, 4, 4);
                    //auto enemyHorizontal = make_shared<Enemy>(eH, "", horizontalR);
                    //objects.push_back(enemyHorizontal);
                    break;
                }
                case '3': {
                    //Quad eH({.5, 0, 0}, {(x * 4 + bx+2+(100*mx)), (y * 4 + by+2+(68*my))}, 4, 4);
                    //auto enemyHorizontal = make_shared<Enemy>(eH, "", horizontalL);
                    //objects.push_back(enemyHorizontal);
                    break;
                }
                case '4': {
                    //Quad eH({.5, 0, 0}, {(x * 4 + bx+2+(100*mx)), (y * 4 + by+2+(68*my))}, 4, 4);
                    //auto enemyHorizontal = make_shared<Enemy>(eH, "", horizontalR);
                    //objects.push_back(enemyHorizontal);
                    Quad b({0, .5, 0}, {(x * 4 + bx+2+(100*mx)), (y * 4 + by+2+(68*my))}, 4, 4);
                    auto block = make_shared<Object>(b, "");
                    objects.push_back(block);
                    break;
                }
                case '5': {
                    //Quad eH({.5, 0, 0}, {(x * 4 + bx+2+(100*mx)), (y * 4 + by+2+(68*my))}, 4, 4);
                    //auto enemyHorizontal = make_shared<Enemy>(eH, "", horizontalL);
                    //objects.push_back(enemyHorizontal);
                    Quad b({0, .5, 0}, {(x * 4 + bx+2+(100*mx)), (y * 4 + by+2+(68*my))}, 4, 4);
                    auto block = make_shared<Object>(b, "");
                    objects.push_back(block);
                    break;
                }
                case '6': {
                    //Point center, Color col, double radius
                    //auto coin = make_shared<Coin>(Point((x * 4 + bx+2+(100*mx)), (y * 4 + by+2+(68*my))), Color(1, .8, 0), 1);
                    //objects.push_back(coin);
                    Quad b({0, .5, 0}, {(x * 4 + bx+2+(100*mx)), (y * 4 + by+2+(68*my))}, 4, 4);
                    auto block = make_shared<Object>(b, "");
                    objects.push_back(block);
                }
                case '7':
                    break;
                case '8':
                    break;
                case '9':{
                    // stationary enemy
                    Quad eH({.5, 0, 0}, {(x * 4 + bx+2+(100*mx)), (y * 4 + by+2+(68*my))}, 4, 4);
                    auto enemyVertical = make_shared<Enemy>(eH, "", none);
                    objects.push_back(enemyVertical);
                    break;
            }
            }
        }
        ++y;
    }
    this->objects = objects;
}
void Scene::draw() const {
    for (int i = 0; i < objects.size(); i++) {
        if(!objects[i]->wasTouched()){
            objects[i]->draw();
        }
    }

}

const vector<shared_ptr<Object>> &Scene::getObjects() const {
    return objects;
}
