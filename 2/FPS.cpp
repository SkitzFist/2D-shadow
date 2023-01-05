#include "FPS.h"
#include <string>
#include "Log.h"
FPS::FPS(sf::Font* font) {
	elapsed = 0;
	frames = 0;

	text.setFont(*font);
	text.setPosition(10, 10);
}

void FPS::update(long _elapsed) {
	elapsed += _elapsed;
	++frames;
	long elapsedInS = static_cast<int>(elapsed / 10000000);
	int fps = 0;
	if (elapsedInS > 0) {
		fps = frames / elapsedInS;
	}
	text.setString(std::to_string(fps));
}

int FPS::getFPS() {
	return static_cast<int>(elapsed / frames);
}

void FPS::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(text, states);
}
