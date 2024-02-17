#pragma once

#include "Globals.h"

// build custom map
void build_map_from_full();

// build map that is symetrical with the vertical line
void build_map_from_half(int half_map[map_i][(map_j / 2)], int sprites[20][sprite_rez][sprite_rez], int full_map[(map_i * sprite_rez)][(map_j * sprite_rez)]);