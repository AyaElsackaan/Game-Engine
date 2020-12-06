
#include <glm/glm.hpp>
#include <glad/gl.h>
#include "../common/RendererSystem.hpp"
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "PlayState.h"
#include <imgui-utils/utils.hpp>
#include <mesh/mesh-utils.hpp>

#include "../common//Components//CameraComponent.h"
#include "../common/Components/MeshRenderer.h"
#include "../common/Components/TransformComponent.h"
#include "../common//Components//CameraControllerComponent.h"
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
    std::cout << "PlayState OnEnter" <<endl;
    program.create();
    program.attach("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/shaders/ex11_transformation/transform.vert", GL_VERTEX_SHADER);
    program.attach("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/shaders/ex11_transformation/tint.frag", GL_FRAGMENT_SHADER);
    program.link();


    GAME::mesh_utils::Cuboid(model, true);


    Component* mesh=new MeshRenderer(0,&program,&model);


    glm::vec3 pos={0,-1,0};
    glm::vec3 rot={0,0,0};
    glm::vec3 sc={7,2,7};
    Component* transform=new TransformComponent(1,pos, rot, sc);

    Entity* E1=new Entity();
    E1->addComponent(mesh);
    E1->addComponent(transform);

    ///////////////////////

     glm::vec3 pos_cam={0,-1,0};
    glm::vec3 rot_c={0,0,0};
    glm::vec3 sc_cam={7,2,7};
    Component* transform_cam=new TransformComponent(1,pos, rot, sc);
    Component* cam_component=new CameraComponent(2);
    Component* cam_controller=new CameraController(3);

    CameraComponent* world_cam;
    world_cam = dynamic_cast<CameraComponent*>(cam_component);

    CameraController* world_camCont;
    world_camCont = dynamic_cast<CameraController*>(cam_controller);

        std:: cout << Width << "  " << Height <<endl;
        world_cam->setEyePosition({10, 10, 10});
        world_cam->setTarget({0, 0, 0});
        world_cam->setUp({0, 1, 0});
        world_cam->setupPerspective(glm::pi<float>()/2, static_cast<float>(Width)/Height, 0.1f, 100.0f);

        if (application == NULL)
            std::cout << "App NULL" <<endl;
        world_camCont->initialize(application, world_cam );

    Entity* camera=new Entity();
    camera->addComponent(transform_cam); // 0
    camera->addComponent(cam_component); // 1
    camera->addComponent(cam_controller); // 2


        World.push_back(camera);  // world[0]
        World.push_back(E1);        // world[1]

        glClearColor(0, 0, 0, 0);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        glClearColor(0, 0, 0, 1);

}
void PlayState::OnDraw(double deltaTime)
{
    std::cout << "PlayState OnDraw" <<endl;

    //// set delta time
    CameraController* cam_delta;
     vector<Component*> controller_setTime;
    controller_setTime = World[0]->getComponents();
    cam_delta = dynamic_cast<CameraController*>( controller_setTime[2]);
    if (cam_delta == NULL)
        std::cout << "NULL CONTROLLER "<< endl;
    cam_delta->setDeltaTime(deltaTime);

    std::cout << "PlayState OnDraw  1" <<endl;

    ///// on update for each entity
    vector<Component*> comp;
    for (int i =0;i<World.size();i++)
    {
        comp = World[i]->getComponents();
        for (int j=0;j< comp.size() ;j++)
            comp[j]->onUpdate();
    }

        std::cout << "PlayState OnDraw  2" <<endl ;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RendererSystem* renderEntities = new RendererSystem();
    vector<Entity*> Entities;
    for (int i =1;i<World.size();i++)
    {
        Entities.push_back(World[i]);
    }
    
    
    std::cout << "PlayState OnDraw  3" <<endl;

    renderEntities->RenderAll(Entities,World[0]);

                std::cout << "PlayState OnDraw  4" <<endl;

        glClear(GL_DEPTH_BUFFER_BIT);

            std::cout << "PlayState OnDraw  END" <<endl;


}
void PlayState::OnExit()
{
    vector<Component*> comp;
    for (int i =0;i<World.size();i++)
    {
        comp = World[i]->getComponents();
        for (int j=0;j< comp.size() ;j++)
            comp[j]->onDeleteState();
    }
}