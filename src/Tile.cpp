/*
 * Tile.cpp
 *
 *  Created on: Dec 1, 2023
 *      Author: Meer
 */
// Tile.cpp
#include "Tile.hpp"
#include <GL/glut.h> // Include OpenGL headers or libraries for texture loading

Tile::Tile() {
    isFlipped = false;
}

void Tile::loadTextures(const char* frontTextureFile, const char* backTextureFile) {
    // Example of texture loading using GLUT library (modify according to your texture loading method)
    // Load front side texture
    frontTexture = LoadTexture(frontTextureFile);

    // Load back side texture
    backTexture = LoadTexture(backTextureFile);
}

void Tile::draw(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    if (isFlipped) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, backTexture);
        glBegin(GL_QUADS);
        // Draw back side quad with texture coordinates
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    } else {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, frontTexture);
        glBegin(GL_QUADS);
        // Draw front side quad with texture coordinates
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }

    glPopMatrix();
}

bool Tile::isPointInside(float x, float y) {
    // Placeholder logic for point inside check
    return (x >= -1.0f && x <= 1.0f && y >= -1.0f && y <= 1.0f);
}

void Tile::flip() {
    isFlipped = !isFlipped;
}

// Example texture loading function (using GLUT)
GLuint Tile::LoadTexture(const char* textureFile) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // Load and set texture parameters here using the specified textureFile
    // Example: Use the SOIL library, stb_image, or other texture loading methods
    // Ensure to handle image data loading, format, and parameters correctly
    return textureID;
}



