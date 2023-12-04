/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03
 */
#include "Menu.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"

#include "glsl/Angel.h"

#include "pixmap/RGBpixmap.h"

#include <ctime>

double totalRotation = 0.0;
double rotationStep = 1.0;
double rotationSpeed = 10.0;
double tolerance = 0.1;
extern GLint csType;
extern Shape* selectObj;
extern GLint transType, xbegin;
extern World myWorld;
extern Camera myCamera;
extern Light myLight;
extern RenderMode renderMode;
extern GLuint ProgramObject;

extern GLint displayOption;

Shape* tile1;
Shape* tile2;
int score;
void tileHide();


void menu() {

	// Create a menu that allows users to select a card to flip
	GLint CardSelect_Menu = glutCreateMenu(CardSelectMenu);
	glutAddMenuEntry("Card 1", 2);
	glutAddMenuEntry("Card 2", 3);
	glutAddMenuEntry("Card 3", 4);
	glutAddMenuEntry("Card 4", 5);
	glutAddMenuEntry("Card 5", 6);
	glutAddMenuEntry("Card 6", 7);
	glutAddMenuEntry("Card 7", 8);
	glutAddMenuEntry("Card 8", 9);


	GLint VCTrans_Menu = glutCreateMenu(VCSTransMenu);
	glutAddMenuEntry("Rotate x", 1);
	glutAddMenuEntry("Rotate y", 2);
	glutAddMenuEntry("Rotate z", 3);
	glutAddMenuEntry("Translate x", 4);
	glutAddMenuEntry("Translate y", 5);
	glutAddMenuEntry("Translate z", 6);

	GLint Shading_Menu = glutCreateMenu(shadeMenu);
	glutAddMenuEntry("OpenGL smooth shading", 4);
	glutAddMenuEntry("Texture", 5);


	GLint Animate_Menu = glutCreateMenu(animateMenu);
	glutAddMenuEntry("Single object", 1);
	glutAddMenuEntry("Stop animation", 4);

	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Reset", 1);
	glutAddSubMenu("Select Card", CardSelect_Menu);
	glutAddSubMenu("VCS Transformations", VCTrans_Menu);

	glutAddSubMenu("Shading", Shading_Menu);
	glutAddSubMenu("Animation", Animate_Menu);

	glutAddMenuEntry("Quit", 2);
}

void mainMenu(GLint option) {
	switch (option){
		case 1:
			reset();
			break;
		case 2:
			exit(0);
			break;
	}
	glutPostRedisplay();
}

void ObjSubMenu(GLint option)
{
	switch (option){
		case 1:
			selectObj = myWorld.searchById(1);
			break;
	}
	glutPostRedisplay();
}


void delayedFlipBack2(int value) {
	selectObj = myWorld.searchById(tile2->getId());
	totalRotation = 0.0;
	glutIdleFunc(move);
	tile1 = NULL;
	tile2 = NULL;
	glutPostRedisplay();
}

void delayedFlipBack1(int value) {
	selectObj = myWorld.searchById(tile1->getId());
	totalRotation = 0.0;
	glutIdleFunc(move);
	glutTimerFunc(500, delayedFlipBack2, 0);
	glutPostRedisplay();
}
void timeDelay(double seconds){
	clock_t start = clock();
	double delay= seconds * CLOCKS_PER_SEC;

	while (clock() - start < delay){
		//wait
	}

}

void CardSelectMenu(GLint option)
{
	if (tile1 && tile2) {
		return;
	}
	selectObj = myWorld.searchById(option);
	displayOption = 0;

	if (tile1 == NULL) {
		tile1 = selectObj;
	} else if (tile1->getId() == selectObj->getId()) {
		return;
	} else {
		tile2 = selectObj;
	}


	Matrix mp = selectObj->getMC();
	//displayOption = 0;
	totalRotation = 0.0;  // Reset the total rotation
	glutIdleFunc(move);

	if (tile1 != NULL && tile2 != NULL) {
		if(tile1->getTexId() == tile2->getTexId()) { //when tile is matched
			++score;
			// implement Hide tile here
			//timeDelay(1.0);
			tileHide();
			tile1 = NULL;
			tile2 = NULL;
			//DISPLAY MATCH FOUND TEXT

		}
		else {
			glutTimerFunc(650, delayedFlipBack1, 0);
			totalRotation = 0.0;

		}

	}

	//LogicInstance.selectTile(objectId, textureId);
	glutPostRedisplay();
}


//timer for delay
//tileHide translates the tile to the back of the board
void tileHide() {
	//add a delay by 2 seconds before translate without using delayflipback
	tile1->translate(0.0, 0.0, -10.0);
	tile2->translate(0.0, 0.0, -10.0);
}



void VCSTransMenu(GLint transOption) {
	csType = 3;
	transType = transOption;
	glutPostRedisplay();
}


void VCSTransform(GLint x){
	GLfloat theta = (xbegin - x > 0) ? 1 : -1;
	if (transType == 1) {  //eye rotate x
		myCamera.rotate(1.0, 0.0, 0.0, theta*0.5);
	}
	else if (transType == 2) { // eye rotate y
		myCamera.rotate(0.0, 1.0, 0.0, theta*0.5);
	}
	else if(transType == 3){ //eye rotate z
		myCamera.rotate(0.0, 0.0, 1.0, theta*0.5);
	}
	else if (transType == 4) { //eye translate x
		myCamera.translate(theta* 0.02, 0.0, 0.0);
	}
	else if(transType == 5){   // eye translate y
		myCamera.translate(0.0, theta* 0.02, 0.0);
	}
	else if(transType == 6){ // eye translate z
		myCamera.translate(0.0, 0.0, theta* 0.02);
	}
	else if(transType == 7){  // change dnear
		myCamera.dnear += theta * .1;
	}
	else if(transType == 8){  // change dfar
		myCamera.dfar += theta *.1;
	}
}


void shadeMenu(GLint option) {
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable( GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);

	glUseProgram( 0 );
	switch (option){
	  case 1:
		//isShading = false;
		renderMode = WIRE;
		break;
	  case 2:
		renderMode = CONSTANT;
		break;
	  case 3:
		renderMode = FLAT;
		break;
	  case 4:
		renderMode = SMOOTH;
		break;
	  case 5:
		renderMode = TEXTURE;
		//glEnable(GL_DEPTH_TEST);
		//glEnable(GL_TEXTURE_2D);
		//glDisable(GL_LIGHTING);
		//glEnable(GL_LIGHT0);
		break;
	  case 6:
		renderMode = PHONE;
		glUseProgram( ProgramObject );

		// light properties
		GLfloat ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
		GLfloat diffuse[] = { .6f, .6f, 1.0f, 1.0f };
		GLfloat position[] = { 1.8, 1.8, 1.5, 1.0 };
		GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
		GLfloat local_view[] = { 0.0 };

		//Material
		GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };

		GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };

		GLfloat high_shininess[] = { 100.0 };


		position[0] = myLight.getMC().mat[0][3];
		position[1] = myLight.getMC().mat[1][3];
		position[2] = myLight.getMC().mat[2][3];

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
		glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ambient);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

		glEnable(GL_LIGHTING);
		glEnable( GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHT0);
		break;
	}

	glutPostRedisplay();
}



void timer(int value){

	double dt = 16.0 / 1000.0;

	double rotationAngle = rotationStep * rotationSpeed * dt;

	double x = selectObj->getMC().mat[0][3];
	double y = selectObj->getMC().mat[1][3];
	double z = selectObj->getMC().mat[2][3];

	if (totalRotation < (180.0 - tolerance)) {
		selectObj->rotate(x, y, z, 0.0, 1.0, 0.0, rotationAngle);

		totalRotation += rotationAngle;
	}

	// Stop the rotation after 180 degrees
	if (totalRotation >= (180.0 - tolerance)) {
		totalRotation = 180.0;
		glutIdleFunc(NULL);  // Stop the idle function
	} else {
		glutTimerFunc(16, timer, 0);
	}

	glutPostRedisplay();
}

void startRotation() {
	glutTimerFunc(0, timer, 0);
}

void move(void) {
	startRotation();
}

void animateMenu(GLint option) {
	switch (option){
	  case 1:
		//displayOption = 0;
		totalRotation = 0.0;  // Reset the total rotation
		glutIdleFunc(move);
		break;
	  case 2:

		break;
	  case 3:

		break;
	case 4:
		glutIdleFunc(NULL);
		break;
	}
	glutPostRedisplay();
}

void reset() {
	tile1 = NULL;
	tile2 = NULL;
	score = 0;
	displayOption = 0;
	renderMode = TEXTURE;
	myWorld.reset();
	myCamera.reset();
	//flip cards back
	



	glUseProgram(0);  // disable GLSL shader
	glutIdleFunc(NULL);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}

