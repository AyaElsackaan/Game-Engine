#ifndef GFX_LAB_RENDERERSYSTEM_H
#define GFX_LAB_RENDERERSYSTEM_H

#include <vector>
#include <Components/CameraComponent.h>
#include <Components/MeshRenderer.h>
#include <Components/TransformComponent.h>
#include <Components/Component.h>
#include <glm/gtx/string_cast.hpp>

#include "Entity.h"

using namespace std;

class RendererSystem  {
private:

    vector<Entity*> Entities;
    Entity* worldEntity;
public:
    void setEntityVector(vector<Entity*> Ent)
    {
        this->Entities = Ent;
    }
    void setworldEntity(Entity* world)
    {
        this->worldEntity = world;
    }
    void RenderAll(vector<Entity*> Ent,Entity* world)
    {
    // vector[0] -> Transform , vector[1] -> MeshRenderer ,
                CameraComponent* cam;
 
           vector<Component*> w = world->getComponents(); // camera
            for (int j =0;j< w.size();j++)
            {
                cam = dynamic_cast<CameraComponent*>(w[j]);
                if (cam != NULL)
                    break;
            }
        for (int i =0;i< Ent.size();i++)
        {
            std::cout << "Render System i = " << i <<endl;

            MeshRenderer* mesh;
            TransformComponent* tranf;
            vector<Component*> m = Ent[i]->getComponents();

            //std::cout << "Render System i = " << i <<endl;

            for (int j =0;j< m.size();j++)
            {
                 tranf = dynamic_cast<TransformComponent*>(m[j]);
                if (tranf != NULL)
                    break;
            }

            //std::cout << "Render System i = " << i <<endl;

            for (int j =0;j< m.size();j++)
            {
                mesh = dynamic_cast<MeshRenderer*>(m[j]);
                if (mesh != NULL)
                    break;
            }
                        std::cout << "Renderer System 1" <<endl;

            //if (mesh->getShader() == NULL)
            //    std::cout << "NULL SHADER" <<endl;
            glUseProgram(*mesh->getShader());
           // if (mesh->getMesh() == NULL)
            mesh->getShader()->set("tint", glm::vec4(1, 1, 1, 1)); 
                        std::cout << "Renderer System 2" <<endl;

            std::cout << "mat" << glm::to_string(cam->getVPMatrix()) << std::endl;
            mesh->getShader()->set("tranform", cam->getVPMatrix() * tranf->to_mat4());
                        std::cout << "Renderer System 3" <<endl;
            std::cout << "mat" << glm::to_string(cam->getVPMatrix() * tranf->to_mat4()) << std::endl;
            mesh->getMesh()->draw(); 

            std::cout << "Renderer System END" <<endl;

        }

    }
};

#endif //GAME_MESH_H
