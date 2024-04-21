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

    inline float getRotation(sf::Vector2f& vector) {
        float angleRadians = std::atan2(vector.y, vector.x);

        float angleDegrees = angleRadians * (180.0f / static_cast<float>(3.14159255));

        if (angleDegrees < 0)
            angleDegrees += 360.0f;

        return angleDegrees;
    }

	inline float getDistance(sf::Vector2f sourcePos, sf::Vector2f destPos) {
		float dx = destPos.x - sourcePos.x;
		float dy = destPos.y - sourcePos.y;
		float length = std::sqrt(dx * dx + dy * dy);

		return length;
	}

    inline sf::Vector2f getArrowDirection(Arrow arrow) {
        sf::Vector2f directionValue;

        switch (arrow) {
        case Arrow::UP:
            directionValue = sf::Vector2f(0.f, -1.f);
            break;
        case Arrow::DOWN:
            directionValue = sf::Vector2f(0.f, 1.f);
            break;
        case Arrow::RIGHT:
            directionValue = sf::Vector2f(1.f, 0.f);
            break;
        case Arrow::LEFT:
            directionValue = sf::Vector2f(-1.f, 0.f);
            break;
        case Arrow::UPRIGHT:
            directionValue = sf::Vector2f(1.f, -1.f);
            break;
        case Arrow::UPLEFT:
            directionValue = sf::Vector2f(-1.f, -1.f);
            break;
        case Arrow::DOWNRIGHT:
            directionValue = sf::Vector2f(1.f, 1.f);
            break;
        case Arrow::DOWNLEFT:
            directionValue = sf::Vector2f(-1.f, 1.f);
            break;
        case Arrow::DEFAULT:
            directionValue = sf::Vector2f(1.f, 0.f);
            break;
        }

        return directionValue;
    }

    inline std::string towerToString(TowerType type) {
        switch (type) {
        case TowerType::PELLET:
            return "pellet";
        case TowerType::SQUIRT:
            return "squirt";
        case TowerType::DART:
            return "dart";
        case TowerType::SWARM:
            return "swarm";
        case TowerType::FROST:
            return "frost";
        case TowerType::BASH:
            return "bash";
        default:
            return "pellet";
        }
    }

    inline std::string enemyTypeToString(EnemyType type) {
        if (type == EnemyType::NORMAL) return "NORMAL";
        else if (type == EnemyType::GROUP) return "GROUP";
        else if (type == EnemyType::IMMUNE) return "IMMUNE";
        else if (type == EnemyType::FAST) return "FAST";
        else if (type == EnemyType::FLYING) return "FLYING";
        else if (type == EnemyType::SPAWN) return "SPAWN";
        else if (type == EnemyType::SPAWNED) return "SPAWNED";
    }

    inline EnemyType stringToEnemyType(std::string type) {
        if (type == "NORMAL") return EnemyType::NORMAL;
        else if (type == "GROUP") return EnemyType::GROUP;
        else if (type == "IMMUNE") return EnemyType::IMMUNE;
        else if (type == "FAST") return EnemyType::FAST;
        else if (type == "FLYING") return EnemyType::FLYING;
        else if (type == "SPAWN") return EnemyType::SPAWN;
        else if (type == "SPAWNED") return EnemyType::SPAWNED;
    }

}