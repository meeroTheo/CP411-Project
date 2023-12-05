#ifndef DECK_HPP
#define DECK_HPP

#include "Tile.hpp"

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
