/*
 * GameLogic.cpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */
// GameLogic.cpp
#include "GameLogic.hpp"

GameLogic::GameLogic() {
    // Initialize the game logic, create the board, set up tiles, etc.
    gameBoard = Board(4, 4, TILE_SIZE);
    gameBoard.initializeBoard("frontTexture.png", "backTexture.png");
    isFlippingAllowed = true; // Assume flipping is allowed at the start
}

void GameLogic::startGame() {
    // Logic to start the game
    gameBoard.initializeBoard("frontTexture.png", "backTexture.png");
    isFlippingAllowed = true; // Reset flipping allowance
}

void GameLogic::handleTileSelection(int row, int col) {
    // Logic to handle tile selection
    if (isFlippingAllowed) {
        int tileID = gameBoard.getTileID(row, col);
        gameBoard.flipTile(row, col); // Flip the selected tile

        // Perform further actions based on the flipped tile
        if (selectedTile.isFlipped()) {
            // Handle logic when the second tile is flipped
            // Check for match, update game state, etc.
            if (selectedTile.matches(gameBoard.getTile(row, col))) {
                // Match found
                // Do something, update score, etc.
            } else {
                // No match
                // Flip the tiles back after a delay or another interaction
            }
            // Reset selectedTile to null or an empty state
            selectedTile.reset();
        } else {
            // Handle logic when the first tile is flipped
            // Update selectedTile to keep track of the first flipped tile
            selectedTile = gameBoard.getTile(row, col);
        }
    }
}

void GameLogic::endGame() {
    // Logic to end the game
    isFlippingAllowed = false; // Disallow flipping
    // Calculate final score, show game-over screen, etc.
}



