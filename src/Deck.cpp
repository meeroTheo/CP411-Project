#include "deck.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>

Deck::Deck() : topCardIndex(0) {
    //initialize tiles using the default constructor of Tile

    for (int i = 0; i < 8; ++i) {
        cards[i] = Tile();
    }
}

void Deck::shuffle() {
    // Shuffle the tiles
    std::srand(std::time(0));
    std::random_shuffle(cards, cards + 8);


}

Tile Deck::dealCard() {
    if (topCardIndex < 8) {
        return cards[topCardIndex++];
    }
    return Tile();
}
