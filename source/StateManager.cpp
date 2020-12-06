

#include "StateManager.h"
#include "./States/PlayState.h"

    StateManager::StateManager()
    {
        PlayState* ps = new PlayState();

        CurrentState = ps;
    }

void StateManager::onDraw (double deltaTime)
{
    std::cout <<"StateManager Draw" <<endl;
    PlayState* ps;
    ps = dynamic_cast<PlayState*>( CurrentState);
    ps->OnDraw(deltaTime);

}
void StateManager:: onInitialize ()
{
        std::cout <<"StateManager INIT" <<endl;
        int w,h;
        glfwGetFramebufferSize(window, &w, &h);
        std::cout << "Width :" << w <<endl;
        std::cout << "Height :" << h <<endl;

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
       // if(CurrentState != NULL)
           // CurrentState->OnDraw();
    }

    if(CurrentState != NULL)
        CurrentState->OnExit();
}

int main(int argc, char** argv)
 {

    return StateManager().run();
}