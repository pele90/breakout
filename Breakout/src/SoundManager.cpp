#include "SoundManager.h"

SoundManager& SoundManager::getInstance()
{
	static SoundManager instance;
	return instance;
}

bool SoundManager::initialize()
{
	//Initialize SDL_mixer 
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) 
	{
		Util::showMessageBox("SDL_mixer could not initialize!");
		return false;
	}

	return true;
}

void SoundManager::destroy()
{
	for (auto mo : musicObjects)
	{
		Mix_FreeMusic(mo.second);
		mo.second = nullptr;
	}

	for (auto soundEffect : soundEffects)
	{
		Mix_FreeChunk(soundEffect.second);
		soundEffect.second = nullptr;
	}

	Mix_Quit();
}

bool SoundManager::addSound(std::string name)
{
	if (soundEffects.find(name) == soundEffects.end()) 
	{
		std::string filename = DEFAULT_SOUND_PATH;
		filename.append(name).append(".wav");
		Mix_Chunk* chunk = Mix_LoadWAV(filename.c_str());
		if (chunk == NULL)
		{
			Util::showMessageBox("Could not load WAV file: " + name);
			return false;
		}

		soundEffects[name] = chunk;
	}

	return true;
}

bool SoundManager::addMusic(std::string name)
{
	if (musicObjects.find(name) == musicObjects.end())
	{
		std::string filename = DEFAULT_SOUND_PATH;
		filename.append(name).append(".wav");
		Mix_Music* music = Mix_LoadMUS(filename.c_str());
		if (music == NULL)
		{
			Util::showMessageBox("Could not load WAV file: " + name);
			return false;
		}

		musicObjects[name] = music;
	}

	return true;
}

void SoundManager::playMusic(std::string name)
{
	std::map<std::string, Mix_Music*>::iterator it = musicObjects.find(name);

	if (currentlyPlayedtMusicName != name)
	{
		
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic((*it).second, -1);
		}
		else
		{
			Mix_HaltMusic();
			Mix_PlayMusic((*it).second, -1);
		}

		currentlyPlayedtMusicName = name;
		Mix_VolumeMusic(MIX_MAX_VOLUME * MUSIC_VOLUME_MODIFIER);
	}
}

void SoundManager::stopMusic(std::string name)
{
	if (Mix_PlayingMusic() == 1)
	{
		Mix_HaltMusic();
	}
}

void SoundManager::playSFX(std::string name)
{
	std::map<std::string, Mix_Chunk*>::iterator it = soundEffects.find(name);
	Mix_PlayChannel(-1, (*it).second, 0);
}

void SoundManager::clearSFX()
{
	for (auto soundEffect : soundEffects)
	{
		Mix_FreeChunk(soundEffect.second);
		soundEffect.second = nullptr;
	}

	soundEffects.clear();
}

// A quirk of C++, static member variables need to be instantiated outside of the class
std::map<std::string, Mix_Music*> SoundManager::musicObjects;
std::map<std::string, Mix_Chunk*> SoundManager::soundEffects;
std::string SoundManager::currentlyPlayedtMusicName;