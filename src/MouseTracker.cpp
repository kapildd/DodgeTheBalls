#include "MouseTracker.h"

void trackMouse(GLFWwindow *window, Ball &mouseBall, bool &isActive) {
  double xpos, ypos;
  double minXPos = -WINDOW_WIDTH/2 + BALL_RADIUS;
  double maxXPos = WINDOW_WIDTH/2 - BALL_RADIUS;
  double minYPos = -WINDOW_HEIGHT/2 + BALL_RADIUS;
  double maxYPos = WINDOW_HEIGHT/2 - BALL_RADIUS;

  while (isActive) {
    glfwGetCursorPos(window, &xpos, &ypos);
    mouseBall.center.x = xpos - WINDOW_WIDTH / 2;
    mouseBall.center.y = -(ypos - WINDOW_HEIGHT / 2);
    mouseBall.center.x = std::max(mouseBall.center.x, minXPos);
    mouseBall.center.x = std::min(mouseBall.center.x, maxXPos);
    mouseBall.center.y = std::max(mouseBall.center.y, minYPos);
    mouseBall.center.y = std::min(mouseBall.center.y, maxYPos);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

MouseTracker::MouseTracker(GLFWwindow *window) {
  mouseBall = GameUtil::getRandomBall(BALL_RADIUS, WINDOW_WIDTH, WINDOW_HEIGHT);
  isActive = true;
  mouse = new std::thread(trackMouse, window, std::ref(mouseBall), std::ref(isActive));
}

MouseTracker::~MouseTracker() {
  isActive = false;
  mouse->join();
  delete mouse;
}

Ball &MouseTracker::getMouseBall() { return mouseBall; }
