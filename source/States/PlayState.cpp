
#include <application.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <imgui-utils/utils.hpp>
#include <mesh/mesh-utils.hpp>
#include <texture/texture-utils.h>
#include "PlayState.h"
#include "../common/RendererSystem.hpp"
#include "../common//Components//CameraComponent.h"
#include "../common/Components/MeshRenderer.h"
#include "../common/Components/TransformComponent.h"
#include "../common//Components//CameraControllerComponent.h"
#include "../common/Material.hpp"

#include <json/json.hpp>

#include <fstream>
#include <algorithm>
#include <cctype>
#include <string>

namespace glm {
    template<length_t L, typename T, qualifier Q>
    void from_json(const nlohmann::json& j, vec<L, T, Q>& v){
        for(length_t index = 0; index < L; ++index)
            v[index] = j[index].get<T>();
    }
}
void from_json(const nlohmann::json& j, Material& m){

    m.AddUniforms("albedo_tint",j.value<glm::vec3>("albedo_tint", {0.0f, 0.0f, 0.0f}));
    m.AddUniforms("specular_map",j.value<std::string>("specular_map", "black"));
    m.AddUniforms("specular_tint",j.value<std::string>("specular_map", "black"));
    m.AddUniforms("specular_tint" ,j.value<glm::vec3>("specular_tint", {0.0f, 0.0f, 0.0f}));
    m.AddUniforms("roughness_map",j.value<std::string>("roughness_map", "white"));
    m.AddUniforms("roughness_range",j.value<glm::vec2>("roughness_scale", {0.0f, 1.0f}));
    m.AddUniforms("ambient_occlusion_map",j.value<std::string>("ambient_occlusion_map", "white"));
    m.AddUniforms("emissive_map",j.value<std::string>("emissive_map", "black"));
    m.AddUniforms("emissive_tint",j.value<glm::vec3>("emissive_tint", {1.0f, 1.0f, 1.0f}));

}
void from_json(const nlohmann::json& j, LightComponent& l,TransformComponent t){
    std::string type_name = j.value("type", "point");
    std::transform(type_name.begin(), type_name.end(), type_name.begin(), [](char c){ return std::tolower(c); });
    if(type_name == "directional") l.setLightType (LightType::DIRECTIONAL);
    else if(type_name == "spot") l.setLightType (LightType::SPOT);
    else l.setLightType (LightType::POINT);

    l.setColor(j.value<glm::vec3>("color", {1,1,1}));
    t.setRotation(j.value<glm::vec3>("direction", {0, -1, 0}));
    t.setPosition( j.value<glm::vec3>("position", {0,0,0}));
    l.setEnable(j.value("enabled", true));
    if(auto it = j.find("attenuation"); it != j.end()){
        auto& a = it.value();
        attenuation att;
        att.constant = a.value("constant", 0.0f);
        att.linear = a.value("linear", 0.0f);
       att.quadratic = a.value("quadratic", 1.0f);
       l.setAttenuation(att);
    } else {
        l.setAttenuation ({0.0f, 0.0f, 1.0f});
    }
    if(auto it = j.find("spot_angle"); it != j.end()){
        auto& a = it.value();
        spot_angle sAng;
        sAng.inner = a.value("inner", glm::quarter_pi<float>());
        sAng.outer = a.value("outer", glm::half_pi<float>());
        l.setAngle(sAng);
    } else {
       l.setAngle({glm::quarter_pi<float>(), glm::half_pi<float>()});
    }
}
PlayState::PlayState(){

}
    void PlayState::setApplication(Application* app)
    {
        this->application = app;
    }

void PlayState::setHeight(int h)
 {
     Height = h;
 }
void PlayState::setWidth(int w)
{
    Width = w;
}
void PlayState::OnEnter()
{
    
    program.create();
    program.attach("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/shaders/ex11_transformation/transform.vert", GL_VERTEX_SHADER);
    program.attach("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/shaders/ex11_transformation/tint.frag", GL_FRAGMENT_SHADER);
    program.link();

    //////////////////////////////////////////////////////////////////
    ///// set light values Light Entities
                     //// spot light ////
     glm::vec3 spotPos={0,1,4};
    glm::vec3 spotRot={0,0,-1};
    glm::vec3 spotScale={1,1,1};
    Component* Spottransform=new TransformComponent(1,spotPos, spotRot,spotScale);
    TransformComponent* SpotTrans;
    SpotTrans = dynamic_cast<TransformComponent*>(Spottransform);
    spot_angle s;
    s.inner = 0.78539816339;
    s.outer = 1.57079632679;
    Component* SpotL=new LightComponent(1,LightType::SPOT,true,s,{1,0,0},{0.0f, 0.0f, 1.0f});
    LightComponent* SpotLight;
    SpotLight = dynamic_cast<LightComponent*>(SpotL);
   // SpotLight->setLightType(LightType::SPOT);
    Entity* spotEntity = new Entity();

    spotEntity->addComponent(SpotLight);
    spotEntity->addComponent(SpotTrans);
    
    lights.push_back(spotEntity);

    ///// Directional Light
     glm::vec3 DirPos={1,1,4};
    glm::vec3 DirRot={-1,-1,-1};
    glm::vec3 DirScale={1,1,1};
    Component* Dirtransform=new TransformComponent(1,DirPos, DirRot,DirScale);
    TransformComponent* DirTrans;
    DirTrans = dynamic_cast<TransformComponent*>(Dirtransform);

    Component* DirL=new LightComponent(1,LightType::DIRECTIONAL,false,s,{1.0f, 0.0f, 0.0f},{0.0f, 0.0f, 1.0f});
    LightComponent* DirLight;
    DirLight = dynamic_cast<LightComponent*>(DirL);
    Entity* DirEntity = new Entity();

    DirEntity->addComponent(DirLight);
    DirEntity->addComponent(DirTrans);
    

    lights.push_back(DirEntity);
    ///////////////////////////////////////////////////////////////////
    // Textures
        Texture2D* texture = new Texture2D("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/images/common/materials/metal/albedo.jpg");
        textures["wood_albedo"] = texture;
        Texture2D* texture1 = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/images/common/materials/metal/specular.jpg");
        textures["wood_specular"] = texture1;
        Texture2D* texture2 = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/images/common/materials/metal/roughness.jpg");
        textures["wood_roughness"] = texture2;
        Texture2D* moon = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/images/common/moon.jpg");
        textures["moon"] = texture;
        Sampler2D* sampler = new Sampler2D();
        for(GLuint unit = 0; unit < 5; ++unit) sampler->bind(unit);
    ///// set uniforms
    
 ////////////////////////////////////////// Entity 1 ////////////////////////////////////
     Entity* E1=new Entity();
    ////// Mesh
    meshes["house"] = std::make_unique<GAME::Mesh>();
    //GAME::mesh_utils::Cuboid(*(meshes["cube"]));
    GAME::mesh_utils::loadOBJ(*(meshes["house"]), "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/House/House.obj");
    ///// Material
    Material* material = new Material();
    pair<Texture2D*,Sampler2D*> pi;
    pi.first = texture;
    pi.second = sampler;
    material->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
    // Set Opaque 
    RenderState* Rstate = new RenderState();
    Rstate->Opaque = true; // 3ashan el tint akher haga feh b 1
    material->setState(Rstate);
    material->AddUniforms("albedo_map", pi);
    glm::vec3 temp = {1.0f, 1.0f, 1.0f};
    material->AddUniforms("albedo_tint",temp);
    pi.first = texture1;
    material->AddUniforms("specular_map",pi);
    glm::vec3 temp2 = {0.0f, 1.0f, 0.0f};
    material->AddUniforms("specular_tint" ,temp2);
    pi.first = texture2;
    material->AddUniforms("roughness_map",pi);
    glm::vec2 temps = {0.0f, 1.0f};
    material->AddUniforms("roughness_range",temps);
    glm::vec3 temp1 = {0.02f, 0.0f, 0.0f};
    pi.first = moon; 
    material->AddUniforms("emissive_map",pi);
    material->AddUniforms("emissive_tint",temp1);
    material->setShader(&program);
    //material->AddUniforms("tint", glm::vec4(1,1, 1, 1)); 
    ////// MeshRanderer Component
    Component* mesh=new MeshRenderer(0,material,&*(meshes["house"]));
   /////// Transform Component
    glm::vec3 pos={0,0,0};
    glm::vec3 rot={0,9,0};
    glm::vec3 sc={1,1,1};
    Component* transform=new TransformComponent(1,pos, rot, sc);
    TransformComponent* TempTrans;
    TempTrans = dynamic_cast<TransformComponent*>(transform);

   ///// Adding Component
    E1->addComponent(mesh);
    E1->addComponent(transform);

 ////////////////////////////////////////// Entity 2 ////////////////////////////////////
    Entity* E2=new Entity();

     ////// Mesh
    meshes["sphere"] = std::make_unique<GAME::Mesh>();
    GAME::mesh_utils::Sphere(*(meshes["sphere"]), {64, 32}, false);
    ////// MeshRanderer Component
    Component* mesh1 =new MeshRenderer(0,material,&*(meshes["sphere"]));
   /////// Transform Component
    glm::vec3 pos1={-20,20,5};
    glm::vec3 rot1={0,9,0};
    glm::vec3 sc1={10,10,10};
    Component* transform1 =new TransformComponent(1,pos1, rot1, sc1);
    TransformComponent* TempTransform;
    TempTransform = dynamic_cast<TransformComponent*>(transform1);
    //TempTransform->setParent(TempTrans); // set cube as parent for sphere

   ///// Adding Component
    E2->addComponent(mesh1);
    E2->addComponent(transform1);

    

 ////////////////////////////////////////// Camera Component ////////////////////////////////////
    Entity* camera=new Entity();
    glm::vec3 pos_cam={0,-1,0};
    glm::vec3 rot_c={0,0,0};
    glm::vec3 sc_cam={7,2,7};
    Component* transform_cam= new TransformComponent(1,pos_cam, rot_c, sc_cam);
    Component* cam_component= new CameraComponent(2);
    Component* cam_controller =new CameraController(3);
    CameraComponent* world_cam;
    world_cam = dynamic_cast<CameraComponent*>(cam_component);
    CameraController* world_camCont;
    world_camCont = dynamic_cast<CameraController*>(cam_controller);
    world_cam->setEyePosition({10, 10, 10});
    world_cam->setTarget({0, 0, 0});
    world_cam->setUp({0, 1, 0});
    world_cam->setupPerspective(glm::pi<float>() / 2, static_cast<float>(1280) / 720, 0.1f, 100.0f);
    world_camCont->initialize(application, world_cam );
    camera->addComponent(transform_cam); // 0
    camera->addComponent(cam_component); // 1
    camera->addComponent(cam_controller); // 2

 //////////////////////////////////////////////////////////////////////////////////////////////////////
        


    //// Pushing Entities into world vector
    World.push_back(camera);    // world[0]
    World.push_back(E1);        // world[1]
    World.push_back(E2);        // world[1]

 //////////////////////////////////////////////////////////////////////////////////////////////////////

        glClearColor(0, 0, 1, 0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        glClearColor(0, 0, 1, 1);

}
void PlayState::OnDraw(double deltaTime)
{

    ///set delta time
    CameraController* cam_delta;
    vector<Component*> controller_setTime;
    controller_setTime = World[0]->getComponents();
    cam_delta = dynamic_cast<CameraController*>( controller_setTime[2]);

    cam_delta->setDeltaTime(deltaTime);
    cam_delta->onUpdate();

    ///// on update for each entity
    TransformComponent* tc;
    vector<Component*> comp;
    comp = World[1]->getComponents();
    tc = dynamic_cast<TransformComponent*>( comp[1]);
    tc->onUpdate();

    TransformComponent* tc2;
    vector<Component*> comp2;
    comp2 = World[2]->getComponents();
    tc2 = dynamic_cast<TransformComponent*>( comp2[1]);
    tc2->onUpdate();

    RendererSystem* renderEntities = new RendererSystem();


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderEntities->RenderAll(World,World[0],lights);

        glClear(GL_DEPTH_BUFFER_BIT);


}
void PlayState::OnExit()
{
   //  this->Sprogram->destroy();
  //  this->model->destroy();
    program.destroy();
    for(auto& [name, mesh]: meshes){
            mesh->destroy();
        }
    vector<Component*> comp;
    for (int i =0;i<World.size();i++)
    {
        comp = World[i]->getComponents();
        for (int j=0;j< comp.size() ;j++)
            comp[j]->onDeleteState();
    }
}