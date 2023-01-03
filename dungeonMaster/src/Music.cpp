#include "../include/Music.hpp"
#include <iostream>
#include <SDL.h>

Music::Music(const glimac::FilePath &applicationPath)
        : _musicDirectory(applicationPath.dirPath() + MUSIC_DIRECTORY) {}

void Music::setMusicNotWorking()
{
    std::cout << Mix_GetError() << std::endl;
    _musicIsWorking = false;
}

bool Music::initMusic()
{
    Mix_Init(MIX_INIT_MP3);
    SDL_Init(SDL_INIT_AUDIO);

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        setMusicNotWorking();
    }

    Mix_AllocateChannels(16);

    loadMusic(MUSIC_MENU_STARTING);
    loadMusic(MUSIC_IN_GAME);
    loadMusic(MUSIC_WIN);
    loadMusic(MUSIC_LOSE);

    loadSound(SOUND_START_GAME);
    loadSound(SOUND_SUCCESS);
    loadSound(SOUND_FAIRY);
    loadSound(SOUND_BOTTLE);
    loadSound(SOUND_CHANGE_WEAPON);

    loadSound(SOUND_PLAYER_HIT_01);
    loadSound(SOUND_PLAYER_HIT_02);
    loadSound(SOUND_PLAYER_HIT_03);
    loadSound(SOUND_PLAYER_HIT_04);

    loadSound(SOUND_PLAYER_HURT_01);
    loadSound(SOUND_PLAYER_HURT_02);
    loadSound(SOUND_PLAYER_HURT_03);
    loadSound(SOUND_PLAYER_HURT_04);

    return _musicIsWorking;
}

void Music::freeMusics()
{
    for (auto &music: _musics)
    {
        Mix_FreeMusic(music.second);
    }

    for (auto &sound: _sounds)
    {
        Mix_FreeChunk(sound.second);
    }

    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

void Music::loadMusic(const std::string &fileName)
{
    if (_musicIsWorking)
    {
        Mix_Music *music = Mix_LoadMUS((_musicDirectory + fileName).c_str());
        if (music == nullptr)
        {
            setMusicNotWorking();
        }

        _musics.emplace(fileName, music);
    }

}

void Music::loadSound(const std::string &fileName)
{
    if (_musicIsWorking)
    {
        Mix_Chunk *music = Mix_LoadWAV((_musicDirectory + fileName).c_str());
        if (music == nullptr)
        {
            setMusicNotWorking();
        }

        _sounds.emplace(fileName, music);
    }
}

void Music::playMenuMusic()
{
    Mix_HaltChannel(MUSIC_CHANNEL);
    Mix_Volume(MUSIC_CHANNEL, _volumeMusic);
    Mix_PlayMusic(_musics.at(MUSIC_MENU_STARTING), -1);
}

void Music::playInGameMusic()
{
    Mix_HaltChannel(MUSIC_CHANNEL);
    Mix_Volume(MUSIC_CHANNEL, _volumeMusic / 2);
    Mix_PlayMusic(_musics.at(MUSIC_IN_GAME), -1);
}

void Music::playWinMusic()
{
    Mix_HaltChannel(MUSIC_CHANNEL);
    Mix_Volume(MUSIC_CHANNEL, _volumeMusic);
    Mix_PlayMusic(_musics.at(MUSIC_WIN), 1);
}

void Music::playLoseMusic()
{
    Mix_HaltChannel(1);
    Mix_Volume(1, _volumeMusic);
    Mix_PlayMusic(_musics.at(MUSIC_LOSE), 1);
}

void Music::playSoundStartGame()
{
    Mix_Volume(2, _volumeSound);
    Mix_PlayChannel(2, _sounds.at(SOUND_START_GAME), 0);
}

void Music::playSoundSuccess()
{
    Mix_Volume(3, _volumeSound);
    Mix_PlayChannel(3, _sounds.at(SOUND_SUCCESS), 0);
}

void Music::playPlayerHit()
{
    if (_playerHitSoundIndex == 4)
    {
        _playerHitSoundIndex = 0;
    }

    if (_playerHitSoundIndex % 4 == 0)
    {
        Mix_Volume(4, _volumeSound * 2);
        Mix_PlayChannel(4, _sounds.at(SOUND_PLAYER_HIT_01), 0);
    }

    else if (_playerHitSoundIndex % 4 == 1)
    {
        Mix_Volume(4, _volumeSound * 2);
        Mix_PlayChannel(4, _sounds.at(SOUND_PLAYER_HIT_02), 0);
    }

    else if (_playerHitSoundIndex % 4 == 2)
    {
        Mix_Volume(4, _volumeSound * 2);
        Mix_PlayChannel(4, _sounds.at(SOUND_PLAYER_HIT_03), 0);
    }

    else if (_playerHitSoundIndex % 4 == 3)
    {
        Mix_Volume(4, _volumeSound * 2);
        Mix_PlayChannel(4, _sounds.at(SOUND_PLAYER_HIT_04), 0);
    }

    _playerHitSoundIndex++;
}

void Music::playPlayerHurt()
{
    if (_playerHurtSoundIndex == 4)
    {
        _playerHurtSoundIndex = 0;
    }

    if (_playerHurtSoundIndex % 4 == 0)
    {
        Mix_Volume(5, _volumeSound * 2);
        Mix_PlayChannel(5, _sounds.at(SOUND_PLAYER_HURT_01), 0);
    }

    else if (_playerHurtSoundIndex % 4 == 1)
    {
        Mix_Volume(5, _volumeSound * 2);
        Mix_PlayChannel(5, _sounds.at(SOUND_PLAYER_HURT_02), 0);
    }

    else if (_playerHurtSoundIndex % 4 == 2)
    {
        Mix_Volume(5, _volumeSound * 2);
        Mix_PlayChannel(5, _sounds.at(SOUND_PLAYER_HURT_03), 0);
    }

    else if (_playerHurtSoundIndex % 4 == 3)
    {
        Mix_Volume(5, _volumeSound * 2);
        Mix_PlayChannel(5, _sounds.at(SOUND_PLAYER_HURT_04), 0);
    }

    _playerHurtSoundIndex += 1;
}

void Music::playFairy()
{
    Mix_Volume(6, _volumeSound);
    Mix_PlayChannel(6, _sounds.at(SOUND_FAIRY), 0);
}

void Music::playBottle()
{
    Mix_Volume(7, _volumeSound * 2);
    Mix_PlayChannel(7, _sounds.at(SOUND_BOTTLE), 0);
}

void Music::changeWeapon()
{
    Mix_Volume(8, _volumeSound * 2);
    Mix_PlayChannel(8, _sounds.at(SOUND_CHANGE_WEAPON), 0);
}