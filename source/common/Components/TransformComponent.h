//
// Created by AG on 26-Nov-20.
//

#ifndef GFX_LAB_TRANSFORMCOMPONENT_H
#define GFX_LAB_TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

#include "Component.h"
class TransformComponent: public Component {
private:
    glm::vec3 postion;
    glm::vec3 rotation;
    glm::vec3 scale;
    //???parent
    /*
     * Parent: It can be a pointer to its parent entity or the transform component of it’s parent entity. For data oriented ECS, it can be the id (an integer) of the parent entity. This is used to define the scene graph.
     */
public:
     void onStartApp() override ; //virtual/pure virtual>> to be modified
     void onStartState() override;
     void onUpdate() override;
     void onDeleteApp() override;
     void onDeleteState() override;

};


#endif //GFX_LAB_TRANSFORMCOMPONENT_H
