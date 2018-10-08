#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <map>
#include <string>

#include "SDL_mixer.h"

#include "Constants.h"
#include "Util.h"

class SoundManager
{
public:
	static SoundManager& getInstance();
	static bool initialize();
	static void destroy();
	static bool addSound(std::string name);
	static bool addMusic(std::string name);
	static void playMusic(std::string name);
	static void stopMusic(std::string name);
	static void playSFX(std::string name);
	static void clearSFX();

private:
	SoundManager() {}

	/* Explicitly disallow copying. */
	SoundManager(const SoundManager&);
	SoundManager& operator= (const SoundManager&);

private:
	static std::map<std::string, Mix_Music*> musicObjects;
	static std::map<std::string, Mix_Chunk*> soundEffects;
	static std::string currentlyPlayedtMusicName;
};

#endif // !SOUND_MANAGER_H
