/*
 * Board.cpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */
// Board.cpp
#include "Board.hpp"

Board::Board(int rows, int cols, float tileSize) {
    // Initialize the board parameters and size of tiles
    this->rows = rows;
    this->cols = cols;
    this->tileSize = tileSize;

    // Resize the vector to match the board dimensions
    tiles.resize(rows, std::vector<Tile>(cols));
}

void Board::initializeBoard(const char* frontTextureFile, const char* backTextureFile) {
    // Load textures for the tiles
    // Loop through the board and initialize each tile with front and back textures
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tiles[i][j].loadTextures(frontTextureFile, backTextureFile);
        }
    }
}

void Board::draw(float startX, float startY, float startZ) {
    float x = startX;
    float y = startY;

    // Loop through the board and draw each tile at its position
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tiles[i][j].draw(x, y, startZ);
            x += tileSize; // Move to the next column
        }
        x = startX; // Reset X position for the next row
        y += tileSize; // Move to the next row
    }
}

void Board::handleMouseClick(float mouseX, float mouseY) {
    // Check which tile the mouse click corresponds to
    // Loop through the board and check if the mouse click is inside any tile
    // If yes, perform the appropriate action (e.g., flip the tile)
}



