#pragma once

#include "include.h"

namespace utils
{

	inline float getRotation(sf::Vector2f& sourcePos, sf::Vector2f& destPos) {

		float dx = destPos.x - sourcePos.x;
		float dy = destPos.y - sourcePos.y;

		float angle = std::atan2(dy, dx);

		return angle * (180 / 3.14159255);
	}

}