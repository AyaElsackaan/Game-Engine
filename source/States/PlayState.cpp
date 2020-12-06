

#include "PlayState.h"
#include "../common//Components//MeshRenderer.h"
#include "../common//Components//TransformComponent.h"
#include "../common//Components//CameraComponent.h"
#include "../common//Components//CameraControllerComponent.h"
PlayState::PlayState(){

}
void PlayState::OnEnter()
{

    program.create();
    program.attach("assets/shaders/ex11_transformation/transform.vert", GL_VERTEX_SHADER);
    program.attach("assets/shaders/ex11_transformation/tint.frag", GL_FRAGMENT_SHADER);
    program.link();

    Component* mesh=new MeshRenderer(0,program,model);
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

    Entity* camera=new Entity();
    camera->addComponent(transform_cam);
    camera->addComponent(cam_component);
    camera->addComponent(cam_controller);



}
void PlayState::OnDraw()
{

}
void PlayState::OnExit()
{

}