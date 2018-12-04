#include "Block.h"
#include "Game.h"


Block::Block (Game *gamePtr, int colorIndex) {
	game = gamePtr;

	colorIndex--; // the max. color index in the file is 6 instead of 5, bc it starts with 1 
	setColor (BlockColor(colorIndex));
	texture = game->getTexture (TextureNames::bricks);
}


Block::~Block () {
	game = nullptr;
	texture = nullptr;
}


void Block::setColor (BlockColor newColor) {
	color = newColor;
	row = color / TEXTURE_ATTRIBUTES[TextureNames::bricks].cols; //spriteSheetRow = colorIndex / 3
	col = color - (TEXTURE_ATTRIBUTES[TextureNames::bricks].cols * row); //spriteSeetCol = colorIndex - 3 * spriteSheetRow
}


void Block::setPosition (uint matrixColumnIndex, uint matrixRowIndex) {
	position.setX (double (width * matrixColumnIndex + WALL_THICKNESS));
	position.setY (double (height * matrixRowIndex + WALL_THICKNESS));
}


void Block::render () {
	texture->renderFrame (getRect(), row, col);
}


void Block::saveToFile (ofstream &file) {
	file << int (color) + 1 << " "; //add 1 because color in the file starts from 1
}



