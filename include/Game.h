#ifndef _GAME_H_
#define _GAME_H_

#define GLFW_INCLUDE_GLU
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include "Constants.h"
#include "GUISession.h"
#include "GameState.h"
#include "GameUtil.h"
#include "MouseTracker.h"
#include "Window.h"

class Game {
  const char *WINDOW_TITLE = "Dodge The Balls";
  const char *INITIAL_MESSAGE = "Press ENTER or S to start:";

  GUISession *session;
  Window *mainWindow;
  MouseTracker *mouseTracker;
  GameState *gameState;
  bool start, finish;
  int startTime, endTime;
  bool checkBound;

  inline bool isNotRunning() { return !start; }

  inline bool isFinished() { return finish; }

  inline bool isStartPressed(GLFWwindow *window) {
    return (glfwGetKey(window, GLFW_KEY_ENTER) || glfwGetKey(window, 'S'));
  }

  inline bool isRestartPressed(GLFWwindow *window) {
    return glfwGetKey(window, 'R');
  }

  void gameEnvironmentInit();
  void startGame();
  void checkBoundary(std::vector<Ball> &balls);
  void dropAll(std::vector<Ball> &balls);
  void checkCollision(std::vector<Ball> &balls, Ball &mouseBall);
  void updateGameState();
  void displayInit();
  void paintBall(Vector3<int> &color, Ball &b);
  void drawFinishScreen();
  void drawInitialScreen();
  void renderGameState();
  void refreshScreen(GLFWwindow *window);

public:
  Game(int argc, char *argv[]);
  ~Game();
  void runMainLoop();
};

#endif /* _GAME_H_ */
