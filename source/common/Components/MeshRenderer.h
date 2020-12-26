#ifndef GFX_LAB_MESHRENDERER_H
#define GFX_LAB_MESHRENDERER_H

#include <glm/glm.hpp>
#include "Component.h"
#include <mesh/mesh.hpp>
#include <mesh/mesh-utils.hpp>
#include "../common/Material.hpp"

using namespace GAME;

class MeshRenderer: public Component {
private:
    Mesh *model;
    Material* material;

public:
    MeshRenderer( int ord,Material* mat,Mesh *m);
    void setMesh(Mesh* m);
    Mesh* getMesh() const;
    void setMaterial(Material* mat);  
    Material* getMaterial() const;
    void onStartApp() override ; //virtual/pure virtual>> to be modified
    void onStartState() override;
    void onUpdate() override;
    void onDeleteApp() override;
    void onDeleteState() override;


};
#endif //GFX_LAB_TRANSFORMCOMPONENT_H
