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

    /* add Tiles into the world object list */
    for (int i = 2; i <= 9; ++i) {
        obj = new Tile();
        obj->setId(i%4);
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

//void World::handleClickEvent(float x, float y) {
//	//coords
//	//cout << x << " " << y << endl;
//    for (std::list<Shape*>::iterator it = objlist.begin(); it != objlist.end(); ++it) {
//        Tile* tile = dynamic_cast<Tile*>(*it);
//        if (tile && tile->isClicked(x, y)) {
//            cout << "Tile with ID " << tile->getId() << " clicked!" << endl;
//            // You can add additional logic or actions here if needed
//        }
//    }
//}
void World::handleClickEvent(float x, float y) {
    for (std::list<Shape*>::iterator it = objlist.begin(); it != objlist.end(); ++it) {
        Tile* tile = dynamic_cast<Tile*>(*it);
        if (tile) {
            // Adjust with the fixed values used during initialization
            float translatedClickX = (x/3) + 4.5;
            float translatedClickY = y - 2;

            if (tile->isClicked(translatedClickX, translatedClickY)) {
                cout << "Tile with ID " << tile->getId() << " clicked!" << endl;
                // You can add additional logic or actions here if needed
            }
        }
    }
}





