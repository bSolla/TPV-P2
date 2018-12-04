#include "InfoBar.h"
#include "Game.h"


InfoBar::InfoBar (Game *gamePtr) {
	game = gamePtr;
	mapWidth = game->getMapWidth ();

	position.setX (0);
	position.setY (game->getMapHeight () - cellHeight);

	loadTextures ();
}


InfoBar::~InfoBar () {
	game = nullptr;
	
	delete textures[TextureTypes::numbers];
	textures[TextureTypes::numbers] = nullptr;

	delete textures[TextureTypes::level];
	textures[TextureTypes::level] = nullptr;

	delete textures[TextureTypes::lives];
	textures[TextureTypes::lives] = nullptr;
}


void InfoBar::loadTextures () {
	textures[TextureTypes::numbers] = new Texture (game->getRenderer (), TEXTURE_NAME_NUMBERS, 1, 11);
	textures[TextureTypes::level] = new Texture (game->getRenderer (), TEXTURE_NAME_LEVEL);
	textures[TextureTypes::lives] = new Texture (game->getRenderer (), TEXTURE_NAME_LIVES);
}


void InfoBar::render (uint seconds, uint minutes, uint currentLevel, uint lives) {
	uint cellWidth = mapWidth / N_DIVISIONS;
	SDL_Rect destRect { position.getX (), position.getY (), cellWidth, cellHeight };

	// renders the time with format  M M : S S
	textures[TextureTypes::numbers]->renderFrame (destRect, 0, minutes / 10); // renders the first digit (minutes)
	destRect.x += cellWidth;
	textures[TextureTypes::numbers]->renderFrame (destRect, 0, minutes % 10); // renders the last digit (minutes)
	destRect.x += cellWidth;
	
	textures[TextureTypes::numbers]->renderFrame (destRect, 0, 10); // renders the :
	destRect.x += cellWidth;

	textures[TextureTypes::numbers]->renderFrame (destRect, 0, seconds / 10); // renders the first digit (seconds)
	destRect.x += cellWidth;
	textures[TextureTypes::numbers]->renderFrame (destRect, 0, seconds % 10); // renders the last digit (seconds)
	destRect.x += cellWidth * 3;

	// renders the level info with format Level 0x
	destRect.w = cellWidth * 4;
	textures[TextureTypes::level]->render (destRect);
	destRect.x += cellWidth * 4;

	destRect.w = cellWidth;
	textures[TextureTypes::numbers]->renderFrame (destRect, 0, currentLevel / 10); // renders the first digit (level)
	destRect.x += cellWidth;
	textures[TextureTypes::numbers]->renderFrame (destRect, 0, currentLevel % 10); // renders the last digit (level)
	destRect.x += cellWidth * 2;

	// renders the lives info with format Lives x
	destRect.w = cellWidth * 4;
	textures[TextureTypes::lives]->render (destRect);
	destRect.x += cellWidth * 4;

	destRect.w = cellWidth;
	textures[TextureTypes::numbers]->renderFrame (destRect, 0, lives % 10); // renders the last digit (level)
}




