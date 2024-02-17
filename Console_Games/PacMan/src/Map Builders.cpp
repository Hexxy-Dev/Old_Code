#include "Map builders.h"

#include "Globals.h"
#include "Sprites.h"

void normal_orientation(int i, int j, int piece, int sprites[20][sprite_rez][sprite_rez], int full_map[(map_i * sprite_rez)][(map_j * sprite_rez)])
{
    for (int k = 0; k < sprite_rez; k++) {
        for (int y = 0; y < sprite_rez; y++) {
            full_map[i * sprite_rez + k][j * sprite_rez + y] = sprites[piece][k][y];
        }
    }
}

void mirror_on_vertical(int i, int j, int piece, int sprites[20][sprite_rez][sprite_rez], int full_map[(map_i * sprite_rez)][(map_j * sprite_rez)])
{
    for (int k = 0; k < sprite_rez; k++) {
        for (int y = 0; y < sprite_rez; y++) {
            full_map[i * sprite_rez + k][j * sprite_rez + y] = sprites[piece][k][sprite_rez - 1 - y];
        }
    }
}

// normal -> up -> right
void diagonal_right_flip(int i, int j, int piece, int sprites[20][sprite_rez][sprite_rez], int full_map[(map_i * sprite_rez)][(map_j * sprite_rez)])
{
    for (int k = 0; k < sprite_rez; k++) {
        for (int y = 0; y < sprite_rez; y++) {
            full_map[i * sprite_rez + k][j * sprite_rez + y] = sprites[piece][y][k];
        }
    }
}

void rotate_right_90(int i, int j, int piece, int sprites[20][sprite_rez][sprite_rez], int full_map[(map_i * sprite_rez)][(map_j * sprite_rez)])
{
    for (int k = 0; k < sprite_rez; k++) {
        for (int y = 0; y < sprite_rez; y++) {
            full_map[i * sprite_rez + k][j * sprite_rez + y] = sprites[piece][sprite_rez - 1 - y][k];
        }
    }
}

void vertical_flip(int i, int j, int piece, int sprites[20][sprite_rez][sprite_rez], int full_map[(map_i * sprite_rez)][(map_j * sprite_rez)])
{
    for (int k = sprite_rez - 1; k >= 0; k--) {
        for (int y = 0; y < sprite_rez; y++) {
            full_map[i * sprite_rez + k][j * sprite_rez + y] = sprites[piece][sprite_rez - 1 - k][y];
        }
    }
}

// normal -> up -> left
void diagonal_left_flip(int i, int j, int piece, int sprites[20][sprite_rez][sprite_rez], int full_map[(map_i * sprite_rez)][(map_j * sprite_rez)])
{
    for (int k = sprite_rez; k >= 0; k--) {
        for (int y = 0; y < sprite_rez; y++) {
            full_map[i * sprite_rez + k][j * sprite_rez + y] = sprites[piece][sprite_rez - 1 - k][sprite_rez - 1 - y];
        }
    }
}

void place_piece(int i, int j, int orientation, int piece, int sprites[20][sprite_rez][sprite_rez], int full_map[(map_i * sprite_rez)][(map_j * sprite_rez)])
{
    switch (orientation) {
    case 0:
    case 1:
        normal_orientation(i, j, piece, sprites, full_map);
        break;
    case 2:
        mirror_on_vertical(i, j, piece, sprites, full_map);
        break;
    case 3:
        diagonal_right_flip(i, j, piece, sprites, full_map);
        break;
    case 4:
        rotate_right_90(i, j, piece, sprites, full_map);
        break;
    case 5:
        vertical_flip(i, j, piece, sprites, full_map);
        break;
    case 6:
        diagonal_left_flip(i, j, piece, sprites, full_map);
        break;
    default:
        throw "orientation not found";
        break;
    }
}

void mirror_map_vertical(int full_map[(map_i * sprite_rez)][(map_j * sprite_rez)])
{
    for (int i = 0; i < map_i * sprite_rez; i++) {
        for (int j = 0; j < (map_j / 2) * sprite_rez; j++) {
            full_map[i][(map_j / 2) * sprite_rez + j] = full_map[i][(map_j / 2) * sprite_rez - j - 1];
        }
    }
}

// NEEDS TO BE FIXTED         IS DEPRECATED
void build_map_from_full()
{
    int orientation = 1, piece = 0;
    int mi = 0, mj = 0;

    for (int i = 0; i < map_i; i++) {
        for (int j = 0; j < map_j; j++) {
            orientation = 1;
            orientation = map_preset[i][j] / 10;
            piece = map_preset[i][j] % 10;

            //place_piece(i, j, orientation, piece);
        }
    }
}


void build_map_from_half(int half_map[map_i][(map_j / 2)], int sprites[20][sprite_rez][sprite_rez], int full_map[(map_i * sprite_rez)][(map_j * sprite_rez)])
{
    int orientation = 1, piece = 0;
    int mi = 0, mj = 0;

    for (int i = 0; i < map_i; i++) {
        for (int j = 0; j < map_j / 2; j++) {
            orientation = 1;
            orientation = half_map[i][j] / 10;
            piece = half_map[i][j] % 10;

            place_piece(i, j, orientation, piece, sprites, full_map);
        }
    }

    mirror_map_vertical(full_map);
}