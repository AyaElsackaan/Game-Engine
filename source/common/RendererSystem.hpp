#ifndef GFX_LAB_RENDERERSYSTEM_H
#define GFX_LAB_RENDERERSYSTEM_H

#include <vector>
#include <Components/CameraComponent.h>
#include <Components/MeshRenderer.h>
#include <Components/TransformComponent.h>
#include <Components/Component.h>
#include <glm/gtx/string_cast.hpp>
#include "Components/LightComponent.h"
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
    void RenderAll(vector<Entity*> Ent,Entity* world,vector<Entity*> lights)
    {
        vector<LightComponent*> ShaderLights;
        vector<TransformComponent*> ShaderTransform;
          CameraComponent* cam;
          vector<Component*> w = world->getComponents(); // camera
            for (int j =0;j< w.size();j++)
            {
                cam = dynamic_cast<CameraComponent*>(w[j]);
                if (cam != NULL)
                    break;
            }
        
       // program.set("sky_light.top_color", sky_light.enabled ? sky_light.top_color : glm::vec3(0.0f));
       /// program.set("sky_light.middle_color", sky_light.enabled ? sky_light.middle_color : glm::vec3(0.0f));
      
       /// program.set("sky_light.bottom_color", sky_light.enabled ? sky_light.bottom_color : glm::vec3(0.0f));
        const int MAX_LIGHT_COUNT = 16;

        for(const auto& light : lights) 
        {
            LightComponent* lightComp;
            TransformComponent* LightTransform;
            vector<Component*> lolo  = light->getComponents(); // camera
            for (int j =0;j< lolo.size();j++)
            {
                lightComp= dynamic_cast<LightComponent*>(lolo[j]);
                if (lightComp != NULL)
                    break;
            }
            for (int j =0;j< lolo.size();j++)
            {
                LightTransform= dynamic_cast<TransformComponent*>(lolo[j]);
                if (LightTransform != NULL)
                    break;
            }
            ShaderLights.push_back(lightComp);
            ShaderTransform.push_back(LightTransform);
        }     
        for (int i =1;i< Ent.size();i++)
        {
            MeshRenderer* mesh;
            TransformComponent* tranf;
            vector<Component*> m = Ent[i]->getComponents();
            for (int j =0;j< m.size();j++)
            {
                 tranf = dynamic_cast<TransformComponent*>(m[j]);
                if (tranf != NULL)
                    break;
            }
            for (int j =0;j< m.size();j++)
            {
                mesh = dynamic_cast<MeshRenderer*>(m[j]);
                if (mesh != NULL)
                    break;
            }
            if (mesh !=NULL && tranf !=NULL)
            {
                glUseProgram(*(mesh->getMaterial()->getShader())); 

                 for (int j =0;j< ShaderTransform.size();j++)
                {
                    if(!ShaderLights[j]->getEnable()) continue;
                    std::string prefix = "lights[" + std::to_string(j) + "].";
                    mesh->getMaterial()->getShader()->set(prefix + "type", static_cast<int>(ShaderLights[j]->getLightType()));
                    mesh->getMaterial()->getShader()->set(prefix + "color", ShaderLights[j]->getColor());
                    switch (ShaderLights[j]->getLightType()) {
                    case LightType::DIRECTIONAL:
                        mesh->getMaterial()->getShader()->set(prefix + "direction", glm::normalize(ShaderTransform[j]->getRotation()));
                        break;
                    case LightType::POINT:
                        mesh->getMaterial()->getShader()->set(prefix + "position",ShaderTransform[j]->getPosition());
                        mesh->getMaterial()->getShader()->set(prefix + "attenuation_constant", ShaderLights[j]->getAttenuation().constant);
                        mesh->getMaterial()->getShader()->set(prefix + "attenuation_linear", ShaderLights[j]->getAttenuation().linear);
                        mesh->getMaterial()->getShader()->set(prefix + "attenuation_quadratic", ShaderLights[j]->getAttenuation().quadratic);
                        break;
                    case LightType::SPOT:
                        mesh->getMaterial()->getShader()->set(prefix + "position", ShaderTransform[j]->getPosition());
                        mesh->getMaterial()->getShader()->set(prefix + "direction", glm::normalize(ShaderTransform[j]->getRotation()));
                        mesh->getMaterial()->getShader()->set(prefix + "attenuation_constant", ShaderLights[j]->getAttenuation().constant);
                        mesh->getMaterial()->getShader()->set(prefix + "attenuation_linear",ShaderLights[j]->getAttenuation().linear);
                        mesh->getMaterial()->getShader()->set(prefix + "attenuation_quadratic", ShaderLights[j]->getAttenuation().quadratic);
                        mesh->getMaterial()->getShader()->set(prefix + "inner_angle", ShaderLights[j]->getAngle().inner);
                        mesh->getMaterial()->getShader()->set(prefix + "outer_angle", ShaderLights[j]->getAngle().outer);
                        break;
                    }
                    if(ShaderLights.size() >= MAX_LIGHT_COUNT) break;
                }

                int size = ShaderLights.size();
                mesh->getMaterial()->getShader()->set("light_count",size );

                mesh->getMaterial()->getShader()->set("camera_position", cam->getEyePosition());
                mesh->getMaterial()->getShader()->set("view_projection", cam->getVPMatrix());

               glm::vec4 s = std::any_cast<glm::vec4>( mesh->getMaterial()->getUniforms("tint"));
               mesh->getMaterial()->getShader()->set("tint", s);

                mesh->getMaterial()->getShader()->set("transform", cam->getVPMatrix() * tranf->to_mat4());
                mesh->getMesh()->draw(); 
            }


        }

    }
};

                             //  mesh->getMaterial()->AddUniforms("tint", glm::vec4(1,1, 1, 1));

#endif //GAME_MESH_H
