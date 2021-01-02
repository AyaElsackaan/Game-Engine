     #include "Sampler2D.h"

     Sampler2D::Sampler2D()
     {
         glGenSamplers(1, &sampler);
        glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, magnification_filter);
        glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, minification_filter);
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrap_s);
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrap_t);
        glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);

     }
     void Sampler2D::bind(int unit)
     {
        glBindSampler(unit, sampler);

     }
     Sampler2D::~Sampler2D()
     {
        glDeleteSamplers(1, &sampler);
     }
