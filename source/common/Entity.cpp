//
// Created by AG on 25-Nov-20.
//

#include "Entity.h"

std::map<int, Component*> Entity::getComponents() const{
    return this->component_list;
}

void Entity::addComponent(Component* new_comp) {
    component_list[new_comp->getOrder()]=new_comp;
}

void Entity::removeComponent() {

}
void Entity::setID(int id)
{
    this->ID = id;
}
int Entity::getID() const
{
    return this->ID;
}
