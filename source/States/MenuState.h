

#ifndef GFX_LAB_MENUSTATE_H
#define GFX_LAB_MENUSTATE_H
#include "State.h"

class MenuState : public State {
public:
    MenuState();
    virtual void OnEnter();
    virtual void OnDraw();
    virtual void OnExit();
};


#endif //GFX_LAB_MENUSTATE_H
