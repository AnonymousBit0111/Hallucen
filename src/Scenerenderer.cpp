#include "Hallucen/Scenerenderer.h"
#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/DrawData.h"
#include "Hallucen/GL/Shader.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/Profile.h"
#include "Hallucen/Ref.h"
#include <_types/_uint32_t.h>
#include <cassert>
#include <iostream>
#include <string>
#include <utility>

std::string defaultEntityV = R"(#version 410
layout(location=0)in vec2 aPos;
layout(location=1)in vec3 aColour;
layout (location =2) in vec2 aTexCoord;
layout (location = 3) in float aTexIndex;

out vec3 vColour;
out vec2 vTexCoord;
flat out int vTexIndex;
uniform mat4 uViewProjectionMatrix;

out mat4 vViewProj;
void main()
{
    // TODO add rotation using model matrix
    
    gl_Position=uViewProjectionMatrix*vec4(aPos.xy,0,1);

    
    vViewProj=uViewProjectionMatrix;
    vColour=aColour;
    vTexCoord = aTexCoord;
    vTexIndex = int(round(aTexIndex));
})";

std::string defaultEntityF = R"(#version 410
out vec4 FragColor;
in vec3 vColour;
in vec2 vTexCoord;
in mat4 vViewProj;
flat in int vTexIndex;



uniform sampler2D uTex;

void main()
{
    // FragColor = vec4(1.0f);
    FragColor = texture(uTex,vTexCoord)*vec4(vColour,1.0f);

})";

using namespace Hallucen;
using namespace Hallucen::GL;

const int MaxVerts = 44000;

void printShaderLog(unsigned int handle) {
  ProfileFunc;
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
}
Ref<ShaderProgram> loadShader(std::string Vsrc, std::string Fsrc) {
  ProfileFunc;
  Ref<ShaderProgram> prog = make_Ref<ShaderProgram>();
  Shader vShader(GL_VERTEX_SHADER);
  Shader fShader(GL_FRAGMENT_SHADER);

  vShader.load(Vsrc);
  fShader.load(Fsrc);

  if (!fShader.compile()) {
    std::cout << "Failed to load Fragment Shader\n";
    printShaderLog(fShader.getID());
    assert(false);
  }

  if (!vShader.compile()) {

    std::cout << "Failed to load Vertex Shader\n";
    printShaderLog(vShader.getID());

    assert(false);
  }
  prog->attachShader(vShader.getID());
  prog->attachShader(fShader.getID());

  prog->link();

  GLint status = 0, log_length = 0;
  glGetProgramiv(prog->getID(), GL_LINK_STATUS, &status);
  glGetProgramiv(prog->getID(), GL_INFO_LOG_LENGTH, &log_length);
  if ((GLboolean)status == GL_FALSE)
    fprintf(stderr, "Error linking shader \n");
  if (log_length > 1) {
    std::vector<char> buf;
    buf.resize((int)(log_length + 1));
    glGetProgramInfoLog(prog->getID(), log_length, nullptr,
                        (GLchar *)buf.data());
    fprintf(stderr, "%s\n", buf.data());
    // assert(false);
  }

  return prog;
}

SceneRenderer::SceneRenderer(Hallucen::Ref<Image> image) {
  ProfileFunc;

  defaultEntityShader = loadShader(defaultEntityV, defaultEntityF);

  texture = Hallucen::make_Ref<Texture2D>();

  texture->bind(0);
  texture->setImage(*image);
  texture->genMipmap();
  defaultEntityShader->use();
  defaultEntityShader->setInt("uTex", 0);

  VAO.bind();
  VBO.bind();
  IBO.bind();

  VBO.reserve(MaxVerts * sizeof(TextureVertex));
  vertices.reserve(MaxVerts);
  for (int i = 0; i < MaxVerts; i++) {

    // TODO review if this really makes a difference
    vertices.push_back(TextureVertex{0, 0, 0, 0, 0, 0, 0});
  }

  VAO.createAttribute(2, GL_FALSE, sizeof(TextureVertex),
                      offsetof(TextureVertex, x)); // coords

  VAO.createAttribute(3, GL_FALSE, sizeof(TextureVertex),
                      offsetof(TextureVertex, r)); // colours
  VAO.createAttribute(2, GL_FALSE, sizeof(TextureVertex),
                      offsetof(TextureVertex, tx)); // tex coords
defaultTex = Hallucen::make_Ref<Texture2D>();
  this->defaultTex->bind(0);
  uint32_t colour = 0xffffffff;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               &colour);
  defaultTex->genMipmap();
}

Hallucen::Ref<SceneRenderer> SceneRenderer::create(Hallucen::Ref<Image> img) {
  ProfileFunc;
  return make_Ref<SceneRenderer>(img);
}
void SceneRenderer::beginBatch() {
  ProfileFunc;
  vertexCount = 0;
  indices.clear();
}
void SceneRenderer::addEntity(Hallucen::Drawable &e) {
  ProfileFunc;
  auto verts = e.getVertices();
  auto inds = e.getIndices();

  indices.reserve(inds.size());
  for (auto &i : inds) {
    i += vertexCount;

    indices.push_back(i);
  }
  for (auto &i : verts) {
    vertices[vertexCount] = i;
    vertexCount++;
  }
}

void SceneRenderer::endBatch() {
  ProfileFunc;
  VAO.bind();
  VBO.bind();
  IBO.bind();

  // NOTE : if i emplace it may be quicker as no memory allocation
  // takes place on the gpu every frame

  IBO.fill(indices);
  VBO.emplace(vertices, 0);
}

void SceneRenderer::flush(Camera2D &cam, bool texture) {
  ProfileFunc;

  if (texture) {
    this->texture->bind(0);
  } else {
    this->defaultTex->bind(0);
  }
  VAO.bind();
  IBO.bind();
  defaultEntityShader->use();

  auto vp = cam.getViewProjMatrix();
  defaultEntityShader->setMat4("uViewProjectionMatrix", vp);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}
