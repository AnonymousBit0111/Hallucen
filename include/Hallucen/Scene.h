#pragma once
#include "Box2D/Box2D.h"
#include "Box2D/Dynamics/b2World.h"
#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/Framebuffer.h"
#include "Hallucen/GL/RenderBuffer.h"
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/GL/gl.h"
#include "Hallucen/Grid.h"
#include "Hallucen/Hallucen.h"
#include "Hallucen/Rect.h"
#include "Hallucen/Rectangle.h"
#include "Hallucen/vector.h"
#include "fwd.hpp"
#include <memory>
#include <vector>
class Scene {
private:
  Hallucen::GL::Camera2D camera;
  std::vector<Hallucen::Rect> rects;
  std::shared_ptr<Hallucen::GL::Framebuffer> fbo;

  float r, g, b;

  // Hallucen::Grid grid;

  // Hallucen::Grid grid;
  // std::vector<unsigned int> indices{0, 1, 2, 2, 3, 0};

public:
  Scene();
  void ImGuiLogic(float frametime);
  void render();
  glm::vec2 getMousePosition(Hallucen::GL::Camera2D camera);
  void update(float deltaTime);
  ~Scene();
};