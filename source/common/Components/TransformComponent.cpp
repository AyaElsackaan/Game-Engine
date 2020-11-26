//
// Created by AG on 26-Nov-20.
//

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/euler_angles.hpp>

#include "TransformComponent.h"

void TransformComponent::onStartApp() {

}

void TransformComponent::onStartState() {

}

void TransformComponent::onUpdate() {

}

void TransformComponent::onDeleteApp() {

}

void TransformComponent::onDeleteState() {

}

TransformComponent::TransformComponent( Entity *e, int ord, glm::vec3 pos, glm::vec3 rot,
                                       glm::vec3 sc) : Component(e, ord) {
    this->position=pos;
    this->rotation=rot;
    this->scale=sc;

}

glm::mat4 TransformComponent::to_mat4() const {
    return glm::translate(glm::mat4(1.0f), position) *
           glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) *
           glm::scale(glm::mat4(1.0f), scale);

}
