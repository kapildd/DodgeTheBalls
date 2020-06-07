#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <vector>

#include "Ball.h"
#include "Constants.h"
#include "GameUtil.h"

class GameState {
  const int BALL_COUNT = 5;
  std::vector<Ball> balls;

public:
  GameState() {}
  void InitGameState();
  std::vector<Ball> getBalls();
  void setBalls(std::vector<Ball> &balls);
};

#endif /* _GAME_STATE_H_ */
