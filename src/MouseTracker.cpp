#include "MouseTracker.h"

void trackMouse(GLFWwindow *window, Ball &mouseBall) {
  double xpos, ypos;
  while (true) {
    glfwGetCursorPos(window, &xpos, &ypos);
    mouseBall.center.x =
        (xpos < BALL_RADIUS)
            ? (xpos + BALL_RADIUS - WINDOW_WIDTH / 2)
            : (xpos - (xpos > (WINDOW_WIDTH - BALL_RADIUS)) * BALL_RADIUS -
               WINDOW_WIDTH / 2);
    mouseBall.center.y =
        -((ypos < BALL_RADIUS)
              ? (ypos + BALL_RADIUS - WINDOW_HEIGHT / 2)
              : (ypos - (ypos > (WINDOW_HEIGHT - BALL_RADIUS)) * BALL_RADIUS -
                 WINDOW_HEIGHT / 2));
  }
}

MouseTracker::MouseTracker(GLFWwindow *window) {
  mouseBall = GameUtil::getRandomBall(BALL_RADIUS, WINDOW_WIDTH, WINDOW_HEIGHT);
  mouse = new std::thread(trackMouse, window, std::ref(mouseBall));
}

Ball &MouseTracker::getMouseBall() { return mouseBall; }
