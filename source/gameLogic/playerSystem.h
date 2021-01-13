

#ifndef GFX_LAB_PLAYERSYSTEM_H
#define GFX_LAB_PLAYERSYSTEM_H
#include "../common/Entity.h"
#include <application.hpp>
#include "../common/Components/TransformComponent.h"
#include <vector>
#include <iostream>
using namespace std;
class playerSystem {
    private : 
        Entity* playerEntity;
        // Entity* powerCohol;
        // Entity* powerMask;
        int health;
        GAME::Application* application;
        vector<Entity*> AllEntities;  // coronas + powerups



    public:
      playerSystem(Entity* p, GAME::Application* app);
      void checkCollision(TransformComponent* p);
      void  movePlayer();
      int getHealth();
      void addObject(Entity* obj);
      vector<Entity*> getUpdatedVector();


      


};


#endif //GFX_LAB_PLAYERSYSTEM_H
