/* Ask for an OpenGL Core Context */
#include "Application.h"
#include "Hallucen/GL/Shader.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/Hallucen.h"
#include "Hallucen/window.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace Hallucen::GL;
int main(){
  Application::init(1000, 720);
  Application::run();

  return 0;
}

