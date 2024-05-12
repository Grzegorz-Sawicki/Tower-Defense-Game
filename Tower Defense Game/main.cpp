#include "include.h"
#include "Game.h"

int main() {
    srand(time(NULL));

    Game game = Game(53000);

    game.run();

    return 0;
}