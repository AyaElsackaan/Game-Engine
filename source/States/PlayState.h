

#ifndef GFX_LAB_PLAYSTATE_H
#define GFX_LAB_PLAYSTATE_H
#include "State.h"
#include "../common/Entity.h"

class PlayState : public State{
    vector <Entity*> World;
        ShaderProgram program;
        Mesh model;

        public:
    PlayState();
    void OnEnter() override;
    void OnDraw() override;
    void OnExit() override;
};


#endif //GFX_LAB_PLAYSTATE_H
