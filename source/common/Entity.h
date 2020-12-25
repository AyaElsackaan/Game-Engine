//
// Created by AG on 25-Nov-20.
//

#ifndef GFX_LAB_ENTITY_H
#define GFX_LAB_ENTITY_H

#include "Components/Component.h"
//#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Entity {
private:
    // leha pointer 3ala awl el array bta3 el world
    std::vector<Component*> component_list;
    int ID;
public:
    std:: vector<Component*> getComponents() const;
    void setID(int id);
    int getID() const;
    void addComponent(Component* new_comp);
    void removeComponent(/*to be added*/);
};


#endif //GFX_LAB_ENTITY_H
