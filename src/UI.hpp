/*
 * UI.hpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */

// UI.hpp
#ifndef UI_HPP
#define UI_HPP

#include <GL/glut.h>
#include "GameLogic.hpp"

class UI {
private:
    GameLogic gameLogic;
    // Add variables for UI elements if needed

public:
    UI(); // Constructor
    void initialize(int argc, char** argv); // Initialize the UI
    // Add UI-related functions (e.g., drawing, handling input) here
};

#endif
