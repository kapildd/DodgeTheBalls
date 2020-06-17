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
  Vector2<double> collisionLine = (b.center - a.center);
  Vector2<double> collisionLineNormalized = collisionLine;
  collisionLineNormalized.normalize();

  double aVelocityParallel = a.velocity.dotProduct(collisionLineNormalized);
  double bVelocityParallel = b.velocity.dotProduct(collisionLineNormalized);
  double diffVelocity = (bVelocityParallel - aVelocityParallel);

  Vector2<double> drift = collisionLineNormalized * diffVelocity;
  a.velocity += drift;
  b.velocity -= drift;

  Vector2<double> centerAdjustment;
  centerAdjustment += collisionLineNormalized * (2 * BALL_RADIUS);
  centerAdjustment -= collisionLine;
  a.center -= centerAdjustment;
  b.center += centerAdjustment;
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
