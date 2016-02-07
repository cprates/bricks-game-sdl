#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <iostream>
#include <vector>

#include "FirstLevel.h"
#include "SecondLevel.h"
#include "ThirdLevel.h"

class LevelManager
{
    public:
        static LevelManager* getInstance()
        {
            if(instance == NULL) {
                instance = new LevelManager;
            }
            return instance;
        }

        Level* getLevel(short level);
        short countLevels();

    private:
        static LevelManager* instance;
        std::vector<Level*> levels;

        LevelManager() {
            levels.push_back(new FirstLevel);
            levels.push_back(new SecondLevel);
            levels.push_back(new ThirdLevel);
        }
        ~LevelManager();
};

#endif // LEVELMANAGER_H
