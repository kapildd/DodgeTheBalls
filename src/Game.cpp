#include "Game.h"

Game::Game(int argc, char *argv[]) {
  glutInit(&argc, argv);
  gameEnvironmentInit();
}

Game::~Game() {
  delete mouseTracker;
  delete mainWindow;
  delete session;
  delete gameState;
}

void Game::runMainLoop() {
  GLFWwindow *window = mainWindow->getWindow();
  int frame = 0, targetFps = 60;
  int targetDelayInMs = 1000 / targetFps;
  int frameStartTime, frameEndTime, additionalDelayInMs;
  while (!glfwGetKey(window, GLFW_KEY_ESCAPE) &&
         !glfwWindowShouldClose(window)) {
    frame++;
    frameStartTime = glutGet(GLUT_ELAPSED_TIME);
    updateGameState();
    refreshScreen(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
    frameEndTime = glutGet(GLUT_ELAPSED_TIME);
    additionalDelayInMs = targetDelayInMs - (frameEndTime - frameStartTime + 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(additionalDelayInMs));
  }
}

void Game::gameEnvironmentInit() {
  session = new GUISession();
  mainWindow = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  mainWindow->Init();
  mouseTracker = new MouseTracker(mainWindow->getWindow());
  gameState = new GameState();
}

void Game::startGame() {
  startTime = glutGet(GLUT_ELAPSED_TIME); // note down the initial time
  checkBound = true;
  gameState->InitGameState();
  start = true;
  finish = false;
}

void Game::checkBoundary(std::vector<Ball> &balls) {
  if (checkBound == true) {
    for (Ball &b : balls) {
      if (b.center.x >= WINDOW_WIDTH / 2 - BALL_RADIUS) {
        b.center.x = WINDOW_WIDTH / 2 - BALL_RADIUS;
        b.velocity.x *= -1;
      } else if (b.center.x <= BALL_RADIUS - WINDOW_WIDTH / 2) {
        b.center.x = BALL_RADIUS - WINDOW_WIDTH / 2;
        b.velocity.x *= -1;
      }
      if (b.center.y >= WINDOW_HEIGHT / 2 - BALL_RADIUS) {
        b.center.y = WINDOW_HEIGHT / 2 - BALL_RADIUS;
        b.velocity.y *= -1;
      } else if (b.center.y <= BALL_RADIUS - WINDOW_HEIGHT / 2) {
        b.center.y = BALL_RADIUS - WINDOW_HEIGHT / 2;
        b.velocity.y *= -1;
      }
    }
  }
}

void Game::dropAll(std::vector<Ball> &balls) {
  checkBound = false;
  if (finish == false)
    endTime = glutGet(GLUT_ELAPSED_TIME);
  finish = true;
  for (Ball &b : balls) {
    b.velocity.x = 0;
    b.velocity.y = -1.5;
  }
}

void Game::checkCollision(std::vector<Ball> &balls, Ball &mouseBall) {
  for (size_t i = 0; i < balls.size(); i++)
    for (size_t j = i + 1; j < balls.size(); j++) {
      if (GameUtil::distance(balls[i], balls[j]) <= 2 * BALL_RADIUS)
        GameUtil::calculateCollisionImpact(balls[i], balls[j]);
    }

  // if collision is with ball controlled by mouse then game is over
  for (size_t i = 0; i < balls.size(); i++)
    if (GameUtil::distance(balls[i], mouseBall) <= 2 * BALL_RADIUS)
      if (start == true)
        dropAll(balls);
}

void Game::updateGameState() {
  std::vector<Ball> balls = gameState->getBalls();
  checkCollision(balls, mouseTracker->getMouseBall());
  checkBoundary(balls);
  for (Ball &b : balls)
    b.center += b.velocity;
  gameState->setBalls(balls);
}

void Game::displayInit() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WINDOW_WIDTH / 2, WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2,
          WINDOW_HEIGHT / 2, -50.0, 50.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Game::paintBall(Vector3<int> &color, Ball &b) {
  glColor3d(color.x, color.y, color.z);
  glPushMatrix();
  glTranslated(b.center.x, b.center.y, 0.0);
  glutSolidSphere(b.radius, 30, 30);
  glPopMatrix();
}

void Game::drawFinishScreen() {
  int t = (endTime - startTime) / 1000;
  char integer_string[32];
  sprintf(integer_string, "%d", t);
  char other_string[64] = "Time: "; // make sure you allocate enough space to
                                    // append the other string
  strcat(other_string, integer_string);
  strcat(other_string, " seconds");
  char gameover[32] = "Game Over";
  char retry[32] = "Press R to retry";
  glColor3f(1.0, 1.0, 1.0);
  GameUtil::renderBitmapString(-40, 00, 0, other_string);
  GameUtil::renderBitmapString(-30, 10, 0, gameover);
  GameUtil::renderBitmapString(-40, 20, 0, retry);
}

void Game::drawInitialScreen() {
  glColor3f(0.0, 1.0, 1.0);
  GameUtil::renderBitmapString(-50, 0, 0, INITIAL_MESSAGE);
}

void Game::renderGameState() {
  displayInit();
  std::vector<Ball> balls = gameState->getBalls();
  Vector3<int> redColor(1, 0, 0);
  paintBall(redColor, mouseTracker->getMouseBall());
  Vector3<int> yellowColor(1, 1, 0);
  for (Ball &b : balls)
    paintBall(yellowColor, b);
  // if the game was not started
  if (!start && !finish)
    drawInitialScreen();
  // if game was finished display the time
  if (finish)
    drawFinishScreen();

  glFlush();
  glGetError();
}

void Game::refreshScreen(GLFWwindow *window) {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  height = height > 0 ? height : 1;
  glViewport(0, 0, width, height);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  if (isNotRunning() && isStartPressed(window))
    startGame();
  else if (isFinished() && isRestartPressed(window))
    startGame();

  renderGameState();
}
