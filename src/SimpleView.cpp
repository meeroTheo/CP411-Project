/*
 *  SimpleView3 
 *  Author: Meer Theodore Baloch
 *  Version: 2023-11-19
 */


#include <windows.h>  // for playing sound
#include <mmsystem.h> //
#include <GL/glew.h>
#include "pixmap/RGBpixmap.h"
#include "glsl/Angel.h"


#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Menu.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"



GLint winWidth = 800, winHeight = 800;
GLint isInMove = 0,
	  xbegin = 0,
	  csType = 1,    /* coordinate system type: 1 for VCS */
	  transType = 4;  /* depends on csType  */

CullMode cullMode = NONE;      /* culling option */
RenderMode renderMode = TEXTURE; //  TEXTURE;  /* shade option  */

World myWorld;
Camera myCamera;
Light myLight;
Shape *selectObj = NULL;  // pointer to select object
GLint displayOption = 0;   /* 0: world, 1: solar system, 2: control points, 3: curve, 4: rotation surface.  */

RGBpixmap pix[8];      /* pixmaps for 6 textures */
GLuint ProgramObject;  /* GLSL program object */

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	selectObj = myWorld.searchById(1);


	ProgramObject = InitShader( "shader/vertexshader.txt", "shader/fragmentshader.txt" );
	glUseProgram(0);  // disable GLSL shader at start

	/* load six texture bitmap */
	pix[0].makeCheckerboard();
	pix[0].setTexture(0);
//
	pix[1].readBMPFile("texture/mandrill.bmp");
	pix[1].setTexture(1);
//
	pix[2].readBMPFile("texture/sun.bmp");
	pix[2].setTexture(2);
//
	pix[3].readBMPFile("texture/earth.bmp");
	pix[3].setTexture(3);
//
	pix[4].readBMPFile("texture/table.bmp");
	pix[4].setTexture(4);
//




}

void drawWCSAxes() {
	glBegin(GL_LINES);
	//x-axis red
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-2, 0, 0);
	glVertex3f(4, 0, 0);
	//y-axis green
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -2, 0);
	glVertex3f(0, 4, 0);
	//z-axis blue
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -2);
	glVertex3f(0, 0, 4);
	glEnd();
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (displayOption) {
	case 0:
	   myCamera.setProjectionMatrix();
	   drawWCSAxes();
	   myWorld.draw();
	   myLight.draw();
	 break;
	case 1:
	   myCamera.setProjectionMatrix();
	 break;
	case 2:

	 break;
	case 3:

	 break;
	case 4:
	 break;
	}
	glFlush();
	glutSwapBuffers();
}


void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseActionFcn(int button, int state, int xMouse, int yMouse) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		isInMove = 1;
		xbegin = xMouse;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		isInMove = 0;
	}
}

void mouseMotionFcn(GLint xMouse, GLint yMouse) {
	if (isInMove) {
		if(csType == 1){
			VCSTransform(xMouse);
		}
		else if(csType == 4) {
			lightTransform(xMouse);
		}
		glutPostRedisplay();
	}
}


int main(int argc, char** argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("SimpleView3 Meer Theodore Baloch ");
	PlaySound((LPCSTR) "BGM.wav", NULL, SND_FILENAME | SND_ASYNC);

	glewInit(); 

	menu();
	init();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMotionFcn);
	glutMouseFunc(mouseActionFcn);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
