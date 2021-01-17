#include "MenuState.h"

MenuState::MenuState(int menu)
{
    current_Menu=menu;
}

void MenuState::setApplication(GAME::Application* app)
 {
      this->application = app;
 }

void MenuState::setHeight(int h)
 {
     Height = h;
 }
void MenuState::setWidth(int w)
{
    Width = w;
}
void MenuState::OnEnter()
{
    program.create();
    program.attach("../../assets/shaders/fullscreen_triangle.vert", GL_VERTEX_SHADER);
    program.attach("../../assets/shaders/texel_fetch.frag", GL_FRAGMENT_SHADER);
    program.link();
   
    glGenVertexArrays(1, &vertex_array);
   
    glGenTextures(1, &texture);
    GAME::texture_utils::loadImage(texture, "../../assets/images/common/MainMenu.jpg");
    textures["mainmenu"] = texture;

    glGenTextures(1, &texture);
    GAME::texture_utils::loadImage(texture, "../../assets/images/common/GameOverMenu.JPG");
    textures["gameover"] = texture;

    glGenTextures(1, &texture);
    GAME::texture_utils::loadImage(texture, "../../assets/images/common/NextLevelMenu.JPG");
    textures["nextlevel"] = texture; 
    
    glGenTextures(1, &texture);
    GAME::texture_utils::loadImage(texture, "../../assets/images/common/WonMenu.JPG");
    textures["Won"] = texture;

    if (current_Menu==0)
        current_texture_name = "mainmenu";
    else if (current_Menu==1)
        current_texture_name = "gameover";
    else if (current_Menu==2)
        current_texture_name = "nextlevel";
    else if (current_Menu==3)
        current_texture_name = "Won";

    glClearColor(0, 0, 0, 1);
}

void MenuState::OnDraw(double deltaTime)
{
        glUseProgram(program);

        glClear(GL_COLOR_BUFFER_BIT);

        GLuint texture = textures[current_texture_name];

        glActiveTexture(GL_TEXTURE0);
   
        glBindTexture(GL_TEXTURE_2D, texture);
     
        program.set("sampler", 0);
        program.set("lod", level_of_detail);
        program.set("zoom", zoom);

        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

}
void MenuState::OnExit()
{
     program.destroy();
        glDeleteVertexArrays(1, &vertex_array);
        for(const auto& [name, texture] : textures)
            glDeleteTextures(1, &texture);
        textures.clear();
}
int MenuState::getCurrentMenu()
{
    return current_Menu;
}
