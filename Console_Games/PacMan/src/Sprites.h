#pragma once

#include "Globals.h"

// For non symetrical maps (custom maps?)
extern int map_preset[map_i][map_j];

// For maps that are symetrical on the vertical line
extern int half_map_preset[map_i][(map_j / 2)];

// Piece normal orientation is right
extern int pieces[11][sprite_rez][sprite_rez];

extern int navmap_half[map_i][map_j / 2];

extern int nav_pieces[10][sprite_rez][sprite_rez];

extern int pacman_frames[4][sprite_rez][sprite_rez];

extern int phantom_preset_frames[5][sprite_rez][sprite_rez];