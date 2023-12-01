/*
 *  SimpleView
 *  Author: Meer Theodore Baloch
 *  Version: 2023-11-19
 */
#include "Board.hpp"
#include "Camera.hpp"
#include <stdio.h>

extern Camera myCamera;
extern Light myLight;
extern CullMode cullMode;
extern RenderMode renderMode;

Board::Board()
{
	// Adjust vertex positions for a board-like rectangle
	vertex[0][0] = -5.0; vertex[0][1] = -3.0; vertex[0][2] = 0.0;
	vertex[1][0] = -5.0; vertex[1][1] = 3.0;  vertex[1][2] = 0.0;
	vertex[2][0] = 5.0;  vertex[2][1] = 3.0;  vertex[2][2] = 0.0;
	vertex[3][0] = 5.0;  vertex[3][1] = -3.0; vertex[3][2] = 0.0;
	vertex[4][0] = -5.0; vertex[4][1] = -3.0; vertex[4][2] = 0.1; // Slightly higher for visibility
	vertex[5][0] = -5.0; vertex[5][1] = 3.0;  vertex[5][2] = 0.1;
	vertex[6][0] = 5.0;  vertex[6][1] = 3.0;  vertex[6][2] = 0.1;
	vertex[7][0] = 5.0;  vertex[7][1] = -3.0; vertex[7][2] = 0.1;

	// Define faces as per the new vertex positions
	face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 3;
	face[1][0] = 7; face[1][1] = 6; face[1][2] = 5; face[1][3] = 4;
	face[2][0] = 0; face[2][1] = 4; face[2][2] = 5; face[2][3] = 1;
	face[3][0] = 2; face[3][1] = 1; face[3][2] = 5; face[3][3] = 6;
	face[4][0] = 3; face[4][1] = 2; face[4][2] = 6; face[4][3] = 7;
	face[5][0] = 0; face[5][1] = 3; face[5][2] = 7; face[5][3] = 4;

	// Update vertex colors for the board-like rectangle
	// These are placeholder colors, modify them as needed
	vertexColor[0][0] = 1.0; vertexColor[0][1] = 0.0; vertexColor[0][2] = 0.0;
	vertexColor[1][0] = 0.0; vertexColor[1][1] = 1.0; vertexColor[1][2] = 0.0;
	vertexColor[2][0] = 0.0; vertexColor[2][1] = 0.0; vertexColor[2][2] = 1.0;
	vertexColor[3][0] = 1.0; vertexColor[3][1] = 1.0; vertexColor[3][2] = 0.0;
	vertexColor[4][0] = 1.0; vertexColor[4][1] = 0.0; vertexColor[4][2] = 1.0;
	vertexColor[5][0] = 0.0; vertexColor[5][1] = 1.0; vertexColor[5][2] = 1.0;
	vertexColor[6][0] = 0.5; vertexColor[6][1] = 0.5; vertexColor[6][2] = 0.5;
	vertexColor[7][0] = 0.0; vertexColor[7][1] = 0.0; vertexColor[7][2] = 0.0;

	// Update vertex normals for the board-like rectangle (assuming flat surface)
	// These are placeholder normals, modify them as needed
	for (int i = 0; i < 8; ++i) {
		vertexNormal[i][0] = 0.0;
		vertexNormal[i][1] = 0.0;
		vertexNormal[i][2] = 1.0;
	}

    r = 1.0;
    g = 0.0;
    b = 0.0;


}

void Board::drawFace(int i)
{
	GLfloat shade = 1, shade1=1, shade2=1, shade3=1;

	switch (renderMode) {
	case WIRE:
		glColor3f(r, g, b);
		glBegin(GL_LINE_LOOP);
		glVertex3fv(vertex[face[i][0]]);
		glVertex3fv(vertex[face[i][1]]);
		glVertex3fv(vertex[face[i][2]]);
		glVertex3fv(vertex[face[i][3]]);
		glEnd();
		break;
	case CONSTANT:
		if (myLight.on == true) {
		shade = getFaceShade(i, myLight);
		}
		glColor3f(faceColor[i][0]*shade, faceColor[i][1]*shade, faceColor[i][2]*shade);
		glBegin(GL_POLYGON);
		glVertex3fv(vertex[face[i][0]]);
		glVertex3fv(vertex[face[i][1]]);
		glVertex3fv(vertex[face[i][2]]);
		glVertex3fv(vertex[face[i][3]]);
		glEnd();
		break;
	case FLAT:
		if (myLight.on == true) shade = getVertexShade(i, myLight);
		glShadeModel(GL_FLAT);
		glBegin(GL_POLYGON);
		glColor3f(vertexColor[face[i][0]][0]*shade, vertexColor[face[i][0]][1]*shade, vertexColor[face[i][0]][2]*shade);
		for (int j=0; j<4; j++) {
			glVertex3fv(vertex[face[i][j]]);
		}
		glEnd();
		break;

	case SMOOTH:
		glEnable(GL_NORMALIZE);
		glShadeModel(GL_SMOOTH);
		glBegin(GL_POLYGON);
		for (int j=0; j<4; j++) {
			if (myLight.on == true) shade = getVertexShade(face[i][j], myLight);
				glColor3f(vertexColor[face[i][j]][0]*shade, vertexColor[face[i][j]][1]*shade, vertexColor[face[i][j]][2]*shade);
				glNormal3f(vertexNormal[face[i][j]][0], vertexNormal[face[i][j]][1], vertexNormal[face[i][j]][2]);
				glVertex3fv(vertex[face[i][j]]);
			}
		glEnd();
		break;
	case PHONE:
		// your
	   break;
    case TEXTURE:
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,4);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3fv(&vertex[face[i][0]][0]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(&vertex[face[i][1]][0]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(&vertex[face[i][2]][0]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(&vertex[face[i][3]][0]);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		break;
	}
}

void Board::draw()
{
	glPushMatrix();
    this->ctmMultiply();
    glScalef(s, s, s);

	for (int i = 0; i < 6; i++) {
		if  (cullMode == BACKFACE ) {
			if (isFrontface(i, myCamera)) {
				drawFace(i);
			}
		}
		else {
			drawFace(i);
		}
	}
    glPopMatrix();
}


bool Board::isFrontface(int faceindex, Camera camera) {
	GLfloat v[4];
	v[0] = faceNormal[faceindex][0];
	v[1] = faceNormal[faceindex][1];
	v[2] = faceNormal[faceindex][2];
	v[3] = 0.0;
	mc.multiplyVector(v);
	if (pmc != NULL) {
		pmc->multiplyVector(v);
		return (pmc->mat[0][3] - camera.eye.x) * v[0] + (pmc->mat[1][3] - camera.eye.y) * v[1] + (pmc->mat[2][3] - camera.eye.z) * v[2] < 0;
	} else {
		return (mc.mat[0][3] - camera.eye.x) * v[0] + (mc.mat[1][3] - camera.eye.y) * v[1] + (mc.mat[2][3] - camera.eye.z) * v[2] < 0;
	}
}

GLfloat Board::getFaceShade(int faceindex, Light light) {
	GLfloat shade = 1, v[4], s[4], temp;


	return shade;
}


GLfloat Board::getVertexShade(int i, Light light) {
	GLfloat shade = 1, v[4], s[4], temp;

	return shade;
}


