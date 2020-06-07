#ifndef _GAME_UTIL_H_
#define _GAME_UTIL_H_

#include "Ball.h"
#include "Constants.h"
#include "vmath.h"

#include <chrono>
#include <random>
#include <thread>
#include <vector>

class GameUtil {
  static Vector2<double> randomVector2(int scaleX, int scaleY);
  static Vector2<double> randomCeter(int width, int height);
  static Vector2<double> randomVelocity(double maxVelocity);

public:
  static double distance(Ball &a, Ball &b);
  static Ball getRandomBall(int radius, int width, int height);
  static void calculateCollisionImpact(Ball &a, Ball &b);
  static void renderBitmapString(float x, float y, float z, const char *string);
};

#endif /* _GAME_UTIL_H_ */
