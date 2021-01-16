

#ifndef GFX_LAB_MENUSTATE_H
#define GFX_LAB_MENUSTATE_H
#include "State.h"
#include <application.hpp>
#include <shader.hpp>
#include <mesh/mesh.hpp>
#include "../common/Texture2D.h"
#include "../common/Sampler2D.h"
#include<unordered_map>

class MenuState : public State {

     GAME::ShaderProgram program;
     GLuint vertex_array=0;

    std::unordered_map<std::string, GLuint> textures;
    std::string current_texture_name;

    int level_of_detail=0;
    float zoom = 1;

     GLuint sampler;
     GLuint texture;
    
    GAME::Application* application;
    int Height;
    int Width;
   
    

public:
    MenuState();
    void setApplication(GAME::Application* app);
   
void setHeight(int h);

void setWidth(int w);
   
    virtual void OnEnter();
    virtual void OnDraw(double deltaTime);
    virtual void OnExit();
    //getKeyPressed();
};


#endif //GFX_LAB_MENUSTATE_H
