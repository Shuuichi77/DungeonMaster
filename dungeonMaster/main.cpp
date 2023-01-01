#include "include/Game.hpp"

int main(int argc, char **argv)
{
    FilePath filePath(argv[0]);

//    Game game(filePath, 600);
//    Game game(filePath, 800);
    Game game(filePath, 1200);

    return game.run();
}