#pragma once

#include "Settings.h"

/// <summary>
/// <para>Audio namespace provides functions for easy async audio flie loading and playing</para>
/// </summary>
namespace Audio
{
    /// <summary>
    /// This function is used internally to initialize necesssary things but can be used to restart sound if you
    /// called the StopSound() function
    /// </summary>
    void init();

    /// <summary>
    /// This function plays .wav files
    /// </summary>
    /// <param name="fileName"></param>
    void PlaySoundWav(const char* fileName);

    /// <summary>
    /// This function can play .ogg and .flac files
    /// </summary>
    /// <param name="fileName"></param>
    void PlayMusic(const char* fileName);

    /// <summary>
    /// Stops all sounds and prevents more from being played
    /// </summary>
    void StopSound();
}

