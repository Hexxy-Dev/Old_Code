#include "Display.h"

#include "Globals.h"
#include "string"
#include "Console stuff.h"

#include <iostream>

using std::cout;

//
// DRAW ORDER:
// map
// vulnerable ghost
// pacman
// ghost
// ghost eyes
//

//
// debug "core" is 777
// 
// vulnerable ghost codes are:  221(red) 222(pink) 223(cyan) 224(orange)
// pacman core  codes are:  111    112
// ghost codes are : 331(red) 332(pink) 333(cyan) 334(orange)
// ghost eyes codes are : 441(red) 442(pink) 443(cyan) 444(orange)
//


// pacman body is 1
// general sprite 11
// wall is 55
// food is 77

void output_select(int i, int j, std::string * output)
{
    switch (map[i][j])
    {
    case 1:                    // pacman
    case 111:
    case 777:
        *output += "\330[103m  ";
        break;
    case 55:
        *output += "\33[104m  ";
        break;
    case 77:
        *output += "\33[102m  ";
        break;
    default:
        *output += "\33[40m  ";
        break;
    }
}


void debug_display(int full_map[(map_i * sprite_rez)][(map_j * sprite_rez)])
{
    for (int i = 0; i < map_i * sprite_rez; i++) {
        for (int j = 0; j < map_j * sprite_rez; j++) {
            if (full_map[i][j] != 0)
                cout << "\33[104m  ";
            else
                cout << "\33[40m  ";
        }
        cout << "\33[40m  \n";
    }
}

void display()
{
    std::string output = ".";
    for (int i = 0; i < 40; i++) // can be optimised
        output += "\n";

    for (int i = 0; i < map_i * sprite_rez; i++) {
        for (int j = 0; j < alignment_spaces; j++)
            output += " ";

        for (int j = 0; j < map_j * sprite_rez; j++) {
            output_select(i, j, &output);
        }
        output += "\33[40m \n";
        cout << output;
        output = "";
    }
    output = ".";
    for (int i = 0; i < 35; i++) // can be optimised
        output += "\n";
    cout << output;
}

void multi_thread_display(int i)
{
    std::string output = "";

    for (int j = 0; j < alignment_spaces; j++)
        output += " ";

    for (int j = 0; j < map_j * sprite_rez; j++) {
        output_select(i, j, &output);
    }
    output += "\33[40m \n";
    cout << output;
}

#include <future>

void refresh_display_lines(int start_line, int lines_to_refresh = 7)
{
    //std::string output = "";

    set_cursor_poz(start_line + 40, 0);

    for (int i = start_line; i < start_line + lines_to_refresh; i++) {
        /*for (int j = 0; j < alignment_spaces; j++)
            output += " ";

        for (int j = 0; j < map_j * sprite_rez; j++) {
            output_select(i, j, &output);
        }
        output += "\33[40m \n";
        cout << output;
        output = "";//*/
        std::async(std::launch::async, multi_thread_display, i);
    }
}

// clamp value between 0 and map_i
int clamp(int a)
{
    return (a < 0) ? 0 : (a > map_i * sprite_rez - 1) ? map_i * sprite_rez - 1 : a;
}

void check_lines_to_be_updated(int lines_to_update[])
{
    for (int i = 0; i < map_i * sprite_rez; i++)
    {
        for (int j = 0; j < map_j * sprite_rez; j++)
        {
            switch (map[i][j])
            {
            case 778:
            case 777:
                for(int k = 0 - sprite_rez / 2 - 2; k < sprite_rez / 2 + 3; k++)
                    lines_to_update[clamp((i + k))] = 1;
                break;
            }
        }
    }
}

void smart_refresh(bool search)
{
    int lines_to_update[map_i * sprite_rez] = { 0 };

    if(search)
        check_lines_to_be_updated(lines_to_update);  
    //  can be done without searching 
    // TODO: store the lines of each "core"

    int last_nr = 0;
    int start = 0, lines = 0;
    bool ok = 0;

    for (int i = 0; i < map_i * sprite_rez; i++)
    {
        if (lines_to_update[i] != last_nr)
        {
            if (ok)
            {
                ok = 0;

                refresh_display_lines(start, lines);

                start = 0;
                lines = 0;
                last_nr = 0;
            }
            else
            {
                last_nr = 1;
                start = i;
                ok = 1;
            }
        }

        if (ok)
        {
            lines++;
        }
    }
}

void display_sprite(int sprite[sprite_rez][sprite_rez], int sprite_i, int sprite_j)
{
    std::string output = "";

    //set_cursor_poz(sprite_i + 40, sprite_j * 2 + alignment_spaces);

    for (int i = 0; i < sprite_rez; i++)
    {
        set_cursor_poz(sprite_i + i + 40, sprite_j * 2 + alignment_spaces);
        output = "";
        
        for (int j = 0; j < sprite_rez; j++) {

            if (sprite[i][j] == 1)
                output += "\33[103m  ";
            else
                output_select(sprite_i + i, sprite_j + j, &output);
        }

       cout << output;
    }
}
