#include "Entity.h"

Entity::Entity(const int x, const int y, const int width, const int height, const bool wild) :
    visible(true),
    wild(wild),
    id(0)
{
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = width;
    this->rect.h = height;
}

Entity::~Entity()
{
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

unsigned Entity::getID() {
    return this->id;
}
