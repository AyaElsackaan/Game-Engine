

#ifndef GFX_LAB_PLAYSTATE_H
#define GFX_LAB_PLAYSTATE_H
#include "../common/Entity.h"
#include "State.h"
#include <application.hpp>
#include <shader.hpp>
#include <mesh/mesh.hpp>
#include "../common/Texture2D.h"
#include "../common/Sampler2D.h"
#include "../gameLogic/playerSystem.h"

struct SkyLight {
    bool enabled = true;
    glm::vec3 top_color = {0.25, 0.3, 0.5}, middle_color{0.35, 0.35, 0.4}, bottom_color{0.25, 0.25, 0.25};
};

class PlayState : public State {

    playerSystem* player;
    vector <Entity*> World;
    vector <Entity*> lights;
    GAME::ShaderProgram program, sky_program;
    SkyLight sky_light;
    float sky_box_exposure = 2.0f;
    std::unordered_map<std::string, std::unique_ptr<GAME::Mesh>> meshes;
    std::unordered_map<std::string, Texture2D*> textures;
    GLuint sampler;
    double generateTimer=0;
    int counter=180;
    int bottleTime=0;
    int bottleCounter = 400;
    int health = 100;
    int finishFlag =0;
    GAME::Application* application;
    int Height;
    int Width;

    public:

    PlayState();
    void setApplication(GAME::Application* app);
     void setHeight(int h);
    void setWidth(int w);
    void generateCorona();
  //  int getHeight();
  //  int getWidth();
    int getHealth();
    int getfinishFlag();
    void OnEnter() ;
    void OnDraw(double deltaTime);
    void OnExit();
};


#endif //GFX_LAB_PLAYSTATE_H
