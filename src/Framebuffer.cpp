
#include "Hallucen/GL/Framebuffer.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/Hallucen.h"
#include "Hallucen/vector.h"
#include "glad/glad.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace Hallucen;
using namespace Hallucen::GL;

Framebuffer::Framebuffer(Vector2 size, Vector2 pos) : m_Position(pos),m_Size(size) {
  glGenFramebuffers(1, &m_ID);
  bind();
  m_Tex = std::make_shared<Texture2D>();

  m_Tex->bind(1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         m_Tex->getID(), 0);
  textureAttached = true;

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "COMPLETE\n";
  }

  Shader fragmentShader(GL_FRAGMENT_SHADER);
  Shader vertexShader(GL_VERTEX_SHADER);
  std::string vertSource =
      Hallucen::loadFile("res/Hallucen/Renderer/Framebuffer/vertex.glsl");
  std::string fragSource =
      Hallucen::loadFile("res/Hallucen/Renderer/Framebuffer/fragment.glsl");

  vertexShader.load(vertSource);
  if (!vertexShader.compile()) {
    char infoLog[512];

    glGetShaderInfoLog(vertexShader.getID(), 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
    exit(-1);
  }

  fragmentShader.load(fragSource);
  if (!fragmentShader.compile()) {
    char infoLog[512];

    glGetShaderInfoLog(fragmentShader.getID(), 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
    exit(-1);
  }

  program.attachShader(vertexShader.getID());
  program.attachShader(fragmentShader.getID());

  program.link();
  Vector2 halfsize;

  halfsize.x = size.x / 2;
  halfsize.y = size.y / 2;

  Vector3 colour = {1.0f, 1.0f, 1.0f};

  std::vector<float> verts{
      m_Position.x, m_Position.y, colour.x, colour.y, colour.z, 0.0f, 0.0f

      ,
      // bottom left
      m_Position.x + size.x, m_Position.y,

      colour.x,

      colour.y,

      colour.z,

      0.0f, 1.0f

      ,
      // bottom right
      m_Position.x + size.x, m_Position.y + size.y,

      colour.x,

      colour.y,

      colour.z, 1.0f, 1.0f

      ,
      // top right
      m_Position.x, m_Position.y + size.y, colour.x,

      colour.y,

      colour.z,

      1.0f, 0.0f

      // top left
  };

  VAO.bind();
  VBO.bind();
  IBO.bind();
  std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0};

  VBO.fill(verts);
  IBO.fill(indices);
  VAO.createAttribute(2, GL_FALSE, sizeof(float) * 7, 0);
  VAO.createAttribute(3, GL_FALSE, sizeof(float) * 7, 2 * sizeof(float));
  VAO.createAttribute(2, GL_FALSE, sizeof(float) * 7, 5 * sizeof(float));

  data.IBO = &IBO;
  data.VAO = &VAO;
  data.shader = &program;
  program.use();
  program.setInt("tex", 1);

  unBind();
}

void Framebuffer::bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
  //   m_Tex->bind(1);
}

void Framebuffer::bindTexture() { m_Tex->bind(1); }
void Framebuffer::bindRead() { glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ID); }
void Framebuffer::bindDraw() { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_ID); }

void Framebuffer::unBind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

Framebuffer::~Framebuffer() {
  glDeleteFramebuffers(1, &m_ID);
  unBind();
}