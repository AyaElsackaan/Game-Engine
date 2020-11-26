//
// Created by AG on 25-Nov-20.
//

#include "Component.h"

Entity *Component::getCurrentEntity() const {
    return this->current_entity;
}

int Component::getOrder() const{
    return this->order;
}

Component::Component(Entity *e, int ord) {
    this->current_entity=e;
    this->order=ord;
}
