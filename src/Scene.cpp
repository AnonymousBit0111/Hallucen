#include "Hallucen/Scene.h"
#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/GL/gl.h"
#include "Hallucen/Hallucen.h"
#include "Hallucen/Rect.h"
#include "Hallucen/vector.h"
#include "ext/matrix_transform.hpp"
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

Scene::Scene() : camera(Camera2D(1024, 720, 0, 0)) {
  srand(1);

  // exit(0);

  int columns, rows;
  int size = 10;
  columns = std::round(Hallucen::getSize().x / size);
  rows = std::round(Hallucen::getSize().y / size);
  // std::vector<Vertex> v;
  // v.reserve(columns * rows * 4);
  // Renderer::beginQuadBatch();
  // for (int c = 0; c < columns; c++) {
  //   for (int r = 0; r < rows; r++) {
  //     Vector3 colour;
  //     colour = {1.0f, 1.0f/r*c, 1.0f/r*c};

  //     Rect rect({(float)size, (float)size}, {(float)c * size, (float)r *
  //     size},
  //               colour);
  //     Renderer::addRect(rect);
  //     for (auto &i : rect.getVerts()) {
  //       v.push_back(i);
  //     }
  //   }
  // }
  // Renderer::endQuadBatch();
}

void Scene::render() {

  Renderer::flush(camera);
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

  ImGui::ShowUserGuide();
}
void Scene::update(float deltaTime) {
//   Vector2 pos = {ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y};
//   for (auto &pair : *p_gridMap) {
//     pair.second->setColour({1.0f, 0.0f, 0.0f});
//   }
//   grid.update();
}

Scene::~Scene() {}