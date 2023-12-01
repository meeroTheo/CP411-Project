/*
 * Tile.hpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */

// Tile.hpp
#ifndef TILE_HPP
#define TILE_HPP

#include <GL/glut.h>

class Tile {
private:
    GLuint frontTexture; // Texture ID for the front side of the tile
    GLuint backTexture; // Texture ID for the back side of the tile
    bool isFlipped; // Flag to track if the tile is flipped

public:
    Tile();
    void loadTextures(const char* frontTextureFile, const char* backTextureFile);
    void draw(float x, float y, float z); // Method to draw the tile at a specified position
    bool isPointInside(float x, float y); // Check if a point is inside the tile
    void flip(); // Method to flip the tile

    // Add more methods or members as needed
};

#endif
