
#include "Hallucen/Hallucen.h"
#include "GLFW/glfw3.h"
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/Image.h"
#include "Hallucen/Scene.h"
#include "Hallucen/Stopwatch.h"
#include "Hallucen/vector.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stb_image.h>
#include <string>
#include "tracy/Tracy.hpp"
using namespace Hallucen;

struct EngineData {

  GLFWwindow *window = nullptr;
  bool initialised = false;
  std::shared_ptr<GL::Renderer> renderer;

  Vector2i size;
  Vector2i frameBuffersize;
  std::shared_ptr<Scene> Hscene;
};

static EngineData data;

bool Engine::init() {
  data.initialised = true;
  if (!glfwInit()) {

    std::cout << "Failed to initialise Glfw\n";
    data.initialised = false;
    return false;
  }
  data.initialised = true;
  return true;
}

bool Engine::initWindow(int width, int height, const std::string &name) {
  if (!data.initialised) {
    std::cout << "GLFW has not been initialised\n";
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  data.window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

  if (data.window == nullptr) {
    std::cout << "Failed to initialise window";
    return false;
  }
  glfwMakeContextCurrent(data.window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return false;
  }
  data.size = {width, height};
  glfwSetFramebufferSizeCallback(data.window, frameBufferSizeCallback);
  glfwSetErrorCallback(errorCallback);

  stbi_set_flip_vertically_on_load(1);
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(Engine::getWindow(), true);
  ImGui_ImplOpenGL3_Init();
  GL::Renderer::init();

  return true;
}

void Engine::Update(float deltaTime) {}

void Engine::mainLoop() {}

void Engine::cleanup() {

  if (!data.initialised) {
    std::cout << "Hallucen was not initialised,nothing to clean up\n";
    return;
  }

  glfwDestroyWindow(data.window);
  glfwTerminate();
}

std::string Engine::loadFile(const std::string &path) {
  std::ifstream t(path);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

GLFWwindow *Engine::getWindow() { return data.window; }

std::shared_ptr<Image> Engine::loadImage(const std::string &path) {
  int width, height, nrChannels;
  unsigned char *data =
      stbi_load(path.c_str(), &width, &height, &nrChannels, 4);

  std::shared_ptr<Image> imageptr = std::make_shared<Image>();
  imageptr->width = width;
  imageptr->height = height;
  imageptr->nrchannels = nrChannels;
  imageptr->data = data;

  return imageptr;
}

Vector2i Engine::getSize() {

  //  glfwGetFramebufferSize(window, &size.x, &size.y);
  glfwGetWindowSize(data.window, &data.size.x, &data.size.y);

  return data.size;
}
Vector2i Engine::getFrameBufferSize() {

  //  glfwGetFramebufferSize(window, &size.x, &size.y);
  glfwGetFramebufferSize(data.window, &data.frameBuffersize.x,
                         &data.frameBuffersize.y);

  return data.frameBuffersize;
}

void Engine::runScene(std::shared_ptr<Scene> scene) {
  float totalframetime;
  data.Hscene = scene;

  while (!glfwWindowShouldClose(data.window)) {
    ZoneScoped;
    GL::Renderer::clear({0.0f, 0.0f, 0.0f});

    Stopwatch watch;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    scene->ImGuiLogic(totalframetime);
    scene->render();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(data.window);

    glfwPollEvents();
    Update(watch.getTimeMs());
    scene->update(watch.getTimeMs());
    totalframetime = watch.getTimeMs();
  }
}

void Engine::frameBufferSizeCallback(GLFWwindow *win, int width, int height) {
  data.size.x = width;
  data.size.y = height;
  glViewport(0, 0, width, height);

  // TODO fix weird resizing problem
  data.Hscene->winSizeChanged(data.size);
}