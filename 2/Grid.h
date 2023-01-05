#pragma once
#include "SFML/Graphics.hpp"
#include "List.h"
#include "Block.h"
#include "Edge.h"
#include "VisibilityPolygon.h"

class Grid : public sf::Drawable {
public:
	Grid();
	~Grid();

	void setBlock(const sf::Vector2i& _pos);
	void update();
	const sf::Vector2i& getGridSize() const;
	const sf::Vector2i& getWorldSize() const;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Vector2i worldSize;
	sf::Vector2i gridSize;
	int blockSize;
	int blockCount;
	Block** blocks;
	List<Edge>* edges;
	List<VisibilityPolygonPoint> visibilityPoints;

	void initGrid();
	const int worldPosToGridIndex(const sf::Vector2i& _pos) const;
	void clear();
	void clearBlocks();
	void findEdges();
	Block* getBlock(int index);
	bool canCreate(Block* block);
	void calculateVisibilityPoint(float ox, float oy, float radius);
};

