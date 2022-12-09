#include "Hallucen/GL/RenderBuffer.h"
#include "glad/glad.h"
using namespace Hallucen;
using namespace Hallucen::GL;

RenderBuffer::RenderBuffer() { glGenRenderbuffers(1, &m_ID); }
RenderBuffer::RenderBuffer(unsigned int width, unsigned int height) {
  glGenRenderbuffers(1, &m_ID);
  bind();
  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width, height);
  unBind();
}

void RenderBuffer::bind() { glBindRenderbuffer(GL_RENDERBUFFER, m_ID); }
void RenderBuffer::unBind() { glBindRenderbuffer(GL_RENDERBUFFER, m_ID); }
RenderBuffer::~RenderBuffer() { glDeleteRenderbuffers(1, &m_ID); }