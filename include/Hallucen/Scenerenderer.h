#pragma once


#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/DrawData.h"
#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/Texture2D.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/Image.h"
#include "Hallucen/Ref.h"
#include <map>
#include <utility>
#include <vector>

#include "Hallucen/Drawable.h"
namespace Hallucen {

struct RenderObject {

  std::vector<unsigned int> indices;
};

class SceneRenderer {

private:
  // ID, RenderObject
  std::map<unsigned int, RenderObject> objects;

  std::vector<Hallucen::GL::TextureVertex> vertices;

  std::vector<unsigned int> indices;

  Hallucen::GL::VertexArray VAO;
  Hallucen::GL::VertexBuffer VBO;
  Hallucen::GL::ElementArrayBuffer IBO;

  Hallucen::Ref<Hallucen::GL::ShaderProgram> defaultEntityShader;

  Hallucen::Ref<Hallucen::GL::ShaderProgram> defaultTileShader;

  Hallucen::Ref<Hallucen::GL::Texture2D> texture;

  Hallucen::Ref<Hallucen::GL::Texture2D> defaultTex;

  int vertexCount;

  // index count comes from indices.size()

public:
  SceneRenderer(Hallucen::Ref<Hallucen::Image> image);
  static Hallucen::Ref<SceneRenderer>
  create(Hallucen::Ref<Hallucen::Image>
             image); // it is a large class so  heap allocation
  void beginBatch();
  void addEntity(Hallucen::Drawable &e);
  void endBatch();
  void flush(Hallucen::GL::Camera2D &cam,bool texture);

  ~SceneRenderer() {}
};
} // namespace Chess