#include "include/Game.hpp"

int main(int argc, char **argv)
{
    FilePath filePath(argv[0]);
    if (argc == 2)
    {
//        Game game(filePath, 600, argv[1]);
//        Game game(filePath, 800, argv[1]);
        Game game(filePath, 1200, argv[1]);
        return game.run();
    }

    else if (argc == 3)
    {
        Game game(filePath, std::stoi(argv[2]), argv[1]);
        return game.run();
    }

    else
    {
//        Game game(filePath, 600);
//        Game game(filePath, 800);
        Game game(filePath, 1200);
        return game.run();
    }
}