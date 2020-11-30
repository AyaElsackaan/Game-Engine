//
// Created by AG on 25-Nov-20.
//

#include "Entity.h"

std::vector<Component*> Entity::getComponents() const{
    return this->component_list;
}

void Entity::addComponent(Component* new_comp)
 {
     this->component_list.push_back(new_comp);
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
