#include "Hallucen/GL/Renderer.h"
#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/DrawData.h"
#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/Shader.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/Texture2D.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/Hallucen.h"
#include "Hallucen/Rect.h"
#include "Hallucen/Ref.h"
#include "fwd.hpp"
#include "tracy/Tracy.hpp"
#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <vector>



// TODO write myself
static bool CheckShader(GLuint handle) {
  GLint status = 0, log_length = 0;
  glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
  glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);
  if ((GLboolean)status == GL_FALSE)
    fprintf(stderr, "Error Compiling shader \n");
  if (log_length > 1) {
    std::vector<char> buf;
    buf.resize((int)(log_length + 1));
    glGetShaderInfoLog(handle, log_length, nullptr, (GLchar *)buf.data());
    fprintf(stderr, "%s\n", buf.data());
  }
  return (GLboolean)status == GL_TRUE;
}

using namespace Hallucen;
using namespace Hallucen::GL;
std::shared_ptr<ShaderProgram> loadDefaultShader();

const int MaxQuads = 440000;
const int MaxVerts = MaxQuads * 4;
const int MaxIndexCount = MaxQuads * 6;

struct EntityRenderData {
  Ref<VertexBuffer> VBO;
  Ref<VertexArray> VAO;
  Ref<ElementArrayBuffer> IBO;
  Ref<ShaderProgram> shader;

  std::vector<TextureVertex> vertices;
  std::shared_ptr<Texture2D> texture;
  std::vector<unsigned int> indices;

  // for multi texture rendering
  // std::map<std::shared_ptr<Texture2D>,
  //          std::pair<std::vector<TextureVertex>, std::vector<unsigned int>>>
  //     texBatches;

  unsigned int Offset = 0;
};

struct RenderData {

  Ref<VertexBuffer> VBO;
  Ref<VertexArray> VAO;
  Ref<ElementArrayBuffer> IBO;
  Ref<ShaderProgram> shader;

  std::vector<Vertex> QuadBuffer;
  unsigned int QuadBufferOffset = 0;
  int MaxTextures;

  size_t indexCount;

  // int drawCalls;
  unsigned int vertexCount;
};
static RenderData Data;
static EntityRenderData eData;

void initEntityRenderer() {
  TracyFunction;
  ZoneScoped;
  eData.VBO = Hallucen::make_Ref<VertexBuffer>();
  eData.VAO = Hallucen::make_Ref<VertexArray>();
  eData.IBO = Hallucen::make_Ref<ElementArrayBuffer>();
  eData.shader = loadDefaultShader();

  eData.VAO->bind();
  eData.VBO->bind();
  eData.IBO->bind();

  eData.VBO->reserve(MaxVerts * sizeof(TextureVertex));
  eData.vertices.reserve(MaxVerts);
  for (int i = 0; i < MaxVerts; i++) {
    eData.vertices.push_back(TextureVertex{0, 0, 0, 0, 0, 0, 0});
  }

  eData.VAO->createAttribute(2, GL_FALSE, sizeof(TextureVertex),
                             offsetof(TextureVertex, x));
  eData.VAO->createAttribute(3, GL_FALSE, sizeof(TextureVertex),
                             offsetof(TextureVertex, r));
  eData.VAO->createAttribute(2, GL_FALSE, sizeof(TextureVertex),
                             offsetof(TextureVertex, tx));
}
void Renderer::init() {
  TracyFunction;
  ZoneScoped;
  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &Data.MaxTextures);

  std::cout << Data.MaxTextures << std::endl;

  Data.VBO = std::make_shared<VertexBuffer>();
  Data.VAO = std::make_shared<VertexArray>();
  Data.IBO = std::make_shared<ElementArrayBuffer>();
  Data.shader = std::make_shared<ShaderProgram>();

  Data.VAO->bind();
  Data.VBO->bind();
  Data.IBO->bind();

  Data.VBO->reserve(MaxVerts * sizeof(Vertex));
  Data.QuadBuffer.reserve(MaxVerts);

  Data.VAO->createAttribute(2, GL_FALSE, sizeof(Vertex), 0);
  Data.VAO->createAttribute(3, GL_FALSE, sizeof(Vertex), offsetof(Vertex, r));

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
    Data.QuadBuffer.push_back(Vertex{0, 0, 1, 1, 1});
  }

  initEntityRenderer();
}

void Renderer::clear(Vector3 colour) {
  TracyFunction;
  ZoneScoped;
  glClearColor(colour.x, colour.y, colour.z, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::addRect(Ref<Hallucen::Rect> rect) {
  TracyFunction;
  ZoneScoped;
  auto verts = rect->getVerts();

  for (auto &i : rect->getVerts()) {
    // Data.QuadBuffer.push_back(i);
    Data.QuadBuffer[Data.QuadBufferOffset] = i;
    Data.QuadBufferOffset++;
  }
  Data.vertexCount += 4;
  Data.indexCount += 6;
}

void Renderer::insertQuad(unsigned int position, Ref<Rect> quad) {

  for (auto &i : quad->getVerts()) {
    // Data.QuadBuffer.push_back(i);
    Data.QuadBuffer[position] = i;
    position++;
  }
  endQuadBatch();
}

void Renderer::beginQuadBatch() {
  TracyFunction;
  ZoneScoped;
  Data.QuadBufferOffset = 0;
  Data.vertexCount = 0;
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
  VBO.fill(verts);

  EBO.fill(inds);

  VAO.createAttribute(2, GL_FALSE, sizeof(Vertex), 0);
  VAO.createAttribute(3, GL_FALSE, sizeof(Vertex), offsetof(Vertex, r));

  Data.shader->use();
  auto vp = cam.getViewProjMatrix();
  Data.shader->setMat4("uViewProjectionMatrix", vp);

  glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, nullptr);
}

void Renderer::flushQuads(Camera2D &camera) {
  TracyFunction;
  ZoneScoped;
  Data.VAO->bind();
  Data.IBO->bind();
  Data.VBO->bind();

  Data.shader->use();
  auto vp = camera.getViewProjMatrix();
  Data.shader->setMat4("uViewProjectionMatrix", vp);

  glDrawElements(GL_TRIANGLES, Data.indexCount, GL_UNSIGNED_INT, nullptr);
}
std::shared_ptr<ShaderProgram> loadDefaultShader() {
  auto shader = std::make_shared<ShaderProgram>();

  Shader vs(GL_VERTEX_SHADER);
  Shader fs(GL_FRAGMENT_SHADER);
  std::string vss =
      Hallucen::Engine::loadFile("res/Hallucen/Renderer/Generic/vertex.glsl");
  std::string fss =
      Hallucen::Engine::loadFile("res/Hallucen/Renderer/Generic/fragment.glsl");

  vs.load(vss);
  fs.load(fss);
  char buf[1024];
  if (!vs.compile()) {
    CheckShader(vs.getID());

    std::cout << "error compiling vertex shader\n";
    exit(-1);
  }
  if (!fs.compile()) {
    CheckShader(fs.getID());
    std::cout << "error compiling fragment shader\n";
    exit(-1);
  }

  shader->attachShader(vs.getID());
  shader->attachShader(fs.getID());
  shader->link();

  return shader;
}
void Renderer::drawEntity(Drawable &e, Camera2D cam) {
  ZoneScoped;

  // very inefficient
  ShaderProgram shader = *loadDefaultShader();

  auto vp = cam.getViewProjMatrix();
  shader.use();
  shader.setInt("uTex", 1);
  shader.setMat4("uViewProjectionMatrix", vp);

  VertexArray VAO;
  VertexBuffer VBO;
  ElementArrayBuffer EBO;

  Texture2D tex;
  tex.bind(1);

  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
  // GL_LINEAR_MIPMAP_LINEAR); glTexParameteri(GL_TEXTURE_2D,
  // GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  VAO.bind();
  VBO.bind();
  EBO.bind();
  std::vector<GL::TextureVertex> vertices = e.getVertices();
  std::vector<unsigned int> indices = e.getIndices();
  tex.setImage(*e.getImage());
  tex.genMipmap();
  VBO.fill(vertices);
  EBO.fill(indices);

  VAO.createAttribute(2, GL_FALSE, sizeof(GL::TextureVertex),
                      offsetof(GL::TextureVertex, x));
  VAO.createAttribute(3, GL_FALSE, sizeof(GL::TextureVertex),
                      offsetof(GL::TextureVertex, r));
  VAO.createAttribute(2, GL_FALSE, sizeof(GL::TextureVertex),
                      offsetof(GL::TextureVertex, tx));

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::beginEntityBatch(std::shared_ptr<Texture2D> tex) {
  eData.Offset = 0;
  eData.texture = tex;
}

unsigned int in = 0;
void Renderer::addEntity(Drawable &e) {
  in %= 16;

  int vertexCount = eData.Offset;

  auto inds = e.getIndices();
  eData.indices.reserve(inds.size());
  for (auto &i : inds) {
    eData.indices.push_back(i + vertexCount);
  }
  for (auto &i : e.getVertices()) {
    eData.vertices[eData.Offset] = i;
    eData.Offset++;
  }

  // one texture for now
  // auto image = e.getImage();
  // Texture2D tex = e.getTexture();
}

void Renderer::endEntityBatch() {
  TracyFunction;
  ZoneScoped;

  uint64_t batchSize = eData.vertices.size();
  eData.VAO->bind();
  eData.VBO->bind();
  eData.IBO->bind();
  // if (batchSize > MaxVerts)
  //   exit(-1);

  eData.VBO->emplace(eData.vertices, 0);
  eData.IBO->fill(eData.indices);
}

void Renderer::flushEntities(Camera2D &camera) {
  TracyFunction;
  ZoneScoped;
  eData.VAO->bind();
  eData.texture->bind(1);
  eData.IBO->bind();
  eData.VBO->bind();

  eData.shader->use();

  auto vp = camera.getViewProjMatrix();
  eData.shader->setMat4("uViewProjectionMatrix", vp);
  eData.shader->setInt("uTex", 1);
  glDrawElements(GL_TRIANGLES, eData.indices.size(), GL_UNSIGNED_INT, nullptr);
}