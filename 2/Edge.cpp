#include "Edge.h"

Edge::Edge(sf::Vector2i _start, sf::Vector2i _end) {
	start = _start;
	end = _end;
	
}

void Edge::updateLine(){
	line[0] = sf::Vertex(static_cast<sf::Vector2f>(start));
	line[0].color = sf::Color::White;
	line[1] = sf::Vertex(static_cast<sf::Vector2f>(end));
	line[0].color = sf::Color::White;
}


const std::string& Edge::toString() const {
	std::string strStart = std::to_string(line[0].position.x) + "." + std::to_string(line[0].position.y);
	std::string strEnd = std::to_string(line[1].position.x) + "." + std::to_string(line[1].position.y);
	return strStart + " -> " + strEnd;
}

void Edge::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(line, 2, sf::Lines);
}
