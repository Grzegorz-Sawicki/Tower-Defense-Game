#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <string>
#include <queue>
#include <fstream>
#include <iomanip>
#include <mutex>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include "json.hpp"

using json = nlohmann::json;

//for named pipe
#include <windows.h>
#include <cstdlib>

#include "Properties.h"
#include "PausableClock.hpp"

enum class Arrow {
    DEFAULT, UP, RIGHT, DOWN, LEFT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT
};

enum class TileType {
    DEFAULT, TOWER, WALL, ENTRANCE, EXIT
};

enum class Path {
    HORIZONTAL, VERTICAL
};

enum class EnemyType {
    NORMAL, GROUP, IMMUNE, FAST, SPAWN, SPAWNED, FLYING
};

enum class TowerType {
    PELLET, SQUIRT, DART, SWARM, FROST, BASH, ELEM_COUNT
};