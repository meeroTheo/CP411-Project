/*
 * UI.cpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */
// UI.cpp
#include "UI.hpp"

UI::UI() {
    // Initialize any UI-related variables if needed
}

void UI::initialize(int argc, char** argv) {
    glutInit(&argc, argv);
    // Initialize GLUT and set up the window
    // Set up callbacks for display, input handling, etc.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(/* window size */);
    glutCreateWindow(/* window title */);
    // Set up the callbacks for display, mouse, keyboard, etc.
    // Initialize OpenGL settings and start the main loop
    // You may call GameLogic functions from here to start the game
    gameLogic.startGame();
    glutMainLoop();
}

// Implement other UI-related functions as needed



