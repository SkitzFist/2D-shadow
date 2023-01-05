#pragma once
#include <SFML/Graphics.hpp>

class Edge : public sf::Drawable {
public:
	Edge(sf::Vector2i _start, sf::Vector2i _end);
	sf::Vector2i start;
	sf::Vector2i end;
	sf::Vertex line[2];
	void updateLine();
	const std::string& toString() const;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

