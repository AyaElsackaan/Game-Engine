
#include <application.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <imgui-utils/utils.hpp>
#include <mesh/mesh-utils.hpp>

#include "PlayState.h"
#include "../common/RendererSystem.hpp"
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
    program.create();
    program.attach("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/shaders/ex11_transformation/transform.vert", GL_VERTEX_SHADER);
    program.attach("C:/Users/aliaa/Desktop/Phase 2/Game-Engine/assets/shaders/ex11_transformation/tint.frag", GL_FRAGMENT_SHADER);
    program.link();

 ///// Entity 1
    GAME::mesh_utils::Cuboid(model, true);


    Component* mesh=new MeshRenderer(0,&program,&model);


    glm::vec3 pos={-5,0,5};
    glm::vec3 rot={0,9,0};
    glm::vec3 sc={10,10,10};
    Component* transform=new TransformComponent(1,pos, rot, sc);

     TransformComponent* TempTrans;
    TempTrans = dynamic_cast<TransformComponent*>(transform);

    Entity* E1=new Entity();
    E1->addComponent(mesh);
    E1->addComponent(transform);
 ///// Entity 2
 
     GAME::mesh_utils::Sphere(model1);

    Component* mesh1 =new MeshRenderer(0,&program,&model1);

    glm::vec3 pos1={5,10,5};
    glm::vec3 rot1={0,9,0};
    glm::vec3 sc1={1,1,1};

    Component* transform1 =new TransformComponent(1,pos1, rot1, sc1);

    // sphere 
    TransformComponent* TempTransform;
    TempTransform = dynamic_cast<TransformComponent*>(transform1);
    TempTransform->setParent(TempTrans);


    Entity* E2=new Entity();
    E2->addComponent(mesh1);
    E2->addComponent(transform1);

    

    ///////////////////////

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

    Entity* camera=new Entity();
    camera->addComponent(transform_cam); // 0
    camera->addComponent(cam_component); // 1
    camera->addComponent(cam_controller); // 2


        World.push_back(camera);    // world[0]
        World.push_back(E1);        // world[1]
        World.push_back(E2);        // world[1]

        glClearColor(0, 1, 0, 0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        glClearColor(1, 0, 0, 1);

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

    renderEntities->RenderAll(World,World[0]);

        glClear(GL_DEPTH_BUFFER_BIT);


}
void PlayState::OnExit()
{
   //  this->Sprogram->destroy();
  //  this->model->destroy();
    program.destroy();
    model.destroy();
    model1.destroy();
    vector<Component*> comp;
    for (int i =0;i<World.size();i++)
    {
        comp = World[i]->getComponents();
        for (int j=0;j< comp.size() ;j++)
            comp[j]->onDeleteState();
    }
}