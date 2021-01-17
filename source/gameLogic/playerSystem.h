

#ifndef GFX_LAB_PLAYERSYSTEM_H
#define GFX_LAB_PLAYERSYSTEM_H
#include "../common/Entity.h"
#include <application.hpp>
#include "../common/Components/TransformComponent.h"
#include <vector>
#include <iostream>
#include "../common/Components/CameraComponent.h"
using namespace std;
class playerSystem {
    private : 
        Entity* playerEntity;
        Entity* HealthBar;
        int health = 100;
        int flag = 0;
        GAME::Application* application;
        vector<Entity*> AllEntities;  // coronas + powerups
        bool shield =false;


    public:
      playerSystem(Entity* p, Entity* H,GAME::Application* app);
      void checkCollision(TransformComponent* p,int level);
      void  movePlayer(int level);
      int getHealth();
      int getFlag();
      void setshield(bool s);
      bool getshield();
      void addObject(Entity* obj);
      vector<Entity*> getUpdatedVector();

    //////////generate ////////
    void generateCorona();
    void generateBottle();
    void generateMask();

      


};


#endif //GFX_LAB_PLAYERSYSTEM_H
