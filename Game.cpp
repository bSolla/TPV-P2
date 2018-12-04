#include "Game.h"

// TODO: CLEAN UP THE COMMENTS


Game::Game () {
	iniSDL ();
	iniTextures ();
}


Game::~Game () {
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
	string errorMsg;

	for (uint i = 0; i < NUM_TEXTURES; ++i) {
		textures[i] = new Texture(renderer, IMAGES_PATH + TEXTURE_ATTRIBUTES[i].filename, TEXTURE_ATTRIBUTES[i].rows, TEXTURE_ATTRIBUTES[i].cols);
	}

	errorMsg = SDL_GetError();
	if (errorMsg != "")
		throw SDLError(errorMsg);
}


void Game::loadMenu () {
	SDL_SetWindowSize (window, WIN_WIDTH, WIN_HEIGHT);
	SDL_Rect destRect { 0, 0, WIN_WIDTH, WIN_HEIGHT / (uint)2 };

	SDL_RenderClear (renderer);

	textures[TextureNames::play_]->render (destRect);
	destRect.y = WIN_HEIGHT / 2;
	textures[TextureNames::load_]->render (destRect);

	SDL_RenderPresent (renderer);
}


void Game::manageMenu () {
	SDL_Event ev;
	bool click = false;
	menu = true;
	int mouseX, mouseY;

	loadMenu ();

	do {
		if (SDL_PollEvent (&ev)) {
			if (ev.type == SDL_QUIT) {
				end = true;
			}
			else if (ev.type == SDL_MOUSEBUTTONUP) {
				SDL_GetMouseState (&mouseX, &mouseY);

				click = true;

				if (mouseY < (int)WIN_HEIGHT / 2) { // play button
					menu = false;
					playScene ();
				}
				else { // load button
					try {
						menuLoadFromFile ();
					}
					catch (FileNotFoundError err) {
						loadMenu ();
						click = false;
					}
				}
			} // if mouse button up
		} // if event exists && game can still run
	} while (!click && !end);
}


void Game::menuLoadFromFile () {
	SDL_Event SDLevent;
	stringstream numberSequence;
	string fileName;
	int number = -2;
	uint iterations = 0;
	bool click = false;

	SDL_Rect destRect { 0, WIN_HEIGHT / 2, STANDARD_CELL_HEIGHT, STANDARD_CELL_HEIGHT };

	renderInstructions ();
	renderNumberButtons ();

	do {
		// get the numbers and store them in a stream + render them
		if (SDL_PollEvent (&SDLevent)) {
			if (SDLevent.type == SDL_QUIT) {
				end = false;
			}
			if (SDLevent.type == SDL_MOUSEBUTTONUP) {
				click = handleNumberButtons (SDLevent, number);
			}
		}

		if (click) {
			if (number != -1) {
				numberSequence << number;

				// render the chosen number in screen
				destRect.x = iterations * STANDARD_CELL_HEIGHT;
				textures[TextureNames::menuNumbers]->renderFrame (destRect, 0, number);
				SDL_RenderPresent (renderer);

				iterations++;
			}
			click = false;
		}
	} while (number != -1 && !end);

	fileName = LEVELS_PATH + numberSequence.str () + LEVEL_EXTENSION;
	
	try { loadFromFile (numberSequence.str ()); }
	catch (...) {
		throw FileNotFoundError (numberSequence.str () + LEVEL_EXTENSION);
	}
}


void Game::renderInstructions () {
	SDL_Rect destRect { 0, 0, WIN_WIDTH, WIN_HEIGHT };
	
	SDL_RenderClear (renderer);

	textures[TextureNames::instructions]->render (destRect);

	SDL_RenderPresent (renderer);
}


void Game::renderNumberButtons () {
	uint numbersCellSize = WIN_HEIGHT / 10;
	SDL_Rect destRect { 0, WIN_HEIGHT - numbersCellSize, WIN_WIDTH, numbersCellSize };

	textures[TextureNames::menuNumbers]->render(destRect);

	SDL_RenderPresent (renderer);
}


bool Game::handleNumberButtons (SDL_Event SDLevent, int &number) {
	int mouseX, mouseY;
	int numberCellSize = WIN_WIDTH / 10;
	int numbersY = WIN_HEIGHT - numberCellSize;
	int index = 0;
	bool click = false;

	SDL_GetMouseState (&mouseX, &mouseY);

	if ((mouseX > 0 && mouseX < numberCellSize) &&
		(mouseY > 0 && mouseY < numberCellSize)) { // click on the finish button
		click = true;
		number = -1;
	}
	else {
		while (!click && index < 10) {
			if ((mouseX > (index * numberCellSize) && mouseX < ((index + 1) * numberCellSize)) &&
				(mouseY > numbersY && mouseY < WIN_HEIGHT)) { // click on each of the numbers
				click = true;
				number = index;
			}

			index++;
		} //while
	} // else

	return click;
}


void Game::playScene () {
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

	firstReward = gameObjects.end ();

	// playerInfoManager = new PlayerDataManager ();
	if (dynamic_cast<BlocksMap*>(*gameObjects.begin ()) != nullptr) {
		dynamic_cast<BlocksMap*>(*gameObjects.begin ())->load (LEVEL_SHARED_NAME + to_string (currentLevel) + LEVEL_EXTENSION);
	}
	else
		throw ArkanoidError ("Casting error\n");

	infoBar = new InfoBar (this);

	positionObjects ();
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
}


void Game::setPaddleSize (double scale) {
	if (dynamic_cast<Paddle*>(*paddleIt) != nullptr) { 
		dynamic_cast<Paddle*>(*paddleIt)->changeSize (scale);
	}
	else
		throw ArkanoidError ("Casting error\n");
}


void Game::handleEvents () {
	SDL_Event ev;  

	if (SDL_PollEvent (&ev)) {
		if (ev.type == SDL_QUIT) {
			end = true;
		}
		else {
			if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_s) {
				string code = pickFileName ();
				saveToFile (code);
			}
			else {
				for (itArkObjList it = gameObjects.begin (); it != gameObjects.end (); ++it) {
					(*it)->handleEvents (ev);
				}
			}
		}
	}
}


void Game::handleLevelUp () {
	if (levelClear) {
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
	if (dynamic_cast<BlocksMap*>(*it) != nullptr) { 
		blockPtr = dynamic_cast<BlocksMap*>(*it)->collides (ballRect, ballSpeed, collVector);
	}
	else
		throw ArkanoidError ("Casting error\n");
	if (blockPtr != nullptr) {
		srand (currentTicks);
		int rewardRand = rand () % 3; // random number [0, 5] to check if a reward is created
		
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
	srand (currentTicks);
	int rewardType = rand () % 4;
	Reward *r = new Reward (this, RewardType (rewardType));
	r->setPosition (rect);

	gameObjects.push_back (r);
	itArkObjList itLastReward = --(gameObjects.end ());
	if (firstReward == gameObjects.end ()) {
		firstReward = itLastReward;
	}

	numRewards++;
	r->setItList (itLastReward);
}


void Game::killObject (itArkObjList it) {
	if (it == firstReward) {
		firstReward++;
	}

	delete *it;
	gameObjects.erase (it);

	numRewards--;
}


void Game::render () const {
	SDL_RenderClear (renderer);

	for (auto it = gameObjects.begin (); it != gameObjects.end (); ++it) {
		(*it)->render ();
	}

	infoBar->render (seconds, minutes, currentLevel, lives);

	SDL_RenderPresent (renderer);
}


void Game::update () {
	itArkObjList it = gameObjects.begin ();

	while (it != gameObjects.end () && !levelClear) {
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
		if (menu) {
			manageMenu ();
			SDL_SetWindowSize (window, mapWidth, mapHeight);
		}
		else {
			render ();
			update ();
		}
		SDL_Delay (DELAY);
	}
}


void Game::quitSDL () {
	SDL_DestroyRenderer (renderer);
	SDL_DestroyWindow (window);
	SDL_Quit ();
}


string Game::pickFileName () {
	SDL_Event sdlEvent;
	bool done = false;
	stringstream name;

	while (!done) {
		if (SDL_PollEvent (&sdlEvent)) {
			if (sdlEvent.type == SDL_KEYDOWN) {
				switch (sdlEvent.key.keysym.sym) {
				case SDLK_0:
					name << "0";
					break;
				case SDLK_1:
					name << "1";
					break;
				case SDLK_2:
					name << "2";
					break;
				case SDLK_3:
					name << "3";
					break;
				case SDLK_4:
					name << "4";
					break;
				case SDLK_5:
					name << "5";
					break;
				case SDLK_6:
					name << "6";
					break;
				case SDLK_7:
					name << "7";
					break;
				case SDLK_8:
					name << "8";
					break;
				case SDLK_9:
					name << "9";
					break;
				case SDLK_RETURN:
					done = true;
				default:
					break;
				}// switch
			}
		}
	}// while !done

	return name.str ();
}


// Creates a new file with a given code and saves the current state of the game
void Game::saveToFile(string code) {
	ofstream file;

	file.open (LEVELS_PATH + code + SAVE_EXTENSION);
	if (file.is_open()) {
		file << currentLevel << " " << seconds << " " << minutes << " " << lastTicks << " " << currentTicks << "\n";

		for (itArkObjList it = gameObjects.begin (); it != firstReward; ++it) {
			(*it)->saveToFile (file);
			file << "\n";
		}

		file << numRewards << "\n";

		for (itArkObjList it = firstReward; it != gameObjects.end (); ++it) {
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

	file.open(LEVELS_PATH + code + SAVE_EXTENSION);
	if (file.is_open()) {
		menu = false;

		file >> currentLevel >> seconds >> minutes >> lastTicks >> currentTicks;
		
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

		firstReward = gameObjects.end ();

		itArkObjList it = gameObjects.begin ();
		(*it)->loadFromFile(file); // loads map
		++it;

		infoBar = new InfoBar (this);

		for (it; it != gameObjects.end(); ++it) {
			(*it)->loadFromFile(file);
		}

		file >> numRewards;
		firstReward = gameObjects.end ();

		for (uint i = 0; i < numRewards; ++i) {
			gameObjects.push_back (new Reward (this));
			itArkObjList it = gameObjects.end ();
			--it;

			(*it)->loadFromFile (file);
			static_cast<Reward*>(*it)->setItList (it);
		}

		file.close();
	}
	else
		throw FileNotFoundError(code + SAVE_EXTENSION);

}