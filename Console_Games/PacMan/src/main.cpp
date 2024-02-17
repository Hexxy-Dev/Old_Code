
#include "Globals.h"
#include "Sprites.h"
#include "Console stuff.h"
#include "Animations.h"
#include "Display.h"
#include "Map builders.h"


#include <future>
#include <conio.h>

int copy[sprite_rez][sprite_rez];

int offset_j = 70;

int i_poz = 145;

void transfer_frame(int frame_buffer[sprite_rez][sprite_rez], int frame[sprite_rez][sprite_rez])
{
    for (int i = 0; i < sprite_rez; i++)
    {
        for (int j = 0; j < sprite_rez; j++)
        {
            frame_buffer[i][j] = frame[i][j];
        }
    }
}

void pac()
{
    display_sprite( pacman_frames[1], i_poz, offset_j);

    display_sprite( phantom_preset_frames[0], i_poz, offset_j + 250);

    display_sprite( phantom_preset_frames[0], i_poz + 250, offset_j);

    display_sprite( phantom_preset_frames[0], i_poz + 260, offset_j + 260);

    display_sprite( phantom_preset_frames[0], i_poz + 370, offset_j + 270);
}

void increment(bool left = true, bool down = false, bool up = false, bool right = false) {
    if (left)
        offset_j++;
    if (right)
        offset_j--;
    if (down)
        i_poz++;
    if (up)
        i_poz--;
}

void move_pacman(bool left = true, bool down = false, bool up = false, bool right = false)
{
    increment(left, down, up, right);
    pac();
    increment(left, down, up, right);
    pac();
    increment(left, down, up, right);
    pac();
    increment(left, down, up, right);
    pac();
    increment(left, down, up, right);
    pac();
}

bool hmm = true;



void pacman_anim()
{
    while (hmm)
    {
        transfer_frame(pacman_frame_buffer[0], phantom_preset_frames[0]);
        //pacman_open2();
        temp_sleep(game_speed);
        //pacman_open1();
        transfer_frame(pacman_frame_buffer[0], phantom_preset_frames[0]);
        temp_sleep(game_speed);
        //pacman_closed();
        transfer_frame(pacman_frame_buffer[0], phantom_preset_frames[0]);
        temp_sleep(game_speed);
        //pacman_open2();
        transfer_frame(pacman_frame_buffer[0], phantom_preset_frames[0]);
        temp_sleep(game_speed);
        temp_sleep(game_speed);
    }
}

char input;

void get_input()
{
    char key;
    while (true)
    {
        key = _getch();
        switch (key)
        {
        case'W':
        case'w':
            input = 'w';
            break;
        case'S':
        case's':
            input = 's';
            break;
        case'A':
        case'a':
            input = 'a';
            break;
        case'D':
        case'd':
            input = 'd';
            break;
        }
    }
}

#include <iostream>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    auto fi = std::async(std::launch::async, pacman_anim);
    auto fj = std::async(std::launch::async, get_input);

    console_setup();

    build_map_from_half(half_map_preset,pieces,map);

    build_map_from_half(navmap_half, nav_pieces, navmap);

    //debug_display(navmap);
    
    display();

    //refresh_display_lines(0, 90);

    /*
    display_sprite(phantom_preset_frames[0], 17, 17 );
    display_sprite(phantom_preset_frames[0], 17, 34);
    display_sprite(phantom_preset_frames[0], 17, 51);
    display_sprite(phantom_preset_frames[0], 17, 68);
    display_sprite(phantom_preset_frames[0], 34, 17);
    display_sprite(phantom_preset_frames[0], 51, 17);
    display_sprite(phantom_preset_frames[0], 68, 17);
    temp_sleep(100);
    display_sprite(phantom_preset_frames[0], 34, 51 );
    temp_sleep(100);
    display_sprite(phantom_preset_frames[0], 51, 51 );
    temp_sleep(100);
    display_sprite(phantom_preset_frames[0], 68, 51 );
    //*/
    ///*
    while (true)
    {
        switch (input)
        {
        case'w':
            move_pacman(false, false, true);
            break;
        case's':
            move_pacman(false, true);
            break;
        case'a':
            move_pacman();
            break;
        case'd':
            move_pacman(false, false, false, true);
            break;
        }
    }//*/

    return 0;
}
