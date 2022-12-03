#pragma once
#include "glad/glad.h"
namespace Hallucen {

namespace GL {
class VertexArray {
private:
  unsigned int m_ID;
  int m_AttribCount = 0;

public:
  VertexArray();
  void bind();
  unsigned int getID();

  // this creates and enables an attribute
  void createAttribute(int size, GLboolean normalized, int stride,
                       unsigned long offset);
  static void unBind();
  ~VertexArray();
};

} // namespace GL
} // namespace Hallucen