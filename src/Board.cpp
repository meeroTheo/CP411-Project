/*
 * Board.cpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */
// Board.cpp
#include <iostream> // for debugging purposes
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
    // Loop through the board and check if the mouse click is inside any tile
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Calculate the boundaries of the current tile
            float tileLeft = j * tileSize;
            float tileRight = (j + 1) * tileSize;
            float tileTop = i * tileSize;
            float tileBottom = (i + 1) * tileSize;

            // Check if the mouse click is inside the current tile
            if (mouseX >= tileLeft && mouseX <= tileRight && mouseY >= tileTop && mouseY <= tileBottom) {
                // Mouse click is inside this tile
                // Perform the appropriate action (e.g., flip the tile)
                tiles[i][j].flip(); // Assuming there's a function to flip the tile

                // For debugging purposes, print the row and column of the clicked tile
                std::cout << "Clicked on tile at row " << i << ", column " << j << std::endl;

                // You may want to break out of the loop if you only want to handle one click
                // break;
            }
        }
    }
}



