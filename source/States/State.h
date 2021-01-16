
#ifndef GFX_LAB_STATE_H
#define GFX_LAB_STATE_H



class State  {
    public:
        virtual void OnEnter() = 0;
        virtual void OnDraw(double deltaTime) = 0;
        virtual void OnExit() = 0;
       /* virtual void setApplication(GAME::Application* app)=0;
        virtual void setHeight(int h)=0;
        virtual void setWidth(int w)=0;*/
};


#endif //GFX_LAB_STATE_H
