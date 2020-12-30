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

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &texture);
}