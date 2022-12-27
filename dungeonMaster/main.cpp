#include "include/Game.hpp"

int main(int argc, char **argv)
{
    FilePath filePath(argv[0]);
//    Game     game(filePath, 800.f * 1.5f, 600.f * 1.5f);
    Game     game(filePath, 800.f * 2.f, 600.f * 2.f);

    return game.run();
}