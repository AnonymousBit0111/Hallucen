#include "Hallucen/GL/Renderer.h"
#include "Hallucen/GL/Camera2D.h"

using namespace Hallucen::GL;

Renderer::Renderer() {}

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

Renderer::~Renderer() {}