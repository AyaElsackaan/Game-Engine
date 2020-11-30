//
// Created by AG on 25-Nov-20.
//

#include "Components/Component.h"

Entity *Component::getCurrentEntity() const {
    return this->current_entity;
}

int Component::getOrder() const{
    return this->order;
}
 void Component::setparent(Entity* e)
 {
     this->parent = e;
 }
    Entity* Component::getparent() const
    {
        return this->parent;
    }
Component::Component(Entity *e, int ord) {
    this->current_entity=e;
    this->order=ord;
}
