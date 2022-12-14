/* Ask for an OpenGL Core Context */
#include "Hallucen/GL/Shader.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/Hallucen.h"
#include "Hallucen/Scene.h"
#include "Hallucen/window.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace Hallucen::GL;
int main() {
  Hallucen::init();
  Hallucen::initWindow(1024, 720, "Pathfinder");
  Hallucen::runScene(std::make_shared<Scene>());
  Hallucen::cleanup();
  return 0;
}
