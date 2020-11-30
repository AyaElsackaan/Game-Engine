//
// Created by AG on 26-Nov-20.
//

#ifndef GFX_LAB_TRANSFORMCOMPONENT_H
#define GFX_LAB_TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

#include "Component.h"
class TransformComponent: public Component {
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;



public:
    TransformComponent( Entity *e, int ord, glm::vec3 pos, glm::vec3 rot,
                       glm::vec3 sc);
    glm:: mat4 to_mat4() const;
    void setScale(glm::vec3 sc);
    void setPosition(glm::vec3 pos);
    void setRotation(glm::vec3 rot);
    glm::vec3 getRotation() const;
    glm::vec3 getPosition() const;
    glm::vec3 getScale() const;

     void onStartApp() override ; //virtual/pure virtual>> to be modified
     void onStartState() override;
     void onUpdate() override;
     void onDeleteApp() override;
     void onDeleteState() override;

};


#endif //GFX_LAB_TRANSFORMCOMPONENT_H
