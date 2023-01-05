#pragma once
#include "SFML/Graphics.hpp"
class FPS : public sf::Drawable {
public:
	FPS(sf::Font* font);
	void update(long elapsed);
	int getFPS();
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	long elapsed;
	int frames;
	sf::Text text;
};

