
#ifndef GFX_LAB_STATE_H
#define GFX_LAB_STATE_H


class State  {
    public:
        virtual void OnEnter() = 0;
        virtual void OnDraw(double deltaTime) = 0;
        virtual void OnExit() = 0;
};


#endif //GFX_LAB_STATE_H
