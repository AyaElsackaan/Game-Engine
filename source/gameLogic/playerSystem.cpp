#include "playerSystem.h"


playerSystem::playerSystem(Entity* p, GAME::Application* app)
{
        playerEntity = p;
        health = 100;
        application = app;
}

void playerSystem::checkCollision(TransformComponent* p)
{
    // player -> id = 1 , corona -> id =2 , cohol -> id = 3 , mask -> id =4
    /*
        loop on all entities :
            if id =2
                check if distance between player and corona == 2
                    dec(health) b 10
                    delete el (this-> corona )
            if id = 3 
                check if distance between player and cohol == 2
                    inc(health) b 5
                    delete el (this-> cohol )
            // level 2
            if id = 4 
                check if distance between player and mask == 2
                    shield
                    delete el (this-> mask ) 
    */
   for (int i =0; i < AllEntities.size();i++)
   {
        vector<Component *> Allcomponents  = AllEntities[i]->getComponents();
        TransformComponent * transfCorona;
        transfCorona = dynamic_cast<TransformComponent*>( Allcomponents[1]); 
       if (AllEntities[i]->getID() == 2)
       {
           double distanceS = distance(transfCorona->getPosition(),p->getPosition());
           if (distanceS <= 8)
           {
               if (health >0)
                     health -= 10;
                cout << health <<endl;
                AllEntities.erase(AllEntities.begin() + i);
           }
       }
       else if (AllEntities[i]->getID() == 3)
       { 
           double distanceS = distance(transfCorona->getPosition(),p->getPosition());
           if (distanceS <= 2)
           {
             if (health < 100)
                health += 5;
                cout << health<<endl;
                AllEntities.erase(AllEntities.begin() + i);
           }
       }
   }
    
}
void  playerSystem::movePlayer()
{
    vector<Component*> transformVector;
    transformVector = playerEntity->getComponents();
    TransformComponent* characterTransform;
    characterTransform = dynamic_cast<TransformComponent*>(transformVector[1]);

    glm::vec3 position = characterTransform->getPosition();
    glm::vec3 rot = characterTransform->getRotation();
    if(application->getKeyboard().isPressed(GLFW_KEY_T))
    { 
        position.z = position.z - 0.05 ;
    }
    if(application->getKeyboard().isPressed(GLFW_KEY_F)) 
    {
        position.x = position.x - 0.05;
    } 
    if(application->getKeyboard().isPressed(GLFW_KEY_H))
    { 
        position.x = position.x + 0.05 ;
    }
    characterTransform->setPosition(position);
    checkCollision(characterTransform);
}
int playerSystem::getHealth()
{
    return health;
}

void playerSystem::addObject(Entity* obj)
{
      AllEntities.push_back(obj);
}
vector<Entity*> playerSystem::getUpdatedVector()
{
    return AllEntities;
}
