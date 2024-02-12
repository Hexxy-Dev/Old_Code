#include "Hexxy2D_pch.h"

#include "Globals.h"
#include "Sprites.h"
#include "Animations.h"
#include "Map builders.h"

#include "Console stuff.h"

#include <iostream>

constexpr size_t GridHeight = map_i* sprite_rez;
constexpr size_t GridWidht = map_j* sprite_rez;
constexpr size_t NumberOfColors = 10;

int pacmanX = sprite_rez * 14, pacmanY = sprite_rez * 21;
int pacmannewX = sprite_rez * 14, pacmannewY = sprite_rez * 21;
bool moving = false;

char dir = 'a';

void W()
{
    dir = 'w';
    pacmannewY -= sprite_rez;
}
void A()
{
    dir = 'a';
    pacmannewX -= sprite_rez;
}
void S()
{
    dir = 's';
    pacmannewY += sprite_rez;
}
void D()
{
    dir = 'd';
    pacmannewX += sprite_rez;
}

void move()
{
    moving = false;
    if (pacmanX < pacmannewX)
    {
        pacmanX++;
        moving = true;
    }
    else if (pacmanX > pacmannewX)
    {
        pacmanX--;
        moving = true;
    }
        
    if (pacmanY < pacmannewY)
    {
        pacmanY++;
        moving = true;
    }
    else if(pacmanY > pacmannewY)
    {
        pacmanY--;
        moving = true;
    }
}

int a = 0, b = 1, c = -1;

Hexxy::Display* display;

void rotate_right_90(int sprite[sprite_rez][sprite_rez])
{
    int rotated[sprite_rez][sprite_rez];
    for (int k = 0; k < sprite_rez; k++) {
        for (int y = 0; y < sprite_rez; y++) {
            rotated[k][y] = sprite[sprite_rez - 1 - y][k];
        }
    }
    for (int k = 0; k < sprite_rez; k++) {
        for (int y = 0; y < sprite_rez; y++) {
            sprite[k][y] = rotated[k][y];
        }
    }
}

void On_FixedUpdate()
{
    Hexxy::Fixed_Update_OK = false;

    std::memcpy(display->Buffer.data(), map.data(), map_i * sprite_rez * map_j * sprite_rez);
    if (moving);

    for (int i = 0; i < sprite_rez; i++)
        for (int j = 0; j < sprite_rez; j++)
            pacman_frame_buffer[i][j] = pacman_frames[a][i][j];

    switch (dir)
    {
    case 'w':
        rotate_right_90(pacman_frame_buffer);
        break;
    case 'a':
        break;
    case 's':
        rotate_right_90(pacman_frame_buffer);
        rotate_right_90(pacman_frame_buffer);
        rotate_right_90(pacman_frame_buffer);
        break;
    case 'd':
        rotate_right_90(pacman_frame_buffer);
        rotate_right_90(pacman_frame_buffer);
        break;
    }
   
    move();

    for (int i = 0; i < sprite_rez; i++)
        for (int j = 0; j < sprite_rez; j++)
            display->Buffer[i + pacmanY][j + pacmanX] = (pacman_frame_buffer[i][j]) ? 3 : display->Buffer[i + pacmanY][j + pacmanX];
    
    Hexxy::Fixed_Update_OK = true;

    if (moving)
    {
        c++;
        if (c == 3)
        {
            if (a == 2)
                b = -1;
            if (a == 0)
                b = 1;
            a += b;
            c = -1;
        }
    }
    else
    {
        a = 0;
        b = 1;
        c = -1;
    }
}

int main()
{
    Hexxy::Display display(GridHeight, GridWidht, NumberOfColors);
    ::display = &display;

    //display.ColorPalette.SetClearColor(0, 7, 12);

    display.ColorPalette.set(1, 0, 0, 255);
    display.ColorPalette.set(2, 0, 255, 0);
    display.ColorPalette.set(3, 255, 255, 0);

    display.UpdateColors();

    build_map_from_half(half_map_preset,pieces, map);

    build_map_from_half(navmap_half, nav_pieces, navmap);

    Input::On("W", "PRESS", W);
    Input::On("A", "PRESS", A);
    Input::On("S", "PRESS", S);
    Input::On("D", "PRESS", D);

    Hexxy::Set_Fixed_Update_Function(On_FixedUpdate);

    display.SetOffsets(0, sprite_rez * 30);

    while (!display.WindowShouldClose())
    {
        Hexxy::Wait_Fixed_Update();

        display.Draw();
    }

    return 0;
}
