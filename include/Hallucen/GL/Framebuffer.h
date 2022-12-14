#pragma once

#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/Shader.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/Texture2D.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/GL/gl.h"
#include "Hallucen/vector.h"
#include <memory>
namespace Hallucen::GL {
struct TextureVertex {
  float positions[2];
  float colour[3];
  float textureCoord[2];
};

class Framebuffer {
private:
  unsigned int m_ID;
  bool textureAttached = false;
  std::shared_ptr<Texture2D> m_Tex;

  ShaderProgram program;
  Vector2 m_Position;
  Vector2 m_Size;

  VertexBuffer VBO;
  ElementArrayBuffer IBO;
  VertexArray VAO;

  DrawData data;

public:
  Framebuffer(Vector2 size, Vector2 pos);

  inline DrawData getData() { return data; }
  inline Vector2 getSize() { return m_Size; }

  void bindTexture();
  void bind();
  void bindRead();
  void bindDraw();
  static void unBind();

  ~Framebuffer();
};
} // namespace Hallucen::GL