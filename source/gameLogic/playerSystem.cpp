#include "playerSystem.h"


playerSystem::playerSystem(Entity* p, Entity* H, GAME::Application* app)
{
        HealthBar = H;
        playerEntity = p;
        health = 100;
        application = app;
        flag =0;
}

void playerSystem::checkCollision(TransformComponent* p,int level)
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
    //healthbar transform
        vector<Component *> bar  = HealthBar->getComponents();
        TransformComponent * healthTransform ;
        healthTransform = dynamic_cast<TransformComponent*>( bar[1]); 
  
   for (int i =0; i < AllEntities.size();i++)
   {
        vector<Component *> Allcomponents  = AllEntities[i]->getComponents();
        TransformComponent * transform;
        transform = dynamic_cast<TransformComponent*>( Allcomponents[1]); 
       
       if (AllEntities[i]->getID() == 2)
       {
           double distanceS = distance(transform->getPosition(),p->getPosition());
           if (distanceS <= 8)
           {
               if (health > 0 && shield == false)
               {
                    health -= 10;
                    if (health <= 0)
                    {
                        glm::vec3 scale = healthTransform->getScale();
                        healthTransform->setScale(glm::vec3{0,scale.y,scale.z});
                        cout << health <<endl;
                    }
                    else
                    {
                        glm::vec3 scale = healthTransform->getScale();
                        healthTransform->setScale(glm::vec3{scale.x - 20,scale.y,scale.z});
                        cout << health <<endl;
                    }
                    transform->setPosition(glm::vec3{0,0,0});
               }
           }
       }
       else if (AllEntities[i]->getID() == 3)
       { 
           double distanceS = distance(transform->getPosition(),p->getPosition());
           if (distanceS <= 6)
           {
                if (health < 100)
                {
                    health += 5;
                    glm::vec3 scale = healthTransform->getScale();
                    healthTransform->setScale(glm::vec3{scale.x + 10,scale.y,scale.z});
                     cout << health<<endl;

                }
                transform->setPosition(glm::vec3{0,0,0}) ;          
            }
       }
       else if (AllEntities[i]->getID() == 4 && level == 2)
       {
        double distanceS = distance(transform->getPosition(),p->getPosition());
           if (distanceS <= 8)
           {
               shield = true;
               // ttrsm waraya aknha etmas7t
                transform->setPosition(glm::vec3{0,0,0}) ;          
            }

       }
   }
    
}
void  playerSystem::movePlayer(int level)
{
    vector<Component*> transformVector;
    transformVector = playerEntity->getComponents();
    TransformComponent* characterTransform;
    characterTransform = dynamic_cast<TransformComponent*>(transformVector[1]);

    glm::vec3 position = characterTransform->getPosition();
    glm::vec3 rot = characterTransform->getRotation();

    if (flag == 0)
    {
        if(level == 1) 
        {
            if (position.z >= -2250)      
                position.z = position.z - 1 ;
            else if(position.z < -2250 && position.z >= -4500)
                position.z = position.z - 1.6;
            else if (position.z < -4500 && position.z >= -6760)
                position.z = position.z - 2.1;
        }
        else
        {
            if (position.z >= -3380)      
                position.z = position.z - 2.2;
            else if(position.z < -3380 && position.z >= -6760)
                position.z = position.z - 2.7;
        }
    }
    if (position.z <= -6760)
        flag =1;
    if(application->getKeyboard().isPressed(GLFW_KEY_F)) 
    {
        if (position.x > -10 )
            position.x = position.x - 0.5;
    } 
    if(application->getKeyboard().isPressed(GLFW_KEY_H))
    { 
        if (position.x < 10)
            position.x = position.x + 0.5;
    }

    characterTransform->setPosition(position);

    checkCollision(characterTransform,level);
}
int playerSystem::getHealth()
{
    return health;
}
int playerSystem::getFlag()
{
    return flag;
}


void playerSystem::addObject(Entity* obj)
{
      AllEntities.push_back(obj);
}
vector<Entity*> playerSystem::getUpdatedVector()
{
    return AllEntities;
}
void playerSystem::setshield(bool s)
{
    shield = s;
}
bool playerSystem::getshield()
{
    return shield;
}



/////////////////////////////////////////////////////////
void  playerSystem::generateBottle()
{
     for(int i =0;i<AllEntities.size();i++)
    {
        if (AllEntities[i]->getID() == 3)
        {
            TransformComponent* bottleTransform;
            for (int j=0;j<AllEntities[i]->getComponents().size() ;j++)
            {
                bottleTransform = dynamic_cast<TransformComponent*>(AllEntities[i]->getComponents()[j]);
                if (bottleTransform != NULL)
                break;
            }
            //////////////////////////
            vector<Component*> transformVector;
            transformVector = playerEntity->getComponents();
            TransformComponent* characterTransform;
            characterTransform = dynamic_cast<TransformComponent*>(transformVector[1]);

            int random;
            do{
                    random = std::rand() % 80;
            }while(random < 60);

                int  randomx = std::rand() % 8;
                int  randSign = std::rand() % 10;

            glm::vec3 position;

            position.z = characterTransform->getPosition().z - random;

            position.y = characterTransform->getPosition().y + 3;

            if (randSign <5)
            {
      //          if(position.x > -10)
                    position.x = characterTransform->getPosition().x - randomx;
                // else
                //     position.x = -9;
            }
            else if (randSign >= 5)
            {
              //  if(position.x < 10)
                    position.x = characterTransform->getPosition().x + randomx;
                // else
                //     position.x = 9;
            }
            bottleTransform->setPosition(position);
        }
    }
        

}
void  playerSystem::generateCorona()
{
    for(int i =0;i<AllEntities.size();i++)
    {
        if (AllEntities[i]->getID() == 2)
        {
            TransformComponent* coronaTransform;
            for (int j=0;j<AllEntities[i]->getComponents().size() ;j++)
            {
                coronaTransform = dynamic_cast<TransformComponent*>(AllEntities[i]->getComponents()[j]);
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
                    random = std::rand() % 80;
            }while(random < 50);

                // int  randomx = std::rand() % 8;
                // int  randSign = std::rand() % 10;

            glm::vec3 position;
            position.z = characterTransform->getPosition().z - random;
            position.y = characterTransform->getPosition().y + 5;
            position.x = characterTransform->getPosition().x;

            // if (randSign <5)
            //     position.x = characterTransform->getPosition().x - randomx;
            // else if (randSign >= 5)
            //     position.x = characterTransform->getPosition().x + randomx;
           
            int randomscale;

            do{
                    randomscale = std::rand() % 4;
                } while (randomscale == 0);

            coronaTransform->setScale(glm::vec3{1.5*randomscale,1.5*randomscale,1.5*randomscale});


            coronaTransform->setPosition(position);
        }
    }
}
void playerSystem::generateMask()
{
        for(int i =0;i<AllEntities.size();i++)
    {
        if (AllEntities[i]->getID() == 4)
        {
            TransformComponent* maskTransform;
            for (int j=0;j<AllEntities[i]->getComponents().size() ;j++)
            {
               maskTransform = dynamic_cast<TransformComponent*>(AllEntities[i]->getComponents()[j]);
                if (maskTransform != NULL)
                break;
            }
            //////////////////////////
            vector<Component*> transformVector;
            transformVector = playerEntity->getComponents();
            TransformComponent* characterTransform;
            characterTransform = dynamic_cast<TransformComponent*>(transformVector[1]);

            int random;
            do{
                    random = std::rand() % 80;
            }while(random < 50);

                int  randomx = std::rand() % 8;
                int  randSign = std::rand() % 10;

            glm::vec3 position;
            position.z = characterTransform->getPosition().z - random;
            position.y = characterTransform->getPosition().y + 5;
            if (randSign <5)
                position.x = characterTransform->getPosition().x - randomx;
            else if (randSign >= 5)
                position.x = characterTransform->getPosition().x + randomx;

            maskTransform->setPosition(position);
        }
    }

}
