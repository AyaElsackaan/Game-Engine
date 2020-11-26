//
// Created by AG on 25-Nov-20.
//

#ifndef GFX_LAB_ENTITY_H
#define GFX_LAB_ENTITY_H

#include "Components/Component.h"
#include <bits/stdc++.h>

class Entity {
private:
    std::map <int, Component*> component_list;
    //int ID;
public:
    std::map <int, Component*> getComponents();
    void addComponent(Component* new_comp);
    void removeComponent(/*to be added*/);
};


#endif //GFX_LAB_ENTITY_H
