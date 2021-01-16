#include "Texture2D.h"

Texture2D::Texture2D(const char* path)
{
  glGenTextures(1, &texture);
 // glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f);

  GAME::texture_utils::loadImage(texture, path);
}

void Texture2D::bind()
{
      glBindTexture(GL_TEXTURE_2D,texture);
}
// void Texture2D::resize(int w,int h)
// {
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
// }

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &texture);
}