#ifndef _MOUSE_TRACKER_H_
#define _MOUSE_TRACKER_H_

#define GLFW_INCLUDE_GLU
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include "Constants.h"
#include "GameUtil.h"

class MouseTracker {
  GLFWwindow *window;
  Ball mouseBall;
  std::thread *mouse;

public:
  MouseTracker(GLFWwindow *window);
  Ball &getMouseBall();
};

#endif /* _MOUSE_TRACKER_H_ */
