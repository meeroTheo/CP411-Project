/*
 * UI.cpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */
// UI.cpp
#include "UI.hpp"
#include "GameLogic.hpp"

GameLogic gameLogic; // Assuming GameLogic is defined globally or through inclusion

UI::UI() {
    // Initialize any UI-related variables if needed
}

void UI::initialize(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Memory Game");

    // Set up callbacks for display, input handling, etc.
    glutDisplayFunc(display);
    glutMouseFunc(mouseAction);
    glutMotionFunc(mouseMotion);

    // Initialize OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set initial states for lights, materials, etc.
    // ...

    // Start the main loop
    glutMainLoop();
}

void UI::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set camera/view settings for a bird's eye view
    gluLookAt(/* parameters for bird's eye view */);

    // Draw the game board and tiles using the GameLogic instance
    gameLogic.drawBoard();

    glutSwapBuffers();
}

void UI::mouseAction(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Handle tile selection based on mouse click
        // Convert screen coordinates (x, y) to board coordinates if needed
        gameLogic.handleTileSelection(/* converted board coordinates */);
    }
}

void UI::mouseMotion(int x, int y) {
    // Handle mouse motion if needed
}

// Implement other UI-related functions as needed



