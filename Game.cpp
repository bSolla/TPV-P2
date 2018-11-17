#include "Game.h"


Game::Game () {
	iniSDL ();
	iniTextures ();
	
	walls[WallType::leftW] = new Wall (this, textures[TextureNames::sideWall]);
	walls[WallType::rightW] = new Wall (this, textures[TextureNames::sideWall]);
	walls[WallType::topW] = new Wall (this, textures[TextureNames::topWall]);
			
	ball = new Ball(this);
	paddle = new Paddle(this);
	map = new BlocksMap(this);
	// playerInfoManager = new PlayerDataManager ();

	map->load(LEVEL_SHARED_NAME + to_string(currentLevel) + LEVEL_EXTENSION);

	infoBar = new InfoBar (this);

	positionObjects ();
}


Game::~Game () {
	delete ball;
	delete paddle;
	delete map;
	delete infoBar;
	// delete playerInfoManager

	for (uint i = 0; i < NUM_TEXTURES; ++i) {
		delete textures[i];
	}

	for (uint i = 0; i < NUM_WALLS; ++i) {
		delete walls[i];
	}
	
	quitSDL ();
}


void Game::iniSDL () {

	SDL_Init(SDL_INIT_EVERYTHING); 
	window = SDL_CreateWindow("test", WIN_X, WIN_Y, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE); 
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
	
	if (window == nullptr || renderer == nullptr) {
		throw "Error initializing SDL\n";
	}
}


void Game::iniTextures () {
	string errorMsg;

	for (uint i = 0; i < NUM_TEXTURES; ++i) {
		textures[i] = new Texture (renderer, IMAGES_PATH + TEXTURE_ATTRIBUTES[i].filename, TEXTURE_ATTRIBUTES[i].rows, TEXTURE_ATTRIBUTES[i].cols);
	}

	errorMsg = SDL_GetError ();
	if (errorMsg != "")
		throw errorMsg;
}


void Game::scaleObjects (uint newMapWidth, uint newMapHeight) {
	mapHeight = newMapHeight;
	mapWidth = newMapWidth;

	walls[WallType::leftW]->setScale (mapHeight - cellHeight, cellHeight, WallType::leftW); // -cellHeight to account for the info bar
	walls[WallType::rightW]->setScale (mapHeight - cellHeight, cellHeight, WallType::rightW);
	walls[WallType::topW]->setScale (cellHeight, mapWidth, WallType::topW);

	SDL_SetWindowSize (window, mapWidth, mapHeight);
}


void Game::positionObjects () {
	paddle->setInitialPosition (mapWidth, mapHeight - cellHeight * 3);
	ball->setInitialPosition (mapWidth, mapHeight - cellHeight * 4);
}


void Game::renderBackground () const{
	for (uint i = 0; i < NUM_WALLS; ++i) {
		walls[i]->render ();
	}
}


void Game::handleEvents () {
	SDL_Event event;  

	if (SDL_PollEvent (&event)) {
		if (event.type == SDL_QUIT) {
			end = true;
		}
		else {
			paddle->handleEvents (event);
		}
	}
}


void Game::handleLevelUp () {
	if (levelClear) {
		delete map;	// delete the old map and make a new one for the new level
		map = new BlocksMap (this);
		delete infoBar; // delete the old info bar to make a new one

		currentLevel++;

		// playerInfoManager->checkTime (seconds, minutes);

		// delete playerInfoManager; // delete the old player info manager and create a new one
		// playerInfoManager = new PlayerDataManager;

		if (currentLevel > MAX_LEVEL)
			end = true;
		else {
			map->load (LEVEL_SHARED_NAME + to_string (currentLevel) + LEVEL_EXTENSION);
			
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

	// if collides with the blocks...
	blockPtr = map->collides (ballRect, ballSpeed, collVector);
	if (blockPtr != nullptr) {
		ballCollides = true;
		map->setBlockNull (blockPtr);
	}
	
		// if collides with any of the walls...
	else if (walls[WallType::leftW]->collides (ballRect, collVector) ||
		walls[WallType::rightW]->collides(ballRect, collVector) ||
		walls[WallType::topW]->collides(ballRect, collVector)) {
		
		ballCollides = true;
	 }


	// if collides with the paddle...
	else if (paddle->collides (ballRect, collVector)) {
		ballCollides = true;
	}

	return ballCollides;
}


void Game::render () const {
	SDL_RenderClear (renderer);

	renderBackground ();
	map->render ();
	paddle->render ();
	ball->render ();
	infoBar->render (seconds, minutes, currentLevel);

	SDL_RenderPresent (renderer);
}


void Game::update () {
	ball->update();
	paddle->update();
	map->update ();

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
