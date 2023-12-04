#include "World.hpp"
#include "Board.hpp"
#include "Tile.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;

World::World() {
	Shape *obj = NULL;

	/* add Board into the world object list */
	obj = new Board();
	obj->setId(1);
	obj->scaleChange(0.8);
	objlist.push_back(obj);

	std::vector<int> randomizedTextureIDs;
	srand(static_cast<unsigned int>(time(NULL)));

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 2; ++j) {
			randomizedTextureIDs.push_back(i);
		}
	}

	int n = randomizedTextureIDs.size();
	for (int i = n - 1; i > 0; --i) {
		int j = rand() % (i + 1);
		std::swap(randomizedTextureIDs[i], randomizedTextureIDs[j]);
	}

    /* add Tiles into the world object list */
    for (int i = 2; i <= 9; ++i) {
        obj = new Tile();
        obj->setId(i);
        obj->setTexId(randomizedTextureIDs[i - 2]);
        obj->scaleChange(-0.4);

        int x = (i - 2) % 4;  // Adjust x-coordinate based on the loop variable
        int y = (i - 2) / 4;  // Adjust y-coordinate based on the loop variable

        obj->translate(-4.5 + x * 3, 2 - y * 4, 2);
        objlist.push_back(obj);
    }
}

World::~World(){
	Shape *obj;
	while (!objlist.empty()) {
		obj = objlist.front();
		objlist.pop_front();
		free(obj);
	}
}



void World::draw() {
	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
	  (*it)->draw();
    }
}

void World::reset(){
	Shape *obj = NULL;

	std::vector<int> randomizedTextureIDs;
	srand(static_cast<unsigned int>(time(NULL)));

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 2; ++j) {
			randomizedTextureIDs.push_back(i);
		}
	}

	int n = randomizedTextureIDs.size();
	for (int i = n - 1; i > 0; --i) {
		int j = rand() % (i + 1);
		std::swap(randomizedTextureIDs[i], randomizedTextureIDs[j]);
	}

	/* add Tiles into the world object list */
	for (int i = 2; i <= 9; ++i) {
		obj = this->searchById(i);
		obj->setTexId(randomizedTextureIDs[i - 2]);
	}
}

Shape* World::searchById(GLint i) {
	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
	  if ((*it)->getId() == i) return *it;
    }
	return NULL;
}

