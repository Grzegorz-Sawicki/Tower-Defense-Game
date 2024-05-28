#include "include.h"
#include "Game.h"
#include "GameServer.h"

//int main() {
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    srand(time(NULL));

    Game game;

    GameServer gameServer(game, 53000);

    std::thread gameServerThread(&GameServer::run, &gameServer);

    gameServerThread.join();

    return 0;
}