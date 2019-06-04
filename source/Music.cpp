#include "Music.hpp"

Music::Music() : music_(), sound_()
{}

Music::~Music()
{
    if (music_)
        Mix_FreeMusic(music_);
    if (!sound_.empty() && sound_[KICK])
        Mix_FreeChunk(sound_[KICK]);
    if (sound_.size() > 1 && sound_[GOAL])
        Mix_FreeChunk(sound_[GOAL]);
    Mix_Quit();
}

Music& Music::operator=(const Music &other)
{
    if (this != &other)
    {
        this->music_ = other.music_;
        this->sound_ = other.sound_;
    }
    return *this;
}

Music::Music(const Music &other)
{
    *this = other;
}

void  Music::play_music()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        throw SdlErr("SDL_mixer could not initialize! SDL_mixer Error: ");
    //Load music
    music_ = Mix_LoadMUS(MUSIC_PATH);
    if (music_ == nullptr)
        throw SdlErr("Failed to load beat music! SDL_mixer Error: ");
    //Load sound effects
    sound_.push_back(Mix_LoadWAV(SOUND_KICK_PATH));
    if (sound_[KICK] == nullptr)
        throw SdlErr("Failed to kick sound effect! SDL_mixer Error: ");
    Mix_VolumeChunk(sound_[KICK], MIX_MAX_VOLUME / 3);
    sound_.push_back(Mix_LoadWAV(SOUND_GOAL_PATH));
    if (sound_[GOAL] == nullptr )
        throw SdlErr("Failed to kick sound effect! SDL_mixer Error: ");
    Mix_VolumeChunk(sound_[GOAL], MIX_MAX_VOLUME / 4);
    Mix_PlayMusic(music_, -1);
}

void Music::play_sound(eSound sound_name)
{
    Mix_PlayChannel(-1, sound_[sound_name], 0);
}

