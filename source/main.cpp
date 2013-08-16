#include "game.hpp"

int main(int argc, char** argv)
{
    if (game.start() != 0)
        return -1;

    return game.mainloop();
}
