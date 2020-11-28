//
// Created by AG on 25-Nov-20.
//

#ifndef GFX_LAB_COMPONENT_H
#define GFX_LAB_COMPONENT_H

#include "./Entity.h"


class Component {
private:
    Entity * current_entity;
    int order;
public:
    Component(Entity* e, int ord);
    Entity* getCurrentEntity() const;
    int getOrder() const;

    virtual void onStartApp() = 0; //virtual/pure virtual>> to be modified
    virtual void onStartState()=0;
    virtual void onUpdate()=0;  //frames
    virtual void onDeleteApp()=0;
    virtual void onDeleteState()=0;
};


#endif //GFX_LAB_COMPONENT_H
