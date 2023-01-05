#include <iostream>
#include <stdexcept>

#include "Game.h"

#ifdef _DEBUG
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-network-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#else
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-network.lib")
#pragma comment(lib, "sfml-audio.lib")
#endif


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	try
	{
		Game game;
		game.run();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown error" << std::endl;
	}

	return 0;
}