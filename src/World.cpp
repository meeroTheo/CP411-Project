#include "World.hpp"
#include "Cube.hpp"
#include "Board.hpp"

using namespace std;

World::World() {
	Shape *obj = NULL;

	/* add Board into the world object list */
		obj = new Board();
		obj->setId(1);
		obj->scaleChange(0.8);
		objlist.push_back(obj);

    /* add Cube into the world object list */
	obj = new Cube();
	obj->setId(2);
	obj->scaleChange(-0.4);
	obj->translate(-3, 2, 2);
	objlist.push_back(obj);

	obj = new Cube();
	obj->setId(3);
	obj->scaleChange(-0.4);
	obj->translate(-1, 2, 2);
	objlist.push_back(obj);

	obj = new Cube();
	obj->setId(4);
	obj->scaleChange(-0.4);
	obj->translate(1, 2, 2);
	objlist.push_back(obj);

	obj = new Cube();
	obj->setId(5);
	obj->scaleChange(-0.4);
	obj->translate(3, 2, 2);
	objlist.push_back(obj);

	obj = new Cube();
		obj->setId(6);
		obj->scaleChange(-0.4);
		obj->translate(-3, -2, 2);
		objlist.push_back(obj);

		obj = new Cube();
		obj->setId(7);
		obj->scaleChange(-0.4);
		obj->translate(-1, -2, 2);
		objlist.push_back(obj);

		obj = new Cube();
		obj->setId(8);
		obj->scaleChange(-0.4);
		obj->translate(1, -2, 2);
		objlist.push_back(obj);

		obj = new Cube();
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

void lineSegment(float x1, float y1, float z1, float x2, float y2, float z2) {
	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}

void World::draw() {
//	glColor3f(1.0, 0.0, 0.0);
//	lineSegment(-2, 0, 0, 4, 0, 0); /* x-axis in red */
// 	glColor3f(0.0, 1.0, 0.0);
//	lineSegment(0, -2, 0, 0, 4, 0); /* y-axis in green */
//	glColor3f(0.0, 0.0, 1.0);
//	lineSegment(0, 0, -2, 0, 0, 4); /* z-axis in blue */

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


//	std::list<Shape*>::iterator it;
//	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
//	  (*it)->reset();
//  }
}

Shape* World::searchById(GLint i) {
	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
	  if ((*it)->getId() == i) return *it;
    }
	return NULL;
}

