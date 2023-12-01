/*
 * main.cpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */

#include <GL/glew.h>
#include <GL/glut.h>
#include "Tile.hpp"
#include "Board.hpp"
#include "GameLogic.hpp"
#include "UI.hpp"

// Initialize game components
Tile tile;
Board board;
GameLogic gameLogic;
UI ui;

int winWidth = 800, winHeight = 800;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render game elements using UI class
    ui.renderGameElements();

    glutSwapBuffers();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int tileClicked = ui.getClickedTile(x, y);
        gameLogic.handleTileSelection(tileClicked);
    }
    glutPostRedisplay();
}

void reshape(int newWidth, int newHeight) {
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    winWidth = newWidth;
    winHeight = newHeight;
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    // Initialize game components
    tile.loadTextures("frontTextureFile", "backTextureFile");
    board.initializeBoard("frontTextureFile", "backTextureFile");
    gameLogic.startGame();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Memory Game");

    glewInit();

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);

    glutMainLoop();
    return 0;
}


