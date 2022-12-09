#include "Hallucen/GL/Texture2D.h"
#include "glad/glad.h"

using namespace Hallucen::GL;

Texture2D::Texture2D() { glGenTextures(1, &m_ID); }

void Texture2D::setImage(Hallucen::Image &image) {
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, image.data);
}

void Texture2D::bind(unsigned int index) {
  glActiveTexture(GL_TEXTURE0 + index);

  glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture2D::unBind() { glBindTexture(GL_TEXTURE_2D, 0); }

void Texture2D::genMipmap() { glGenerateMipmap(GL_TEXTURE_2D); }

Texture2D::~Texture2D() { glDeleteTextures(1, &m_ID); }