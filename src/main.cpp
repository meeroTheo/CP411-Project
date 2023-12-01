/*
 * main.cpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */

#include <GL/glew.h>
#include <GL/glut.h>
#include "Tile.hpp" // Include your Tile class header
#include "Board.hpp" // Include your Board class header
#include "GameLogic.hpp" // Include your GameLogic class header
#include "UI.hpp" // Include your UI class header

// Initialize game components
Tile tile; // Sample Tile instance
Board board; // Sample Board instance
GameLogic gameLogic; // Sample GameLogic instance
UI ui; // Sample UI instance

int winWidth = 800, winHeight = 800;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Implement rendering of game elements using UI class
    ui.renderGameElements(); // Method to render game components

    glutSwapBuffers();
}

void mouseClick(int button, int state, int x, int y) {
    // Implement logic to handle mouse clicks on tiles
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int tileClicked = ui.getClickedTile(x, y); // Get the tile clicked
        gameLogic.handleTileClick(tileClicked); // Handle the click in the game logic
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

    // Initialize your game components here
    // e.g., setup textures, initialize the game board, etc.
    // tile.init(); // Sample initialization method

    // Initialize the game board and logic
    board.initialize(); // Sample initialization method for the board
    gameLogic.initialize(&board); // Sample initialization method for game logic
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Memory Game");

    glewInit(); // Initialize GLEW

    init(); // Initialize game components

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);

    glutMainLoop();
    return 0;
}


