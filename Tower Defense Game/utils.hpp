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

    inline sf::Color enemyTypeToColor(EnemyType type) {
        switch (type) {
        case EnemyType::NORMAL: return Properties::levelScrollNormalColor;
        case EnemyType::GROUP: return Properties::levelScrollGroupColor;
        case EnemyType::IMMUNE: return Properties::levelScrollImmuneColor;
        case EnemyType::FAST: return Properties::levelScrollFastColor;
        case EnemyType::SPAWN: return Properties::levelScrollSpawnColor;
        case EnemyType::FLYING: return Properties::levelScrollFlyingColor;
        }
    }

    inline TowerType stringToTowerType(std::string type) {
        if (type == "PELLET") return TowerType::PELLET;
        else if (type == "SQUIRT") return TowerType::SQUIRT;
        else if (type == "DART") return TowerType::DART;
        else if (type == "SWARM") return TowerType::SWARM;
        else if (type == "FROST") return TowerType::FROST;
        else if (type == "BASH") return TowerType::BASH;
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

    inline std::string wrapText(const std::string& text, unsigned int width, const sf::Font& font) {
        std::stringstream ss(text);
        std::string line;
        std::string wrappedText;
        unsigned int lineWidth = 0;

        while (std::getline(ss, line, ' ')) {
            sf::Text tempText(line, font);
            lineWidth += tempText.getLocalBounds().width;

            if (lineWidth >= width) {
                wrappedText += "\n";
                lineWidth = tempText.getLocalBounds().width;
            }

            wrappedText += line + " ";
        }

        return wrappedText;
    }

    inline json handleJson(std::string fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Failed to open JSON file." << std::endl;
            system("pause");
        }

        json jsonData;
        try {
            file >> jsonData;
        }
        catch (json::parse_error& e) {
            std::cerr << "Parse error: " << e.what() << std::endl;
            system("pause");
        }

        file.close();

        return jsonData;
    }

}