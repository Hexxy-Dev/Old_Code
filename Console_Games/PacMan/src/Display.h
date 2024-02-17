#pragma once

#include "Globals.h"

void display();

void refresh_display_lines(int start_line, int lines_to_refresh);

void smart_refresh(bool search = false);

void display_sprite(int sprite[sprite_rez][sprite_rez], int sprite_i, int sprite_j);

void debug_display(int full_map[(map_i * sprite_rez)][(map_j * sprite_rez)]);