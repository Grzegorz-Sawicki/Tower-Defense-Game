#include "PausableClock.h"

float PausableClock::globalTimeScale = 1.0; // Define static member variable

void PausableClock::restart() {
    m_isPaused = false;
    m_elapsedTime = sf::Time::Zero;
    m_clock.restart();
}

void PausableClock::pause() {
    if (!m_isPaused) {
        m_isPaused = true;
        m_elapsedTime += m_clock.getElapsedTime();
    }
}

void PausableClock::resume() {
    if (m_isPaused) {
        m_isPaused = false;
        m_clock.restart();
    }
}

sf::Time PausableClock::getElapsedTime() const {
    if (m_isPaused)
        return m_elapsedTime * globalTimeScale;
    else
        return (m_elapsedTime + m_clock.getElapsedTime()) * globalTimeScale;
}