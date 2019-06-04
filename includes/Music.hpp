#ifndef AIRHOCKEY_MUSIC_HPP
#define AIRHOCKEY_MUSIC_HPP

#include "headers.hpp"

#define SOUND_KICK_PATH "sounds/kick.wav"
#define MUSIC_PATH "sounds/music1.wav"
#define SOUND_GOAL_PATH "sounds/goal-2.wav"



class Music
{
public:
	Music();
	~Music();
	Music &operator=(const Music &other);
	Music(const Music &other);

	void	play_music();
	void	play_sound(eSound sound_name);

private:
	Mix_Music					*music_;
	std::vector<Mix_Chunk*>		sound_;
};


#endif //AIRHOCKEY_MUSIC_HPP
