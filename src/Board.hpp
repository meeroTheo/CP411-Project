/*
 * Board.hpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */

// Board.hpp
#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Tile.hpp"

class Board {
private:
    std::vector<std::vector<Tile>> tiles; // 2D vector representing the game board
    int rows; // Number of rows in the board
    int cols; // Number of columns in the board
    float tileSize; // Size of each tile

public:
    Board(int rows, int cols, float tileSize);
    void initializeBoard(const char* frontTextureFile, const char* backTextureFile);
    void draw(float startX, float startY, float startZ); // Draw the entire game board
    void handleMouseClick(float mouseX, float mouseY); // Handle mouse clicks on the board
};

#endif
