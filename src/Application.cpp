#include "Application.h"
#include "GLFW/glfw3.h"
#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/Texture2D.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/GL/gl.h"
#include "Hallucen/Hallucen.h"
#include "Hallucen/Image.h"
#include <iostream>
#include <memory>
#include <vector>

#include "Hallucen/Rectangle.h"
#include "Hallucen/vector.h"
#include "ext/matrix_transform.hpp"
#include "fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

using namespace Hallucen::GL;

// unsigned int texture;
static float sizex = 0.0f;
static float sizey = 0.0f;
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  std::cout << "here\n";
  // if (action == GLFW_PRESS) {
  switch (key) {

  case GLFW_KEY_A:
    Application::cameraPos.x -= 1;
    break;
  case GLFW_KEY_D:
    Application::cameraPos.x += 1;
    break;
  case GLFW_KEY_W:
    Application::cameraPos.y += 1;
    break;
  case GLFW_KEY_S:
    Application::cameraPos.y -= 1;
    break;

  default:
    break;
  }

  // Application::view = glm::translate(glm::mat4(1.0f),
  // -Application::cameraPos); Application::proj = glm::ortho(0.0f, sizex, 0.0f,
  // sizey, 0.0f, 1.0f);

  // Application::mvp = Application::proj * Application::view *
  // Application::model; Application::shaderProgram->use();
  Application::camera->setPosition(
      {Application::cameraPos.x, Application::cameraPos.y});

  // Application::mvp =
  //     Application::camera->getViewProjMatrix() * Application::model;
  // Application::shaderProgram->setMat4("uProjMatrix", Application::mvp);
  // }
}
void Application::init(int width, int height) {
  appwidth = width;
  appheight = height;

  Hallucen::init();
  Hallucen::initWindow(width, height, "Learning OpenGL");
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(Hallucen::getWindow(), true);
  ImGui_ImplOpenGL3_Init();

  buffer = std::make_shared<VertexBuffer>();
  VAO = std::make_shared<VertexArray>();
  vertexShader = std::make_shared<Shader>(GL_VERTEX_SHADER);
  fragmentShader = std::make_shared<Shader>(GL_FRAGMENT_SHADER);
  shaderProgram = std::make_shared<ShaderProgram>();
  EBO = std::make_shared<ElementArrayBuffer>();
  camera = std::make_shared<Camera2D>((float)width, (float)height, 0.0f, 0.0f);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //   glEnable(GL_BLEND);
  //   glBlendFunc(GL_BLEND_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  texture2D = std::make_shared<Texture2D>();
  texture2D2 = std::make_shared<Texture2D>();
  rectangle = std::make_shared<Hallucen::Rectangle>(
      Hallucen::Vector2{(float)width, (float)height},
      Hallucen::Vector2{0.0f, 0.0f});

  glfwSetErrorCallback(errorCallback);
  std::string vertexShaderSource = Hallucen::loadFile("res/vertex.glsl");
  std::string fragmentShaderSource = Hallucen::loadFile("res/fragment.glsl");

  std::vector<float> vertices{
      //   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
      //     0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
      //      0.5f,   0.5f,  0.0f,  0.0f, 0.0f,
      //       -0.5f, 0.5f, 0.0f,  0.0f, 0.0f

      0.0f,         0.0f,          1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, // bottom left
      (float)width, 0.0f,          0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, // bottom right
      (float)width, (float)height, 0.0f, 0.0f, 1.0f, 1.0f,
      1.0f, // top right
      0.0f,         (float)height, 1.0f, 1.0f, 0.0f, 0.0f,
      1.0f // top left
  };

  std::vector<unsigned int> elements{0, 1, 2, 2, 3, 0};

  vertexShader->load(vertexShaderSource);
  if (!vertexShader->compile()) {
    char infoLog[512];

    glGetShaderInfoLog(vertexShader->getID(), 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  fragmentShader->load(fragmentShaderSource);
  if (!fragmentShader->compile()) {
    char infoLog[512];

    glGetShaderInfoLog(fragmentShader->getID(), 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  shaderProgram->attachShader(vertexShader->getID());
  shaderProgram->attachShader(fragmentShader->getID());
  shaderProgram->link();

  cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);

  camera->setPosition({cameraPos.x, cameraPos.y});

  model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  view = glm::translate(glm::mat4(1.0f), cameraPos);
  proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.0f, 1.0f);
  colour = glm::vec3(1.0f, 1.0f, 1.0f);

  VAO->bind();

  // 2. copy our vertices array in a buffer for OpenGL to use
  buffer->bind();

  mvp = camera->getViewProjMatrix() * model;

  buffer->fill(vertices);

  // vertexArray.createAttribute(2, GL_FALSE, 5, 0);
  // vertexArray.createAttribute(3, GL_FALSE, 5, 2);

  EBO->bind();
  EBO->fill(elements);

  // EBO MUST BE BOUND WHEN CREATING ATTRIBUTES
  VAO->createAttribute(2, GL_FALSE, 7, 0);
  VAO->createAttribute(3, GL_FALSE, 7, 2);
  VAO->createAttribute(2, GL_FALSE, 7, 5);

  std::shared_ptr<Hallucen::Image> image =
      Hallucen::loadImage("res/woodcontainer.jpeg");
  std::shared_ptr<Hallucen::Image> image2 =
      Hallucen::loadImage("res/smiley.png");

  texture2D->bind(0);
  texture2D->setImage(*image);
  texture2D->genMipmap();

  texture2D2->bind(1);
  texture2D2->setImage(*image2);
  texture2D2->genMipmap();

  shaderProgram->use();
  shaderProgram->setInt("uTexture", 0);
  shaderProgram->setInt("uTexture2", 1);
  shaderProgram->setMat4("uModelMatrix", model);

  Hallucen::setUpdateFunc(Application::update);
  Hallucen::setRenderFunction(Application::render);
  Hallucen::setImGuiFunc(Application::ImGuiLogic);

  glfwSetKeyCallback(Hallucen::getWindow(), key_callback);
  rectangle->setColour({1.0f, 1.0f, 1.0f});
}

void Application::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  texture2D->bind(0);
  texture2D2->bind(1);
  DrawData data = rectangle->getData();

  // renderer.draw(*data.VAO, *data.shader, *data.IBO, *camera);

  // data.VAO->bind();
  // data.IBO->bind();

  // glm::mat4 vp = camera->getViewProjMatrix();

  // data.shader->use();

  // data.shader->setMat4("uViewProjectionMatrix", vp);
  // glDrawElements(GL_TRIANGLES, data.IBO->getSize(), GL_UNSIGNED_INT,
  // nullptr);

  // renderer.draw(*VAO, *shaderProgram, *EBO, *camera);
  renderer.draw(data, *camera);
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void Application::update(float deltaTime) {
  // shaderProgram->setVec3("uColour", {colour.x, colour.y, colour.z});

  // std::cout << "before\n";
  // std::cout << mvp[0].x << std::endl;

  // cameraPos.x += 10;
  // std::cout << "after\n";

  // std::cout << mvp[0].x << std::endl;
  // Application::view = glm::translate(glm::mat4(1.0f),
  // Application::cameraPos);

  // Application::mvp = Application::proj * Application::view *
  // Application::model; Application::shaderProgram->use();
  // Application::shaderProgram->setMat4("uProjMatrix", Application::mvp);
  // shaderProgram->setMat4("uProjMatrix", mvp);
}

void Application::ImGuiLogic(float deltaTime) {
  ImGui::Begin("Camera");

  cameraPos.x = camera->getPosition().x;
  cameraPos.y = camera->getPosition().y;
  ImGui::Text("cameraPos.x%.2f", cameraPos.x);
  ImGui::Text("cameraPos.y%.2f", cameraPos.y);

  // ImGui::SliderFloat("zoomOut", &sizey, 0, 1000);
  if (ImGui::Button("zoomIn")) {
    // camera->setPosition({cameraPos.x, cameraPos.y});
  }

  if (ImGui::Button("zoomOut")) {
    // camera->setPosition({cameraPos.x, cameraPos.y});
  }
  ImGui::End();

  mvp = camera->getViewProjMatrix() * model;

  Application::camera->setPosition(
      {Application::cameraPos.x, Application::cameraPos.y});

  double x, y;
  int sizex,sizey;
  glfwGetCursorPos(Hallucen::getWindow(), &x, &y);
  glfwGetWindowSize(Hallucen::getWindow(), &sizex, &sizey);


  glm::vec4 lightpos = glm::vec4(x, y, 1.0f, 1.0f);

  std::cout << lightpos.x << "," << lightpos.y << std::endl;

  rectangle->setLightPos(
      {(lightpos.x) * 2, (sizey - lightpos.y) * 2});
  rectangle->setColour({1.0f, 0.0f, 0.0f});
  // Application::mvp = Application::proj * Application::view *
  // Application::model;
}

void Application::run() {
  Hallucen::mainLoop();
  Hallucen::cleanup();
}