#pragma once
#include "SFML/Graphics.hpp"
#include "FPS.h"
#include "ResourceManager.h"
#include "Grid.h"

class Game {
public:
	Game();
	~Game();
	void run();

private:
	sf::RenderWindow* window;
	ResourceManager rm;
	FPS* fps;
	Grid grid;
	void handleInput();
	void update();
	void render();
};

