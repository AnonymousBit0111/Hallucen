
#include "Hallucen/GL/Framebuffer.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/Hallucen.h"
#include "Hallucen/vector.h"
#include "glad/glad.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace Hallucen;
using namespace Hallucen::GL;

Framebuffer::Framebuffer(Vector2 size, Vector2 pos)
    : m_Position(pos), m_Size(size) {
  // TODO maybe use a renderbuffer for some performance?
  glGenFramebuffers(1, &m_ID);
  bind();
  m_Tex = std::make_shared<Texture2D>();

  m_Tex->bind(1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         m_Tex->getID(), 0);
  textureAttached = true;

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "COMPLETE\n";
  }

  unBind();
}

void Framebuffer::bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
  //   m_Tex->bind(1);
}

void Framebuffer::setSize(Vector2 size) { m_Size = size; }

void Framebuffer::bindTexture() { m_Tex->bind(1); }
void Framebuffer::bindRead() { glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ID); }
void Framebuffer::bindDraw() { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_ID); }
void Framebuffer::blit(Vector2i frameBuffer) {
  glBlitFramebuffer(0, 0, m_Size.x, m_Size.y, 0, 0, frameBuffer.x,
                    frameBuffer.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void Framebuffer::unBind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

Framebuffer::~Framebuffer() {
  glDeleteFramebuffers(1, &m_ID);
  unBind();
}