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

  glLightfv(GL_LIGHT0, GL_AMBIENT, LIGHT_AMBIENT);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHT_DIFFUSE);
  glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_SPECULAR);
  glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);

  glMaterialfv(GL_FRONT, GL_AMBIENT, MAT_AMBIENT);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, MAT_DIFFUSE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, MAT_SPECULAR);
  glMaterialfv(GL_FRONT, GL_SHININESS, HIGH_SHININESS);
}

GLFWwindow *Window::getWindow() { return window; }
