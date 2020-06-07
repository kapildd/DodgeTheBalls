#ifndef _WINDOW_H_
#define _WINDOW_H_

#define GLFW_INCLUDE_GLU
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include "Constants.h"

class Window {
  GLFWwindow *window;

public:
  Window(int width, int height, const char *title);
  ~Window();
  void Init();
  GLFWwindow *getWindow();
};

#endif /* _WINDOW_H_ */
