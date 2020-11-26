

#include "StateManager.h"

void StateManager::GoToState (State * NextState){
    while(!exit) {
        if(NextState != NULL)
        {
            if(CurrentState != NULL)
                CurrentState->OnExit();

            CurrentState = NextState;
            NextState = NULL;
            CurrentState->OnEnter();
        }
        if(CurrentState != NULL)
            CurrentState->OnDraw();
    }

    if(CurrentState != NULL)
        CurrentState->OnExit();
}

int main(int argc, char** argv) {
    return StateManager().run();
}