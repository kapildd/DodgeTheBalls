#include "GameState.h"

void GameState::InitGameState() {
  balls.clear();
  for (int i = 0; i < BALL_COUNT; i++) {
    Ball b = GameUtil::getRandomBall(BALL_RADIUS, WINDOW_WIDTH, WINDOW_HEIGHT);
    balls.push_back(b);
  }
}

std::vector<Ball> GameState::getBalls() { return balls; }

void GameState::setBalls(std::vector<Ball> &balls) { this->balls = balls; }
