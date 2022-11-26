#include "Hallucen/GL/Shader.h"
#include <fstream>
#include <istream>
using namespace Hallucen::GL;

Shader::Shader(GLenum type) : type(type) { m_ID = glCreateShader(type); }

bool Shader::load(std::string &data) {
  std::fstream stream;

  const char *datacstr = data.c_str();

  glShaderSource(m_ID, 1, &datacstr, NULL);

  return true;
}

bool Shader::compile() {
  glCompileShader(m_ID);
  int compiled;

  glGetShaderiv(m_ID, GL_COMPILE_STATUS, &compiled);

  if (compiled == GL_FALSE) {
    return false;
  }
  return true;
}
unsigned int Shader::getID() { return m_ID; }

Shader::~Shader() {}