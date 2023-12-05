
#ifndef MENU_HPP_
#define MENU_HPP_

#include "glsl/Angel.h"
#include <GL/glut.h>

void menu();
void mainMenu(GLint option);
void ObjSubMenu(GLint objectOption);
void VCSTransMenu(GLint transOption);
void reset();
void VCSTransform(GLint);


void shadeMenu(GLint option);
void animateMenu(GLint option);


void curveSurfaceMenu(GLint option);
void move();

void CardSelectMenu(GLint option);


#endif
