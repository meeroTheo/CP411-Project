#include "World.hpp"
#include "Board.hpp"
#include "Tile.hpp"

using namespace std;

World::World() {
	Shape *obj = NULL;

	/* add Board into the world object list */
	obj = new Board();
	obj->setId(1);
	obj->scaleChange(0.8);
	objlist.push_back(obj);

    /* add Tile into the world object list */
	obj = new Tile();
	obj->setId(2);
	obj->scaleChange(-0.4);
	obj->translate(-3, 2, 2);
	objlist.push_back(obj);

	obj = new Tile();
	obj->setId(3);
	obj->scaleChange(-0.4);
	obj->translate(-1, 2, 2);
	objlist.push_back(obj);

	obj = new Tile();
	obj->setId(4);
	obj->scaleChange(-0.4);
	obj->translate(1, 2, 2);
	objlist.push_back(obj);

	obj = new Tile();
	obj->setId(5);
	obj->scaleChange(-0.4);
	obj->translate(3, 2, 2);
	objlist.push_back(obj);

	obj = new Tile();
	obj->setId(6);
	obj->scaleChange(-0.4);
	obj->translate(-3, -2, 2);
	objlist.push_back(obj);

	obj = new Tile();
	obj->setId(7);
	obj->scaleChange(-0.4);
	obj->translate(-1, -2, 2);
	objlist.push_back(obj);

	obj = new Tile();
	obj->setId(8);
	obj->scaleChange(-0.4);
	obj->translate(1, -2, 2);
	objlist.push_back(obj);

	obj = new Tile();
	obj->setId(9);
	obj->scaleChange(-0.4);
	obj->translate(3, -2, 2);
	objlist.push_back(obj);
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

	obj = this->searchById(1);
	obj->reset();
	obj->setScale(0.5);
	obj->translate(2.5, 0, 0);

	obj = this->searchById(2);
	obj->reset();
	obj->setScale(0.5);
	obj->translate(4, 0, 0);

	obj = this->searchById(3);
	obj->reset();
	obj->setScale(0.5);
}

Shape* World::searchById(GLint i) {
	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
	  if ((*it)->getId() == i) return *it;
    }
	return NULL;
}

