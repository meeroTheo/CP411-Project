#ifndef DECK_HPP
#define DECK_HPP

#include "Tile.hpp" // Include your Tile class definition

class Deck {
private:
    Tile cards[8];
    int topCardIndex;

public:
    Deck();
    void shuffle();
    Tile dealCard();
};

#endif /* DECK_HPP */
