

#include "StateManager.h"
#include "./States/PlayState.h"
#include "./States/MenuState.h"
#include "./States/State.h"


void StateManager::setNext(State * ns)
{
    NextState = ns;
}
State* StateManager::getCurrent()
{
    return CurrentState;
}
State* StateManager::getNext()
{
    return NextState;
}

   GAME::WindowConfiguration StateManager::getWindowConfiguration(){
        return { "our GAME", {1280, 720}, false };
    }
    StateManager::StateManager()
    {
        MenuState* ms = new MenuState();

        CurrentState = ms;
    }

void StateManager::onDraw (double deltaTime)
{
    /*PlayState* ps = dynamic_cast<PlayState*>( CurrentState);
    if(ps)
        ps->OnDraw(deltaTime);
    else
    {
        MenuState* ms = dynamic_cast<MenuState*>( CurrentState); 
        ms->OnDraw(deltaTime);
    }*/
    CurrentState->OnDraw(deltaTime);
    
  

}
void StateManager:: onInitialize ()
{
            int w,h;
            glfwGetFramebufferSize(window, &w, &h);
            MenuState* ms;
            ms = dynamic_cast<MenuState*>( CurrentState);
            ms->setHeight(h);
            ms->setWidth(w);
            ms->setApplication(this);
            ms->OnEnter();

}
void StateManager:: onDestroy ()
{
       /* PlayState* ps;
        ps = dynamic_cast<PlayState*>( CurrentState);
        ps->OnExit();*/
        CurrentState->OnExit();
}

void StateManager::GoToState (State * NextState){
   while(!exit) {
        if(NextState != NULL)
        {
            if(CurrentState != NULL)
                CurrentState->OnExit();

            CurrentState = NextState;
            NextState = NULL;
        }
        CurrentState->OnEnter();
    }

}

int main(int argc, char** argv)
{
    GAME::Application* app= new GAME::Application();
    PlayState* ps = new PlayState();
    MenuState* ms = new MenuState();
    app->CurrentState = ms;
    app->NextState = NULL;

    return app->run();
    //return StateManager().run();
}