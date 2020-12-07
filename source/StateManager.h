

#ifndef GFX_LAB_STATEMANAGER_H
#define GFX_LAB_STATEMANAGER_H
#include <application.hpp>
#include <shader.hpp>
#include <iostream>
#include "./States/State.h"

class StateManager : public GAME::Application {
private:
    State* CurrentState = NULL;
    State * NextState = NULL;
    bool exit = false;

public:

    StateManager();
    void GoToState(State * NextState);
    void setNext(State * ns);
    //void setCurrent(State * ps);
    State* getCurrent();
    State* getNext();

    GAME::WindowConfiguration getWindowConfiguration() override;
    void onDraw(double deltaTime) override;
    void onDestroy() override;
    void onInitialize() override;
};



#endif //GFX_LAB_STATEMANAGER_H
