/*
 *  SimpleView
 *  Author: Meer Theodore Baloch
 *  Version: 2023-11-19
 */
#include "Tile.hpp"
#include "Camera.hpp"
#include <stdio.h>

Tile::Tile()
{
    // Adjust vertex positions for a card-like rectangle
//    vertex[0][0] = -1.5; vertex[0][1] = -2; vertex[0][2] = 0;
//    vertex[1][0] = -1.5; vertex[1][1] = 2;  vertex[1][2] = 0;
//    vertex[2][0] = 1.5;  vertex[2][1] = 2;  vertex[2][2] = 0;
//    vertex[3][0] = 1.5;  vertex[3][1] = -2; vertex[3][2] = 0;
//    vertex[4][0] = -1.5; vertex[4][1] = -2; vertex[4][2] = 0.1; // Slightly higher for visibility
//    vertex[5][0] = -1.5; vertex[5][1] = 2;  vertex[5][2] = 0.1;
//    vertex[6][0] = 1.5;  vertex[6][1] = 2;  vertex[6][2] = 0.1;
//    vertex[7][0] = 1.5;  vertex[7][1] = -2; vertex[7][2] = 0.1;
	vertex[0][0] = -2;   vertex[0][1] = -1.5; vertex[0][2] = 0;
	vertex[1][0] = 2;    vertex[1][1] = -1.5; vertex[1][2] = 0;
	vertex[2][0] = 2;    vertex[2][1] = 1.5;  vertex[2][2] = 0.3; // Increased thickness
	vertex[3][0] = -2;   vertex[3][1] = 1.5;  vertex[3][2] = 0.3; // Increased thickness
	vertex[4][0] = -2;   vertex[4][1] = -1.5; vertex[4][2] = 0.3; // Slightly higher for visibility and increased thickness
	vertex[5][0] = 2;    vertex[5][1] = -1.5; vertex[5][2] = 0.3; // Slightly higher for visibility and increased thickness
	vertex[6][0] = 2;    vertex[6][1] = 1.5;  vertex[6][2] = 0.3; // Slightly higher for visibility and increased thickness
	vertex[7][0] = -2;   vertex[7][1] = 1.5;  vertex[7][2] = 0.3; // Slightly higher for visibility and increased thickness


    // Define faces as per the new vertex positions
    face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 3;
    face[1][0] = 7; face[1][1] = 6; face[1][2] = 5; face[1][3] = 4;
    face[2][0] = 0; face[2][1] = 4; face[2][2] = 5; face[2][3] = 1;
    face[3][0] = 2; face[3][1] = 1; face[3][2] = 5; face[3][3] = 6;
    face[4][0] = 3; face[4][1] = 2; face[4][2] = 6; face[4][3] = 7;
    face[5][0] = 0; face[5][1] = 3; face[5][2] = 7; face[5][3] = 4;

    // Update vertex colors for the card-like rectangle
    vertexColor[0][0] = 1.0; vertexColor[0][1] = 0.0; vertexColor[0][2] = 0.0;
    vertexColor[1][0] = 0.0; vertexColor[1][1] = 1.0; vertexColor[1][2] = 0.0;
    vertexColor[2][0] = 0.0; vertexColor[2][1] = 0.0; vertexColor[2][2] = 1.0;
    vertexColor[3][0] = 1.0; vertexColor[3][1] = 1.0; vertexColor[3][2] = 0.0;
    vertexColor[4][0] = 1.0; vertexColor[4][1] = 0.0; vertexColor[4][2] = 1.0;
    vertexColor[5][0] = 0.0; vertexColor[5][1] = 1.0; vertexColor[5][2] = 1.0;
    vertexColor[6][0] = 0.5; vertexColor[6][1] = 0.5; vertexColor[6][2] = 0.5;
    vertexColor[7][0] = 0.0; vertexColor[7][1] = 0.0; vertexColor[7][2] = 0.0;

    // Update vertex normals for the card-like rectangle (assuming flat surface)
    // These normals are simplified assuming a flat surface
    vertexNormal[0][0] = 0.0; vertexNormal[0][1] = 0.0; vertexNormal[0][2] = 1.0;
    vertexNormal[1][0] = 0.0; vertexNormal[1][1] = 0.0; vertexNormal[1][2] = 1.0;
    vertexNormal[2][0] = 0.0; vertexNormal[2][1] = 0.0; vertexNormal[2][2] = 1.0;
    vertexNormal[3][0] = 0.0; vertexNormal[3][1] = 0.0; vertexNormal[3][2] = 1.0;
    vertexNormal[4][0] = 0.0; vertexNormal[4][1] = 0.0; vertexNormal[4][2] = 1.0;
    vertexNormal[5][0] = 0.0; vertexNormal[5][1] = 0.0; vertexNormal[5][2] = 1.0;
    vertexNormal[6][0] = 0.0; vertexNormal[6][1] = 0.0; vertexNormal[6][2] = 1.0;
    vertexNormal[7][0] = 0.0; vertexNormal[7][1] = 0.0; vertexNormal[7][2] = 1.0;

    r = 1.0;
    g = 0.0;
    b = 0.0;

}


void Tile::drawFace(int i)
{

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	if (i==1){
        glBindTexture(GL_TEXTURE_2D,getId());
		
	}
	else{
		glBindTexture(GL_TEXTURE_2D,6);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3fv(&vertex[face[i][0]][0]);
	glTexCoord2f(1.0, 0.0); glVertex3fv(&vertex[face[i][1]][0]);
	glTexCoord2f(1.0, 1.0); glVertex3fv(&vertex[face[i][2]][0]);
	glTexCoord2f(0.0, 1.0); glVertex3fv(&vertex[face[i][3]][0]);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	}

void Tile::draw()
{
	glPushMatrix();
    this->ctmMultiply();
    glScalef(s, s, s);
    // Rotate the tile by 90 degrees around the Z-axis
	glRotatef(270.0f, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < 6; i++) {
		drawFace(i);
	}
    glPopMatrix();
}



