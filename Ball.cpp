#include "Ball.h"
#include "Game.h"


Ball::Ball (Game* gamePtr) {
	game = gamePtr;
	texture = game->getTexture (TextureNames::ball_);
}


Ball::~Ball () {
	game = nullptr;
	texture = nullptr;
}


void Ball::setInitialPosition (int mapWidth, int verticalOffset) {
	position.setX (double (mapWidth) / 2 + double (cellSize));
	position.setY (double (verticalOffset));
}


void Ball::render () const {
	SDL_Rect destRect { position.getX (), position.getY (), cellSize, cellSize };

	texture->render (destRect);
}


void Ball::checkCollisions () {
	SDL_Rect ballRect { position.getX (), position.getY (), cellSize, cellSize };
	Vector2D collVect;

	if (game->collides (ballRect, speed, collVect)) {
		if (collVect.getX () == 0.0) {
			speed.setY (-1 * speed.getY ());
		}
		else if (collVect.getY () == 0.0) {
			speed.setX (-1 * speed.getX ());
		}
		else { // collision with the paddle
			Vector2D collVectCopy = collVect;
			double xAux = -1 * collVect.getX () * MAX_SPEED_MODULE;
			double yAux = -1 * collVect.getY () * MAX_SPEED_MODULE;

			if (xAux == 0) {
				if (collVectCopy.getX () < 0)
					xAux = -(MAX_SPEED_MODULE + yAux);
				else 
					xAux = MAX_SPEED_MODULE + yAux;
			}

			speed.setX (xAux);
			speed.setY (yAux);
		}
	}
}


bool Ball::checkBallOut () {
	return (position.getY () + cellSize > game->getMapHeight ());
}


void Ball::update () {
	position = position + speed;
	checkCollisions ();

	if (checkBallOut ()) {
		game->setGameOver ();
	}
}
