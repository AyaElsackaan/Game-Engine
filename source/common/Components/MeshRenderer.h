#ifndef GFX_LAB_MESHRENDERER_H
#define GFX_LAB_MESHRENDERER_H

#include <glm/glm.hpp>
#include "Component.h"
#include <mesh/mesh.hpp>
#include <shader.hpp>
#include <mesh/mesh-utils.hpp>
using namespace GAME;

class MeshRenderer: public Component {
private:
    ShaderProgram * Sprogram;
    Mesh *model;

public:
    MeshRenderer( int ord, ShaderProgram * S,Mesh *m);
    void setShader(ShaderProgram * S);
    void setMesh(Mesh* m);
    ShaderProgram* getShader() const;
    Mesh* getMesh() const;
    void onStartApp() override ; //virtual/pure virtual>> to be modified
    void onStartState() override;
    void onUpdate() override;
    void onDeleteApp() override;
    void onDeleteState() override;


};
#endif //GFX_LAB_TRANSFORMCOMPONENT_H
