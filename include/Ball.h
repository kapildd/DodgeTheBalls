#ifndef _BALL_H_
#define _BALL_H_

#include "Constants.h"
#include "vmath.h"

class Ball {
public:
  double radius;
  Vector2<double> center;
  Vector2<double> velocity;
  Ball()
      : radius(BALL_RADIUS), center(Vector2<double>(0, 0)),
        velocity(Vector2<double>(0, 0)) {}
  Ball(double radius, Vector2<double> &center, Vector2<double> &velocity)
      : radius(radius), center(center), velocity(velocity) {}
  Vector2<double> getCenter();
  Vector2<double> getVelocity();
};

#endif /* _BALL_H_ */
