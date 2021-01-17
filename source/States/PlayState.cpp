
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
    program.attach("../../assets/shaders/ex11_transformation/transform.vert", GL_VERTEX_SHADER);
    program.attach("../../assets/shaders/ex11_transformation/tint.frag", GL_FRAGMENT_SHADER);
    program.link();
    sky_program.create();
        sky_program.attach("../../assets/shaders/ex11_transformation/sky.vert", GL_VERTEX_SHADER);
        sky_program.attach("../../assets/shaders/ex11_transformation/sky.frag", GL_FRAGMENT_SHADER);
        sky_program.link();

        if (level == 1)
        {
            sky_light.top_color = glm::vec3{0.35, 0.35, 0.4};
            sky_light.middle_color = glm::vec3{0.25, 0.3, 0.5};
            sky_light.bottom_color = glm::vec3{0.25, 0.25, 0.25};
        }
        else
        {
            sky_light.top_color = glm::vec3 {0.298, 0.329, 0.643};
            sky_light.middle_color = glm::vec3{0.047, 0.078, 0.2705};
            sky_light.bottom_color = glm::vec3{0.219, 0.1568, 0.36};
        }
        
        ///////////// Lights //////////////
        Initialize_Lights();
        ///////////// Textures ////////////
        Initialize_Textures(level);

        ///////////// Entities ////////////
        Initialize_Entities(level);
    
    
 //////////////////////////////////////////////////////////////////////////////////////////////////////

        glClearColor(0, 0, 1, 0);


        glClearColor(0, 0, 1, 1);

}
void PlayState::OnDraw(double deltaTime)
{
    /// check if the level completed , or health =0 -> will be used in application.cpp
    health = player->getHealth();
    finishFlag = player->getFlag();

    ///set delta time
    CameraComponent* camSky;
    TransformComponent* camTransform;

    vector<Component*> skyCamera;
    skyCamera = World[0]->getComponents();
    camSky = dynamic_cast<CameraComponent*>( skyCamera[1]);
    camTransform = dynamic_cast<TransformComponent*>(skyCamera[0]);


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

    /////////////////////////// check shield ///////////////////////
    if (level == 2)
    {
        if (player->getshield())
        {
            shieldTimer++;
        }
        if (shieldTimer == shield_Setfalse)
        {
            player->setshield(false);
            shieldTimer =0;
        }
    }
    ///////////////////////////Move Player///////////////////////////
    player->movePlayer(level);
    camTransform->to_mat4();
    ///////////////////////// generate random corona + bottle + mask ///////////////
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
    if (level == 2)
    {
        shieldGenerate++;
        if (shieldGenerate > shieldcounter)
        {
            player->generateMask();
            shieldcounter = 1000;
            shieldGenerate = 0;
        }

    }
/////////////////////////////Render System//////////////////////////////
    RendererSystem* renderEntities = new RendererSystem();

    renderEntities->RenderAll(player->getUpdatedVector(),World[0],lights,sky_light,player->getshield());

    glClear(GL_DEPTH_BUFFER_BIT);


}
void PlayState::OnExit()
{
    for (auto const& t : textures)
    {
        t.second->~Texture2D();
    }

    program.destroy();
    sky_program.destroy();

    for(auto& [name, mesh]: meshes)
    {
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
void PlayState::Initialize_Entities(int level)
{


   /// Set RenderStateg
    float alpha = 1.0f;

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
    Rstate->Enable_Culling = true;
    Rstate->culled_face = GL_BACK;
    Rstate->front_face_winding = GL_CCW;
    Rstate->Enable_Blending = true;
    Rstate->blend_equation = GL_FUNC_ADD;
    Rstate->blend_source_function = GL_SRC_ALPHA;
    Rstate->blend_destination_function = GL_ONE_MINUS_SRC_ALPHA;
    Rstate->enable_alpha_to_coverage = false;
    ///////////////////////////////////////////// character //////////////////////////////////////////////
     Entity* E1=new Entity();
    E1->setID(1);
    // Mesh
    meshes["character"] = std::make_unique<GAME::Mesh>();
    GAME::mesh_utils::loadOBJ(*(meshes["character"]), "../../assets/models/char/among us.obj");
    ///// Material
    Material* material = new Material();
    
    
    
    material->setState(Rstate);
    ///
    material->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
    material->AddUniforms("alpha",alpha);
    pair<Texture2D*,Sampler2D*> pi;
    pi.first = textures["among_albedo"];
    //pi.second = sampler;
    material->AddUniforms("albedo_map", pi);
    glm::vec3 temp = {1.0f, 1.0f, 1.0f};
    material->AddUniforms("albedo_tint",temp);
    pi.first = textures["among_specular"];
    material->AddUniforms("specular_map",pi);
    glm::vec3 temp2 = {1.0f, 1.0f, 1.0f};
    material->AddUniforms("specular_tint" ,temp2);
    pi.first = textures["among_roughness"];
    material->AddUniforms("roughness_map",pi);
    glm::vec2 temps = {0.0f, 1.0f};
    material->AddUniforms("roughness_range",temps);
    glm::vec3 temp1 = {0.02f, 0.0f, 0.0f};
    pi.first =textures["map"];
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

  ////////////////////////////////////////// health ////////////////////////////////////

    Entity* healthbar=new Entity();
    healthbar->setID(15);
    /// Set Material
    ///// Material
    Material*  healthbarmaterial = new Material();
   
    healthbarmaterial->setState(Rstate);
    ///
    healthbarmaterial->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
    healthbarmaterial->AddUniforms("alpha",alpha);
    //pair<Texture2D*,Sampler2D*> pi;
    pi.first = textures["health_albedo"];
  // pi.second = sampler;
    healthbarmaterial->AddUniforms("albedo_map", pi);
    healthbarmaterial->AddUniforms("albedo_tint",glm::vec3{1,0,0});
    pi.first = textures["health_specular"];
    healthbarmaterial->AddUniforms("specular_map",pi);
    healthbarmaterial->AddUniforms("specular_tint" ,glm::vec3{1,1,1});
    pi.first = textures["health_roughness"];
    healthbarmaterial->AddUniforms("roughness_map",pi);
    healthbarmaterial->AddUniforms("roughness_range",temps);
    pi.first = textures["moon"];
    healthbarmaterial->AddUniforms("emissive_map",pi);
    healthbarmaterial->AddUniforms("emissive_tint",temp1);
    healthbarmaterial->setShader(&program);
    ////// MeshRanderer Component
    meshes["health"] = std::make_unique<GAME::Mesh>();
    GAME::mesh_utils::Cuboid(*(meshes["health"]));

    Component* healthbarmesh =new MeshRenderer(0,healthbarmaterial,&*(meshes["health"]));
   /////// Transform Component
    glm::vec3 healthbarpos={60,455,0};
    glm::vec3 healthbarrot={1.55,1.29,0.83};
    glm::vec3 healthbarsc={200,0.5,10};
    Component* healthbartransform =new TransformComponent(1,healthbarpos,healthbarrot,healthbarsc,TempTrans);
    TransformComponent* healthbarTransform;
    healthbarTransform = dynamic_cast<TransformComponent*>(healthbartransform);
   // roadTransform->setParent(camTransform);
    //TempTransform->setParent(TempTrans); // set cube as parent for sphere

   ///// Adding Component
    healthbar->addComponent(healthbarmesh);
    healthbar->addComponent(healthbartransform);

player = new playerSystem(E1,healthbar,application);

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
 
    world_cam->setFlags();

    world_cam->setupPerspective(glm::pi<float>() / 2, static_cast<float>(1280) / 720, 0.1f, 100.0f);
    //world_camCont->initialize(application, world_cam,camTransform);
    camera->addComponent(transform_cam); // 0
    camera->addComponent(cam_component); // 1
   // camera->addComponent(cam_controller); // 2
      player->addObject(camera);

    ////////////////////////////////////////// bottle ////////////////////////////////////

    Entity* bottle=new Entity();
    bottle->setID(3);
    /// Set Material
    Material* bottlematerial = new Material();

   /// Set RenderState
    
    bottlematerial->setState(Rstate);
    ///
    bottlematerial->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
    bottlematerial->AddUniforms("alpha",alpha);
    //pair<Texture2D*,Sampler2D*> pi;
    pi.first = textures["bottle_albedo"];
    //pi.second = sampler;
    bottlematerial->AddUniforms("albedo_map", pi);
    bottlematerial->AddUniforms("albedo_tint",temp);
    pi.first =  textures["bottle_specular"];
    bottlematerial->AddUniforms("specular_map",pi);
    bottlematerial->AddUniforms("specular_tint" ,temp2);
    pi.first =  textures["bottle_roughness"];
    bottlematerial->AddUniforms("roughness_map",pi);
    bottlematerial->AddUniforms("roughness_range",temps);
    pi.first =  textures["moon"];
    bottlematerial->AddUniforms("emissive_map",pi);
    bottlematerial->AddUniforms("emissive_tint",temp1);
    bottlematerial->setShader(&program);
     ////// Mesh
    meshes["bottle"] = std::make_unique<GAME::Mesh>();
   GAME::mesh_utils::loadOBJ(*(meshes["bottle"]), "../../assets/models/bottle/Bottle.obj");
    ////// MeshRanderer Component
    Component* bottlemesh =new MeshRenderer(0,bottlematerial,&*(meshes["bottle"]));
   /////// Transform Component
    glm::vec3 bottlepos={5,2,0};
    glm::vec3 bottlerot={350,5,0};
    glm::vec3 bottlesc={0.3,0.3,0.3};
    Component* bottletransform =new TransformComponent(1,bottlepos,bottlerot, bottlesc,NULL);
    TransformComponent* bottleTransform;
    bottleTransform = dynamic_cast<TransformComponent*>(bottletransform);
   ///// Adding Component
    bottle->addComponent(bottlemesh);
    bottle->addComponent(bottletransform);


    ////////////////////////////////////////// corona ////////////////////////////////////
        Entity* corona=new Entity();
        corona->setID(2);
        /// Set Material
        ///// Material
        Material* coronamaterial = new Material();
        
        coronamaterial->setState(Rstate);
        ///
        coronamaterial->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
        coronamaterial->AddUniforms("alpha",alpha);
        //pair<Texture2D*,Sampler2D*> pi;
        pi.first = textures["corona_albedo"];
        coronamaterial->AddUniforms("albedo_map", pi);
        coronamaterial->AddUniforms("albedo_tint",temp);
        pi.first = textures["corona_specular"];
        coronamaterial->AddUniforms("specular_map",pi);
        coronamaterial->AddUniforms("specular_tint" ,temp2);
        pi.first = textures["corona_roughness"];
        coronamaterial->AddUniforms("roughness_map",pi);
        coronamaterial->AddUniforms("roughness_range",temps);
        pi.first = textures["moon"]; 
        coronamaterial->AddUniforms("emissive_map",pi);
        coronamaterial->AddUniforms("emissive_tint",temp1);
        coronamaterial->setShader(&program);
        ////// Mesh
        meshes["corona"] = std::make_unique<GAME::Mesh>();
       GAME::mesh_utils::loadOBJ(*(meshes["corona"]), "../../assets/models/corona/corona_virus.obj");
       // GAME::mesh_utils::Sphere(*(meshes["corona"]), {64, 32}, false);
        ////// MeshRanderer Component
        Component* coronamesh =new MeshRenderer(0,coronamaterial,&*(meshes["corona"]));
    /////// Transform Component
        glm::vec3 coronapos={20,5,0};
        glm::vec3 coronarot={0,0,0};
        glm::vec3 coronasc={1,1,1};
        Component* coronatransform =new TransformComponent(1,coronapos,coronarot, coronasc,NULL);
        TransformComponent* coronaTransform;
        coronaTransform = dynamic_cast<TransformComponent*>(coronatransform);
    ///// Adding Component
        corona->addComponent(coronamesh);
        corona->addComponent(coronatransform);

        player->addObject(corona);
    ////////////////////////////////////////// road ////////////////////////////////////

    Entity* road=new Entity();
    /// Set Material
    ///// Material
    Material* roadmaterial = new Material();

    roadmaterial->setState(Rstate);
    ///
    roadmaterial->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
    roadmaterial->AddUniforms("alpha",alpha);
    pi.first =  textures["road_albedo"];;
   // pi.second = sampler;
    roadmaterial->AddUniforms("albedo_map", pi);
    roadmaterial->AddUniforms("albedo_tint",temp);
    pi.first =  textures["road_specular"];
    roadmaterial->AddUniforms("specular_map",pi);
    roadmaterial->AddUniforms("specular_tint" ,temp2);
    pi.first = textures["road_roughness"];
    roadmaterial->AddUniforms("roughness_map",pi);
    roadmaterial->AddUniforms("roughness_range",temps);
    pi.first = textures["moon"];
    roadmaterial->AddUniforms("emissive_map",pi);
    roadmaterial->AddUniforms("emissive_tint",temp1);
    roadmaterial->setShader(&program);
     ////// Mesh
    meshes["road"] = std::make_unique<GAME::Mesh>();
       GAME::mesh_utils::loadOBJ(*(meshes["road"]), "../../assets/models/road/road.obj");

    ////// MeshRanderer Component
    Component* roadmesh =new MeshRenderer(0,roadmaterial,&*(meshes["road"]));
   /////// Transform Component
    glm::vec3 roadpos={0,0,0};
    glm::vec3 roadrot={0,0,0};
    glm::vec3 roadsc={10,1,6000};
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

    housematerial->setState(Rstate);
    ///
     housematerial->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
     housematerial->AddUniforms("alpha",alpha);
    pi.first = textures["house_albedo"];
    //pi.second = sampler;
    housematerial->AddUniforms("albedo_map", pi);
     housematerial->AddUniforms("albedo_tint",temp);
    pi.first = textures["house_specular"];
    housematerial->AddUniforms("specular_map",pi);
    housematerial->AddUniforms("specular_tint" ,temp2);
    pi.first = textures["house_roughness"];
    housematerial->AddUniforms("roughness_map",pi);
    housematerial->AddUniforms("roughness_range",temps);
    pi.first = textures["moon"]; 
    housematerial->AddUniforms("emissive_map",pi);
    housematerial->AddUniforms("emissive_tint",temp1);
    housematerial->setShader(&program);
     ////// Mesh
    meshes["house"] = std::make_unique<GAME::Mesh>();
    GAME::mesh_utils::loadOBJ(*(meshes["house"]), "../../assets/models/House/House.obj");

    ////// MeshRanderer Component
    Component* housemesh =new MeshRenderer(0,housematerial,&*(meshes["house"]));
   /////// Transform Component
    glm::vec3 housepos={0,0,-6800};
    glm::vec3 houserot={0,0,0};
    glm::vec3 housesc={10,10,10};
    Component* housetransform =new TransformComponent(1,housepos,houserot,housesc,NULL);
    TransformComponent* houseTransform;
    houseTransform = dynamic_cast<TransformComponent*>(housetransform);

   ///// Adding Component
    house->addComponent(housemesh);
    house->addComponent(housetransform);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
       ////////////////////////////////////////// ground ////////////////////////////////////

    Entity* ground=new Entity();
    /// Set Material
    ///// Material
    Material* groundmaterial = new Material();
   
    
    
    groundmaterial->setState(Rstate);
    ///
    groundmaterial->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
    groundmaterial->AddUniforms("alpha",alpha);
    //pair<Texture2D*,Sampler2D*> pi;
    pi.first = textures["ground_albedo"];
    groundmaterial->AddUniforms("albedo_map", pi);
    groundmaterial->AddUniforms("albedo_tint",temp);
    pi.first = textures["ground_specular"];
    groundmaterial->AddUniforms("specular_map",pi);
    groundmaterial->AddUniforms("specular_tint" ,temp2);
    pi.first = textures["ground_roughness"];
    groundmaterial->AddUniforms("roughness_map",pi);
    groundmaterial->AddUniforms("roughness_range",temps);
    pi.first = textures["moon"];
    groundmaterial->AddUniforms("emissive_map",pi);
    groundmaterial->AddUniforms("emissive_tint",temp1);
    groundmaterial->setShader(&program);
     ////// Mesh
    meshes["ground"] = std::make_unique<GAME::Mesh>();
       GAME::mesh_utils::loadOBJ(*(meshes["ground"]), "../../assets/models/road/road.obj");

    ////// MeshRanderer Component
    Component* groundmesh =new MeshRenderer(0,groundmaterial,&*(meshes["ground"]));
   /////// Transform Component
    glm::vec3 groundpos={0,-2,0};
    glm::vec3 groundrot={0,0,0};
    glm::vec3 groundsc={12,1,6000};
    Component* groundtransform =new TransformComponent(1,groundpos,groundrot,groundsc,NULL);
    TransformComponent* groundTransform;
    groundTransform = dynamic_cast<TransformComponent*>(groundtransform);
   ///// Adding Component
    ground->addComponent(groundmesh);
    ground->addComponent(groundtransform);
       
    Entity* mask;
       /////////////////////// if level 2 //////////////////
       if (level == 2)
       {
                    ////////////////////////////////////////// mask ////////////////////////////////////
            mask=new Entity();
            mask->setID(4);
            /// Set Material
            ///// Material
            Material* material1 = new Material();
            
            material1->setState(Rstate);
            ///
            material1->AddUniforms("tint", glm::vec4(1.0,0.0, 0.0, 1));
            material1->AddUniforms("alpha",alpha);
            //pair<Texture2D*,Sampler2D*> pi;
            pi.first = textures["mask_albedo"];
            material1->AddUniforms("albedo_map", pi);
            material1->AddUniforms("albedo_tint",temp);
            pi.first = textures["mask_specular"] ;
            material1->AddUniforms("specular_map",pi);
            material1->AddUniforms("specular_tint" ,temp2);
            pi.first = textures["mask_roughness"];
            material1->AddUniforms("roughness_map",pi);
            material1->AddUniforms("roughness_range",temps);
            pi.first = textures["moon"] ; 
            material1->AddUniforms("emissive_map",pi);
            material1->AddUniforms("emissive_tint",glm::vec3{0,0,0.9});
            material1->setShader(&program);
            ////// Mesh
            meshes["mask"] = std::make_unique<GAME::Mesh>();
            GAME::mesh_utils::loadOBJ(*(meshes["mask"]), "C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/models/mask/mask.obj");
            ////// MeshRanderer Component
            Component* mesh1 =new MeshRenderer(0,material1,&*(meshes["mask"]));
            /////// Transform Component
            glm::vec3 pos1={-15,0,0};
            glm::vec3 rot1={0,0,0};
            glm::vec3 sc1={2,2,2};
            Component* transform1 =new TransformComponent(1,pos1, rot1, sc1,NULL);
            TransformComponent* TempTransform;
            TempTransform = dynamic_cast<TransformComponent*>(transform1);
            
            //TempTransform->setParent(TempTrans); // set cube as parent for sphere

            ///// Adding Component
            mask->addComponent(mesh1);
            mask->addComponent(transform1);

       }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
    meshes["cube"] = std::make_unique<GAME::Mesh>();
    GAME::mesh_utils::Cuboid(*(meshes["cube"]));


    //// Pushing Entities into world vector
    World.push_back(camera);    // world[0]
    player->addObject(E1);
    if (level == 2)
    {
        player->addObject(mask);
    }
    player->addObject(ground);
    player->addObject(road);
    player->addObject(bottle);
    player->addObject(house);
    player->addObject(healthbar);

}
void PlayState::Initialize_Textures(int level)
{
    // Textures
    if (level == 2)
    {
        Texture2D* texturem0 = new Texture2D("../../assets/models/corona/normal.png");
        textures["mask_albedo"] = texturem0;
        Texture2D* texturem1 = new Texture2D( "../../assets/images/common/materials/asphalt/specular.jpg");
        textures["mask_specular"] = texturem1;
        Texture2D* texturem2 = new Texture2D( "../../assets/images/common/materials/asphalt/roughness.jpg");
        textures["mask_roughness"] = texturem2;
    }   
        Texture2D* textureroad = new Texture2D("../../assets/images/common/materials/asphalt/road.jpg");
        textures["road_albedo"] = textureroad;
        Texture2D* textureroad1 = new Texture2D( "../../assets/images/common/materials/asphalt/specular.jpg");
        textures["road_specular"] = textureroad1;
        Texture2D* textureroad2 = new Texture2D( "../../assets/images/common/materials/asphalt/roughness.jpg");
        textures["road_roughness"] = textureroad2;

        Texture2D* textureground = new Texture2D("../../assets/images/common/materials/metal/albedo.jpg");
        textures["ground_albedo"] = textureground;
        Texture2D* textureground1 = new Texture2D( "../../assets/images/common/materials/metal/specular.jpg");
        textures["ground_specular"] = textureground1;
        Texture2D* textureground2 = new Texture2D( "../../assets/images/common/materials/metal/roughness.jpg");
        textures["ground_roughness"] = textureground2;


        Texture2D* texture = new Texture2D("../../assets/models/char/Plastic_4K_Diffuse.jpg");
        textures["among_albedo"] = texture;
        Texture2D* texture1 = new Texture2D( "../../assets/models/char/Plastic_4K_Normal.jpg");
        textures["among_specular"] = texture1;
        Texture2D* texture2 = new Texture2D( "../../assets/models/char/Plastic_4K_Reflect.jpg");
        textures["among_roughness"] = texture2;
        Texture2D* texture3 = new Texture2D( "../../assets/models/mask/bluemap.jpg");
        textures["map"] = texture3;
        

        Texture2D* texturebottle = new Texture2D("../../assets/images/common/materials/glass/diffuse.jpg");
        textures["bottle_albedo"] = texturebottle;
        Texture2D* texturebottle1 = new Texture2D( "../../assets/images/common/materials/glass/glasss.png");
        textures["bottle_specular"] = texturebottle1;
        Texture2D* texturebottle2 = new Texture2D( "../../assets/images/common/materials/glass/roughness.png");
        textures["bottle_roughness"] = texturebottle2;

        Texture2D* texturecorona = new Texture2D("../../assets/models/corona/base.png");
        textures["corona_albedo"] = texturecorona;
        Texture2D* texturecorona1 = new Texture2D( "../../assets/models/corona/specular.png");
        textures["corona_specular"] = texturecorona1;
        Texture2D* texturecorona2 = new Texture2D( "../../assets/models/corona/roughness.png");
        textures["corona_roughness"] = texturecorona2;
        
        Texture2D* texturehouse = new Texture2D("../../assets/models/House/House.jpeg");
        textures["house_albedo"] = texturehouse;
        Texture2D* texturehouse1 = new Texture2D( "../../assets/images/common/materials/wood/specular.jpg");
        textures["house_specular"] = texturehouse1;
        Texture2D* texturehouse2 = new Texture2D( "../../assets/images/common/materials/wood/roughness.jpg");
        textures["house_roughness"] = texturehouse2;

         Texture2D* texturehealth = new Texture2D("../../assets/images/common/materials/red.jpg");
        textures["health_albedo"] = texturehealth;
        Texture2D* texturehealth1 = new Texture2D( "../../assets/images/common/materials/wood/specular.jpg");
        textures["health_specular"] = texturehealth1;
        Texture2D* texturehealth2 = new Texture2D( "../../assets/images/common/materials/wood/roughness.jpg");
        textures["health_roughness"] = texturehealth2;
        
        
        Texture2D* moon = new Texture2D( "../../assets/images/common/moon.jpg");
        textures["moon"] = texture;
        
        Sampler2D* sampler = new Sampler2D();
        for(GLuint unit = 0; unit < 5; ++unit) sampler->bind(unit);
}
void PlayState::Initialize_Lights()
{
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
    Component* SpotL=new LightComponent(1,LightType::SPOT,false,s,{1,0,0},{0.0f, 0.0f, 1.0f});
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
    glm::vec3 color;
    if (level == 1)
    {
        color = glm::vec3{1,1,1};
    }
    else
    {
        color = glm::vec3{0.6117, 0.686, 0.788};
    }
    Component* DirL=new LightComponent(1,LightType::DIRECTIONAL,true,s,color,{0.0f, 0.0f, 1.0f});
    LightComponent* DirLight;
    DirLight = dynamic_cast<LightComponent*>(DirL);
    Entity* DirEntity = new Entity();
    DirEntity->addComponent(DirLight);
    DirEntity->addComponent(DirTrans);

    // Momken yb2a 3ando meshrenderer 3shan arsem light source
    lights.push_back(DirEntity);

}

void PlayState::setLevel(int l)
{
    level =l;
}
int PlayState::getLevel()
{
    return level;
}


