//
// Created by AG on 26-Nov-20.
//

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/euler_angles.hpp>
#include <iostream>
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
                                       glm::vec3 sc, TransformComponent* p) : Component(ord) 
{
    this->position=pos;
    this->rotation=rot;
    this->scale=sc;
    parent=p;

}

glm::mat4 TransformComponent::to_mat4() const {
    if (parent == NULL)
    {
        return glm::translate(glm::mat4(1.0f),position) * glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) *glm::scale(glm::mat4(1.0f), scale);
    }
    else
    {
   // std::cout << "Parent Pos matrix " << (parent->to_mat4() * glm::vec4 {0,0,0,1}).x << "," << (parent->to_mat4() * glm::vec4 {0,0,0,1}).y <<" "<< (parent->to_mat4() * glm::vec4 {0,0,0,1}).z <<std::endl;

       return  parent->to_mat4()* (glm::translate(glm::mat4(1.0f),position) * glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) *glm::scale(glm::mat4(1.0f), scale)) ;
    }
}
void TransformComponent::setScale(glm::vec3 sc)
{
    
    this->scale = sc;
    this->to_mat4();
}
void TransformComponent::setPosition(glm::vec3 pos)
{
    this->position = pos;
    this->to_mat4();
}
void TransformComponent::setRotation(glm::vec3 rot)
{
    this->rotation = rot;
    this->to_mat4();
}
glm::vec3 TransformComponent::getRotation() const
{
  //  return this->to_mat4() * glm::vec4{0,1,0,0};
    return this->rotation;
}
glm::vec3 TransformComponent::getPosition() const
{
 //   return (((glm::translate(glm::mat4(1.0f),position)) * parent->to_mat4()) * glm::vec4{0,0,0,1});
//  if (parent != NULL)
//  {
//    //  std::cout << "Parent Pos matrix " << (parent->to_mat4() * glm::vec4 {0,0,0,1}).x << "," << (parent->to_mat4() * glm::vec4 {0,0,0,1}).y <<" ,"<< (parent->to_mat4() * glm::vec4 {0,0,0,1}).z <<std::endl;
//      std::cout << "position " << (this->to_mat4() *  parent->to_mat4()*  glm::vec4{0,0,0,1}).x << "," << (this->to_mat4() *  parent->to_mat4()*  glm::vec4{0,0,0,1}).y <<", "<< (this->to_mat4() *  parent->to_mat4() *  glm::vec4{0,0,0,1}).z <<std::endl;
//    // this->position = glm::vec3(( this->to_mat4() * parent->to_mat4() )* glm::vec4{0,0,0,1});
//    return ( this->to_mat4() * parent->to_mat4() )* glm::vec4{0,0,0,1};
//  }
    return  this->to_mat4() *  glm::vec4{0,0,0,1};
   //return this->position;
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
