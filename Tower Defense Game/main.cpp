#include "include.h"
#include "Game.h"

int main() {
    srand(time(NULL));

    Game game = Game();

    game.run();

    return 0;
}