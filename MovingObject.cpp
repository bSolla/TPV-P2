#include "MovingObject.h"



MovingObject::MovingObject () {

}


MovingObject::~MovingObject () {
}

void MovingObject::update() {
	position = position + speed;
}

void MovingObject::saveToFile(ofstream &file) {
	// save position
	ArkanoidObject::saveToFile (file);
	// save speed
	file << speed.getX() << " " << speed.getY() << " ";
}

void MovingObject::loadFromFile (ifstream &file) {
	double speedX, speedY;

	// load position 
	ArkanoidObject::loadFromFile (file);
	
	// load speed
	file >> speedX >> speedY;
	speed.setX (speedX);
	speed.setY (speedY);
}