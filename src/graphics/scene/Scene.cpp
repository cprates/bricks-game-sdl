#include "Scene.h"

Scene::Scene():
    entityIDSeed(0)

{

}

Scene::~Scene()
{

}


void Scene::onDraw(SDL_Renderer* renderer) {

}

void Scene::onUpdate(const unsigned elapsedTime) {

}

void Scene::onMouseEvent(SDL_Event* ev) {
    if(ev->button.button == SDL_BUTTON_LEFT && ev->type == SDL_MOUSEBUTTONUP)
        std::cout << "Event: x: " << ev->button.x << " y: " << ev->button.y << std::endl;
}
