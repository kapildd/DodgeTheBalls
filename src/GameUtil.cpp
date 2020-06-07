#include "GameUtil.h"

Vector2<double> GameUtil::randomVector2(int scaleX, int scaleY) {
  static std::default_random_engine generator;
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  double x = scaleX * distribution(generator);
  double y = scaleY * distribution(generator);
  return Vector2<double>(x, y);
}

Vector2<double> GameUtil::randomCeter(int width, int height) {
  Vector2<double> center = randomVector2(width, height);
  center.x -= width / 2;
  center.y -= height / 2;
  return center;
}

Vector2<double> GameUtil::randomVelocity(double maxVelocity) {
  static std::default_random_engine generator;
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  Vector2<double> velocity = randomVector2(maxVelocity, maxVelocity);
  int xDir = distribution(generator) < 0.5 ? -1 : 1;
  int yDir = distribution(generator) < 0.5 ? -1 : 1;
  velocity.x *= xDir;
  velocity.y *= yDir;
  return velocity;
}

double GameUtil::distance(Ball &a, Ball &b) {
  Vector2<double> diff = a.center - b.center;
  return diff.length();
}

Ball GameUtil::getRandomBall(int radius, int width, int height) {
  Vector2<double> center = randomCeter(width, height);
  Vector2<double> velocity = randomVelocity(15);
  return Ball(radius, center, velocity);
}

void GameUtil::calculateCollisionImpact(Ball &a, Ball &b) {
  int rep = 0;
  while (distance(a, b) < 2 * BALL_RADIUS && rep++ < 150) {
    a.center -= a.velocity * 0.1;
    b.center -= b.velocity * 0.1;
  }

  Vector2<double> ballPositionDiff = (b.center - a.center);
  Vector2<double> normal = ballPositionDiff;
  normal.normalize();

  Vector2<double> tangent; // unit tangent between two balls
  tangent.x = -normal.y;
  tangent.y = normal.x;

  Vector2<double> v1n =
      a.velocity * normal; // components of velocity of balls along normal
  Vector2<double> v2n = b.velocity * normal;
  Vector2<double> v1t =
      a.velocity * tangent; // components of velocity of balls along tangent
  Vector2<double> v2t = b.velocity * tangent;

  // swapping the normal components and keeping the tangential components same
  Vector2<double> newv1n = v2n * normal;
  Vector2<double> newv2n = v1n * normal;
  Vector2<double> newv1t = v1t * tangent;
  Vector2<double> newv2t = v2t * tangent;

  // assign new velocities
  a.velocity = newv1n + newv1t;
  b.velocity = newv2n + newv2t;

  // adjust the ball position to avoid sticking of balls in case of intersection
  // of ball boundaries
  Vector2<double> adjust =
      normal * ((a.radius + b.radius) - distance(a, b)) / 2;
  if (newv1n < 0)
    a.center += adjust;
  else
    a.center -= adjust;
  if (newv2n < 0)
    b.center -= adjust;
  else
    b.center += adjust;
}

void GameUtil::renderBitmapString(float x, float y, float z,
                                  const char *string) {
  const char *c;
  glMatrixMode(GL_PROJECTION);
  glDisable(GL_LIGHTING);
  glPushMatrix();
  glLoadIdentity();

  gluOrtho2D(0, 400, 0, 300);
  glScalef(1, -1, 1);
  glTranslatef(200, -150, 0);
  glRasterPos3f(x, y, z);

  glMatrixMode(GL_MODELVIEW);
  for (c = string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }

  glPopMatrix();
  glEnable(GL_LIGHTING);
}
