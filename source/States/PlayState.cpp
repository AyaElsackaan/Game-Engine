
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
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

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
    sky_program.create();
        sky_program.attach("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/shaders/ex11_transformation/sky.vert", GL_VERTEX_SHADER);
        sky_program.attach("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/shaders/ex11_transformation/sky.frag", GL_FRAGMENT_SHADER);
        sky_program.link();

    //////////////////////////////////////////////////////////////////
    ///// set light values Light Entities
                     //// spot light ////
    glm::vec3 spotPos={-4,1,2};
    glm::vec3 spotRot={0,0,-1};
    glm::vec3 spotScale={1,1,1};
    Component* Spottransform=new TransformComponent(1,spotPos, spotRot,spotScale,NULL);
    TransformComponent* SpotTrans;
    SpotTrans = dynamic_cast<TransformComponent*>(Spottransform);
    spot_angle s;
    s.inner = 0.78539816339;
    s.outer = 1.57079632679;
    Component* SpotL=new LightComponent(1,LightType::SPOT,true,s,{1,0,0},{0.0f, 0.0f, 1.0f});
    LightComponent* SpotLight;
    SpotLight = dynamic_cast<LightComponent*>(SpotL);
    Entity* spotEntity = new Entity();
    spotEntity->addComponent(SpotLight);
    spotEntity->addComponent(SpotTrans);  
    lights.push_back(spotEntity);
    ///// Directional Light
     glm::vec3 DirPos={1,1,4};
    glm::vec3 DirRot={-1,-1,-1};
    glm::vec3 DirScale={1,1,1};
    Component* Dirtransform=new TransformComponent(1,DirPos, DirRot,DirScale,NULL);
    TransformComponent* DirTrans;
    DirTrans = dynamic_cast<TransformComponent*>(Dirtransform);
    Component* DirL=new LightComponent(1,LightType::DIRECTIONAL,true,s,{1.0f, 1.0f, 1.0f},{0.0f, 0.0f, 1.0f});
    LightComponent* DirLight;
    DirLight = dynamic_cast<LightComponent*>(DirL);
    Entity* DirEntity = new Entity();
    DirEntity->addComponent(DirLight);
    DirEntity->addComponent(DirTrans);
    // Momken yb2a 3ando meshrenderer 3shan arsem light source
    lights.push_back(DirEntity);
    ///////////////////////////////////////////////////////////////////
    // Textures
        Texture2D* texturem0 = new Texture2D("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/corona/normal.png");
        textures["mask_albedo"] = texturem0;
        Texture2D* texturem1 = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/images/common/materials/asphalt/specular.jpg");
        textures["mask_specular"] = texturem1;
        Texture2D* texturem2 = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/images/common/materials/asphalt/roughness.jpg");
        textures["mask_roughness"] = texturem2;
        
          Texture2D* textureroad = new Texture2D("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/images/common/materials/asphalt/road.jpg");
        textures["road_albedo"] = textureroad;
        Texture2D* textureroad1 = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/images/common/materials/asphalt/specular.jpg");
        textures["road_specular"] = textureroad1;
        Texture2D* textureroad2 = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/images/common/materials/asphalt/roughness.jpg");
        textures["road_roughness"] = textureroad2;

        Texture2D* texture = new Texture2D("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/char/Plastic_4K_Diffuse.jpg");
        textures["among_albedo"] = texture;
        Texture2D* texture1 = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/char/Plastic_4K_Normal.jpg");
        textures["among_specular"] = texture1;
        Texture2D* texture2 = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/char/Plastic_4K_Reflect.jpg");
        textures["among_roughness"] = texture2;
        

        Texture2D* texturebottle = new Texture2D("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/images/common/materials/glass/diffuse.jpg");
        textures["bottle_albedo"] = texturebottle;
        Texture2D* texturebottle1 = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/images/common/materials/glass/glasss.png");
        textures["bottle_specular"] = texturebottle1;
        Texture2D* texturebottle2 = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/images/common/materials/glass/roughness.png");
        textures["bottle_roughness"] = texturebottle2;

        Texture2D* texturecorona = new Texture2D("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/corona/base.png");
        textures["corona_albedo"] = texturecorona;
        Texture2D* texturecorona1 = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/corona/specular.png");
        textures["corona_specular"] = texturecorona1;
        Texture2D* texturecorona2 = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/corona/roughness.png");
        textures["corona_roughness"] = texturecorona2;
        
        Texture2D* texturehouse = new Texture2D("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/House/House.jpeg");
        textures["house_albedo"] = texturehouse;
        Texture2D* texturehouse1 = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/images/common/materials/wood/specular.jpg");
        textures["house_specular"] = texturehouse1;
        Texture2D* texturehouse2 = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engin/assets/images/common/materials/wood/roughness.jpg");
        textures["house_roughness"] = texturehouse2;
        
        Texture2D* moon = new Texture2D( "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/images/common/moon.jpg");
        textures["moon"] = texture;
        
        Sampler2D* sampler = new Sampler2D();
        for(GLuint unit = 0; unit < 5; ++unit) sampler->bind(unit);
    
    

    
    ///////////////////////////////////////////// character //////////////////////////////////////////////
     Entity* E1=new Entity();
    ////// Mesh
    E1->setID(1);
    meshes["character"] = std::make_unique<GAME::Mesh>();
    GAME::mesh_utils::loadOBJ(*(meshes["character"]), "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/char/among us.obj");
    ///// Material
    Material* material = new Material();
    
    float alpha = 1.0f;

   /// Set RenderState
    RenderState* Rstate = new RenderState();
    if (alpha == 1)
    {
        Rstate->Opaque = true; // 3ashan el tint akher haga feh b 1
        Rstate->Enable_DepthTesting = true;
    }
    else
    {
        Rstate->Opaque = false; // 3ashan el tint akher haga feh b 1
        Rstate->Enable_DepthTesting = false;
    }
    Rstate->depth_function = GL_LEQUAL;
    Rstate->enable_transparent_depth_write = true;
    Rstate->Enable_Culling = true;
    Rstate->culled_face = GL_BACK;

    Rstate->front_face_winding = GL_CCW;
    Rstate->Enable_Blending = true;
    Rstate->blend_equation = GL_FUNC_ADD;
    Rstate->blend_source_function = GL_SRC_ALPHA;
    Rstate->blend_destination_function = GL_ONE_MINUS_SRC_ALPHA;
    Rstate->blend_constant_color = {1.0f,1.0f,1.0f,0.5f};
    Rstate->enable_alpha_to_coverage = false;
    Rstate->enable_alpha_test = false;
    Rstate->alpha_test_threshold = 0.5;
    
    material->setState(Rstate);
    ///
    material->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
    material->AddUniforms("alpha",alpha);
    pair<Texture2D*,Sampler2D*> pi;
    pi.first = texture;
    pi.second = sampler;
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
    ////// MeshRanderer Component
    Component* mesh=new MeshRenderer(0,material,&*(meshes["character"]));
   /////// Transform Component
    glm::vec3 pos={0,1,0};
    glm::vec3 rot={0,9,0};
    glm::vec3 sc={0.05,0.05,0.05};
    Component* transform=new TransformComponent(1,pos, rot, sc,NULL);
    TransformComponent* TempTrans;
    TempTrans = dynamic_cast<TransformComponent*>(transform);
   // TempTrans->setParent(camTransform);

   ///// Adding Component
    E1->addComponent(mesh);
    E1->addComponent(transform);

    player = new playerSystem(E1,application);

    ////////////////////////////////////////// Camera Component ////////////////////////////////////
    Entity* camera=new Entity();
    camera->setID(5);
    glm::vec3 pos_cam={0,500,-150};
    glm::vec3 rot_c={-0.98,3.55,0};
    glm::vec3 sc_cam={1,1,1};

    Component* transform_cam= new TransformComponent(1,pos_cam, rot_c, sc_cam,TempTrans);
    Component* cam_component= new CameraComponent(2);
    Component* cam_controller =new CameraController(3);

    CameraComponent* world_cam;
    CameraController* world_camCont;
    TransformComponent* camTransform;

    world_cam = dynamic_cast<CameraComponent*>(cam_component);
    world_camCont = dynamic_cast<CameraController*>(cam_controller);
    camTransform = dynamic_cast<TransformComponent*>(transform_cam);
   // camTransform->setParent(TempTrans);
    world_cam->setFlags();
    //world_cam->setEyePosition({10, 10, 10});
    //world_cam->setTarget({0, 0, 0});
    //world_cam->setUp({0, 1, 0});
    world_cam->setupPerspective(glm::pi<float>() / 2, static_cast<float>(1280) / 720, 0.1f, 100.0f);
    world_camCont->initialize(application, world_cam,camTransform);
    camera->addComponent(transform_cam); // 0
    camera->addComponent(cam_component); // 1
    camera->addComponent(cam_controller); // 2

      player->addObject(camera);


    ////////////////////////////////////////// bottle ////////////////////////////////////

    Entity* bottle=new Entity();
    bottle->setID(3);
    /// Set Material
    ///// Material
    Material* bottlematerial = new Material();
    
    alpha = 1;

   /// Set RenderState
    RenderState* bottlestate = new RenderState();
    if (alpha == 1)
    {
        bottlestate->Opaque = true; // 3ashan el tint akher haga feh b 1
        bottlestate->Enable_DepthTesting = true;
    }
    else
    {
        bottlestate->Opaque = false; // 3ashan el tint akher haga feh b 1
        bottlestate->Enable_DepthTesting = true;
    }
    bottlestate->depth_function = GL_LEQUAL;
    bottlestate->enable_transparent_depth_write = true;
    bottlestate->Enable_Culling = true;
    bottlestate->culled_face = GL_BACK;

    bottlestate->front_face_winding = GL_CCW;
    bottlestate->Enable_Blending = true;
    bottlestate->blend_equation = GL_FUNC_ADD;
    bottlestate->blend_source_function = GL_SRC_ALPHA;
    bottlestate->blend_destination_function = GL_ONE_MINUS_SRC_ALPHA;
    bottlestate->blend_constant_color = {1.0f,1.0f,1.0f,1.0f};
    bottlestate->enable_alpha_to_coverage = false;
    bottlestate->enable_alpha_test = false;
    bottlestate->alpha_test_threshold = 0.5;
    
    bottlematerial->setState(bottlestate);
    ///
    bottlematerial->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
    bottlematerial->AddUniforms("alpha",alpha);
    //pair<Texture2D*,Sampler2D*> pi;
    pi.first = texturebottle;
    pi.second = sampler;
    bottlematerial->AddUniforms("albedo_map", pi);
    bottlematerial->AddUniforms("albedo_tint",temp);
    pi.first = texturebottle1;
    bottlematerial->AddUniforms("specular_map",pi);
    bottlematerial->AddUniforms("specular_tint" ,temp2);
    pi.first = texturebottle2;
    bottlematerial->AddUniforms("roughness_map",pi);
    bottlematerial->AddUniforms("roughness_range",temps);
    pi.first = moon; 
    bottlematerial->AddUniforms("emissive_map",pi);
    bottlematerial->AddUniforms("emissive_tint",temp1);
    bottlematerial->setShader(&program);
     ////// Mesh
    meshes["bottle"] = std::make_unique<GAME::Mesh>();
   GAME::mesh_utils::loadOBJ(*(meshes["bottle"]), "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/bottle/Bottle.obj");
    ////// MeshRanderer Component
    Component* bottlemesh =new MeshRenderer(0,bottlematerial,&*(meshes["bottle"]));
   /////// Transform Component
    glm::vec3 bottlepos={5,0,0};
    glm::vec3 bottlerot={350,5,0};
    glm::vec3 bottlesc={0.2,0.2,0.2};
    Component* bottletransform =new TransformComponent(1,bottlepos,bottlerot, bottlesc,NULL);
    TransformComponent* bottleTransform;
    bottleTransform = dynamic_cast<TransformComponent*>(bottletransform);
    
    //TempTransform->setParent(TempTrans); // set cube as parent for sphere

   ///// Adding Component
    bottle->addComponent(bottlemesh);
    bottle->addComponent(bottletransform);


    ////////////////////////////////////////// corona ////////////////////////////////////
    for (int i =0; i<1 ;i++)
    {
        Entity* corona=new Entity();
        corona->setID(2);
        /// Set Material
        ///// Material
        Material* coronamaterial = new Material();
        
        alpha = 1;

    /// Set RenderState
        RenderState* coronastate = new RenderState();
        if (alpha == 1)
        {
            coronastate->Opaque = true; // 3ashan el tint akher haga feh b 1
            coronastate->Enable_DepthTesting = true;
        }
        else
        {
            coronastate->Opaque = false; // 3ashan el tint akher haga feh b 1
            coronastate->Enable_DepthTesting = true;
        }
        coronastate->depth_function = GL_LEQUAL;
        coronastate->enable_transparent_depth_write = true;
        coronastate->Enable_Culling = true;
        coronastate->culled_face = GL_BACK;

        coronastate->front_face_winding = GL_CCW;
        coronastate->Enable_Blending = true;
        coronastate->blend_equation = GL_FUNC_ADD;
        coronastate->blend_source_function = GL_SRC_ALPHA;
        coronastate->blend_destination_function = GL_ONE_MINUS_SRC_ALPHA;
        coronastate->blend_constant_color = {1.0f,1.0f,1.0f,1.0f};
        coronastate->enable_alpha_to_coverage = false;
        coronastate->enable_alpha_test = false;
        coronastate->alpha_test_threshold = 0.5;
        
        coronamaterial->setState(coronastate);
        ///
        coronamaterial->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
        coronamaterial->AddUniforms("alpha",alpha);
        //pair<Texture2D*,Sampler2D*> pi;
        pi.first = texturecorona;
        pi.second = sampler;
        coronamaterial->AddUniforms("albedo_map", pi);
        coronamaterial->AddUniforms("albedo_tint",temp);
        pi.first = texturecorona1;
        coronamaterial->AddUniforms("specular_map",pi);
        coronamaterial->AddUniforms("specular_tint" ,temp2);
        pi.first = texturecorona2;
        coronamaterial->AddUniforms("roughness_map",pi);
        coronamaterial->AddUniforms("roughness_range",temps);
        pi.first = moon; 
        coronamaterial->AddUniforms("emissive_map",pi);
        coronamaterial->AddUniforms("emissive_tint",temp1);
        coronamaterial->setShader(&program);
        ////// Mesh
        meshes["corona" + std::to_string(i)] = std::make_unique<GAME::Mesh>();
       // GAME::mesh_utils::loadOBJ(*(meshes["corona" + std::to_string(i)]), "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/corona/corona_virus.obj");
        GAME::mesh_utils::Sphere(*(meshes["corona" + std::to_string(i)]), {64, 32}, false);
        ////// MeshRanderer Component
        Component* coronamesh =new MeshRenderer(0,coronamaterial,&*(meshes["corona"+ std::to_string(i)]));
    /////// Transform Component
        glm::vec3 coronapos={20,5,0};
        glm::vec3 coronarot={0,0,0};
        glm::vec3 coronasc={3,3,3};
        Component* coronatransform =new TransformComponent(1,coronapos,coronarot, coronasc,NULL);
        TransformComponent* coronaTransform;
        coronaTransform = dynamic_cast<TransformComponent*>(coronatransform);
    //  coronaTransform->setParent(TempTrans);

    ///// Adding Component
        corona->addComponent(coronamesh);
        corona->addComponent(coronatransform);

        player->addCorona(corona);

    }
    ////////////////////////////////////////// road ////////////////////////////////////

    Entity* road=new Entity();
    /// Set Material
    ///// Material
    Material* roadmaterial = new Material();
    
    alpha = 1;

   /// Set RenderState
    RenderState* roadstate = new RenderState();
    if (alpha == 1)
    {
        roadstate->Opaque = true; // 3ashan el tint akher haga feh b 1
        roadstate->Enable_DepthTesting = true;
    }
    else
    {
        roadstate->Opaque = false; // 3ashan el tint akher haga feh b 1
        roadstate->Enable_DepthTesting = true;
    }
    roadstate->depth_function = GL_LEQUAL;
    roadstate->enable_transparent_depth_write = true;
    roadstate->Enable_Culling = true;
    roadstate->culled_face = GL_BACK;

    roadstate->front_face_winding = GL_CCW;
    roadstate->Enable_Blending = true;
    roadstate->blend_equation = GL_FUNC_ADD;
    roadstate->blend_source_function = GL_SRC_ALPHA;
    roadstate->blend_destination_function = GL_ONE_MINUS_SRC_ALPHA;
    roadstate->blend_constant_color = {1.0f,1.0f,1.0f,1.0f};
    roadstate->enable_alpha_to_coverage = false;
    roadstate->enable_alpha_test = false;
    roadstate->alpha_test_threshold = 0.5;
    
    roadmaterial->setState(roadstate);
    ///
    roadmaterial->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
    roadmaterial->AddUniforms("alpha",alpha);
    //pair<Texture2D*,Sampler2D*> pi;
    pi.first = textureroad;
    pi.second = sampler;
    roadmaterial->AddUniforms("albedo_map", pi);
    roadmaterial->AddUniforms("albedo_tint",temp);
    pi.first = textureroad1;
    roadmaterial->AddUniforms("specular_map",pi);
    roadmaterial->AddUniforms("specular_tint" ,temp2);
    pi.first = textureroad2;
    roadmaterial->AddUniforms("roughness_map",pi);
    roadmaterial->AddUniforms("roughness_range",temps);
    pi.first = moon; 
    roadmaterial->AddUniforms("emissive_map",pi);
    roadmaterial->AddUniforms("emissive_tint",temp1);
    roadmaterial->setShader(&program);
     ////// Mesh
    meshes["road"] = std::make_unique<GAME::Mesh>();
    GAME::mesh_utils::loadOBJ(*(meshes["road"]), "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/road/road.obj");

    ////// MeshRanderer Component
    Component* roadmesh =new MeshRenderer(0,roadmaterial,&*(meshes["road"]));
   /////// Transform Component
    glm::vec3 roadpos={0,0,0};
    glm::vec3 roadrot={0,0,0};
    glm::vec3 roadsc={10,1,8000};
    Component* roadtransform =new TransformComponent(1,roadpos,roadrot,roadsc,NULL);
    TransformComponent* roadTransform;
    roadTransform = dynamic_cast<TransformComponent*>(roadtransform);
   // roadTransform->setParent(camTransform);
    //TempTransform->setParent(TempTrans); // set cube as parent for sphere

   ///// Adding Component
    road->addComponent(roadmesh);
    road->addComponent(roadtransform);

  ////////////////////////////////////////// house ////////////////////////////////////

    Entity* house=new Entity();
    house->setID(10);
    /// Set Material
    ///// Material
    Material* housematerial = new Material();
    
    alpha = 1;

   /// Set RenderState
    RenderState* housestate = new RenderState();
    if (alpha == 1)
    {
        housestate->Opaque = true; // 3ashan el tint akher haga feh b 1
        housestate->Enable_DepthTesting = true;
    }
    else
    {
       housestate->Opaque = false; // 3ashan el tint akher haga feh b 1
        housestate->Enable_DepthTesting = true;
    }
    housestate->depth_function = GL_LEQUAL;
    housestate->enable_transparent_depth_write = true;
    housestate->Enable_Culling = true;
    housestate->culled_face = GL_BACK;

    housestate->front_face_winding = GL_CCW;
    housestate->Enable_Blending = true;
    housestate->blend_equation = GL_FUNC_ADD;
    housestate->blend_source_function = GL_SRC_ALPHA;
    housestate->blend_destination_function = GL_ONE_MINUS_SRC_ALPHA;
    housestate->blend_constant_color = {1.0f,1.0f,1.0f,1.0f};
    housestate->enable_alpha_to_coverage = false;
    housestate->enable_alpha_test = false;
    housestate->alpha_test_threshold = 0.5;
    
    housematerial->setState(housestate);
    ///
     housematerial->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
     housematerial->AddUniforms("alpha",alpha);
    //pair<Texture2D*,Sampler2D*> pi;
    pi.first = texturehouse;
    pi.second = sampler;
    housematerial->AddUniforms("albedo_map", pi);
     housematerial->AddUniforms("albedo_tint",temp);
    pi.first = texturehouse1;
    housematerial->AddUniforms("specular_map",pi);
    housematerial->AddUniforms("specular_tint" ,temp2);
    pi.first = texturehouse2;
    housematerial->AddUniforms("roughness_map",pi);
    housematerial->AddUniforms("roughness_range",temps);
    pi.first = moon; 
    housematerial->AddUniforms("emissive_map",pi);
    housematerial->AddUniforms("emissive_tint",temp1);
    housematerial->setShader(&program);
     ////// Mesh
    meshes["house"] = std::make_unique<GAME::Mesh>();
    GAME::mesh_utils::loadOBJ(*(meshes["house"]), "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/House/House.obj");

    ////// MeshRanderer Component
    Component* housemesh =new MeshRenderer(0,housematerial,&*(meshes["house"]));
   /////// Transform Component
    glm::vec3 housepos={0,0,-8800};
    glm::vec3 houserot={0,0,0};
    glm::vec3 housesc={10,10,10};
    Component* housetransform =new TransformComponent(1,housepos,houserot,housesc,NULL);
    TransformComponent* houseTransform;
    houseTransform = dynamic_cast<TransformComponent*>(housetransform);
   // roadTransform->setParent(camTransform);
    //TempTransform->setParent(TempTrans); // set cube as parent for sphere

   ///// Adding Component
    house->addComponent(housemesh);
    house->addComponent(housetransform);

  ////////////////////////////////////////// health ////////////////////////////////////

    Entity* healthbar=new Entity();
    healthbar->setID(11);
    /// Set Material
    ///// Material
    Material*  healthbarmaterial = new Material();
    
    alpha = 1;

   /// Set RenderState
    RenderState*  healthbarstate = new RenderState();
    if (alpha == 1)
    {
         healthbarstate->Opaque = true; // 3ashan el tint akher haga feh b 1
         healthbarstate->Enable_DepthTesting = true;
    }
    else
    {
       healthbarstate->Opaque = false; // 3ashan el tint akher haga feh b 1
        healthbarstate->Enable_DepthTesting = true;
    }
    healthbarstate->depth_function = GL_LEQUAL;
    healthbarstate->enable_transparent_depth_write = true;
    healthbarstate->Enable_Culling = true;
    healthbarstate->culled_face = GL_BACK;

    healthbarstate->front_face_winding = GL_CCW;
    healthbarstate->Enable_Blending = true;
    healthbarstate->blend_equation = GL_FUNC_ADD;
    healthbarstate->blend_source_function = GL_SRC_ALPHA;
    healthbarstate->blend_destination_function = GL_ONE_MINUS_SRC_ALPHA;
    healthbarstate->blend_constant_color = {1.0f,1.0f,1.0f,1.0f};
    healthbarstate->enable_alpha_to_coverage = false;
    healthbarstate->enable_alpha_test = false;
    healthbarstate->alpha_test_threshold = 0.5;
    
    healthbarmaterial->setState(healthbarstate);
    ///
    healthbarmaterial->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
    healthbarmaterial->AddUniforms("alpha",alpha);
    //pair<Texture2D*,Sampler2D*> pi;
    pi.first = texturehouse;
    pi.second = sampler;
    healthbarmaterial->AddUniforms("albedo_map", pi);
    healthbarmaterial->AddUniforms("albedo_tint",temp);
    pi.first = texturehouse1;
    healthbarmaterial->AddUniforms("specular_map",pi);
    healthbarmaterial->AddUniforms("specular_tint" ,temp2);
    pi.first = texturehouse2;
    healthbarmaterial->AddUniforms("roughness_map",pi);
    healthbarmaterial->AddUniforms("roughness_range",temps);
    pi.first = moon; 
    healthbarmaterial->AddUniforms("emissive_map",pi);
    healthbarmaterial->AddUniforms("emissive_tint",temp1);
    healthbarmaterial->setShader(&program);
    ////// MeshRanderer Component
    meshes["health"] = std::make_unique<GAME::Mesh>();
    GAME::mesh_utils::Cuboid(*(meshes["health"]));

    Component* healthbarmesh =new MeshRenderer(0,healthbarmaterial,&*(meshes["health"]));
   /////// Transform Component
    glm::vec3 healthbarpos={800,300,0};
    glm::vec3 healthbarrot={-0.98,4,1.2};
    glm::vec3 healthbarsc={100,0,150};
    Component* healthbartransform =new TransformComponent(1,healthbarpos,healthbarrot,healthbarsc,TempTrans);
    TransformComponent* healthbarTransform;
    healthbarTransform = dynamic_cast<TransformComponent*>(healthbartransform);
   // roadTransform->setParent(camTransform);
    //TempTransform->setParent(TempTrans); // set cube as parent for sphere

   ///// Adding Component
    healthbar->addComponent(healthbarmesh);
    healthbar->addComponent(healthbartransform);


      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
        meshes["cube"] = std::make_unique<GAME::Mesh>();
        GAME::mesh_utils::Cuboid(*(meshes["cube"]));


    //// Pushing Entities into world vector
    World.push_back(camera);    // world[0]
    World.push_back(road);
    World.push_back(E1);        // world[2]
    World.push_back(bottle);
    World.push_back(house);
  //  World.push_back(corona);

    player->addObject(E1);
    player->addObject(road);
    player->addObject(bottle);
    player->addObject(house);
    player->addObject(healthbar);
   
    

 //////////////////////////////////////////////////////////////////////////////////////////////////////

        glClearColor(0, 0, 1, 0);


        glClearColor(0, 0, 1, 1);

}
void PlayState::OnDraw(double deltaTime)
{
    health = player->getHealth();
    finishFlag = player->getFlag();
    ///set delta time
    CameraController* cam_delta;
    CameraComponent* camSky;
    TransformComponent* camTransform;

    vector<Component*> controller_setTime;
    controller_setTime = World[0]->getComponents();
    cam_delta = dynamic_cast<CameraController*>( controller_setTime[2]);
    if (cam_delta == NULL)
        std::cout << "Controller" << std::endl;
    camSky = dynamic_cast<CameraComponent*>( controller_setTime[1]);
    if (camSky == NULL)
        std::cout << "Camera" << std::endl;
    camTransform = dynamic_cast<TransformComponent*>(controller_setTime[0]);
    if (camTransform == NULL)
        std::cout << "Transform" << std::endl;
    

    
    cam_delta->setDeltaTime(deltaTime);

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

    glUseProgram(sky_program);

    sky_program.set("view_projection", camSky->getVPMatrix(camTransform));
    sky_program.set("camera_position", camTransform->getPosition());
    sky_program.set("sky_light.top_color", sky_light.enabled ? sky_light.top_color : glm::vec3(1.0f));
    sky_program.set("sky_light.middle_color", sky_light.enabled ? sky_light.middle_color : glm::vec3(1.0f));
    sky_program.set("sky_light.bottom_color", sky_light.enabled ? sky_light.bottom_color : glm::vec3(1.0f));
    sky_program.set("exposure", sky_box_exposure);

        glCullFace(GL_FRONT);
        meshes["cube"]->draw();
        glCullFace(GL_BACK);

/////////////////////////////////////////////////////////////////////
    player->movePlayer();
   // cam_delta->update(deltaTime,camTransform,camSky);
    camTransform->to_mat4();
    generateTimer++;
    if (generateTimer > counter)
    {
        player->generateCorona();
        counter = counter +180;
    }
    bottleTime++;
    if (bottleTime > bottleCounter)
    {
        player->generateBottle();
        bottleCounter = bottleCounter +360;
    }
    // get el vector w ab3to ll render system

/////////////////////////////////////////////////////////////////
    renderEntities->RenderAll(player->getUpdatedVector(),World[0],lights);

    glClear(GL_DEPTH_BUFFER_BIT);


}
void PlayState::OnExit()
{
  // Delete textures
    program.destroy();
    sky_program.destroy();
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
int PlayState::getHealth()
{
    return health;
}
int PlayState::getfinishFlag()
{
    return finishFlag;
}
