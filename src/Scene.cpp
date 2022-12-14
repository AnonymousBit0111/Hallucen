#include "Hallucen/Scene.h"
#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/Framebuffer.h"
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/GL/ShaderProgram.h"
#include <chrono>
#include <math.h>
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/GL/gl.h"
#include "Hallucen/Hallucen.h"
#include "Hallucen/Rect.h"
#include "Hallucen/vector.h"
#include "ext/matrix_transform.hpp"
#include "ext/scalar_constants.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <compare>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <vector>

using namespace Hallucen::GL;
using namespace Hallucen;

Scene::Scene()
    : camera(Camera2D(Hallucen::getSize().x, Hallucen::getSize().y, 0, 0)),
      fbo({(float)Hallucen::getFrameBufferSize().x, (float)Hallucen::getFrameBufferSize().y}, {0, 0}) {
  srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  camera.setSize({(float)Hallucen::getSize().x, (float)Hallucen::getSize().y});

  // exit(0);

  columns = std::round(Hallucen::getSize().x / size);
  rows = std::round(Hallucen::getSize().y / size);


  std::vector<Vertex> v;
  Renderer::beginQuadBatch();
  for (int c = 0; c < columns; c++) {
    for (int r = 0; r < rows; r++) {
      Vector3 colour;

      colour.x = (1.0f / rand()) * 100000000;
      colour.y = (1.0f / rand()) * 100000000;
      colour.z = (1.0f / rand()) * 100000000;

      Rect rect({(float)size, (float)size}, {(float)c * size, (float)r * size},
                colour);

      Renderer::addRect(rect);

    }
  }
  Renderer::endQuadBatch();
}

void Scene::render() {

  if (useFBO) {
    fbo.bind();
    fbo.bindTexture();
    Renderer::clear({0.0f,0.0f,0.0f});
    Renderer::flush(camera);
    fbo.unBind();
    fbo.bindRead();
    // glBlitFramebuffer(camera.getPosition().x, camera.getPosition().y,
    // camera.getSize().x, camera.getSize().y, camera.getPosition().x,
    // camera.getPosition().y, 1024*2, 720*2,
    // GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT,
    //                   GL_NEAREST);
    Vector2 size = fbo.getSize();
    Vector2i winsize = Hallucen::getFrameBufferSize();

    glBlitFramebuffer(0, 0, size.x, size.y, 0, 0, winsize.x, winsize.y,
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);

  } else {
    Renderer::flush(camera);
  }

  // Renderer::drawRect(Rect({100, 100}, {500, 500}), camera);
}

void Scene::ImGuiLogic(float frametime) {

  if (ImGui::IsKeyDown(ImGuiKey_A)) {
    camera.move({-10, 0});
  } else if (ImGui::IsKeyDown(ImGuiKey_D)) {
    camera.move({10, 0});
  } else if (ImGui::IsKeyDown(ImGuiKey_S)) {
    camera.move({0, -10});
  } else if (ImGui::IsKeyDown(ImGuiKey_W)) {
    camera.move({0, 10});
  }

  ImGui::Begin("info");

  if (ImGui::Checkbox("useFBO", &useFBO)) {
  }
  ImGui::Text("Framerate is %.2f",1/(frametime/1000));
  ImGui::Text("size.x is %.0f",fbo.getSize().x);
  ImGui::Text("size.y is %.0f",fbo.getSize().y);

  ImGui::Text("size.x is %.1d",Hallucen::getSize().x);
  ImGui::Text("size.y is %.1d",Hallucen::getSize().y);
  ImGui::Text("rows is %.1d",rows);
  ImGui::Text("columns is %.1d",columns);

  ImGui::End();
}
void Scene::update(float deltaTime) {
  //   Vector2 pos = {ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y};
  //   for (auto &pair : *p_gridMap) {
  //     pair.second->setColour({1.0f, 0.0f, 0.0f});
  //   }
  //   grid.update();

  // Renderer::beginQuadBatch();
  // for (int c = 0; c < columns; c++) {
  //   for (int r = 0; r < rows; r++) {
  //     Vector3 colour;

  //     colour.x = (1.0f / rand()) * 100000000;
  //     colour.y = (1.0f / rand()) * 100000000;
  //     colour.z = (1.0f / rand()) * 100000000;

  //     Rect rect({(float)size, (float)size}, {(float)c * size, (float)r * size},
  //               colour);

  //     Renderer::addRect(rect);
  //   }
  // }
  // Renderer::endQuadBatch();
}

void Scene::winSizeChanged(Hallucen::Vector2i newsize) {

  Vector2 size;
  size.x = std::round(newsize.x);
  size.y = std::round(newsize.y);
  camera.setSize(size);
}

Scene::~Scene() {}