#include "Scene.h"

Scene::Scene(SDL_Renderer* renderer, int sceneID):
    sceneID(sceneID),
    renderer(renderer),
    entityIDSeed(1),
    lastClicked(NULL),
    lastOnFocus(NULL)
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

int Scene::getSceneID() {
    return sceneID;
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

Entity* Scene::searchTarget(const int x, const int y) {
    // iterating from the end to give precedence from top to bottom
    vector<Entity*>::reverse_iterator it = this->childs.rbegin();
    for(; (it != this->childs.rend() && !overIt(x, y, (*it)->getRect())) ||
          (it != this->childs.rend() && !(*it)->isVisible()) ||
          (it != this->childs.rend() && !(*it)->isEnabled()) ; it++) {}
    if(it != this->childs.rend()) {
        return *it;
    }
    return NULL;
}

/**
**  Only works with AA Box's
**/
bool Scene::overIt(const int x, const int y, SDL_Rect* rect) {
    bool axiX = x >= rect->x && x <= (rect->x + rect->w);
    bool axiY = y >= rect->y && y <= (rect->y + rect->h);
    return axiX && axiY;
}


void Scene::onMouseMove(SDL_Event* ev) {
    Entity* target = searchTarget(ev->button.x, ev->button.y);
    if(target == NULL) return;

    if(lastOnFocus != target) {
        target->onFocusChange(ev, true);
        if(lastOnFocus != NULL)
            lastOnFocus->onFocusChange(ev, false);
        lastOnFocus = target;
    }
    target->onMouseOver(ev);
}

void Scene::onMouseButton(SDL_Event* ev) {
    Entity* target = searchTarget(ev->button.x, ev->button.y);
    if(target != NULL) {
        notifyOnClick(target, ev);
    }
}

void Scene::notifyOnClick(Entity* target, SDL_Event* ev) {
    if(ev->button.button == SDL_BUTTON_LEFT) {
        if(ev->type == SDL_MOUSEBUTTONUP) {
            // is it a click event?
            if(target == this->lastClicked) {
                target->onClick(ev);
            }
            // clean the state
            this->lastClicked = NULL;
        }
        else if(ev->type == SDL_MOUSEBUTTONDOWN) {
            // may be a click event...
            this->lastClicked = target;
        }
    }

}
