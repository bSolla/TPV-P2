#pragma once
#include "ArkanoidObject.h"


class MovingObject :
	public ArkanoidObject {
protected:
	Vector2D speed;
public:
	MovingObject ();
	virtual ~MovingObject ();

	virtual void loadFromFile() {} // add speed too
	virtual void saveToFile() {} // add speed too

};

