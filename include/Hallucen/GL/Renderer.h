#pragma once

#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/gl.h"
#include <GLFW/glfw3.h>

namespace Hallucen {
namespace GL {

class Renderer {

private:
public:
  Renderer();
  void draw(VertexArray &vertexArray, ShaderProgram &shaderProgram,
            ElementArrayBuffer &indexBuffer, Camera2D &cam);
  void draw(DrawData data,Camera2D &camera);
  ~Renderer();
};
} // namespace GL
} // namespace Hallucen