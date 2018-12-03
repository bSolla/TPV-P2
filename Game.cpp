#include "Game.h"

// TODO: CLEAN UP THE COMMENTS


Game::Game () {
	iniSDL ();
	iniTextures ();
	
	gameObjects.push_back (new BlocksMap (this));

	gameObjects.push_back (new Wall (this, textures[TextureNames::sideWall])); //leftW
	gameObjects.push_back (new Wall (this, textures[TextureNames::sideWall])); //rightW
	gameObjects.push_back (new Wall (this, textures[TextureNames::topWall])); //topW

	gameObjects.push_back (new Ball (this));
	ballIt = gameObjects.end(); // ballIt set past the end
	ballIt--; // ballIt actually pointing to the position in the list

	gameObjects.push_back (new Paddle (this));
	paddleIt = gameObjects.end (); // paddleIt set past the end
	paddleIt--; //paddleIt actually pointing to the position in the list

	//walls[WallType::leftW] = new Wall (this, textures[TextureNames::sideWall]);
	//walls[WallType::rightW] = new Wall (this, textures[TextureNames::sideWall]);
	//walls[WallType::topW] = new Wall (this, textures[TextureNames::topWall]);
	//		
	//ball = new Ball(this);
	//paddle = new Paddle(this);
	//map = new BlocksMap(this);

	// playerInfoManager = new PlayerDataManager ();
	if (dynamic_cast<BlocksMap*>(*gameObjects.begin ()) != nullptr) {
		dynamic_cast<BlocksMap*>(*gameObjects.begin ())->load (LEVEL_SHARED_NAME + to_string (currentLevel) + LEVEL_EXTENSION);
	}
	else
		throw ArkanoidError ("Casting error\n");
	//map->load(LEVEL_SHARED_NAME + to_string(currentLevel) + LEVEL_EXTENSION);

	infoBar = new InfoBar (this);

	positionObjects ();
}


Game::~Game () {
	//delete ball;
	//delete paddle;
	//delete map;
	//delete infoBar;
	//for (uint i = 0; i < NUM_WALLS; ++i) {
	//	delete walls[i];
	//}
	for (itArkObjList it = gameObjects.begin (); it != gameObjects.end (); ++it) {
		delete (*it);
	}

	// delete playerInfoManager

	for (uint i = 0; i < NUM_TEXTURES; ++i) {
		delete textures[i];
	}

	quitSDL ();
}


void Game::iniSDL () {

	SDL_Init(SDL_INIT_EVERYTHING); 
	window = SDL_CreateWindow("test", WIN_X, WIN_Y, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE); 
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
	
	if (window == nullptr || renderer == nullptr) {
		throw SDLError(SDL_GetError());
	}
}


void Game::iniTextures () {

	//try {
	//	for (uint i = 0; i < NUM_TEXTURES; ++i) {
	//		textures[i] = new Texture(renderer, IMAGES_PATH + TEXTURE_ATTRIBUTES[i].filename, TEXTURE_ATTRIBUTES[i].rows, TEXTURE_ATTRIBUTES[i].cols);
	//	}
	//}

	//catch (SDLError error) {
	//	throw SDLError(SDL_GetError());
	//}

	string errorMsg;

	for (uint i = 0; i < NUM_TEXTURES; ++i) {
		textures[i] = new Texture(renderer, IMAGES_PATH + TEXTURE_ATTRIBUTES[i].filename, TEXTURE_ATTRIBUTES[i].rows, TEXTURE_ATTRIBUTES[i].cols);
	}

	errorMsg = SDL_GetError();
	if (errorMsg != "")
		throw SDLError(errorMsg);
}


void Game::scaleObjects (uint newMapWidth, uint newMapHeight) {
	mapHeight = newMapHeight;
	mapWidth = newMapWidth;

	itArkObjList wallIt = gameObjects.begin (); // it points to map for now
	wallIt++; // but now it points to the first wall

	// we can't make it in a loop because each wall has unique scale

	// left wall -------------------------------------------
	if (dynamic_cast<Wall*>(*wallIt) != nullptr) { 
		dynamic_cast<Wall*>(*wallIt)->setScale (mapHeight - STANDARD_CELL_HEIGHT, WALL_THICKNESS, WallType::leftW); // -STANDARD_CELL_HEIGHT to account for the info bar
	}
	else
		throw ArkanoidError ("Casting error\n");
	wallIt++;

	// right wall ----------------------------------------
	if (dynamic_cast<Wall*>(*wallIt) != nullptr) { 
		dynamic_cast<Wall*>(*wallIt)->setScale (mapHeight - STANDARD_CELL_HEIGHT, WALL_THICKNESS, WallType::rightW);
	}
	else
		throw ArkanoidError ("Casting error\n");
	wallIt++;

	// top wall ------------------------------------------
	if (dynamic_cast<Wall*>(*wallIt) != nullptr) { 
		dynamic_cast<Wall*>(*wallIt)->setScale (WALL_THICKNESS, mapWidth, WallType::topW);
	}
	else
		throw ArkanoidError ("Casting error\n");
	//walls[WallType::leftW]->setScale (mapHeight - STANDARD_CELL_HEIGHT, WALL_THICKNESS, WallType::leftW); // -STANDARD_CELL_HEIGHT to account for the info bar
	//walls[WallType::rightW]->setScale (mapHeight - STANDARD_CELL_HEIGHT, WALL_THICKNESS, WallType::rightW);
	//walls[WallType::topW]->setScale (WALL_THICKNESS, mapWidth, WallType::topW);

	SDL_SetWindowSize (window, mapWidth, mapHeight);
}


void Game::positionObjects () {
	// position paddle -------------------------------------
	if (dynamic_cast<Paddle*>(*paddleIt) != nullptr) { 
		dynamic_cast<Paddle*>(*paddleIt)->setInitialPosition (mapWidth, mapHeight - STANDARD_CELL_HEIGHT * 3);
	}
	else
		throw ArkanoidError ("Casting error\n");

	// position ball --------------------------------------
	if (dynamic_cast<Ball*>(*ballIt) != nullptr) { 
		dynamic_cast<Ball*>(*ballIt)->setInitialPosition (mapWidth, mapHeight - STANDARD_CELL_HEIGHT * 4);
	}
	else
		throw ArkanoidError ("Casting error\n");
	//paddle->setInitialPosition (mapWidth, mapHeight - cellHeight * 3);
	//ball->setInitialPosition (mapWidth, mapHeight - cellHeight * 4);
}


void Game::renderBackground () const{
	//for (uint i = 0; i < NUM_WALLS; ++i) {
	//	walls[i]->render ();
	//}
}


void Game::handleEvents () {
	SDL_Event ev;  

	if (SDL_PollEvent (&ev)) {
		if (ev.type == SDL_QUIT) {
			end = true;
		}
		else {
			//paddle->handleEvents (ev);
			for (itArkObjList it = gameObjects.begin (); it != gameObjects.end (); ++it) {
				(*it)->handleEvents (ev);
			}
		}
	}
}


void Game::handleLevelUp () {
	if (levelClear) {
		//delete map;	// delete the old map and make a new one for the new level
		//map = new BlocksMap (this);

		delete (*gameObjects.begin ());// delete the old map and make to new one for the new level
		gameObjects.erase (gameObjects.begin ());
		gameObjects.push_front (new BlocksMap (this)); // new map

		delete infoBar; // delete the old info bar to make a new one

		currentLevel++;

		// playerInfoManager->checkTime (seconds, minutes);

		// delete playerInfoManager; // delete the old player info manager and create a new one
		// playerInfoManager = new PlayerDataManager;

		if (currentLevel > MAX_LEVEL)
			end = true;
		else {
			// static cast because we know for sure that the first object is the map (it was created within this method)
			static_cast<BlocksMap*>(*gameObjects.begin())->load (LEVEL_SHARED_NAME + to_string (currentLevel) + LEVEL_EXTENSION);
			//map->load (LEVEL_SHARED_NAME + to_string (currentLevel) + LEVEL_EXTENSION);
			
			seconds = 0;
			minutes = 0;

			infoBar = new InfoBar (this);
			positionObjects ();

			levelClear = false;
		}
	}
}


void Game::handleTime () {
	currentTicks = SDL_GetTicks ();

	if (currentTicks > lastTicks + MILLISECONDS_IN_A_TICK) {
		seconds++;

		if (seconds > 59) {
			seconds = 0;
			minutes++;
		}

		lastTicks = currentTicks;
	}
}


bool Game::collides (SDL_Rect ballRect, Vector2D ballSpeed, Vector2D &collVector) {
	bool ballCollides = false;
	Block* blockPtr = nullptr;
	itArkObjList it = gameObjects.begin (); // it starts pointing at the map

	// ----------------------------------------------- if collides with the blocks...
	//blockPtr = map->collides (ballRect, ballSpeed, collVector);
	if (dynamic_cast<BlocksMap*>(*it) != nullptr) { 
		dynamic_cast<BlocksMap*>(*it)->collides (ballRect, ballSpeed, collVector);
	}
	else
		throw ArkanoidError ("Casting error\n");
	if (blockPtr != nullptr) {
		int rewardRand = rand () % 6; // random number [0, 5] to check if a reward is created
		
		ballCollides = true;
		dynamic_cast<BlocksMap*>(*it)->setBlockNull (blockPtr);

		if (rewardRand < 1) {
			createReward (ballRect);
		}
	}
	
	++it; // it now points to the first wall
	// ----------------------------------------------- if collides with any of the walls or the paddle...
	while (it != firstReward && !ballCollides) { // the paddle is the last object before the rewards
		ballCollides = (*it)->collides (ballRect, collVector);
		++it;
	}
	//// ----------------------------------------------- if collides with any of the walls...
	//else if (walls[WallType::leftW]->collides (ballRect, collVector) ||
	//	walls[WallType::rightW]->collides(ballRect, collVector) ||
	//	walls[WallType::topW]->collides(ballRect, collVector)) {
	//	
	//	ballCollides = true;
	// }

	//// ---------------------------------------------- if collides with the paddle...
	//else if (paddle->collides (ballRect, collVector)) {
	//	ballCollides = true;
	//}

	return ballCollides;
}


bool Game::rewardCollides (SDL_Rect rewardRect) {
	Vector2D dummyVector2D;
	bool ret = false;

	if (dynamic_cast<Paddle*>(*paddleIt) != nullptr) { 
		ret = dynamic_cast<Paddle*>(*paddleIt)->collides (rewardRect, dummyVector2D);
	}
	else
		throw ArkanoidError ("Casting error\n");

	return ret;
	//return paddle->collides (rewardRect, dummyVector2D);
}


void Game::createReward (SDL_Rect rect) {
	int rewardType = rand () % 4;
	Reward *r = new Reward (this, RewardType (rewardType));
	r->setPosition (rect);

	gameObjects.push_back (r);
	itArkObjList itLastReward = --(gameObjects.end ());
	if (firstReward == gameObjects.end ()) {
		firstReward = itLastReward;
	}

	r->setItList (itLastReward);
}


void Game::killObject (itArkObjList it) {
	if (it == firstReward) {
		firstReward++;
	}

	delete *it;
	gameObjects.erase (it);
}


void Game::render () const {
	SDL_RenderClear (renderer);

	renderBackground ();
	//map->render ();
	//paddle->render ();
	//ball->render ();
	for (auto it = gameObjects.begin (); it != gameObjects.end (); ++it) {
		(*it)->render ();
	}

	infoBar->render (seconds, minutes, currentLevel);

	SDL_RenderPresent (renderer);
}


void Game::update () {
	//ball->update();
	//paddle->update();
	//map->update ();

	for (itArkObjList it = gameObjects.begin (); it != gameObjects.end (); ) {
		itArkObjList next = it;
		++next;
		(*it)->update ();
		it = next;
	}

	handleEvents ();
	handleLevelUp ();
	handleTime ();
}


void Game::run () {
	while (!end && !gameOver) {
		render ();
		update ();

		SDL_Delay (DELAY);
	}
}


void Game::quitSDL () {
	SDL_DestroyRenderer (renderer);
	SDL_DestroyWindow (window);
	SDL_Quit ();
}

// Creates a new file with a given code and saves the current state of the game
// +include a case in which the file already exists
void Game::saveToFile(string code) {
	ofstream file;

	file.open (code + SAVE_EXTENSION);
	if (file.is_open()) {
		file << currentLevel << " " << seconds << " " << minutes << " " << lastTicks << " " << currentTicks << "\n";

		for (itArkObjList it = gameObjects.begin (); it != gameObjects.end (); ++it) {
			(*it)->saveToFile (file);
			file << "\n";
		}

		file.close ();
	}
	else
		throw FileNotFoundError (code + SAVE_EXTENSION);
}

void Game::loadFromFile(string code) {
	ifstream file;

	file.open(code + SAVE_EXTENSION);
	if (file.is_open()) {
		file >> currentLevel >> seconds >> minutes >> lastTicks >> currentTicks;

		for (itArkObjList it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			(*it)->loadFromFile(file);
		}

		file.close();
	}
	else
		throw FileNotFoundError(code + SAVE_EXTENSION);

}