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

float totalRotation = 0.0;
const float rotationStep = 0.1;
extern GLint csType;
extern Shape* selectObj;
extern GLint transType, xbegin;
extern World myWorld;
extern Camera myCamera;
extern Light myLight;
extern CullMode cullMode;
extern RenderMode renderMode;
extern GLuint ProgramObject;

extern GLint displayOption;
void menu() {
	GLint Object_Menu = glutCreateMenu(ObjSubMenu);
	glutAddMenuEntry("Tile", 1);

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

	GLint Cull_Menu = glutCreateMenu(cullMenu);
	glutAddMenuEntry("No culling", 1);
	glutAddMenuEntry("My back-face", 2);
	glutAddMenuEntry("OpenGL cull", 3);
	glutAddMenuEntry("OpenGL depth buffer", 4);
	glutAddMenuEntry("OpenGL cull & depth buffer", 5);

	GLint VCTrans_Menu = glutCreateMenu(VCSTransMenu);
	glutAddMenuEntry("Rotate x", 1);
	glutAddMenuEntry("Rotate y", 2);
	glutAddMenuEntry("Rotate z", 3);
	glutAddMenuEntry("Translate x", 4);
	glutAddMenuEntry("Translate y", 5);
	glutAddMenuEntry("Translate z", 6);
	glutAddMenuEntry("Clipping Near", 7);
	glutAddMenuEntry("Clipping Far", 8);

	GLint Light_Menu = glutCreateMenu(lightMenu);
	glutAddMenuEntry("Turn on light", 8);
	glutAddMenuEntry("Turn off light", 9);
	glutAddMenuEntry("Change intensity", 7);
	glutAddMenuEntry("Rotate x ", 1);
	glutAddMenuEntry("Rotate y ", 2);
	glutAddMenuEntry("Rotate z", 3);
	glutAddMenuEntry("Translate x ", 4);
	glutAddMenuEntry("Translate y ", 5);
	glutAddMenuEntry("Translate z", 6);
	//glutAddMenuEntry("OpenGL light", 10);

	/* SimpleView2 features */
	GLint Shading_Menu = glutCreateMenu(shadeMenu);
	glutAddMenuEntry("No shading", 1);
	glutAddMenuEntry("My constant shading", 2);
	glutAddMenuEntry("OpenGL flat shading", 3);
	glutAddMenuEntry("OpenGL smooth shading", 4);

	/* SimppleView3 features */
	glutAddMenuEntry("Texture", 5);
	glutAddMenuEntry("GLSL phone shading", 6);


	GLint Animate_Menu = glutCreateMenu(animateMenu);
	glutAddMenuEntry("Single object", 1);
	glutAddMenuEntry("Stop animation", 4);

	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Reset", 1);
	glutAddSubMenu("Select Object", Object_Menu);
	glutAddSubMenu("Select Card", CardSelect_Menu);
	glutAddSubMenu("VCS Transformations", VCTrans_Menu);
	glutAddSubMenu("Light", Light_Menu);
	glutAddSubMenu("Shading", Shading_Menu);
	glutAddSubMenu("Animation", Animate_Menu);
	glutAddSubMenu("Culling", Cull_Menu);
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

void CardSelectMenu(GLint option)
{
	selectObj = myWorld.searchById(option);
	displayOption = 0;

	Matrix mp = selectObj->getMC();

	//displayOption = 0;
	totalRotation = 0.0;  // Reset the total rotation
	glutIdleFunc(move);
	glutPostRedisplay();
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


void lightMenu(GLint option) {
	csType = 4;
	transType = option;
	switch (option) {
	   case 8:
		myLight.on = true;
		break;
	  case 9:
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_DEPTH_TEST);
		myLight.on = false;
		break;

	  case 10:
		glLightModelf( GL_LIGHT_MODEL_TWO_SIDE , 0 );



		GLfloat material_Kd[] = { 1.0f*myLight.I, 0.4f*myLight.I, 0.0f*myLight.I, 0.0f };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);

		GLfloat pos[] = { myLight.getMC().mat[0][3], myLight.getMC().mat[1][3], myLight.getMC().mat[2][3], 1.0 };
		GLfloat Ka[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat Kd[] = { 1.0*myLight.I, 1.0*myLight.I, 1.0*myLight.I, 1.0 };
		GLfloat Ks[] = { 1.0, 1.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		//glLightfv(GL_LIGHT0, GL_AMBIENT, Ka);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Kd);
		glLightfv(GL_LIGHT0, GL_SPECULAR, Ks);

		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);
		glEnable(GL_DEPTH_TEST);
		glShadeModel (GL_SMOOTH);
		glEnable(GL_LIGHT0);
		break;
	}

	glutPostRedisplay();
}

void lightTransform(GLint x){
	GLfloat theta = (xbegin - x > 0) ? 1 : -1;
	if (transType == 1) {   // rotate x
		myLight.rotate(0, 0, 0, 1.0, 0.0, 0.0, theta*0.5);
	}
	else if (transType == 2) { // rotate y
		myLight.rotate(0, 0, 0, 0.0, 1.0, 0.0, theta*0.5);
	}
	else if(transType == 3){ // rotate z
		myLight.rotate(0, 0, 0, 0.0, 0.0, 1.0, theta*0.5);
	}
	else if (transType == 4) { // translate x
		myLight.translate(theta*0.1, 0.0, 0.0);
	}
	else if(transType == 5){   // eye translate y
		myLight.translate(0.0, theta*0.1, 0.0);
	}
	else if(transType == 6){ // eye translate z
		myLight.translate(0.0, 0.0, theta*0.1);
	}
	else if(transType == 7){  // change intensity
		myLight.I += theta *0.01;
	}


	GLfloat Kd[] = { 1.0*myLight.I, 1.0*myLight.I, 1.0*myLight.I, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Kd);

	GLfloat material_Ke[] = { 0.5*myLight.I, 0.5*myLight.I, 0.5*myLight.I, 0.0f };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);

	glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);

	GLfloat pos[] = { myLight.getMC().mat[0][3], myLight.getMC().mat[1][3], myLight.getMC().mat[2][3], 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);


	glutPostRedisplay();
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
		GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat position[] = { 1.8, 1.8, 1.5, 1.0 };
		GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
		GLfloat local_view[] = { 0.0 };

		//Material
		GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
		GLfloat mat_ambient_color[] = { 1, 1, 1, 1 };
		GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat high_shininess[] = { 100.0 };
		GLfloat mat_emission[] = { 1, 1, 1, 1 };

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



void move(void){
	   float x = selectObj->getMC().mat[0][3];
	    float y = selectObj->getMC().mat[1][3];
	    float z = selectObj->getMC().mat[2][3];

	    // Assuming selectObj->rotate(float x, float y, float z, float axisX, float axisY, float axisZ, float angle)
	    selectObj->rotate(x, y, z, 1.0, 0.0, 0.0, rotationStep);

	    totalRotation += rotationStep;

	    // Stop the rotation after 180 degrees
	    if (totalRotation >= 180.0) {
	        totalRotation = 0.0;
	        glutIdleFunc(NULL);  // Stop the idle function
	    }

	    glutPostRedisplay();
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
	displayOption = 0;
	renderMode = TEXTURE;
	myWorld.reset();
	myLight.reset();
	myCamera.reset();

	glUseProgram(0);  // disable GLSL shader
	glutIdleFunc(NULL);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}


void cullMenu(GLint option) {
	switch (option){
	  case 1:
		cullMode = NONE;
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		break;
	  case 2:
		cullMode = BACKFACE;
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		break;
	  case 3:
		cullMode = GLCULL;
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		break;
	  case 4:
		cullMode = GLCULLDEPTHBUFFER;
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		break;
	  case 5:
		cullMode = GLCULLDEPTHBUFFER;
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		break;
	}
	glutPostRedisplay();
}
