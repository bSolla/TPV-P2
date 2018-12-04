#include "BlocksMap.h"
#include "Game.h"


BlocksMap::BlocksMap (Game* gamePtr) {
	game = gamePtr;
}


BlocksMap::~BlocksMap () {
	if (cells != nullptr) {
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				delete cells[r][c];
			}
		}
	}
}


void BlocksMap::load (const string & filename) {
	ifstream file;

	file.open (LEVELS_PATH + filename);
	if (!file.is_open ()) {
		throw (FileNotFoundError (filename));
	}
	else {
		BlocksMap::loadFromFile (file);
		game->scaleObjects (mapWidth, mapHeight);

		file.close ();
	}
}


/* Dados el rectángulo y vector de dirección de la pelota, devuelve un puntero al 
   bloque con el que ésta colisiona (nullptr si no colisiona con nadie) y el 
   vector normal perpendicular a la superficie de colisión.
*/
Block* BlocksMap::collides(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D& collVector){
	Vector2D topLeftPoint = { double (ballRect.x), double (ballRect.y) }; 
	Vector2D topRightPoint = { double (ballRect.x + ballRect.w), double (ballRect.y) }; 
	Vector2D bottomLeftPoint = { double (ballRect.x), double (ballRect.y + ballRect.h) }; 
	Vector2D bottomRightPoint = { double (ballRect.x + ballRect.w), double (ballRect.y + ballRect.h) }; // bottom-right
	Block* block = nullptr;

	if (ballVel.getX() < 0 && ballVel.getY() < 0){
		if ((block = blockAt(topLeftPoint))){
			if ((block->getY() + cellHeight - topLeftPoint.getY()) <= (block->getX() + cellWidth - topLeftPoint.getX()))
				collVector = {0,1}; // Borde inferior mas cerca de topLeftPoint
			else
				collVector = {1,0}; // Borde dcho mas cerca de topLeftPoint
		} else if ((block = blockAt(topRightPoint))) { collVector = {0,1};
		} else if ((block = blockAt(bottomLeftPoint))) collVector = {1,0};
	} else if (ballVel.getX() >= 0 && ballVel.getY() < 0){
		if ((block = blockAt(topRightPoint))){
			if (((block->getY() + cellHeight - topRightPoint.getY()) <= (topRightPoint.getX() - block->getX())) || ballVel.getX() == 0)
				collVector = {0,1}; // Borde inferior mas cerca de topRightPoint
			else
				collVector = {-1,0}; // Borde izqdo mas cerca de topRightPoint
		} else if ((block = blockAt(topLeftPoint))) { collVector = {0,1};
		} else if ((block = blockAt(bottomRightPoint))) collVector = {-1,0};
	} else if (ballVel.getX() > 0 && ballVel.getY() > 0){
		if ((block = blockAt(bottomRightPoint))){
			if (((bottomRightPoint.getY() - block->getY()) <= (bottomRightPoint.getX() - block->getX()))) // || ballVel.getX() == 0)
				collVector = {0,-1}; // Borde superior mas cerca de bottomRightPoint
			else
				collVector = {-1,0}; // Borde dcho mas cerca de bottomRightPoint
		} else if ((block = blockAt(bottomLeftPoint))) { collVector = {0,-1};
		} else if ((block = blockAt(topRightPoint))) collVector = {-1,0};
	} else if (ballVel.getX() < 0 && ballVel.getY() > 0){
		if ((block = blockAt(bottomLeftPoint))){
			if (((bottomLeftPoint.getY() - block->getY()) <= (block->getX() + cellWidth - bottomLeftPoint.getX()))) // || ballVel.getX() == 0)
				collVector = {0,-1}; // Borde superior mas cerca de bottomLeftPoint
			else
				collVector = {1,0}; // Borde dcho mas cerca de topLeftPoint
		} else if ((block = blockAt(bottomRightPoint))) { collVector = {0,-1};
		} else if ((block = blockAt(topLeftPoint))) collVector = {1,0};
	}
	return block;
}


void BlocksMap::getBlockMatrixCoordinates (const Vector2D &point, int &c, int &r) {
	int wallThickness = cellHeight; // we have set the wall thickness to be the same as the rest of the sprites' height

	c = int ((point.getX () - wallThickness) / cellWidth);
	r = int ((point.getY () - wallThickness) / cellHeight);
}


/*  Devuelve el puntero al bloque del mapa de bloques al que pertenece el punto p.
	En caso de no haber bloque en ese punto (incluido el caso de que p esté fuera
	del espacio del mapa) devuelve nullptr. 	
*/
Block* BlocksMap::blockAt(const Vector2D& p){
	Block* blockPtr;
	int wallThickness = cellHeight; // we have set the wall thickness to be the same as the rest of the sprites' height

	if (p.getX() - wallThickness <= 0  || p.getX() >= mapWidth - wallThickness || p.getY() >= (rows * cellHeight + wallThickness)) { // out of the map on the left side   OR  out of the map on the right side  OR  too low to collide
		blockPtr = nullptr;
	}
	else {
		int c, r;

		getBlockMatrixCoordinates (p, c, r);

		if (cells[r][c] != nullptr)
			blockPtr = cells[r][c];
		else
			blockPtr = nullptr;
	}

	return blockPtr;
}


void BlocksMap::setBlockNull (Block* blockPtr) {
	Vector2D blockPos (blockPtr->getX (), blockPtr->getY ());
	int c, r;

	getBlockMatrixCoordinates (blockPos, c, r);

	delete cells[r][c];
	cells[r][c] = nullptr;

	nBlocks--;
}


void BlocksMap::render (){
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (cells[r][c] != nullptr)
				cells[r][c]->render ();
		}
	}
}


void BlocksMap::update () {
	if (nBlocks <= 0) {
		game->setLevelClear ();
	}
}


// Saves the actual state of the map with the same format of the level.ark files
void BlocksMap::saveToFile(ofstream &file) {
	file << rows << " " << cols << "\n";

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (cells[r][c] != nullptr)
				cells[r][c]->saveToFile (file);
			else
				file << 0 << " ";
		}
		file << "\n";
	}
}


void BlocksMap::loadFromFile (ifstream &file) {
	int color = 0;

	file >> rows >> cols;

	if (rows < 1 || cols < 1) {
		throw FileFormatError (WRONG_MAP_SIZE);
	}

	mapWidth = cellWidth * cols + cellHeight * 2; // to account for the walls we add cellHeight * 2 (the thickness of the walls is the same as the height of the rest of sprites)
	mapHeight = 2 * (cellHeight * rows) + cellHeight * 2;

	game->setMapSize (mapWidth, mapHeight);

	// pointer initialization
	cells = new Block**[rows];

	for (uint r = 0; r < rows; ++r) {
		cells[r] = new Block*[cols];
	}

	// fill values in
	for (uint r = 0; r < rows; ++r) {
		for (uint c = 0; c < cols; ++c) {
			file >> color;

			if (color < 0 || color > 6) {
				throw FileFormatError (WRONG_COLOR);
			}

			if (color == 0) { 
				cells[r][c] = nullptr;
			}
			else {
				cells[r][c] = new Block (game, BlockColor(color));
				cells[r][c]->setPosition (c, r);
				++nBlocks;
			}
		}
	}
}