#include "Game.h"
#include "Log.h"
#include <chrono>

Game::Game() {
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "test");
	fps = new FPS(rm.getFont(Fonts::debug));
}

Game::~Game() {
	delete fps;
	delete window;
}

void Game::run() {
	int targetUpdateFrequence = 60;
	long gameSpeed = 10000000 / targetUpdateFrequence;
	long delta = 0;
	auto prev = std::chrono::system_clock::now();
	while (window->isOpen()) {	
		auto elapsed = std::chrono::system_clock::now() - prev;
		prev = std::chrono::system_clock::now();
		delta += static_cast<long>(elapsed.count());
		while (delta >= gameSpeed) {
			handleInput();
			update();
			fps->update(static_cast<long>(elapsed.count()));
			delta -= gameSpeed;
		}
		render();
	}
}

void Game::handleInput() {
	sf::Event e;
	while (window->pollEvent(e)) {
		if (e.type == sf::Event::Closed || e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Escape) {
			window->close();
		}

		if (e.type == sf::Event::MouseButtonPressed) {
			if (e.mouseButton.button == sf::Mouse::Button::Left) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
				if (mousePos.x > 0 && mousePos.y > 0 && mousePos.x < grid.getWorldSize().x && mousePos.y < grid.getWorldSize().y) {
					grid.setBlock(mousePos);
				}
			}
		}
	}
}

void Game::update() {
	grid.update();
}

void Game::render() {
	window->clear();
	window->draw(grid);
	window->draw(*fps);
	window->display();
}
