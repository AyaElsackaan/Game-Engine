#include <application.hpp>
#include <shader.hpp>
#include <iostream>
using namespace std;

class UniformsApplication : public GAME::Application {

    //GAME::ShaderProgram program;
    /////////////////////////////////////
    GAME::ShaderProgram program1;
GAME::ShaderProgram program2;
GAME::ShaderProgram program3;
GAME::ShaderProgram program4;
    /////////////////////////////////////
    GLuint vertex_array = 0;

    glm::vec2 scale = glm::vec2(1,1);
    glm::vec2 key = glm::vec2(1,0);
    glm::vec2 mousePos = glm::vec2(0,0);
    GAME::WindowConfiguration getWindowConfiguration() override {
        return { "Shapes", {1280, 720}, false };
    }

    void onInitialize() override {
        program1.create();
        program1.attach("G:/Engineering/senior1/graphics/Phase1_V1/assets/draw_shapes.vert", GL_VERTEX_SHADER);
        program1.attach("G:/Engineering/senior1/graphics/Phase1_V1/assets/face.frag", GL_FRAGMENT_SHADER);
        program1.link();

        program2.create();
        program2.attach("G:/Engineering/senior1/graphics/Phase1_V1/assets/draw_shapes.vert", GL_VERTEX_SHADER);
        program2.attach("G:/Engineering/senior1/graphics/Phase1_V1/assets/pacman.frag", GL_FRAGMENT_SHADER);
        program2.link();

        program3.create();
        program3.attach("G:/Engineering/senior1/graphics/Phase1_V1/assets/draw_shapes.vert", GL_VERTEX_SHADER);
        program3.attach("G:/Engineering/senior1/graphics/Phase1_V1/assets/heart.frag", GL_FRAGMENT_SHADER);
        program3.link();

        program4.create();
        program4.attach("G:/Engineering/senior1/graphics/Phase1_V1/assets/draw_shapes.vert", GL_VERTEX_SHADER);
        program4.attach("G:/Engineering/senior1/graphics/Phase1_V1/assets/g.frag", GL_FRAGMENT_SHADER);
        program4.link();

        glGenVertexArrays(1, &vertex_array);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void onDraw(double deltaTime) override {
        glClear(GL_COLOR_BUFFER_BIT);
        if (key.x == 1) //face
        {
        glUseProgram(program1);

                GLuint scale_uniform_location = glGetUniformLocation(program1, "scale");
        glUniform2f(scale_uniform_location, scale.x, scale.y);
        
        GLuint mousePos_uniform_location = glGetUniformLocation(program1, "mousePos");
        glUniform2f(mousePos_uniform_location, mousePos.x, mousePos.y);

        GLuint key_uniform_location = glGetUniformLocation(program1, "key");
        glUniform2f(key_uniform_location,key.x,key.y);
        }
         if (key.x == 2) //pacman
        {
        glUseProgram(program2);
       
         GLuint scale_uniform_location = glGetUniformLocation(program2, "scale");
        glUniform2f(scale_uniform_location, scale.x, scale.y);
        
        GLuint mousePos_uniform_location = glGetUniformLocation(program2, "mousePos");
        glUniform2f(mousePos_uniform_location, mousePos.x, mousePos.y);

        GLuint key_uniform_location = glGetUniformLocation(program2, "key");
        glUniform2f(key_uniform_location,key.x,key.y);
        }
         if (key.x == 3) //heart
         {
            
        glUseProgram(program3);
                GLuint scale_uniform_location = glGetUniformLocation(program3, "scale");
        glUniform2f(scale_uniform_location, scale.x, scale.y);
        
        GLuint mousePos_uniform_location = glGetUniformLocation(program3, "mousePos");
        glUniform2f(mousePos_uniform_location, mousePos.x, mousePos.y);

        GLuint key_uniform_location = glGetUniformLocation(program3, "key");
        glUniform2f(key_uniform_location,key.x,key.y);
  
        }
         if (key.x == 4) //g
        {
        glUseProgram(program4);
               GLuint scale_uniform_location = glGetUniformLocation(program4, "scale");
        glUniform2f(scale_uniform_location, scale.x, scale.y);
        
        GLuint mousePos_uniform_location = glGetUniformLocation(program4, "mousePos");
        glUniform2f(mousePos_uniform_location, mousePos.x, mousePos.y);

        GLuint key_uniform_location = glGetUniformLocation(program4, "key");
        glUniform2f(key_uniform_location,key.x,key.y);
        }

       

        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    void onDestroy() override {
        program1.destroy();
        program2.destroy();
        program3.destroy();
        program4.destroy();

        glDeleteVertexArrays(1, &vertex_array);
    }

    void onImmediateGui(ImGuiIO &io) override {

        if (keyboard.isPressed(49))
        {
            key.x = 1;
        }
        else if (keyboard.isPressed(50))
        {
            key.x = 2;
        }
        else if (keyboard.isPressed(51))
        {
            key.x = 3;
        }
        else if (keyboard.isPressed(52))
        {
            key.x =4;
        }
        //cout << key.x;
        mousePos = mouse.getMousePosition();

    }
};

int main(int argc, char** argv) {
    return UniformsApplication().run();
}
