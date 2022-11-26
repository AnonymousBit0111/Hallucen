#include "Hallucen/GL/ElementBuffer.h"
#include "glad/glad.h"

void Hallucen::GL::ElementArrayBuffer::unBind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Hallucen::GL::ElementArrayBuffer::bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}
Hallucen::GL::ElementArrayBuffer::ElementArrayBuffer() {
  glGenBuffers(1, &m_ID);
}

void Hallucen::GL::ElementArrayBuffer::fill(std::vector<unsigned int> data) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data.at(0)) * data.size(),
               data.data(), GL_DYNAMIC_DRAW);
  m_Size = data.size();
}

Hallucen::GL::ElementArrayBuffer::~ElementArrayBuffer() {
  glDeleteBuffers(1, &m_ID);
}