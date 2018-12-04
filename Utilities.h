#pragma once
#include "SDL.h" // Windows

using namespace std;

// ------------------ type definitions ---------------------------------------------------
struct TextureAttributes {
	string filename;
	unsigned int cols;
	unsigned int rows;
};
// added the underscores to avoid mixing them with the variables
enum TextureNames { ball_, bricks, paddle_, sideWall, topWall, rewards, play_, load_, instructions, menuNumbers};


// ---------------------- constants -----------------------------------------------------
const unsigned int WALL_THICKNESS = 20;

const unsigned int STANDARD_CELL_WIDTH = 60;
const unsigned int STANDARD_CELL_HEIGHT = 20;

const double MAKE_PADDLE_BIGGER = 1.25;
const double MAKE_PADDLE_SMALLER = 0.75;
const unsigned int MAX_PADDLE_WIDTH = 120;
const unsigned int MIN_PADDLE_WIDTH = 25;

const unsigned int WIN_WIDTH = 800;
const unsigned int WIN_HEIGHT = 600;
const unsigned int WIN_X = SDL_WINDOWPOS_CENTERED;
const unsigned int WIN_Y = SDL_WINDOWPOS_CENTERED;

const unsigned int NUM_TEXTURES = 10;
const unsigned int NUM_WALLS = 3;

const unsigned int DELAY = 60;
const unsigned int MILLISECONDS_IN_A_TICK = 1000;

const string IMAGES_PATH = "images\\";
const TextureAttributes TEXTURE_ATTRIBUTES[NUM_TEXTURES] = 
	{	{ "ball.png", 1, 1 },
		{ "bricks.png", 3, 2 },
		{ "paddle.png", 1, 1 },
		{ "side.png", 1, 1 },
		{ "topSide.png", 1, 1 },
		{ "rewards.png", 8, 10},
		{ "play.png", 1, 1},
		{ "load.png", 1, 1},
		{ "instructions.png", 1, 1},
		{ "menuNumbers.png", 10, 1}
	};


const string LEVEL_SHARED_NAME = "level0";
const string LEVEL_EXTENSION = ".ark";
const string SAVE_EXTENSION = ".ark";
const unsigned int MAX_LEVEL = 3;

const unsigned int MAX_LIVES = 5;

