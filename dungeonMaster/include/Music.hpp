#pragma once

#include <SDL/SDL_mixer.h>
#include "glimac/FilePath.hpp"
#include <unordered_map>

class Music
{
private:
    static constexpr int VOLUME        = 20;
    static constexpr int MUSIC_CHANNEL = 1;

    static constexpr const char *MUSIC_DIRECTORY = "/assets/musics";

    static constexpr const char *MUSIC_MENU_STARTING = "/menuStarting_TP.mp3";
    static constexpr const char *MUSIC_IN_GAME       = "/inGame_lavenderTown.mp3";
    static constexpr const char *MUSIC_WIN           = "/menuWin_SSBU.mp3";
    static constexpr const char *MUSIC_LOSE          = "/menuLose_TP.mp3";

    static constexpr const char *SOUND_START_GAME = "/startGame_TP.wav";
    static constexpr const char *SOUND_SUCCESS    = "/success_WW.wav";

    static constexpr const char *SOUND_FAIRY         = "/fairy.wav";
    static constexpr const char *SOUND_BOTTLE        = "/bottle.wav";
    static constexpr const char *SOUND_CHANGE_WEAPON = "/changeWeapon.wav";

    static constexpr const char *SOUND_PLAYER_HIT_01 = "/playerHit_01.wav";
    static constexpr const char *SOUND_PLAYER_HIT_02 = "/playerHit_02.wav";
    static constexpr const char *SOUND_PLAYER_HIT_03 = "/playerHit_03.wav";
    static constexpr const char *SOUND_PLAYER_HIT_04 = "/playerHit_04.wav";
    int                         _playerHitSoundIndex = 0;

    static constexpr const char *SOUND_PLAYER_HURT_01         = "/playerHurt_01.wav";
    static constexpr const char *SOUND_PLAYER_HURT_02         = "/playerHurt_02.wav";
    static constexpr const char *SOUND_PLAYER_HURT_03         = "/playerHurt_03.wav";
    static constexpr const char *SOUND_PLAYER_HURT_04         = "/playerHurt_04.wav";
    int                         _playerHurtSoundIndex         = 0;

    std::unordered_map<std::string, Mix_Music *> _musics;
    std::unordered_map<std::string, Mix_Chunk *> _sounds;
    int                                          _volumeMusic = (MIX_MAX_VOLUME * VOLUME) / 100;
    int                                          _volumeSound = (MIX_MAX_VOLUME * VOLUME * 3) / 100;

    const std::string _musicDirectory;

    bool _musicIsWorking = true;


    void loadMusic(const std::string &fileName);

    void loadSound(const std::string &fileName);

    void setMusicNotWorking();

public:
    explicit Music(const glimac::FilePath &applicationPath);

    ~Music() = default;

    bool initMusic();

    void playMenuMusic();

    void playInGameMusic();

    void playWinMusic();

    void playLoseMusic();

    void playSoundSuccess();

    void freeMusics();

    void playSoundStartGame();

    void playPlayerHit();

    void playFairy();

    void playBottle();

    void changeWeapon();

    void playPlayerHurt();
};