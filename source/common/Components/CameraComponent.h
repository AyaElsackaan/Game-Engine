//
// Created by AG on 26-Nov-20.
//

#ifndef GFX_LAB_CAMERACOMPONENT_H
#define GFX_LAB_CAMERACOMPONENT_H

#include <glm/gtx/euler_angles.hpp>
#include "Component.h"

class CameraComponent:public Component {
private:
    glm::vec3 eye; //position of camera
    glm::vec3 center; //position we look at
    glm::vec3 up;

    bool is_perspective;

    // Common camera projection properties
    float near, far;
    float aspect_ratio;

    // "Perspective camera"-only properties
    float vertical_field_of_view_angle;

    // "Orthographic camera"-only properties
    float orthographic_height;

public:

    CameraComponent(Entity *e, int ord, glm::vec3 eye, glm::vec3 center, glm::vec3 up,
                    bool is_perspective, float near, float far, float aspect_ratio,
                    float vertical_field_of_view_angle, float orthographic_height);
    void onStartApp() override ; //virtual/pure virtual>> to be modified
    void onStartState() override;
    void onUpdate() override;
    void onDeleteApp() override;
    void onDeleteState() override;

};


#endif //GFX_LAB_CAMERACOMPONENT_H
