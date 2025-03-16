# Hexxy2D: A Simple 2D Graphics Library

## Overview
Hexxy2D is a user-friendly C++ graphics library designed to transform console-based games into visually appealing graphical applications. It provides a streamlined approach to rendering 2D arrays as windows, making it perfect for creating classic games and educational projects.

![](./0.DEMOS/IMAGES/Conway%20Big.gif)


## 🎮 Featured [Demos](./0.DEMOS/README.md)
- [**Minesweeper**](./0.DEMOS/README.md#minesweeper): A fully functional implementation of the classic puzzle game
- [**Conway's Game of Life**](./0.DEMOS//README.md#conway): Interactive simulation of cellular automata
- [**Rubik's Cube Visualizer**](./0.DEMOS/README.md#rubiks): 2D representation of a Rubik's cube solver
- [**Paint Clone**](./0.DEMOS//README.md#demo1): Simple drawing application demonstrating input handling
- [**Pac-Man (WIP)**](./0.DEMOS/README.md#pac-man): Visual demonstration of the classic arcade game

## ✨ Key Features
- **Simple Array-to-Graphics Conversion**: Easily transform 2D arrays into rendered windows
- **Input Handling**: Comprehensive mouse and keyboard input support
- **Custom Styling**: Flexible color palette system for unique visual designs
- **Audio Support**: Basic sound playback capabilities
- **Font Systems**: Built-in 3x3 and 5x5 pixel font rendering
- **Smart Scaling**: Automatic window scaling for different resolutions
- [**Development Tools**](./0.DEMOS/README.md#devtools): 
  - Built-in profiler
  - Debug mode
  - FPS counter
  - Fixed update callbacks

## 🛠️ Technical Details
### Dependencies
- OpenGL
- GLFW
- GLEW
- GLM
- SFML

### System Requirements
- Windows (primary support)
- Linux support through Proton/Wine

## 📚 Example Usage
```cpp
#include "Hexxy2D_pch.h"

constexpr size_t GridHeight = 528;
constexpr size_t GridWidht = 477;
constexpr size_t NumberOfColors = 5;

int main()
{
    Hexxy::Display display(GridHeight, GridWidht, NumberOfColors);

    display.ColorPalette.SetClearColor(0, 255, 255);

    display.ColorPalette.set(0, 255, 255, 255);
    display.ColorPalette.set(1, 255, 0, 255, 0.5f);
    display.ColorPalette.set(2, 0, 255, 0);

    display.UpdateColors();

    for(int j = 0; j < GridHeight; j++)
        for(int i = 0; i < GridWidht - 100; i++)
            display.Buffer[j][i] = 1;

    display.PrintColorPalette();

    while (!display.WindowShouldClose())
    {
        display.Draw();
    }

    return 0;
}
```

## 🔗 Additional Resources
- [Original console games collection](https://github.com/Hexxy-Dev/Old_Code/tree/main/Console_Games)