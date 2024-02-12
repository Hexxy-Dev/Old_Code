#include "Globals.h"


////// Global internal variables //////
int pacman_frame_buffer[sprite_rez][sprite_rez];

Hexxy::Data::array2D navmap(map_i * sprite_rez, map_j * sprite_rez);
Hexxy::Data::array2D map(map_i* sprite_rez, map_j* sprite_rez);

int red_ghost_frame_buffer[2][sprite_rez][sprite_rez];
int pink_ghost_frame_buffer[2][sprite_rez][sprite_rez];
int cyan_ghost_frame_buffer[2][sprite_rez][sprite_rez];
int orange_ghost_frame_buffer[2][sprite_rez][sprite_rez];