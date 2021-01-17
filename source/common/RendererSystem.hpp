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
bool compare(const pair<Entity*,int> &a, const pair<Entity*,int> &b)
{
       return (a.second > b.second);
}
class RendererSystem 
{
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
    
 
    void RenderAll(vector<Entity*> Ent,Entity* world,vector<Entity*> lights,SkyLight skylight,bool shield)
    {
        //// Get Camera Component
          CameraComponent* cam;
          TransformComponent * CameraTransform;
          vector<Component*> w = world->getComponents(); // camera
            for (int j =0;j< w.size();j++)
            {
                cam = dynamic_cast<CameraComponent*>(w[j]);
                if (cam != NULL)
                    break;
            }
            for (int j =0;j< w.size();j++)
            {
                CameraTransform = dynamic_cast<TransformComponent*>(w[j]);
                if (CameraTransform != NULL)
                    break;
            } 

        /// Collecting light
        const int MAX_LIGHT_COUNT = 16;
         vector<LightComponent*> ShaderLights;
        vector<TransformComponent*> ShaderTransform;
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
        ///////////////////////////////////////////////////////////
        ////////// Sort  M
        vector<pair<Entity*,int>> Opaque;
        vector<pair<Entity*,int>> Transparent; 
        for (int i =1;i< Ent.size();i++)
        {
            // get mesh randerer component
            MeshRenderer* meshT;
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
                meshT = dynamic_cast<MeshRenderer*>(m[j]);
                if (meshT != NULL)
                    break;
            }
            if (meshT !=NULL && tranf !=NULL)
            {
               RenderState* state = new RenderState();
               state = meshT->getMaterial()->getState(); 
                double distanceCT  = distance(tranf->getPosition(),CameraTransform->getPosition());
              if (Ent[i]->getID() == 1 && shield == true) // da el character
                {
                    Transparent.push_back(make_pair(Ent[i],distanceCT));       
                }
                else
                {
                    if (state->Opaque == true)
                    {
                        Opaque.push_back(make_pair(Ent[i],distanceCT));
                    }
                    else
                    {
                        Transparent.push_back(make_pair(Ent[i],distanceCT));       
                    }
                    
                }
               
            }
        }
        /// Sort transparent far -> near
        sort(Transparent.begin(),Transparent.end(),compare);
        Opaque.insert(Opaque.end(), Transparent.begin(), Transparent.end()); // merge 2 vectors
        ///////////////////////////////////////////////////////////
        for (int i =0;i< Opaque.size();i++)
        {
            MeshRenderer* mesh;
            TransformComponent* tranf;
            vector<Component*> m = Opaque[i].first->getComponents();
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
                ////////////////////////////////////// Use render state to set OpenGl state /////////////////////////////////////////////////
           
            
           RenderState* Rstate;
           Rstate = mesh->getMaterial()->getState();
           
           if(Rstate->Enable_DepthTesting) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
           glDepthFunc(Rstate->depth_function);
           if(Rstate->Enable_Culling) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
           glCullFace(Rstate->culled_face);

           glFrontFace(Rstate->front_face_winding);
            glEnable(GL_BLEND);

            glBlendEquation(Rstate->blend_equation);

            glBlendFunc(Rstate->blend_source_function, Rstate->blend_destination_function);

           if(Rstate->enable_alpha_to_coverage) glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
            else glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);       
           
            glUseProgram(*(mesh->getMaterial()->getShader())); 

           if (shield == true && Opaque[i].first->getID() == 1)
            {

                mesh->getMaterial()->getShader()->set("alpha",0.4f);  
            }
            else
            {
                float shaderalpha = std::any_cast<float>( mesh->getMaterial()->getUniforms("alpha"));
                mesh->getMaterial()->getShader()->set("alpha", shaderalpha);  
            }
                ///////////////////////////////////// Send Light to Shader /////////////////////////////////////////////
                int light_count = 0;
                 for (int j =0;j< ShaderTransform.size();j++)
                {
                    if(!ShaderLights[j]->getEnable()) continue;
                    std::string prefix = "lights[" + std::to_string(light_count) + "].";
                    mesh->getMaterial()->getShader()->set(prefix + "type", static_cast<int>(ShaderLights[j]->getLightType()));
                    mesh->getMaterial()->getShader()->set(prefix + "color", ShaderLights[j]->getColor());
                    glm::vec3 direction = (ShaderTransform[j]->to_mat4() * glm::vec4 {0,0,-1,0});
                    glm::vec3 position = ShaderTransform[j]->to_mat4() * glm::vec4 {0,0,0,1};
                    switch (ShaderLights[j]->getLightType()) {
                    case 0: // directional
                        mesh->getMaterial()->getShader()->set(prefix + "direction", glm::normalize(direction));
                         // Rotation -> "model matrix" x Pos:{0,0,0,1}, up{0,1,0,0} ,dir:{0,0,-1,0}

                        break;
                    case 1: // point
                        mesh->getMaterial()->getShader()->set(prefix + "position",position);
                        
                        mesh->getMaterial()->getShader()->set(prefix + "attenuation_constant", ShaderLights[j]->getAttenuation().constant);
                        mesh->getMaterial()->getShader()->set(prefix + "attenuation_linear", ShaderLights[j]->getAttenuation().linear);
                        mesh->getMaterial()->getShader()->set(prefix + "attenuation_quadratic", ShaderLights[j]->getAttenuation().quadratic);
                        break;
                    case 2: // spot
                        mesh->getMaterial()->getShader()->set(prefix + "position", position);
                        mesh->getMaterial()->getShader()->set(prefix + "direction", glm::normalize(direction));
                        mesh->getMaterial()->getShader()->set(prefix + "attenuation_constant", ShaderLights[j]->getAttenuation().constant);
                        mesh->getMaterial()->getShader()->set(prefix + "attenuation_linear",ShaderLights[j]->getAttenuation().linear);
                        mesh->getMaterial()->getShader()->set(prefix + "attenuation_quadratic", ShaderLights[j]->getAttenuation().quadratic);
                        mesh->getMaterial()->getShader()->set(prefix + "inner_angle", ShaderLights[j]->getAngle().inner);
                        mesh->getMaterial()->getShader()->set(prefix + "outer_angle", ShaderLights[j]->getAngle().outer);
                        break;
                    }
                    light_count++;
                    if(ShaderLights.size() >= MAX_LIGHT_COUNT) break;
                }
                
                int size = ShaderLights.size();
                mesh->getMaterial()->getShader()->set("light_count",light_count );

                /////////////////////////////// send material uniforms ////////////////////////////////////////////
                mesh->getMaterial()->getShader()->set("camera_position", CameraTransform->getPosition());
                mesh->getMaterial()->getShader()->set("view_projection", cam->getVPMatrix(CameraTransform));
                mesh->getMaterial()->getShader()->set("object_to_world", tranf->to_mat4());
                mesh->getMaterial()->getShader()->set("object_to_world_inv_transpose", glm::inverse(tranf->to_mat4()), true);              
                mesh->getMaterial()->getShader()->set("sky_light.top_color", skylight.top_color);
                mesh->getMaterial()->getShader()->set("sky_light.middle_color", skylight.middle_color);
                mesh->getMaterial()->getShader()->set("sky_light.bottom_color", skylight.bottom_color);     
            // glm::vec4 shadertint = std::any_cast<glm::vec4>( mesh->getMaterial()->getUniforms("tint"));
            // mesh->getMaterial()->getShader()->set("tint", shadertint);  
                glm::vec3 s = std::any_cast<glm::vec3>( mesh->getMaterial()->getUniforms("albedo_tint"));
                mesh->getMaterial()->getShader()->set("material.albedo_tint", s);
                glm::vec3 s1 = std::any_cast<glm::vec3>( mesh->getMaterial()->getUniforms("specular_tint"));
                mesh->getMaterial()->getShader()->set("material.specular_tint", s1);
                glm::vec2 r = std::any_cast<glm::vec2>( mesh->getMaterial()->getUniforms("roughness_range"));
                mesh->getMaterial()->getShader()->set("material.roughness_range", r);
                glm::vec3 s2 = std::any_cast<glm::vec3>( mesh->getMaterial()->getUniforms("emissive_tint"));
                mesh->getMaterial()->getShader()->set("material.emissive_tint", s2);
                ///////////////////////////////////// send texture ////////////////////////
                pair<Texture2D*,Sampler2D*> pi = std::any_cast<pair<Texture2D*,Sampler2D*>>( mesh->getMaterial()->getUniforms("albedo_map"));
                glActiveTexture(GL_TEXTURE0);
                pi.first->bind();
                mesh->getMaterial()->getShader()->set("material.albedo_map", 0);
                
                pi = std::any_cast<pair<Texture2D*,Sampler2D*>>( mesh->getMaterial()->getUniforms("specular_map"));
                glActiveTexture(GL_TEXTURE1);
                pi.first->bind();
                mesh->getMaterial()->getShader()->set("material.specular_map", 1);
                
                pi = std::any_cast<pair<Texture2D*,Sampler2D*>>( mesh->getMaterial()->getUniforms("roughness_map"));
                glActiveTexture(GL_TEXTURE2);
                pi.first->bind();
                mesh->getMaterial()->getShader()->set("material.roughness_map", 2);
                
                pi = std::any_cast<pair<Texture2D*,Sampler2D*>>( mesh->getMaterial()->getUniforms("emissive_map"));
                glActiveTexture(GL_TEXTURE3);
                pi.first->bind();
                mesh->getMaterial()->getShader()->set("material.emissive_map", 3);
            
            
               
        ////////////////////////////////////// Draw ////////////////////////////////
               mesh->getMesh()->draw(); 
            }


        }

    }
};


#endif //GAME_MESH_H
 