#include "Entity.h"
#include "BaseModifier.h"

Entity::Entity(const int x, const int y, const int width, const int height, SDL_Renderer* renderer, const bool wild) :
    visible(true),
    wild(wild),
    entityRenderer(renderer),
    id(0)
{
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = width;
    this->rect.h = height;
}

Entity::~Entity()
{
    vector<BaseModifier*>::iterator it = modifiersList.begin();
    for(; it != modifiersList.end(); it++) {
        delete *it;
        modifiersList.erase(it);
    }
}

bool Entity::isVisible() {
    return this->visible;
}

void Entity::setVisible(bool flag) {
    this->visible = flag;
}

bool Entity::isWild() {
    return this->wild;
}

void Entity::setWild(bool flag) {
    this->wild = flag;
}

/**
**  Used only by the Scene::attachChild method
**/
void Entity::setID(const unsigned id) {
    this->id = id;
}

void Entity::onUpdate(const unsigned elapsedTime) {
    vector<BaseModifier*>::iterator it = modifiersList.begin();
    for(; it != modifiersList.end(); ) {
        (*it)->onUpdate(elapsedTime);
        if((*it)->isFinished()) {
            delete *it;
            modifiersList.erase(it);
        }
        else {
            it++;
        }
    }
}

unsigned Entity::getID() {
    return this->id;
}

SDL_Rect* Entity::getRect() {
    return &this->rect;
}

void Entity::setWidth(unsigned width) {
    this->rect.w = width;
}

void Entity::setHeight(unsigned height) {
    this->rect.h = height;
}

void Entity::setPosition(int x, int y) {
    this->rect.x = x;
    this->rect.y = y;
}

void Entity::setPosX(int x) {
    this->rect.x = x;
}

void Entity::setPosY(int y) {
    this->rect.y = y;
}

void Entity::onClick(SDL_Event* ev) {
    //cout << "Clicked: " << this->id << endl;
}

void Entity::onMouseOver(SDL_Event* ev) {
    //cout << "MouseOver: " << this->id << endl;
}

void Entity::addModifier(BaseModifier* modifier) {
    this->modifiersList.push_back(modifier);
    modifier->setTarget(this);
}
