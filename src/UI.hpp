/*
 * UI.hpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */

// UI.hpp
#ifndef UI_HPP_
#define UI_HPP_

#include <GL/glut.h>

class UI {
public:
    UI();
    void initialize(int argc, char** argv);

    // Static functions for callbacks
    static void display();
    static void mouseAction(int button, int state, int x, int y);
    static void mouseMotion(int x, int y);
};

#endif /* UI_HPP_ */
