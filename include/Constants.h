#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <GL/freeglut.h>

const double WINDOW_WIDTH = 800;
const double WINDOW_HEIGHT = 600;
const double BALL_RADIUS = 18.0;

const GLfloat LIGHT_AMBIENT[] = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat LIGHT_DIFFUSE[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat LIGHT_SPECULAR[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat LIGHT_POSITION[] = {2.0f, 5.0f, 5.0f, 0.0f};

const GLfloat MAT_AMBIENT[] = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat MAT_DIFFUSE[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat MAT_SPECULAR[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat HIGH_SHININESS[] = {100.0f};

#endif /* _CONSTANTS_H_ */
