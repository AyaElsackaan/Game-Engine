

#ifndef GFX_LAB_PLAYSTATE_H
#define GFX_LAB_PLAYSTATE_H
#include "State.h"

class PlayState : public State{
public:
    PlayState();
    virtual void OnEnter();
    virtual void OnDraw();
    virtual void OnExit();
};


#endif //GFX_LAB_PLAYSTATE_H
