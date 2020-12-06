

#include "StateManager.h"
#include "./States/PlayState.h"
   GAME::WindowConfiguration StateManager::getWindowConfiguration(){
        return { "our GAME", {1280, 720}, false };
    }
    StateManager::StateManager()
    {
        PlayState* ps = new PlayState();

        CurrentState = ps;
    }

void StateManager::onDraw (double deltaTime)
{
    PlayState* ps;
    ps = dynamic_cast<PlayState*>( CurrentState);
    ps->OnDraw(deltaTime);

}
void StateManager:: onInitialize ()
{
        int w,h;
        glfwGetFramebufferSize(window, &w, &h);

        PlayState* ps;
        ps = dynamic_cast<PlayState*>( CurrentState);
        ps->setHeight(h);
        ps->setWidth(w);
        ps->setApplication(this);
        ps->OnEnter();
}
void StateManager:: onDestroy ()
{
        PlayState* ps;
        ps = dynamic_cast<PlayState*>( CurrentState);
        ps->OnExit();
}

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
    }

    if(CurrentState != NULL)
        CurrentState->OnExit();
}

int main(int argc, char** argv)
 {

    return StateManager().run();
}