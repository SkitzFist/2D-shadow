#pragma once
#include "SFML/Graphics.hpp"

class Block : public sf::Drawable {
public:
	Block(int _size, bool _exists, sf::Vector2f _pos);

	bool exists;
	bool edgeExists[4] = { false,false,false,false };
	int edgeId[4] = { 0,0,0,0 };
	sf::RectangleShape shape;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
