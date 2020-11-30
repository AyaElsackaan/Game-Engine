//
// Created by AG on 25-Nov-20.
//

#include "Components/Component.h"


int Component::getOrder() const
{
    return this->order;
}

Component::Component(int ord) {
    this->order=ord;
}
