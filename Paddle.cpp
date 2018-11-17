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


void Paddle::render() const {
	SDL_Rect destRect{ position.getX(), position.getY(), width, height };
	texture->render(destRect);
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


bool Paddle::collides (SDL_Rect ballRect, Vector2D &collVector) {
	bool ballCollides = false;
	bool boundariesOK;
	int xCenterBall = ballRect.x + (ballRect.w / 2);
	int yBottomBall = ballRect.y + ballRect.h;

	// checks that the ball's collision points are within the paddle's boundaries
	boundariesOK = yBottomBall > position.getY () && yBottomBall < (position.getY () + height);
	boundariesOK &= xCenterBall > position.getX () && xCenterBall < (position.getX () + width);

	if (boundariesOK) {
		int mid = position.getX () + (width / 2);
		double n = cos (MAX_ANGLE * RADIAN_CONVERSION_FACTOR);  

		// for debugging, delete after it's done
		//double d = (n * double (xCenterBall - mid));
		//double f = (position.getX () - double (mid) );

		collVector.setX ((n * double(xCenterBall - mid)) / (position.getX () - double(mid)));
		collVector.setY (sqrt (1.0 - pow (collVector.getX (), 2)));

		ballCollides = true;
	}
	// if not, ballCollides is initialized to false so no need to do anything
	
	return ballCollides;
}


void Paddle::update () {
	mapWidth = game->getMapWidth ();

	if (position.getX () > 20 && speed.getX() < 0) {
		position = position + speed;
	}
	if (position.getX () < (mapWidth - width - 20) && speed.getX() > 0)
		position = position + speed;
	
}
