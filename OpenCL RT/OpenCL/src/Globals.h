#pragma once

#include <array>

const int Current_Scene = 6;

// IMAGE
constexpr double aspect_ratio = 16.0 / 9.0;
//constexpr int image_width = 1920;
constexpr int image_width = 400;

//Cornell box
//constexpr double aspect_ratio = 1.0;
//constexpr int image_width = 100; // 400 600 800

constexpr int image_height = static_cast<int>(image_width / aspect_ratio);

const int max_depth = 50;
int samples_per_pixel = 100;

// RENDER
std::array<unsigned char, image_height* image_width * 4> image;
bool PROGRESS_DONE = false;