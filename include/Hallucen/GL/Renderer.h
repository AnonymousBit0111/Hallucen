#pragma once

#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/gl.h"
#include "Hallucen/vector.h"
#include <GLFW/glfw3.h>
namespace Hallucen {
class Rect;
namespace GL {

class Renderer {

public:
  static void init();

  static void addRect(Hallucen::Rect r);
  static void shutDown();

  static void draw(VertexArray &vertexArray, ShaderProgram &shaderProgram,
                   ElementArrayBuffer &indexBuffer, Camera2D &cam);
  static void draw(DrawData data, Camera2D &camera);

  static ShaderProgram *getShader();
  static void clear(Vector3 colour);
  static void drawRect(Rect rect, Camera2D &cam);
  static void beginQuadBatch();

  static void endQuadBatch();
  static void flush(Camera2D &cam);
};
} // namespace GL
} // namespace Hallucen