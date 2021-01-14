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
        position.z = position.z - 0.3 ;
    if(application->getKeyboard().isPressed(GLFW_KEY_F)) 
    {
        if (position.x > -8 )
            position.x = position.x - 0.5;
    } 
    if(application->getKeyboard().isPressed(GLFW_KEY_H))
    { 
        if (position.x < 8)
            position.x = position.x + 0.5 ;
    }

    characterTransform->setPosition(position);

    vector<Component*> cameraVector;
    cameraVector = AllEntities[0]->getComponents();
    TransformComponent* cameraTransform;
    CameraComponent* camComp;
    cameraTransform = dynamic_cast<TransformComponent*>(cameraVector[0]);
    camComp = dynamic_cast<CameraComponent*>(cameraVector[1]);
    cameraTransform->to_mat4();
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

/////////////////////////////////////////////////////////
   /*
        get trnaform ll corona , among us /
        do{
            int rand = rand() % 15;
        }while(rand < 5);

        corona.z -> character.z + rand
        corona.x = char.x
        corona.y = char.y 
        push All Entities
    */
void  playerSystem::generateCorona(Entity* corona)
{
    TransformComponent* coronaTransform;
    for (int i=0;i<corona->getComponents().size() ;i++)
    {
        coronaTransform = dynamic_cast<TransformComponent*>(corona->getComponents()[i]);
        if (coronaTransform != NULL)
         break;
    }
    //////////////////////////
    vector<Component*> transformVector;
    transformVector = playerEntity->getComponents();
    TransformComponent* characterTransform;
    characterTransform = dynamic_cast<TransformComponent*>(transformVector[1]);

    int random;
    do{
            random = std::rand() % 50;
    }while(random < 20);
    glm::vec3 position;
    position.z = characterTransform->getPosition().z - random;
    position.y = characterTransform->getPosition().y;
    position.x = characterTransform->getPosition().x;

    coronaTransform->setPosition(position);

    AllEntities.push_back(corona);
}
