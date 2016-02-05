#include "LevelManager.h"

LevelManager* LevelManager::instance = NULL;

Level* LevelManager::getLevel(short level) {
    return levels[level - 1];
}


short LevelManager::countLevels() {
    return levels.size();
}
