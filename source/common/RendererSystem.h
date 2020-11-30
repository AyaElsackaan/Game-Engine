#ifndef GFX_LAB_RENDERERSYSTEM_H
#define GFX_LAB_RENDERERSYSTEM_H


#include "Components/CameraComponent.h"
#include "Components/MeshRenderer.h"
#include "Components/TransformComponent.h "
#include "Entity.h"
#include <vector>


using namespace GAME
{

class RendererSystem {
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
       //map<int,Component*> m = this->getCurrentEntity()->getComponents();
    //TransformComponent* tranf = dynamic_cast<TransformComponent*>(m[0]);
    //CameraComponent* cam = dynamic_cast<CameraComponent*>(m[2]);
    //this->Sprogram->set("tranform", cam->getVPMatrix() * tranf->to_mat4());
    //this->model->draw(); 

    // vector[0] -> Transform , vector[1] -> MeshRenderer , 
        for (int i =0;i< Ent.size();i++)
        {
            MeshRenderer* mesh;
            TransformComponent* tranf;
            CameraComponent* cam;
            vector<Component*> m = Ent[i]->getComponents();
            for (int i =0;i< m.size();i++)
            {
                 tranf = dynamic_cast<TransformComponent*>(m[i]);
                if (tranf != NULL)
                    break;
            }
            for (int i =0;i< m.size();i++)
            {
                mesh = dynamic_cast<MeshRenderer*>(m[i]);
                if (mesh != NULL)
                    break;
            }
            // camera
            vector<Component*> w = world->getComponents();
            for (int i =0;i< w.size();i++)
            {
                cam = dynamic_cast<CameraComponent*>(w[i]);
                if (cam != NULL)
                    break;
            }

            mesh->getShader()->set("tranform", cam->getVPMatrix() * tranf->to_mat4());
            mesh->getMesh()->draw(); 

        }

    }
};
}

#endif //GAME_MESH_H
