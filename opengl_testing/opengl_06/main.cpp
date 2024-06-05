#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// if the window be resized, the glfwSetFrambufferSizeCallback will call this function
// this function just change the glViewport
void framebuffer_size_callback(GLFWwindow *window, int width, int height){
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
  //if the esc key is pressed the window will close
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    //set the parameter to true so when it start checking the while cycle it will end the while cycle
    glfwSetWindowShouldClose(window, true);
  }
}

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
  
  // object that holds window data
  // first two arguments is width and height of the window
  // third argument is name of the window
  // last two arguments we can ignore (the tutorial said it later I will write what they mean) TODO
  // by chatgpt:
  // GLFWmonitor *monitor -> the monitor to use for full-screen mode (can be NULL for windowed mode)
  // GLFWwindow *share -> The window whose context to share resources with (can be NULL)
  // this command create a window of the size first and second parameter
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
  
  // I have some thoughts what this do so sorry if the explanation isn't correct
  // it will transform coordinates from (-1, 1) to (0, widows_size)
  // so if we set window size and viewport to same number
  // the coordination (-0.5, 0.5) to (200, 450)
  // chatgpt: this defines the tranformation between normalized device coordinates and window coordinates
  // if the numbers is larger, it will show only a portion of the image
  // if the numbers is smaller, it will show the image in portion of the window surrounded by blank space
  glViewport(0, 0, 800, 600);
  
  // i am going by the book so now they create a function called framebuffer_size_callback
  // look above to find it, it will be used in next code
  
  // there is many types of callback
  // callback is registered after we create window and before the render loop
  // this will tell the GLFW that to call function on every resize window event
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
  // we can set the "background" color so when the glClear is called, it will set the entire buffer to that colour
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  
  // creating the game loop
  // the while loop end, when the user click the close button
  // later there will be more option to exit the loop
  uint64_t framecounter = 0;  // why not 32 bit? well realistically nobody open game for 138 days with 360 fps but...
  while(!glfwWindowShouldClose(window)){
    // we call glClear to clean the buffer to default background we set
    glClear(GL_COLOR_BUFFER_BIT);
    // there are two buffers, one is being displayed and rendering is happening on the second and they swap
    // why is there two you can find online
    // write: why double buffering and read why
    // there can be more buffers like triple buffering but I'm new to opengl so I don't know how how to implement etc
    glfwSwapBuffers(window);
    // this function check if any events happens and update the window state and calls the corresponding events
    // like keyboard, mouse (and probably resize too)
    glfwPollEvents();
    
    // increase the number of frames counter
    framecounter++;
    // just automatic closing when programing, so i can just wait to close
    if(framecounter == 200){
      glfwSetWindowShouldClose(window, true);
    }
  }
  std::cout << "number of frames: " << framecounter << std::endl;
  std::cout << "END OF GAME" << std::endl;
  
  return 0;
}
