
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Game.h"
#include "checkML.h"

using namespace std;

int main(int argc, char* argv[]){
	_CrtSetDbgFlag ( _CRTDBG_LEAK_CHECK_DF);

	try {
		Game* game = new Game();

		game->run();

		delete game;
	}

	catch (string error) {
		cout << error << endl;
	}

	return 0;
}