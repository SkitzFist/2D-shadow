#include "Block.h"

Block::Block(int _size, bool _exists, sf::Vector2f _pos) {
	exists = _exists;
	shape.setSize(sf::Vector2f(static_cast<float>(_size), static_cast<float>(_size)));
	shape.setPosition(_pos);

}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape, states);
}
