//
// Created by AG on 26-Nov-20.
//

#include "CameraComponent.h"

CameraComponent::CameraComponent(Entity *e, int ord, glm::vec3 eye, glm::vec3 center, glm::vec3 up,
                                 bool is_perspective, float near, float far, float aspect_ratio,
                                 float vertical_field_of_view_angle, float orthographic_height) : Component(e, ord) {
    this-> eye=eye;
    this-> center=center;
    this->up=up;
    this-> is_perspective=is_perspective;
    this-> near=near;
    this-> far=far;
    this-> aspect_ratio=aspect_ratio;
    this-> vertical_field_of_view_angle=vertical_field_of_view_angle;
    this-> orthographic_height=orthographic_height;

}

void CameraComponent::onStartApp() {

}

void CameraComponent::onStartState() {

}

void CameraComponent::onUpdate() {

}

void CameraComponent::onDeleteApp() {

}

void CameraComponent::onDeleteState() {

}
