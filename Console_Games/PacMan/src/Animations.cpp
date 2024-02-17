#include "Animations.h"

#include "Globals.h"
#include "Sprites.h"


void pacman_closed()
{
    for (int i = 0; i < sprite_rez; i++) {
        for (int j = 0; j < sprite_rez; j++) {
            pacman_frame_buffer[0][i][j] = 1;
        }
    }
    pacman_frame_buffer[0][2][2] = 111;
    pacman_frame_buffer[0][0][0] = 0;
    pacman_frame_buffer[0][0][4] = 0;
    pacman_frame_buffer[0][4][0] = 0;
    pacman_frame_buffer[0][4][4] = 0;
}

void pacman_open1()
{
    pacman_closed();
    pacman_frame_buffer[0][2][0] = 0;
    pacman_frame_buffer[0][2][1] = 0;
    pacman_frame_buffer[0][2][2] = 0;
}

void pacman_open2()
{
    pacman_open1();
    pacman_frame_buffer[0][0][1] = 0;
    pacman_frame_buffer[0][1][0] = 0;
    pacman_frame_buffer[0][1][1] = 0;
    pacman_frame_buffer[0][1][2] = 0;
    pacman_frame_buffer[0][2][2] = 112;
    pacman_frame_buffer[0][2][3] = 0;
}