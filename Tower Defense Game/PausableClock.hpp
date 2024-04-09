#pragma once
#include <SFML/System.hpp>

class PausableClock {
public:
    PausableClock() : m_isPaused(false), m_elapsedTime(sf::Time::Zero) {}

    void restart() {
        m_isPaused = false;
        m_elapsedTime = sf::Time::Zero;
        m_clock.restart();
    }

    void pause() {
        if (!m_isPaused) {
            m_isPaused = true;
            m_elapsedTime += m_clock.getElapsedTime();
        }
    }

    void resume() {
        if (m_isPaused) {
            m_isPaused = false;
            m_clock.restart();
        }
    }

    sf::Time getElapsedTime() const {
        if (m_isPaused)
            return m_elapsedTime;
        else
            return m_elapsedTime + m_clock.getElapsedTime();
    }

private:
    sf::Clock m_clock;
    bool m_isPaused;
    sf::Time m_elapsedTime;
};
