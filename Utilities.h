#pragma once

using namespace std;

// ------------------ type definitions ---------------------------------------------------
struct TextureAttributes {
	string filename;
	unsigned int cols;
	unsigned int rows;
};
// added the underscores after ball and paddle to avoid mixing them with the variables ball and paddle
enum TextureNames { ball_, bricks, paddle_, sideWall, topWall };


// ---------------------- constants -----------------------------------------------------
const unsigned int WALL_THICKNESS = 20;

const unsigned int STANDARD_CELL_WIDTH = 60;
const unsigned int STANDARD_CELL_HEIGHT = 20;