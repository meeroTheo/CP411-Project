/*
 * Board.cpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */
// Board.cpp
#include "Board.hpp"

Board::Board(int rows, int cols, float tileSize) {
    this->rows = rows;
    this->cols = cols;
    this->tileSize = tileSize;

    // Resize the vector to match the board dimensions
    tiles.resize(rows, std::vector<Tile>(cols));
}

void Board::initializeBoard(const char* frontTextureFile, const char* backTextureFile) {
    // Load textures for the tiles
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tiles[i][j].loadTextures(frontTextureFile, backTextureFile);
        }
    }
}

void Board::draw(float startX, float startY, float startZ) {
    float x = startX;
    float y = startY;

    // Draw each tile at its position
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tiles[i][j].draw(x, y, startZ);
            x += tileSize;
        }
        x = startX;
        y += tileSize;
    }
}

void Board::handleMouseClick(float mouseX, float mouseY) {
    // Check which tile the mouse click corresponds to
    float startX = /* calculate starting X position */;
    float startY = /* calculate starting Y position */;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (tiles[i][j].isPointInside(mouseX - startX, mouseY - startY)) {
                // Perform tile action (e.g., flip the tile)
                tiles[i][j].flip();
                // Additional logic can be added based on the game's requirements
                return; // Exit loop after finding the clicked tile
            }
            startX += tileSize;
        }
        startX = /* calculate starting X position */;
        startY += tileSize;
    }
}



