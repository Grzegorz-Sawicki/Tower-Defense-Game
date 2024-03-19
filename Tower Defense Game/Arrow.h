#pragma once

#include "include.h"

enum DirectionArrow {
    DEFAULT, UP, RIGHT, DOWN, LEFT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT
};

class Arrow {
private:
    DirectionArrow directionArrow;
    sf::Vector2f directionValue;
public:
    Arrow(DirectionArrow directionArrow);

    //Arrow(DirectionArrow directionArrow) {
    //    this->directionArrow = directionArrow;
    //    switch (this->directionArrow) {
    //    case LEFT:
    //        directionValue = sf::Vector2f(-1.f, 0.f);
    //        break;
    //    case RIGHT:
    //        directionValue = sf::Vector2f(1.f, 0.f);
    //        break;
    //    case UP:
    //        directionValue = sf::Vector2f(0.f, -1.f);
    //        break;
    //    case DOWN:
    //        directionValue = sf::Vector2f(0.f, 1.f);
    //        break;
    //    case UPRIGHT:
    //        directionValue = sf::Vector2f(1.f, -1.f);
    //        break;
    //    case UPLEFT:
    //        directionValue = sf::Vector2f(-1.f, -1.f);
    //        break;
    //    case DOWNRIGHT:
    //        directionValue = sf::Vector2f(1.f, 1.f);
    //        break;
    //    case DOWNLEFT:
    //        directionValue = sf::Vector2f(-1.f, 1.f);
    //        break;
    //    default:
    //        directionValue = sf::Vector2f(1.f, 0.f);
    //    }
    //}

    sf::Vector2f getDirectionValue;
};

