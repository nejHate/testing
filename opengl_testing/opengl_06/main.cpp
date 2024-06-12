// github.com/JoeyDeVries/learnopengl
#include <iostream>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


// for now we create simple vertex shader
// vertex shader is the part of rendering we can programe
// vertex shader look similar to C/C++
// this is only temporary so we can render the triangle
// later it will be discuss in more detail
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

// just for testing time
long long current_time() {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
}

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
  // GLFWwindow* window = glfwCreateWindow(1920, 1080, "LearnOpenGL", NULL, NULL);
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
  
  // i am going by the book so now they create a function called framebuffer_size_callback
  // look above to find it, it will be used in next code
  
  // there is many types of callback
  // callback is registered after we create window and before the render loop
  // this will tell the GLFW that to call function on every resize window event
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
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
  // glViewport(0, 0, 1920, 1080);
  
  // we can set the "background" color so when the glClear is called, it will set the entire buffer to that colour
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  
  // just to see the performance, we can disable the wait for screen to swap bufers
  // because without that it only create 60 swaps when using 60fps monitor
  glfwSwapInterval(0);
  
  // to render a single triangle, we must specify the vertex of the triangle
  float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
     };

  // I don't really know what exactly all these steps do but I will try to explain them as I can
	
  // this is an inteager storinf an ID of the buffer we create
  unsigned int VBO;
  // we create an object buffer and bind it to the ID
  glGenBuffers(1, &VBO);
  // 
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  // vertex shader
  // shader is dynamically compiled at run-time from source code
  // first we must create an unsigned int to store the ID of object
  unsigned int vertexShader;
  // we provide the type of shader we want vertex shader -> GL_VERTEX_SHADER
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // this function tahes the object with ID, number of strings, string with vertex shader and the last argument we set to NULL
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  // now we compile the shader now
  glCompileShader(vertexShader);
  
  // if we want to check if the compilation was successfull, we can check it
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  
  if(!success){
  glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
  std::cout << "ERROR shader vertex compilation failed\n" << infoLog << " " << __LINE__ << std::endl;
  }
  
  // fragment shader 
  // it is second and last shader we create for rendering triangle
  // fragment shader is all about calculating the color output of pixel
  // to keep it now simple we output always orange color
  // (color have 4 values Red, Green, Blue and Alpha)
  // we define the string up in this file and call it fragmentShaderSource
  // the process of making and compiling will be similar to vertex shader
  // TODO
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // shader program
  // it will combine multiple shaders combined
  // we will link them to a shader program and activate it when rendering objects
  //first we will create an program and return the ID of the shader program
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  // after that we attach the the compiled shaders into the program
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  // and then link them
  glLinkProgram(shaderProgram);
  // we can check if the the linking was successfully
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success){
  glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
  std::cout << "ERROR shader program linking shader and vertex fragment failed\n" << infoLog << " " << __LINE__ << std::endl;
  }
  // now activate the program
  glUseProgram(shaderProgram);
  // and delete shaders object because we no longer need them
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // we are almost there but now we must tell the opengl how to interpret the vertex data before rendering
  // our vertex data is formatted as follow
  // | vertex 0  | vertex 1  | vertex 2  |
  // | X | Y | Z | X | Y | Z | X | Y | Z |
  // 0   4   8   12  16  20  24  28  32  36 bytes
  // it is 12 bytes per vertex and there is no space between each vertex and the data starts with offset 0
  //with information we can tell the opengl how it should interpret the vertex data (per vertex attribute) using
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  
  // TODO
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  // 0. copy our vertices array in a buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // 1. then set the vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
  (void*)0);
  glEnableVertexAttribArray(0);
  // 2. use our shader program when we want to render an object
  glUseProgram(shaderProgram);
  // 3. now draw the object
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);



  
  // creating the game loop
  // the while loop end, when the user click the close button
  // later there will be more option to exit the loop
  uint64_t framecounter = 0;  // why not 32 bit? well realistically nobody open game for 138 days with 360 fps but...
  auto start = current_time();
  while(!glfwWindowShouldClose(window)){
    // we call glClear to clean the buffer to default background we set
    // the GL_COLOR_BUFFER_BIT is command which is saying what we want to clear
    // we can clear/set COLOR, DEPTH and STENCIL but now we clear the color buffer
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
    
    //std::cout << framecounter << std::endl;
    // just automatic closing when programing, so i can just wait to close
    if(framecounter == 10000){
      glfwSetWindowShouldClose(window, true);
    }
  }
  auto end = current_time();
  std::cout << "number of frames: " << framecounter << std::endl;
  std::cout << "framerate: "<< framecounter/((float)(end-start)/1000000000) << "fps" << std::endl;
  std::cout << "END OF GAME" << std::endl << std::endl;
  
  return 0;
}
