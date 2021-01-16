#ifndef GFX_LAB_TEXTURE2D_H
#define GFX_LAB_TEXTURE2D_H
 

#include <imgui-utils/utils.hpp>
#include <texture/texture-utils.h>
#include <glm/gtx/euler_angles.hpp>

class Texture2D {

    private:
    // name, GLuint , Filters, set of textures for all mipmap level
    GLuint texture;
     std::string name;
     // Ahoto fl sampler

    public:
     Texture2D(const char* path);
     void bind();
     ~Texture2D();
  //  void resize(int,int);
     Texture2D(Texture2D const &) = delete;
     Texture2D &operator=(Texture2D const &) = delete;
    
    };

#endif //MATERIAL_H
