#pragma once

#include "SFML/Audio.hpp"
#pragma once

#include <iostream>
#include <string>
#include <future>
#include <array>
#include <atomic>

std::atomic_bool STOP_ALL = false;

// Play music from an wav file
void playSound(const std::string& filename)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(Settings_Audio_Path + filename))
        return;
    sf::Sound sound(buffer);
    sound.play();

    //sf::sleep(sf::milliseconds(buffer.getDuration().asMilliseconds()));

    while (sound.getStatus() == sf::Sound::Playing)
    {
        if (STOP_ALL)
        {
            sound.stop();
            return;
        }
        sf::sleep(sf::milliseconds(100));
    }
        
    return;
}

// Play music from an ogg file
// Play music from a flac file
void playMusic(const std::string& filename)
{
    sf::Music music;
    if (!music.openFromFile(Settings_Audio_Path + filename))
        return;

    music.play();

    //sf::sleep(sf::milliseconds(music.getDuration().asMilliseconds()));

    while (music.getStatus() == sf::Music::Playing)
    {
        if (STOP_ALL)
        {
            music.stop();
            return;
        }
        sf::sleep(sf::milliseconds(100));
    }
    return;
}

std::array<std::future<void>, Settings_Number_Of_Audio_Tracks> tracks;

void Nothing() { return; };

namespace Audio
{
    void init()
    {
        STOP_ALL = false;

        for (uint8_t i = 0; i < Settings_Number_Of_Audio_Tracks; i++)
            tracks[i] = std::async(std::launch::async, Nothing);
    }

    void PlaySoundWav(const char* fileName)
    {
        for(uint8_t i = 0; i < Settings_Number_Of_Audio_Tracks; i++)
            if (tracks[i]._Is_ready())
            {
                tracks[i] = std::async(std::launch::async, playSound, fileName);
                return;
            }
        std::cout << "No free tracks found!!!\n";    
    }

    void PlayMusic(const char* fileName)
    {
        for (uint8_t i = 0; i < Settings_Number_Of_Audio_Tracks; i++)
            if (tracks[i]._Is_ready())
            {
                tracks[i] = std::async(std::launch::async, playMusic, fileName);
                return;
            }
        std::cout << "No free tracks found!!!\n";
    }

    void StopSound()
    {
        STOP_ALL = true;
        std::cout << "SoundStopped!!!\n";
    }
}

