#pragma once

#include "Hallucen/GL/Shader.h"
#include "Hallucen/vector.h"
#include "glm/glm.hpp"
namespace Hallucen {
namespace GL {
class ShaderProgram {
private:
  unsigned int m_ID;

public:
  ShaderProgram();
  void attachShader(unsigned int shaderID);
  void link();
  unsigned int getID();
  void use();

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setVec3(const std::string &name, Hallucen::Vector3 value) const;
  void setVec2(const std::string &name, Hallucen::Vector2 value) const;
  void setMat4(const std::string &name, glm::mat4 &value) const;
  ~ShaderProgram();
};
} // namespace GL
} // namespace Hallucen