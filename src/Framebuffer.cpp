#include "Hallucen/GL/Framebuffer.h"
#include "Hallucen/GL/Texture2D.h"
#include "Hallucen/Hallucen.h"
#include "glad/glad.h"
#include "imgui.h"
#include <cassert>
#include <memory>

using namespace Hallucen;
using namespace Hallucen::GL;

Framebuffer::Framebuffer(unsigned int width, unsigned int height)
    : m_Width(width), m_Height(height) {
  glGenFramebuffers(1, &m_ID);
}

bool Framebuffer::isComplete() {
  bind();
  auto a = (glCheckFramebufferStatus(GL_FRAMEBUFFER));

  switch (a) {

  case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
    Hallucen::log("INCOMPLETE ATTACHMENT");
  case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
    Hallucen::log("MISSING ATTACHMENT");

  case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
    Hallucen::log("INCOMPLETE DRAW BUFFER");
  case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
    Hallucen::log("INCOMPLETE READ BUFFER");

  case GL_FRAMEBUFFER_UNSUPPORTED:
    Hallucen::log("FRAMEBUFFER UNSUPPORTED");
  case GL_FRAMEBUFFER_COMPLETE:
    Hallucen::log("FRAMEBUFFER GOOD");

    return true;
  default:
    return false;
  }
  unBind();

  return false;
}

void Framebuffer::bind() {
  // maybe split up into read and write?
  glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
}

void Framebuffer::unBind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

void Framebuffer::attachTexture2D(std::shared_ptr<Texture2D> tex) {
  m_ColourAtachment = tex;
  m_ColourAtachment->bind(1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         m_ColourAtachment->getID(), 0);
}
void Framebuffer::attachRenderBuffer(RenderBuffer buffer) {
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                            GL_RENDERBUFFER, buffer.getID());
}

void Framebuffer::blit(unsigned int DrawfboID) {

  glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ID);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, ImGui::GetWindowWidth(),
                    ImGui::GetWindowHeight(), GL_COLOR_BUFFER_BIT, GL_LINEAR);
  unBind();
}

Framebuffer::~Framebuffer() { glDeleteFramebuffers(1, &m_ID); }