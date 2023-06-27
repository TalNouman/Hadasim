#include <iostream>

#include "draft_music.hpp"

int main()
{
    MediaPlayer media_player;
    media_player.run();

    return 0;
}

//g++ -o output main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
