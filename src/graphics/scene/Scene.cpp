#include "Scene.h"

Scene::Scene():
    entityIDSeed(1)
{

}

Scene::~Scene()
{

    // remove all the wild Entitys
    vector<Entity*>::iterator it = childs.begin();
    for(; it != childs.end(); it++ ) {
        if((*it)->isWild()) {
            delete *it;
        }
    }
}


void Scene::onDraw(SDL_Renderer* renderer) {
    vector<Entity*>::iterator it = childs.begin();
    for(; it != childs.end(); it++ ) {
        if((*it)->isVisible()) {
            (*it)->onDraw(renderer);
        }
    }
}

void Scene::onUpdate(unsigned elapsedTime) {
    vector<Entity*>::iterator it = childs.begin();
    for(; it != childs.end(); it++ ) {
        (*it)->onUpdate(elapsedTime);
    }
}

bool Scene::attachChild(Entity* entity) {
    if(this->childs.size() < Scene::MAX_CHILDS) {
        entity->setID(this->entityIDSeed);
        this->entityIDSeed++;
        this->childs.push_back(entity);
        return true;
    }
    return false;
}

bool Scene::detatchEntity(Entity* entity) {
    vector<Entity*>::iterator it = this->childs.begin();
    for(; it != this->childs.end() && (*it)->getID() != entity->getID() ; it++) {}
    if(it != this->childs.end()) {
        if((*it)->isWild()) {
            delete *it;
        }
        this->childs.erase(it);
        return true;
    }

    return false;
}

void Scene::onMouseEvent(SDL_Event* ev) {
    if(ev->button.button == SDL_BUTTON_LEFT && ev->type == SDL_MOUSEBUTTONUP)
        std::cout << "Event: x: " << ev->button.x << " y: " << ev->button.y << std::endl;
}
