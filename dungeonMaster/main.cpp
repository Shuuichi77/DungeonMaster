#include "include/Game.hpp"

int main(int argc, char **argv)
{
    FilePath filePath(argv[0]);
    if (argc == 2)
    {
//        Game game(filePath, 60, argv[1]);
//        Game game(filePath, 800, argv[1]);
        Game game(filePath, 1200, argv[1]);
        return game.run();

    }
    else
    {
//        Game game(filePath, 600);
        Game game(filePath, 800);
//        Game game(filePath, 1200);
        return game.run();
    }
}