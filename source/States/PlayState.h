

#ifndef GFX_LAB_PLAYSTATE_H
#define GFX_LAB_PLAYSTATE_H
#include "../common/Entity.h"
#include "State.h"
#include <application.hpp>
#include <shader.hpp>
#include <mesh/mesh.hpp>
#include "../common/Texture2D.h"
#include "../common/Sampler2D.h"
struct SkyLight {
    bool enabled;
    glm::vec3 top_color, middle_color, bottom_color;
};

class PlayState : public State {


    vector <Entity*> World;
    vector <Entity*> lights;
    GAME::ShaderProgram program, sky_program;
    SkyLight sky_light;
    float sky_box_exposure = 2.0f;
    std::unordered_map<std::string, std::unique_ptr<GAME::Mesh>> meshes;
    std::unordered_map<std::string, Texture2D*> textures;
    GLuint sampler;


    GAME::Application* application;
    int Height;
    int Width;

    public:

    PlayState();
    void setApplication(GAME::Application* app);
     void setHeight(int h);
    void setWidth(int w);
  //  int getHeight();
  //  int getWidth();
    void OnEnter() ;
    void OnDraw(double deltaTime);
    void OnExit();
};


#endif //GFX_LAB_PLAYSTATE_H
