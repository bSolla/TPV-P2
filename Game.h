#pragma once
#include <iostream>
#include <fstream>
#include <new>
#include <string>
#include <list>
//#include <SDL_ttf.h>
#include "checkML.h"
#include "Utilities.h"
#include "Texture.h"
#include "Ball.h"
#include "BlocksMap.h"
#include "Paddle.h"
#include "Wall.h"
#include "InfoBar.h"
#include "PlayerDataManager.h"
#include "ArkanoidObject.h"
#include "Reward.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"
#include "SDLError.h"
#include "ArkanoidError.h"

typedef list<ArkanoidObject*>::iterator itArkObjList;
class Game {
	// --------------------- variables------------------------------------------------------
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// order...... map; walls; ball; paddle; rewards
	list<ArkanoidObject*> gameObjects; 
	itArkObjList firstReward;
	int numRewards = 0;

	itArkObjList paddleIt;
	itArkObjList ballIt;

	Texture* textures[NUM_TEXTURES];
	InfoBar* infoBar = nullptr;
	// PlayerDataManager* playerInfoManager = nullptr;

	bool end = false;
	bool gameOver = false;
	bool levelClear = false;
	bool menu = true;

	uint lives = 3;
	uint currentLevel = 1;
	uint seconds = 0, minutes = 0;
	uint lastTicks = 0, currentTicks = 0;
	uint score = 0;

	uint mapHeight, mapWidth;

	// ---------------------- methods ------------------------------------------------------
public:
	Game();
	~Game();

	// getter functions
	uint getMapWidth() const { return mapWidth; }
	uint getMapHeight() const { return mapHeight; }
	Texture* getTexture(TextureNames textureName) const { return textures[textureName]; }
	SDL_Renderer* getRenderer() const { return renderer; }

	// setter functions
	void setLevelClear() { levelClear = true; }
	void setGameOver() { gameOver = true; }
	void increaseLives() { if (lives < MAX_LIVES) lives++; }
	void decreaseLives () { lives--; if (lives == 0) setGameOver (); else positionObjects (); }
	void setPaddleSize (double scale);
	void setMapSize (int w, int h) { mapWidth = w; mapHeight = h; }

	// takes in the map dimensions calculated in BlocksMap::load() and scales the walls and window to fit accordingly
	void scaleObjects(uint newMapWidth, uint newMapHeight);
	// main game loop, runs until a quit event is detected
	void run();
	// returns wether the ball collides with an object or not, and if it does, returns the collision vector
	bool collides(SDL_Rect ballRect, Vector2D ballSpeed, Vector2D &collVector);
	// checks if a reward collides with the paddle
	bool rewardCollides(SDL_Rect rewardRect);
	// deletes an object from the list
	void killObject(itArkObjList it);

private:
	// initializes SDL 
	void iniSDL();
	// initializes all textures
	void iniTextures();

	// loads the menu
	void loadMenu ();
	// manages the menu
	void manageMenu ();
	// reads the code file and loads that file if it exists
	void menuLoadFromFile ();
	// renders the instructions screen for entering the file code for loading
	void renderInstructions ();
	// renders a number "keyboard" to use for entering the file code for loading
	void renderNumberButtons ();
	// returns true if the player clicked on one of the numbers or the "done" button, and returns a reference to said number (-1=done)
	bool handleNumberButtons (SDL_Event SDLevent, int &number);

	// initializes all game objects
	void playScene ();
	// gives the ball and paddle their initial positions, calculated from the map dimensions
	void positionObjects();

	// polls events, and checks for quit events. also calls handleEvents(SDL_Event &e) for all the objects in the list
	void handleEvents();
	// if the control bool levelClear is true, deletes the old BlocksMap, creates a new one and reads all the corresponding info
	void handleLevelUp();
	// keeps track of the time elapsed since starting a level
	void handleTime();
	// creates a new reward positioned where the ball hit a block (using the ball SDL_Rect)
	void createReward(SDL_Rect rect);
	// polymorphic call to render()
	void render() const;
	// polymorphic call to update()
	void update();

	// destroys both renderer and window and quits SDL
	void quitSDL();

	// pauses the game and saves numeric keyboard input as the file name
	string pickFileName ();
	// saves the current state on the game in file code.ark
	void saveToFile(string code);

	void loadFromFile(string code);
};

