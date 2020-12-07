

#include "StateManager.h"
#include "./States/PlayState.h"
#include "./States/MenuState.h"


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
        PlayState* ps = new PlayState();

        CurrentState = ps;
    }

void StateManager::onDraw (double deltaTime)
{
    PlayState* ps;
    ps = dynamic_cast<PlayState*>( CurrentState);
    ps->OnDraw(deltaTime);
  //  MenuState* ms;
   // ps = dynamic_cast<MenuState*>(NextState);
   // ps->OnDraw(deltaTime);

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
        }
        CurrentState->OnEnter();
      //  CurrentState->OnDraw(delta);
    }

  // if(CurrentState != NULL)
  //      CurrentState->OnExit();

}

int main(int argc, char** argv)
{
    GAME::Application* app= new GAME::Application();
    PlayState* ps = new PlayState();
   // MenuState* ms = new MenuState();
    app->CurrentState = ps;
    app->NextState = NULL;

    return app->run();
    //return StateManager().run();
}