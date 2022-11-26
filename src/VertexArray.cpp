#include "Hallucen/GL/VertexArray.h"
#include "glad/glad.h"
using namespace Hallucen::GL;

VertexArray::VertexArray() { glGenVertexArrays(1, &m_ID); }

void VertexArray::bind() { glBindVertexArray(m_ID); }

void VertexArray::unBind() { glBindVertexArray(0); }

void VertexArray::createAttribute(int size, GLboolean normalized, int stride,
                                  int offset) {
  glVertexAttribPointer(m_AttribCount, size, GL_FLOAT, normalized,
                        stride * sizeof(float),
                        (void *)(sizeof(float) * offset));
  glEnableVertexAttribArray(m_AttribCount);

  m_AttribCount++;
}

unsigned int VertexArray::getID() { return m_ID; }
VertexArray::~VertexArray() {
  // bind();
  // unsigned int arr[] = {m_ID};
  // glDeleteVertexArrays(1, arr);
  unBind();
}
