

#ifndef GFX_LAB_STATEMANAGER_H
#define GFX_LAB_STATEMANAGER_H
#include <application.hpp>
#include <shader.hpp>
#include <iostream>
#include "./States/State.h"
using namespace std;


class StateManager : public GAME::Application {
private:
    State * CurrentState = NULL;
    State * NextState = NULL;
    bool exit = false;

public:
    void GoToState(State * NextState);

};



#endif //GFX_LAB_STATEMANAGER_H
