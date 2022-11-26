#pragma once
#include "glad/glad.h"
#include <string>

namespace Hallucen {

namespace GL {

class Shader {
private:
  unsigned int m_ID = 0;
  GLenum type;

public:
    Shader(GLenum type);
    bool load(std::string &data);
    bool compile();

    unsigned int getID();
    ~Shader();
};
} // namespace GL
} // namespace Hallucen