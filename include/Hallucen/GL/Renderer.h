#pragma once

#include "Hallucen/Drawable.h"
#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/Texture2D.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/gl.h"
#include "Hallucen/vector.h"

#include "Hallucen/Ref.h"
#include <GLFW/glfw3.h>
#include <memory>

namespace Hallucen {
class Rect;
class Drawable;
namespace GL {

class Renderer {

public:
  static void init();

  static void shutDown();

  static void draw(VertexArray &vertexArray, ShaderProgram &shaderProgram,
                   ElementArrayBuffer &indexBuffer, Camera2D &cam);
  static void draw(DrawData data, Camera2D &camera);

  static void drawEntity(Drawable &e, Camera2D cam);

  static ShaderProgram *getShader();
  static void clear(Vector3 colour);
  static void drawRect(Rect rect, Camera2D &cam);
  static void beginQuadBatch();
  static void addRect(Ref<Hallucen::Rect> r);
  static void insertQuad(unsigned int position,Ref<Rect> Quad);
  static void endQuadBatch();
  static void flushQuads(Camera2D &cam);

  static void beginEntityBatch(std::shared_ptr<Texture2D> tex);
  static void addEntity(Drawable &e);
  static void flushEntities(Camera2D &camera);
  static void endEntityBatch();
};
} // namespace GL
} // namespace Hallucen