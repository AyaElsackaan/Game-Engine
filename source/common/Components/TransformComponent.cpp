//
// Created by AG on 26-Nov-20.
//

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/euler_angles.hpp>

#include "TransformComponent.h"

void TransformComponent::onStartApp() {

}

void TransformComponent::onStartState() 
{

}

void TransformComponent::onUpdate() 
{
    this->to_mat4();
}

void TransformComponent::onDeleteApp() {

}

void TransformComponent::onDeleteState() {

}

TransformComponent::TransformComponent(int ord, glm::vec3 pos, glm::vec3 rot,
                                       glm::vec3 sc) : Component(ord) 
{
    this->position=pos;
    this->rotation=rot;
    this->scale=sc;
    parent=NULl;

}

glm::mat4 TransformComponent::to_mat4() const {
    if(parent)
    {
        return glm::translate(parent->to_mat4(), position) *
               glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) *
               glm::scale(parent->to_mat4(), scale);
    }
    return glm::translate(glm::mat4(1.0f), position) *
           glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) *
           glm::scale(glm::mat4(1.0f), scale);

}
void TransformComponent::setScale(glm::vec3 sc)
{
    this->scale = sc;
}
void TransformComponent::setPosition(glm::vec3 pos)
{
    this->position = pos;
}
void TransformComponent::setRotation(glm::vec3 rot)
{
    this->rotation = rot;
}
glm::vec3 TransformComponent::getRotation() const
{
    return this->rotation;
}
glm::vec3 TransformComponent::getPosition() const
{
    return this->position;
}
glm::vec3 TransformComponent::getScale() const
{
    return this->scale;
}
TransformComponent* TransformComponent::getParent()const
{
    return this->parent;
}
void TransformComponent::setParent(TransformComponent* P)
{
    parent=P;
}
