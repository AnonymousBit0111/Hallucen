
#include "Hallucen/Hallucen.h"
#include "GLFW/glfw3.h"
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/Image.h"
#include "Hallucen/Stopwatch.h"
#include "Hallucen/vector.h"
#include "Hallucen/Scene.h"
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
using namespace Hallucen;

bool Hallucen::init() {

  if (!glfwInit()) {

    std::cout << "Failed to initialise Glfw\n";
    initialised = false;
    return false;
  }
  initialised = true;
  return true;
}

bool Hallucen::initWindow(int width, int height, const std::string &name) {
  if (!initialised) {
    std::cout << "GLFW has not been initialised\n";
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

  if (window == nullptr) {
    std::cout << "Failed to initialise window";
    return false;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return false;
  }
  size = {(float)width, (float)height};
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
  glfwSetErrorCallback(errorCallback);

  stbi_set_flip_vertically_on_load(1);
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(Hallucen::getWindow(), true);
  ImGui_ImplOpenGL3_Init();
  GL::Renderer::init();

  return true;
}

void Hallucen::Update(float deltaTime) {
  
}

void Hallucen::mainLoop() {}

void Hallucen::cleanup() {

  if (!initialised) {
    std::cout << "Hallucen was not initialised,nothing to clean up\n";
    return;
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}


std::string Hallucen::loadFile(const std::string &path) {
  std::ifstream t(path);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

GLFWwindow *Hallucen::getWindow() { return window; }

std::shared_ptr<Image> Hallucen::loadImage(const std::string &path) {
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

Vector2 Hallucen::getSize() { return size; }

void Hallucen::runScene(Scene scene) {
  float totalframetime;

  while (!glfwWindowShouldClose(window)) {
    GL::Renderer::clear({0.0f, 0.0f, 0.0f});

    Stopwatch watch;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    scene.ImGuiLogic(totalframetime);
    scene.render();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);

    glfwPollEvents();
    Update(watch.getTimeMs());
    scene.update(watch.getTimeMs());
    totalframetime = watch.getTimeMs();
  }
}

void Hallucen::frameBufferSizeCallback(GLFWwindow *win, int width, int height) {
  size.x = (float)width;
  size.y = (float)height;
  glViewport(0, 0, width, height);
}