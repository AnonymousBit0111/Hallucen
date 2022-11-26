#include "Hallucen/GL/VertexBuffer.h"
#include "glad/glad.h"
using namespace Hallucen::GL;

void VertexBuffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, m_ID); }

void VertexBuffer::unBind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

VertexBuffer::VertexBuffer() { glGenBuffers(1, &m_ID); }

void VertexBuffer::fill(std::vector<float> data) {
  m_Vertices = data;
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Vertices.size(),
               m_Vertices.data(), GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
  // unsigned int arr[] = {m_ID};
  //   glDeleteBuffers(1, arr);

  unBind();
}