#include "MeshRenderer.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"
MeshRenderer::MeshRenderer( Entity *e, int ord, ShaderProgram * S,Mesh *m) : Component(e, ord) {
    this->Sprogram = S;
    this->model = m;

}

void MeshRenderer::setShader(ShaderProgram * S)
{
    this->Sprogram = S;
}
void MeshRenderer::setMesh(Mesh* m)
{
    this->model = m;
}
ShaderProgram* MeshRenderer::getShader()
{
    return this->Sprogram;
}
Mesh* MeshRenderer::getMesh()
{
    return model;
}

void MeshRenderer::onStartApp() 
{
    
}

void MeshRenderer::onStartState() 
{
    this->Sprogram->create();
    this->Sprogram->attach("assets/shaders/ex11_transformation/transform.vert", GL_VERTEX_SHADER);
    this->Sprogram->attach("assets/shaders/ex11_transformation/tint.frag", GL_FRAGMENT_SHADER);
    this->Sprogram->link();
}  
void MeshRenderer::onUpdate() 
{

// Transform 0 , MeshRenderer 1 , Camera 2
    map<int,Component*> m = this->getCurrentEntity()->getComponents();
    TransformComponent* tranf = dynamic_cast<TransformComponent*>(m[0]);
    CameraComponent* cam = dynamic_cast<CameraComponent*>(m[2]);
    this->Sprogram->set("tranform", cam->getVPMatrix() * tranf->to_mat4());
    this->model->draw();
}


void MeshRenderer::onDeleteState()
{
    this->Sprogram->destroy();
    this->model->destroy();
}

void MeshRenderer::onDeleteApp() 
{
    
}