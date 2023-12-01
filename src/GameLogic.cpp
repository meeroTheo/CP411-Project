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
}

void GameLogic::startGame() {
    // Logic to start the game
    // May involve shuffling tiles, setting up the initial game state, etc.
}

void GameLogic::handleTileSelection(int tileID) {
    // Logic to handle tile selection
    // May involve flipping the tile, checking for matches, etc.
    // You may interact with the Board object to perform these actions
    gameBoard.flipTile(tileID);
    // Add more logic as needed
}



