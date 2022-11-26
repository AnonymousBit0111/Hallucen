#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/vector.h"
#include "glad/glad.h"
using namespace Hallucen::GL;

ShaderProgram::ShaderProgram() { m_ID = glCreateProgram(); }

void ShaderProgram::attachShader(unsigned int shaderID) {
  glAttachShader(m_ID, shaderID);
  // NOTE this could be dangerous to do
  glad_glDeleteShader(shaderID);
}

void ShaderProgram::link() { glLinkProgram(m_ID); }

void ShaderProgram::use() { glUseProgram(m_ID); }

unsigned int ShaderProgram::getID() { return m_ID; }

void ShaderProgram::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}
void ShaderProgram::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}
void ShaderProgram::setVec3(const std::string &name, Vector3 value) const {
  glUniform3f(glGetUniformLocation(m_ID, name.c_str()), value.x, value.y,
              value.z);
}

void ShaderProgram::setMat4(const std::string &name, glm::mat4 &value) const {
  glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE,
                     &value[0][0]);
}

void ShaderProgram::setVec2(const std::string &name,
                            Hallucen::Vector2 value) const {
  glUniform2f(glGetUniformLocation(m_ID, name.c_str()), value.x, value.y);
}

ShaderProgram::~ShaderProgram() { glDeleteProgram(m_ID); }