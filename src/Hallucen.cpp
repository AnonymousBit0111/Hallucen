
#include "Hallucen/Hallucen.h"
#include "GLFW/glfw3.h"
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/Image.h"
#include "Hallucen/Scene.h"
#include "Hallucen/Stopwatch.h"
#include "Hallucen/vector.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_mouse.h"
#include "SDL2/SDL_video.h"
#include "fwd.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui_impl_sdl.h"
#include "tracy/Tracy.hpp"
#include <SDL2/SDL.h>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <ratio>
#include <sstream>
#include <stb_image.h>
#include <string>
#include <thread>

using namespace Hallucen;

struct EngineData {

  SDL_Window *window = nullptr;
  SDL_GLContext context;
  bool initialised = false;
  bool windowOpen = false;
  std::shared_ptr<GL::Renderer> renderer;

  Vector2i size;
  Vector2i frameBuffersize;
  std::shared_ptr<Scene> Hscene;
  std::map<SDL_Keycode, bool> keyboard;
};

static EngineData data;

bool Engine::init() {

  data.initialised = true;
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {

    std::cout << "Failed to initialise SDL\n";
    data.initialised = false;
    return false;
  }
  SDL_GL_LoadLibrary(NULL);
  data.initialised = true;

  return true;
}

bool Engine::initWindow(int width, int height, const std::string &name) {
  if (!data.initialised) {
    std::cout << "GLFW has not been initialised\n";
    return false;
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

  //   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  //   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // #ifdef __APPLE__
  //   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // #endif
  //   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  data.window =
      SDL_CreateWindow("name", 0, 0, width, height, SDL_WINDOW_OPENGL);

  if (data.window == nullptr) {
    std::cout << "Failed to initialise window";
    return false;
  }
  data.context = SDL_GL_CreateContext(data.window);
  SDL_GL_MakeCurrent(data.window, data.context);

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return false;
  }
  data.size = {width, height};

  // glfwSetFramebufferSizeCallback(data.window, frameBufferSizeCallback);
  // glfwSetErrorCallback(errorCallback);

  stbi_set_flip_vertically_on_load(1);
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // ImGui_ImplSDL2_InitForOpenGL(Engine::getWindow(), true);
  ImGui_ImplSDL2_InitForOpenGL(data.window, data.context);
  ImGui_ImplOpenGL3_Init();
  GL::Renderer::init();

  return true;
}

void Engine::Update(float deltaTime) {}

bool Engine::isKeyDown(SDL_Keycode key) { return data.keyboard[key]; }

void Engine::mainLoop() {}

void Engine::cleanup() {

  if (!data.initialised) {
    std::cout << "Hallucen was not initialised,nothing to clean up\n";
    return;
  }

  // glfwDestroyWindow(data.window);
  SDL_DestroyWindow(data.window);
  SDL_Quit();
}

std::string Engine::loadFile(const std::string &path) {
  std::ifstream t(path);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

SDL_Window *Engine::getWindow() { return data.window; }

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
  SDL_GetWindowSize(data.window, &data.size.x, &data.size.y);

  return data.size;
}
Vector2i Engine::getFrameBufferSize() {

  //  glfwGetFramebufferSize(window, &size.x, &size.y);
  SDL_GL_GetDrawableSize(data.window, &data.frameBuffersize.x,
                         &data.frameBuffersize.y);

  return data.frameBuffersize;
}

void Engine::runScene(std::shared_ptr<Scene> scene) {
  TracyFunction;
  float totalframetime;
  data.Hscene = scene;

  data.windowOpen = true;
  while (data.windowOpen) {
    ZoneScopedN("frame");
    Stopwatch watch;
    GL::Renderer::clear({0.0f, 0.0f, 0.0f});

    ImGui_ImplOpenGL3_NewFrame();
    // ImGui_ImplGlfw_NewFrame();
    ImGui_ImplSDL2_NewFrame(data.window);
    ImGui::NewFrame();
    scene->ImGuiLogic(totalframetime);
    scene->render();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(data.window);

    // glfwPollEvents();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) {
        data.windowOpen = false;
      } else if (event.type == SDL_KEYDOWN) {
        data.keyboard[event.key.keysym.sym] = true;

        scene->handleKey(event.key.keysym.sym);
      } else if (event.type == SDL_KEYUP) {
        data.keyboard[event.key.keysym.sym] = false;
      }
    }
    Update(watch.getTimeMs());
    scene->update(watch.getTimeMs());
    totalframetime = watch.getTimeMs();

    if (totalframetime < 8.0f) {
      ZoneScopedN("sleeping");
      int frametimenano = totalframetime * 1000000;
      std::chrono::nanoseconds secs(8000000 - frametimenano);
      std::this_thread::sleep_for(secs);
    }
  }
}

void Engine::frameBufferSizeCallback(GLFWwindow *win, int width, int height) {
  data.size.x = width;
  data.size.y = height;
  glViewport(0, 0, width, height);

  // TODO fix weird resizing problem
  // data.Hscene->winSizeChanged(data.size);
}

glm::vec2 Engine::getMousePosition() {
  int x, y;
  SDL_GetMouseState(&x, &y);
  y = data.size.y - y;
  return glm::vec2(x, y);
}