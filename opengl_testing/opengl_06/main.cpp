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
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for MAC
  std::cout << "END OF GAME" << std::endl;
  
  // object that holds window data
  // first two arguments is width and height of the window
  // third argument is name of the window
  // last two arguments we can ignore (the tutorial said it later I will write what they mean) TODO
  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  // check if the object was created
  // if no, print error and exit
  if(window == NULL){
    std::cout << "Failed to create GLFW window " << __LINE__ << std::endl;
    glfwTerminate();
    return -1;
  }
  // if the window is created, we say that the window (object) is current
  // by internet opengl is state machine and if we want to swith between more we will use this command
  // (used in multithreaded opengl)
  // (if I understand this correctly)
  glfwMakeContextCurrent(window);
  
  // glad manages pointers to the opengl functions
  // the function pointers is OS specific
  // it will help us find correct function to the OS which the code is compiled for
  // if it failed load, it return error and 
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  //
  glViewport(0, 0, 800, 600);
  
  return 0;
}
