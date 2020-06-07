#include "Window.h"

Window::Window(int width, int height, const char *title) {
  window = glfwCreateWindow(width, height, title, NULL, NULL);
}

Window::~Window() { glfwDestroyWindow(window); }

void Window::Init() {
  glfwMakeContextCurrent(window);

  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0, 0, 0, 0);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glDisable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

GLFWwindow *Window::getWindow() { return window; }
