#pragma once
#include "ElementBuffer.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <memory>
#include "DrawData.h"
namespace Hallucen {

namespace GL {

struct RawVertexBuffer {
  unsigned int ID;
  void *bufferData;
  unsigned int bufferCount;
};

struct DrawData {
  ElementArrayBuffer *IBO;
  ShaderProgram *shader;
  VertexArray *VAO;
};



void activateTextureUnit(unsigned int index);
} // namespace GL
} // namespace Hallucen