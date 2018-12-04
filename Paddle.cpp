#include "Paddle.h"
#include "Game.h"



Paddle::Paddle (Game* gamePtr) {
	game = gamePtr;
	texture = game->getTexture (TextureNames::paddle_);
	speed.setY (0.0);
}


Paddle::~Paddle () {
	game = nullptr;
	texture = nullptr;
}


void Paddle::render() {
	ArkanoidObject::render ();
}


void Paddle::changeSize (double scale) {
	uint newWidth = width * scale;

	if (newWidth < MAX_PADDLE_WIDTH && newWidth > MIN_PADDLE_WIDTH)
		width = newWidth;
}


void Paddle::setInitialPosition (int mapWidth, int verticalOffset) {
	position.setX (double (mapWidth) / 2);
	position.setY (double (verticalOffset));
}


void Paddle::handleEvents (SDL_Event &e) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			speed.setX (-basicIncrement);
			break;
		case SDLK_RIGHT:
			speed.setX (basicIncrement);
			break;
		default:
			break;
		}
	}
	else if (e.type == SDL_KEYUP) {
		speed.setX (0.0);
	}
}


bool Paddle::collides (SDL_Rect objectRect, Vector2D &collVector) {
	bool objectCollides = false;
	bool boundariesOK;
	int xCenterBall = objectRect.x + (objectRect.w / 2);
	int yBottomBall = objectRect.y + objectRect.h;

	// checks that the object's collision points are within the paddle's boundaries
	boundariesOK = yBottomBall > position.getY () && yBottomBall < (position.getY () + height);
	boundariesOK &= xCenterBall > position.getX () && xCenterBall < (position.getX () + width);

	if (boundariesOK) {
		int mid = position.getX () + (width / 2);
		double n = cos (MAX_ANGLE * RADIAN_CONVERSION_FACTOR);  

		collVector.setX ((n * double(xCenterBall - mid)) / (position.getX () - double(mid)));
		collVector.setY (sqrt (1.0 - pow (collVector.getX (), 2)));

		objectCollides = true;
	}
	// if not, objectCollides is initialized to false so no need to do anything
	
	return objectCollides;
}


void Paddle::update () {
	mapWidth = game->getMapWidth ();

	if (position.getX () > 20 && speed.getX() < 0) {
		MovingObject::update();
	}
	if (position.getX () < (mapWidth - width - 20) && speed.getX () > 0)
		MovingObject::update ();
	
}


void Paddle::saveToFile (ofstream &file) {
	MovingObject::saveToFile (file);

	file << width;
}


void Paddle::loadFromFile (ifstream &file) {
	MovingObject::loadFromFile (file);

	file >> width;
}
