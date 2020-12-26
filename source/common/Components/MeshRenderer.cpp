#include "MeshRenderer.h"

 /* 



        wazefto eno be attach el mesh bl shader bta3 kol entity




*/
MeshRenderer::MeshRenderer(int ord,Material* mat,Mesh *m) : Component(ord) {
    this->model = m;
    material = mat;
}

void MeshRenderer::setMaterial(Material* mat)
{
    material = mat;
}

Material* MeshRenderer::getMaterial() const
{
    return material;
}

void MeshRenderer::setMesh(Mesh* m)
{
    this->model = m;
}

Mesh* MeshRenderer::getMesh() const
{
    return model;
}

void MeshRenderer::onStartApp() 
{
    
}

void MeshRenderer::onStartState() 
{
}
void MeshRenderer::onUpdate() 
{
}


void MeshRenderer::onDeleteState()
{
}

void MeshRenderer::onDeleteApp() 
{
    
}