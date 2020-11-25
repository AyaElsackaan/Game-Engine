//
// Created by AG on 25-Nov-20.
//

#include "Component.h"

Entity *Component::getCurrentEntity() {
    return this->current_entity;
}

int Component::getOrder() {
    return this->order;
}
