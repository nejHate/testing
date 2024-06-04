#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
  // initialization of GLFW
  glfwInit();
  // setting major version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  // setting minor version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // seting GLFW to core_profile
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // for MAC (to run the app on mac)
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for MAC
  std::cout << "END OF GAME" << std::endl;
  return 0;
}
