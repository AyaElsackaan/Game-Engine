#ifndef GFX_LAB_SAMPLER2D_H
#define GFX_LAB_SAMPLER2D_H
 

#include <imgui-utils/utils.hpp>
#include <texture/texture-utils.h>

class Sampler2D {

    private:
    // name, GLuint , Filters, set of textures for all mipmap level
     GLuint sampler;
          
    GLenum magnification_filter = GL_NEAREST, minification_filter = GL_NEAREST;
    GLenum wrap_s = GL_CLAMP_TO_EDGE, wrap_t = GL_CLAMP_TO_EDGE;

    GLfloat max_anisotropy = 1.0f;

    public:
     Sampler2D();
     void bind(int unit );
     ~Sampler2D();

     Sampler2D(Sampler2D const &) = delete;
     Sampler2D &operator=(Sampler2D const &) = delete;
    };

#endif //MATERIAL_H
