/*
 * GameLogic.hpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */

// GameLogic.hpp
#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP

#include "Tile.hpp"
#include "Board.hpp"

class GameLogic {
private:
    Board gameBoard;

public:
    GameLogic(); // Constructor
    void startGame(); // Start the game logic
    void handleTileSelection(int tileID); // Handle the selected tile
    // Add more game logic functions as needed
};

#endif
