#pragma once

////// Settings //////

// Map size in rows and columns
const int map_i = 31;
const int map_j = 28;

// Sprite size (square)
const int sprite_rez = 17;

// Spaces from the leftmost part of the screen
// Used for aligning the board and sprites in the middle
const int alignment_spaces = 250;

// Game speed in ms
const int game_speed = 50;  // mabye??? sleep for pacman

////// End of Settings //////




////// Global internal variables //////

extern int map[(map_i * sprite_rez)][(map_j * sprite_rez)];

extern int pacman_frame_buffer[2][sprite_rez][sprite_rez];

extern int red_ghost_frame_buffer[2][sprite_rez][sprite_rez];
extern int pink_ghost_frame_buffer[2][sprite_rez][sprite_rez];
extern int cyan_ghost_frame_buffer[2][sprite_rez][sprite_rez];
extern int orange_ghost_frame_buffer[2][sprite_rez][sprite_rez];

extern int navmap[(map_i * sprite_rez)][(map_j * sprite_rez)];