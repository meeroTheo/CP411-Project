#include "deck.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>

Deck::Deck() : topCardIndex(0) {
    // Initialize tiles using the default constructor of Tile
    // Adjust this initialization according to your Tile class requirements

    for (int i = 0; i < 8; ++i) {
        cards[i] = Tile(); // Assuming Tile has a default constructor
    }
}

void Deck::shuffle() {
    // Shuffle the tiles
    // Adjust this according to your Tile class requirements
    std::srand(std::time(0));
    std::random_shuffle(cards, cards + 8);


}

Tile Deck::dealCard() {
    if (topCardIndex < 8) {
        return cards[topCardIndex++];
    }
    // Handle an error if all cards have been dealt
    // For example: throw an exception or return a default Tile
    return Tile(); // Return a default-constructed Tile for now
}
