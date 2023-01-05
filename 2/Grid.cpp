#include "Grid.h"
#include "LineTesting.h"
#include "Log.h"

static constexpr int NORTH = 0;
static constexpr int SOUTH = 1;
static constexpr int EAST = 2;
static constexpr int WEST = 3;

Grid::Grid() {
	worldSize = { 800, 600 };
	blockSize = 20;
	gridSize = { worldSize.x / blockSize, (worldSize.y / blockSize)};
	blockCount = gridSize.x * gridSize.y;
	blocks = new Block*[blockCount]{ nullptr };
	edges = new List<Edge>(30);
	initGrid();
}

Grid::~Grid() {
	for (int i = 0; i < blockCount; ++i) {
		delete blocks[i];
	}
	delete[] blocks;
	delete edges;
}

void Grid::setBlock(const sf::Vector2i& _pos) {
	int index = worldPosToGridIndex(_pos);
	blocks[index]->exists = !blocks[index]->exists;
}

void Grid::update() {
	clear();
	findEdges();
}

const sf::Vector2i& Grid::getWorldSize() const {
	return worldSize;
}

const sf::Vector2i& Grid::getGridSize() const {
	return gridSize;
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//draw blocks
	for (int y = 0; y < gridSize.y; ++y) {
		for (int x = 0; x < gridSize.x; ++x) {
			Block* block = blocks[y * gridSize.x + x];
			sf::Color color;
			if (block->exists) {
				color = sf::Color::Blue;
			}
			else {
				color = sf::Color::Black;
			}
			block->shape.setFillColor(color);
			target.draw(*block, states);
		}
	}

	//draw lines;
	for (int i = 0; i < edges->size(); ++i) {
		edges->get(i)->updateLine();
		target.draw(*edges->get(i));
	}
}

void Grid::initGrid() {
	for (int y = 0; y < gridSize.y; ++y) {
		for (int x = 0; x < gridSize.x; ++x) {
			int index = y * gridSize.x + x;
			bool exists = false;
			if (y == 0 || x == 0 || y == gridSize.y -1 || x == gridSize.x -1) {
				exists = true;
			}
			blocks[index] = new Block(blockSize, exists, sf::Vector2f(static_cast<float>(x * blockSize), static_cast<float>(y * blockSize)));
		}
	}
}

const int Grid::worldPosToGridIndex(const sf::Vector2i& _pos) const {
	return (_pos.y / blockSize) * gridSize.x + (_pos.x / blockSize);
}

void Grid::clear() {
	clearBlocks();
	edges->clear();
}

void Grid::clearBlocks() {
	for (int i = 0; i < blockCount; ++i) {
		Block* block = blocks[i];
		for (int j = 0; j < 4; ++j) {
			block->edgeExists[j] = false;
			block->edgeId[j] = -1;
		}
	}
}

void Grid::findEdges() {
	for (int y = 0; y < gridSize.y; ++y) {
		for (int x = 0; x < gridSize.x; ++x) {
			int index = y * gridSize.x + x;
			Block* block = blocks[index];
			Block* n = getBlock(index - gridSize.x);// blocks[index - gridSize.x];
			Block* s = getBlock(index + gridSize.x);//blocks[index + gridSize.x];
			Block* e = getBlock(index + 1);// blocks[index + 1];
			Block* w = getBlock(index - 1);// blocks[index - 1];
			if (block->exists) {
				if (canCreate(w)) {
					if (n != nullptr && n->edgeExists[WEST]) {
						edges->get(n->edgeId[WEST])->end.y += blockSize;
						block->edgeExists[WEST] = true;
						block->edgeId[WEST] = n->edgeId[WEST];
					}
					else {
						block->edgeExists[WEST] = true;
						block->edgeId[WEST] = edges->size();
						sf::Vector2i start = {
							x * blockSize,
							y * blockSize
						};
						sf::Vector2i end = {
							x * blockSize,
							(y * blockSize) + blockSize
						};
						edges->add(new Edge(start, end));
					}
				}

				if (canCreate(n)) {
					if (w != nullptr && w->edgeExists[NORTH]) {
						edges->get(w->edgeId[NORTH])->end.x += blockSize;
						block->edgeExists[NORTH] = true;
						block->edgeId[NORTH] = w->edgeId[NORTH];
					}
					else {
						block->edgeExists[NORTH] = true;
						block->edgeId[NORTH] = edges->size();
						sf::Vector2i start = {
							x * blockSize,
							y * blockSize
						};
						sf::Vector2i end = {
							(x * blockSize) + blockSize,
							(y * blockSize)
						};
						edges->add(new Edge(start, end));
					}
				}

				if (canCreate(e)) {
					if (n != nullptr && n->edgeExists[EAST]) {
						edges->get(n->edgeId[EAST])->end.y += blockSize;
						block->edgeExists[EAST] = true;
						block->edgeId[EAST] = n->edgeId[EAST];
					}
					else {
						block->edgeExists[EAST] = true;
						block->edgeId[EAST] = edges->size();
						sf::Vector2i start = {
							(x * blockSize) + blockSize,
							y * blockSize
						};
						sf::Vector2i end = {
							(x * blockSize) + blockSize,
							(y * blockSize) + blockSize
						};
						edges->add(new Edge(start, end));
					}
				}

				if (canCreate(s)) {
					if (w != nullptr && w->edgeExists[SOUTH]) {
						edges->get(w->edgeId[SOUTH])->end.x += blockSize;
						block->edgeExists[SOUTH] = true;
						block->edgeId[SOUTH] = w->edgeId[SOUTH];
					}
					else {
						block->edgeExists[SOUTH] = true;
						block->edgeId[SOUTH] = edges->size();
						sf::Vector2i start = {
							x * blockSize,
							(y * blockSize) + blockSize
						};
						sf::Vector2i end = {
							(x * blockSize) + blockSize,
							(y * blockSize) + blockSize
						};
						edges->add(new Edge(start, end));
					}
				}
			}
		}
	}
}

Block* Grid::getBlock(int index) {
	if (index < 0 || index >= blockCount) {
		return nullptr;
	}
	return blocks[index];
}

bool Grid::canCreate(Block* block) {
	if (block == nullptr) {
		return true;
	}else if (!block->exists) {
		return true;
	}else {
		return false;
	}
}

void Grid::calculateVisibilityPoint(float ox, float oy, float radius) {
	visibilityPoints.clear();

	for (int i = 0; i < edges->size(); ++i) {
		Edge* e1 = edges->get(i);
		for (int j = 0; j < 2; ++j) {
			float radiusX, radiusY;
			radiusX = (i == 0 ? e1->start.x : e1->end.x) - ox;
			radiusY = (i == 0 ? e1->start.y : e1->end.y) - oy;

			float baseAngle = atan2f(radiusX, radiusY);
			float angle;
			for (int k = 0; k < 3; ++k) {
				if (k == 0) angle = baseAngle - 0.0001f;
				if (k == 1) angle = baseAngle;
				if (k == 2) angle = baseAngle + 0.0001f;
				
				radiusX = radius * cosf(angle);
				radiusY = radius * sinf(angle);

				float min_t1 = INFINITY;
				float min_px = 0, min_py = 0, min_ang = 0;
				bool bValid = false;


				for (int l = 0; l < edges->size(); ++l) {
					if (l == i) { continue; }

					Edge* e2 = edges->get(l);
					
					float sdx = e2->end.x - e2->start.x;
					float sdy = e2->end.y - e2->start.y;

					if (fabs(sdx - radiusX) > 0.0f && fabs(sdy - radiusY) > 0.0f) {
						float t2 = (radiusX * (e2->start.y - oy) + (radiusY * (ox - e2->start.x))) / (sdx * radiusY - sdy * radiusX);
						float t1 = (e2->start.x + sdx * t2 - ox) / radiusX;

						if (t1 > 0 && t2 >= 0 && t2 <= 1.0f) {
							if (t1 < min_t1) {
								min_t1 = t1;
								min_px = ox + radiusX * t1;
								min_py = oy + radiusY * t1;
								min_ang = atan2f(min_py - oy, min_px - ox);
								bValid = true;
							}
						}
					}
				}
				if (bValid) {
					visibilityPoints.add(new VisibilityPolygonPoint(min_ang, min_px, min_py));
				}
			}
			

		}
	}
}
