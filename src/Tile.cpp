/*
 * Tile.cpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */
// Tile.cpp
#include "Tile.hpp"

Tile::Tile() {
    // Initialize variables, load textures, etc.
    isFlipped = false;
}

void Tile::loadTextures(const char* frontTextureFile, const char* backTextureFile) {
    // Load textures for front and back sides of the tile
    // Use OpenGL functions or libraries to load textures
    // Example: Load frontTexture and backTexture using SOIL, stb_image, etc.
}

void Tile::draw(float x, float y, float z) {
    glPushMatrix();
    // Translate to the specified position (x, y, z)
    glTranslatef(x, y, z);

    // Draw the tile based on the flip state
    if (isFlipped) {
        // Draw the back side of the tile
        // Use backTexture and draw a textured quad
    } else {
        // Draw the front side of the tile
        // Use frontTexture and draw a textured quad
    }

    glPopMatrix();
}

bool Tile::isPointInside(float x, float y) {
    // Check if a point (x, y) is inside the tile's bounds
    // Return true if the point is inside, false otherwise
    // Useful for handling mouse clicks on tiles
}

void Tile::flip() {
    // Method to flip the tile from its current state
    isFlipped = !isFlipped;
}



