#pragma once
#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/GL/Shader.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/Texture2D.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/Rectangle.h"
#include "fwd.hpp"
#include "glad/glad.h"
#include <iostream>
#include <memory>
namespace Application {

static std::shared_ptr<Hallucen::GL::VertexBuffer> buffer;
static std::shared_ptr<Hallucen::GL::VertexArray> VAO;
static std::shared_ptr<Hallucen::GL::Shader> vertexShader;
static std::shared_ptr<Hallucen::GL::Shader> fragmentShader;
static std::shared_ptr<Hallucen::GL::ShaderProgram> shaderProgram;
static std::shared_ptr<Hallucen::GL::ElementArrayBuffer> EBO;
static std::shared_ptr<Hallucen::GL::Texture2D> texture2D;
static std::shared_ptr<Hallucen::GL::Texture2D> texture2D2;
static std::shared_ptr<Hallucen::GL::Camera2D> camera;
static std::shared_ptr<Hallucen::Rectangle> rectangle;
static Hallucen::GL::Renderer renderer;

static float appwidth ;
static float appheight ;

static glm::mat4 proj;
static glm::mat4 view;

static glm::mat4 model;
static glm::mat4 mvp;

static glm::vec3 cameraPos;

static glm::vec3 colour;
void init(int width, int height);
void run();
static void update(float deltaTime);
static inline void errorCallback(int error_code, const char *description) {

  std::cout << "Error: " << error_code << std::endl << description;
}
static void render();
static void ImGuiLogic(float deltaTime);

}; // namespace Application