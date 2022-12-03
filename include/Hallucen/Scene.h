#pragma once
#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/GL/gl.h"
#include "Hallucen/Hallucen.h"
#include "Hallucen/Rectangle.h"
#include "Hallucen/vector.h"
#include <memory>
#include <vector>
class Scene {
private:
  Hallucen::GL::Camera2D camera;
  Hallucen::GL::VertexArray VAO;
  Hallucen::GL::VertexBuffer VBO;
  Hallucen::GL::ElementArrayBuffer EBO;
  Hallucen::GL::DrawData data;
  // Hallucen::Grid grid;
  // std::vector<unsigned int> indices{0, 1, 2, 2, 3, 0};

public:
  Scene();
  void ImGuiLogic(float frametime);
  void render();
  void update(float deltaTime);
  ~Scene();
};