#pragma once
#include <SFML/System.hpp>

class PausableClock {
public:
    static float globalTimeScale; // Declare static member variable

    PausableClock() : m_isPaused(false), m_elapsedTime(sf::Time::Zero) {}

    void restart();
    void pause();
    void resume();
    sf::Time getElapsedTime() const;

private:
    sf::Clock m_clock;
    bool m_isPaused;
    sf::Time m_elapsedTime;
};
