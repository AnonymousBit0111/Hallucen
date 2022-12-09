#include "Hallucen/Scene.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Collision/Shapes/b2Shape.h"
#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Common/b2Math.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "GLFW/glfw3.h"
#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/Framebuffer.h"
#include "Hallucen/GL/RenderBuffer.h"
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/GL/gl.h"
#include "Hallucen/Grid.h"
#include "Hallucen/Hallucen.h"
#include "Hallucen/Rect.h"
#include "Hallucen/vector.h"
#include "ext/matrix_transform.hpp"
#include "ext/scalar_constants.hpp"
#include "fwd.hpp"
#include "gtc/constants.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cassert>
#include <cmath>
#include <compare>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <math.h>
#include <memory>
#include <vector>

using namespace Hallucen::GL;
using namespace Hallucen;

int fib(int n) {

  if (n <= 1) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}
// grid(10, {1024, 720})
Scene::Scene() : camera(Camera2D(1024, 720, 0, 0)) {
  srand(1);

  // fbo = std::make_shared<Framebuffer>(1024, 720);
  // fbo->bind();
  // fbo->attachTexture2D(std::make_shared<Texture2D>());
  // for (int i = 0; i < 1000; i++) {
  // }

  // for (auto &i : *grid.getRects()) {

  //   int random = rand();

  //   if (random % 2 == 0) {
  //     i.setColour({1.0f, 0.77f, 0.5f});
  //   }
  //   if (random % 3 == 0) {
  //     i.setColour({1.0f / random, 0.31415f, 0.82312f});
  //   }
  // }

  // auto gridrects = grid.getRects();
  float phi = (std::sqrt(5) + 1) / 2;

  std::vector<unsigned long long> fibonacci;
  fibonacci.reserve(100 * 100);

  fibonacci.push_back(1);
  fibonacci.push_back(1);
  Renderer::beginQuadBatch();

  std::vector<Rect> rects;
  rects.reserve(500 * 500);

  for (int i = 0; i < (500 * 500); i++) {
    // if (i == 0) {
    //   fibonacci[i] = 0;
    // } else
    if (i <= 1) {
      fibonacci[i] = 1;

      Rect rect({1.0f, 1.0f}, {1.0f, 1.0f}, {0, 0, 0});
      rects.push_back(rect);
      Renderer::addRect(rect);

      continue;
    }
    // } else if (i == 3) {
    //   fibonacci[i] = 2;
    //   continue;
    // }

    // fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];

    fibonacci.push_back(fibonacci[i - 1] + fibonacci[i - 2]);

    // std::cout << fibonacci[i] << std::endl;

    float factor = 1000;

    // +0, 0 +, -0, 0 - ;
    int num = (i) % 4;

    Vector2 position;

    Vector2 pos2 = {fibonacci[i] * 1.0f, fibonacci[i] * 1.0f};

    auto prevrect = rects[i - 1];
    switch (num) {

    case 0:
      position = {pos2.x * phi, pos2.y};

      break;

    case 1:
      position = {pos2.x, pos2.y * phi};
      break;
    case 2:
      position = {pos2.x * -phi, pos2.y};
      break;
    case 3:
      position = {pos2.x, pos2.y * -phi};
      break;
    }

    Vector2 size = {1.0f * fibonacci[i], 1.0f * fibonacci[i]};

    Vector3 colour = {1.0f, 1.0f, 1.0f};

    if (i % 2 == 0) {
      colour.x = 0.0f;
    }
    if (i % 3 == 0) {
      colour.y = 0.0f;
    }
    if (i % 5 == 0) {
      colour.z = 0.0f;
    }
    if (i % 7 == 0) {
      colour.x = 1.0f - phi;
      colour.y *= 1.0f - glm::pi<float>();
      colour.z *= 1.0f - glm::e<float>();
    }
    // if (i % 2 == 0) {
    //   colour.x = 1.0f;
    // } else if (i % 3 == 0) {
    //   colour.y = 1.0f;
    // } else if (i % 5 == 0) {
    //   colour.z = 1.0f;
    // }
    Rect rect(size, position, colour);

    rects.push_back(rect);
    Renderer::addRect(rect);
  }

  Renderer::endQuadBatch();

  // exit(0);

  // }  if (std::fmod(gridPos.y, 2) == 0) {
  //   grid.getRects()->at(i).setColour({1.0f / i, 0.31415f, 0.82312f});
  // }

  // // exit(0);
  // auto grav = b2Vec2(0, -10);

  // int columns, rows;
  // int size = 10;
  // columns = 100;
  // rows = 100;

  // std::vector<Vertex> v;
  // rects.reserve(rows * columns);

  // Renderer::beginQuadBatch();
  // for (int c = 0; c < columns; c++) {
  //   for (int r = 0; r < rows; r++) {
  //     Vector3 colour;
  //     colour = {1.0f, 1.0f, 1.0f};

  //     Rect rect({(float)size, (float)size}, {(float)c * size, (float)r *
  //     size},
  //               colour);

  //     Renderer::addRect(rect);

  //     rects.push_back(rect);
  //   }
  // }
  // Renderer::endQuadBatch();
}

void Scene::render() {
  // glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  // glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo->getID());

  // fbo->bind();
  // glViewport(0,0,1024,720);
  Renderer::flush(camera);
  // fbo->blit(0);
  // Renderer::drawRect(Rect({100, 100}, {500, 500}, {1.0f, 1.0f, 1.0f}),
  // camera);
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
  } else if (ImGui::IsKeyDown(ImGuiKey_M)) {
    camera.zoom(1.5);
  } else if (ImGui::IsKeyDown(ImGuiKey_N)) {
    camera.zoom(1 / 1.5);
  }

  ImGui::ShowUserGuide();
}

//   ImGui::Begin("Colour");
//   ImGui::ColorPicker3("select", &r);
//   int columns, rows;
//   int size = 10;
//   columns = std::round(Hallucen::getSize().x / size);
//   rows = std::round(Hallucen::getSize().y / size);
//   Renderer::beginQuadBatch();

//   Vector3 colour;

//   colour = {1.0f, 1.0f, 1.0f};

//   auto pos = getMousePosition(camera);
//   for (auto &i : rects) {

//     Renderer::addRect(i);
//   }
//   Renderer::endQuadBatch();
//   ImGui::End();
// }
void Scene::update(float deltaTime) {

  // grid.update();

  //   Vector2 pos = {ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y};
  //   for (auto &pair : *p_gridMap) {
  //     pair.second->setColour({1.0f, 0.0f, 0.0f});
  //   }
  //   grid.update();
}

Scene::~Scene() {}

glm::vec2 Scene::getMousePosition(Hallucen::GL::Camera2D camera) {
  glm::vec2 pos = glm::vec2(ImGui::GetMousePos().x,
                            Hallucen::getSize().y - ImGui::GetMousePos().y);

  pos.x += camera.getPosition().x;
  pos.y += camera.getPosition().y;

  return pos;
}