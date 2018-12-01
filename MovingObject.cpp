#include "MovingObject.h"



MovingObject::MovingObject () {

}


MovingObject::~MovingObject () {
}

void MovingObject::update() {
	position = position + speed;
}

void MovingObject::saveToFile(ofstream file) {
	file << speed.getX() << " " << speed.getY() << " ";
}