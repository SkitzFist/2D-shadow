#pragma once
#include "SFML/Graphics.hpp"

class VisibilityPolygonPoint {
	float angle;
	float x;
	float y;

	VisibilityPolygonPoint(float _angle, float _x, float _y) {
		angle = _angle;
		x = _x;
		y = _y;
	}
};

