#include "Hallucen/GL/Renderer.h"
#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/Hallucen.h"
#include "Hallucen/Rect.h"
#include "fwd.hpp"
#include <_types/_uint32_t.h>
#include <cstddef>
#include <memory>
#include <sys/_types/_size_t.h>

using namespace Hallucen::GL;

const int MaxQuads = 10000;
const int MaxVerts = MaxQuads * 4;
const int MaxIndexCount = MaxQuads * 6;

template <typename T> using Ref = std::shared_ptr<T>;

struct RenderData {

  Ref<VertexBuffer> VBO;
  Ref<VertexArray> VAO;
  Ref<ElementArrayBuffer> IBO;
  Ref<ShaderProgram> shader;

  std::vector<Vertex> QuadBuffer;
  unsigned int QuadBufferOffset = 0;
  unsigned int MaxTextures;

  size_t indexCount;

  int drawCalls;
  unsigned int vertexCount;
};
static RenderData Data;

void Renderer::init() {

  Data.VBO = std::make_shared<VertexBuffer>();
  Data.VAO = std::make_shared<VertexArray>();
  Data.IBO = std::make_shared<ElementArrayBuffer>();
  Data.shader = std::make_shared<ShaderProgram>();

  Data.VAO->bind();
  Data.VBO->bind();
  Data.IBO->bind();

  Data.VBO->reserve(MaxVerts);
  Data.QuadBuffer.reserve(MaxVerts);

  Data.VAO->createAttribute(2, GL_FALSE, sizeof(Vertex), 0);
  Data.VAO->createAttribute(3, GL_FALSE, sizeof(Vertex),
                            offsetof(Vertex, colour));

  std::vector<unsigned int> indices;
  indices.reserve(MaxIndexCount);

  unsigned int offset = 0;
  for (int i = 0; i < MaxIndexCount; i += 6) {
    indices.push_back(0 + offset);
    indices.push_back(1 + offset);
    indices.push_back(2 + offset);
    indices.push_back(2 + offset);
    indices.push_back(3 + offset);
    indices.push_back(0 + offset);

    offset += 4;
  }

  Data.IBO->fill(indices);

  Shader frag(GL_FRAGMENT_SHADER);
  Shader vert(GL_VERTEX_SHADER);

  auto fragsource = Engine::loadFile("res/Hallucen/Rectangle/fragment.glsl");
  auto vertsource = Engine::loadFile("res/Hallucen/Rectangle/vertex.glsl");

  frag.load(fragsource);
  vert.load(vertsource);
  frag.compile();
  vert.compile();
  Data.shader->attachShader(frag.getID());
  Data.shader->attachShader(vert.getID());
  Data.shader->link();
  for (int i = 0; i < MaxVerts; i++) {
    Data.QuadBuffer.push_back(Vertex{{0, 0}, {1, 1, 1}});
  }
}

void Renderer::clear(Vector3 colour) {
  glClearColor(colour.x, colour.y, colour.z, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::addRect(Hallucen::Rect rect) {
  auto verts = rect.getVerts();

  for (auto &i : verts) {
    // Data.QuadBuffer.push_back(i);
    Data.QuadBuffer[Data.QuadBufferOffset] = i;
    Data.QuadBufferOffset++;
  }
  Data.vertexCount += verts.size();

  Data.indexCount += 6;
}

void Renderer::beginQuadBatch() {
  Data.QuadBufferOffset = 0;
  // Data.QuadBuffer.clear();
}

void Renderer::endQuadBatch() {

  uint64_t batchSize = Data.QuadBuffer.size();
  Data.VBO->bind();
  // if (batchSize > MaxVerts)
  //   exit(-1);

  Data.VBO->emplace(Data.QuadBuffer, 0);
  // Data.vertexCount = batchSize;
}

void Renderer::draw(VertexArray &vertexArray, ShaderProgram &shaderProgram,
                    ElementArrayBuffer &indexBuffer, Camera2D &camera) {

  vertexArray.bind();
  indexBuffer.bind();

  glm::mat4 vp = camera.getViewProjMatrix();
  shaderProgram.use();
  shaderProgram.setMat4("uViewProjectionMatrix", vp);

  glDrawElements(GL_TRIANGLES, indexBuffer.getSize(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::draw(DrawData data, Camera2D &cam) {
  data.VAO->bind();
  data.IBO->bind();

  glm::mat4 vp = cam.getViewProjMatrix();

  data.shader->use();
  data.shader->setMat4("uViewProjectionMatrix", vp);

  glDrawElements(GL_TRIANGLES, data.IBO->getSize(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::shutDown() {}

ShaderProgram *Renderer::getShader() { return Data.shader.get(); }

void Renderer::drawRect(Rect rect, Camera2D &cam) {
  auto verts = rect.getVerts();

  VertexArray VAO;
  VertexBuffer VBO;
  ElementArrayBuffer EBO;

  int indices = (verts.size() / 4) * 6;

  std::vector<unsigned int> inds{0, 1, 2, 2, 3, 0};

  VAO.bind();
  VBO.bind();
  EBO.bind();
  VBO.reserve(verts.size());
  VBO.emplace(verts, 0);

  EBO.fill(inds);

  VAO.createAttribute(2, GL_FALSE, sizeof(Vertex), 0);
  VAO.createAttribute(3, GL_FALSE, sizeof(Vertex), offsetof(Vertex, colour));

  Data.shader->use();
  auto vp = cam.getViewProjMatrix();
  Data.shader->setMat4("uViewProjectionMatrix", vp);

  glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, nullptr);
}

void Renderer::flush(Camera2D &camera) {

  Data.VAO->bind();
  Data.IBO->bind();
  Data.VBO->bind();

  Data.shader->use();
  auto vp = camera.getViewProjMatrix();
  Data.shader->setMat4("uViewProjectionMatrix", vp);

  glDrawElements(GL_TRIANGLES, (Data.vertexCount / 4) * 6, GL_UNSIGNED_INT,
                 nullptr);
}