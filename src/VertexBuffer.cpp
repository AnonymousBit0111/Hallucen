#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/GL/gl.h"
#include "glad/glad.h"
using namespace Hallucen::GL;

void VertexBuffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, m_ID); }

void VertexBuffer::unBind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

VertexBuffer::VertexBuffer() { glGenBuffers(1, &m_ID); }

void VertexBuffer::fill(std::vector<float> &data) {
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(),
               GL_DYNAMIC_DRAW);
}

void VertexBuffer::emplace(std::vector<float> &data, long offset) {
  glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(float) * data.size(),
                  data.data());
}
void VertexBuffer::emplace(Vertex *data, long size, long offset) {

  glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(Vertex) * size, data);
}

void VertexBuffer::emplace(Vertex vertex, long offset) {
  glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(Vertex), &vertex);
}
void VertexBuffer::reserve(unsigned int size) {
  glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

void VertexBuffer::fill(std::vector<Vertex> &data) {
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * data.size(), data.data(),
               GL_DYNAMIC_DRAW);
}

void VertexBuffer::fill(std::vector<TextureVertex> &data) {
  glBufferData(GL_ARRAY_BUFFER, sizeof(TextureVertex) * data.size(),
               data.data(), GL_DYNAMIC_DRAW);
}

void VertexBuffer::emplace(std::vector<Vertex> &data, long offset) {
  glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(Vertex) * data.size(),
                  data.data());
}

void VertexBuffer::emplace(std::vector<TextureVertex> &data, long offset) {
   glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(TextureVertex) * data.size(),
                  data.data());
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &m_ID);
  unBind();
}