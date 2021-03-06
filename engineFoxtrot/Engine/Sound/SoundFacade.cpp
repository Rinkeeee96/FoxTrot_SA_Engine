#include "stdafx.h"
#include "SoundFacade.h"


#include <SDL.h>
#include <SDL_mixer.h>
#undef main

/// @brief 
SoundFacade::SoundFacade()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    //Initialize SDL_mixer
    if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, AUDIO_CHANNEL_AMOUNT, AUDIO_CHUNK_SIZE) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

/// @brief 
// TODO no sound memory is freed
SoundFacade::~SoundFacade()
{
	flush();
    /*SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);*/
}

/// @brief returns if a song is playing
/// @return 
bool SoundFacade::isMix_PlayingMusic()
{
	return Mix_PlayingMusic();
}

/// @brief
/// Replaces the identifier,filepath map
/// @param files
void SoundFacade::setFiles(map<string, string> files)
{
	this->soundPaths = files;
}

/// @brief 
/// Adds a file to the files map
/// @param identifier 
/// The identifier to link the file to
/// @param file
/// The file path to the music/effect
void SoundFacade::addFile(const string& identifier, const string& file) {
	this->soundPaths[identifier] = file;
}

/// @brief 
/// Flushes the audio buffers
void SoundFacade::flush()
{
	for (auto it = loadedSoundEffects.begin(); it != loadedSoundEffects.end(); /* don't increment here*/) {
		it = loadedSoundEffects.erase(it);
	}
	for (auto it = loopChannels.begin(); it != loopChannels.end(); /* don't increment here*/) {
		it = loopChannels.erase(it);
	}
}

/// @brief 
/// Plays the effect that belongs to the given identifier at the given volume
/// @param identifier 
/// The sound identifier saved when the file has been added
/// @param volume
/// The volume to play the effect at. Ranges from 1 to 128. Defaults to 128 if not given
void SoundFacade::playEffect(const string& identifier, const int volume = MIX_MAX_VOLUME) {
	if (soundPaths.find(identifier) != soundPaths.end() && loadedSoundEffects.find(identifier) == loadedSoundEffects.end()) {
		loadEffect(identifier);
	}
	if (loadedSoundEffects.find(identifier) != loadedSoundEffects.end()) {
		int channel = Mix_PlayChannel(FIRST_AVAILABLE_CHANNEL, loadedSoundEffects[identifier], DONT_LOOP);
		Mix_Volume(channel, volume);
	}
	else {
		throw exception("SoundFacade: identifier does not exist");
	}
}

/// @brief 
/// Loads the effect that belongs to the given identifier into the buffer
/// @param identifier 
/// The sound identifier saved when the file has been added
void SoundFacade::loadEffect(const string& identifier) {
	if (loadedSoundEffects.find(identifier) == loadedSoundEffects.end()) {
		loadedSoundEffects[identifier] = Mix_LoadWAV(soundPaths.at(identifier).c_str());
		if (!loadedSoundEffects[identifier]) {
			std::cerr << "Mix_LoadWAV Error: " << Mix_GetError() << std::endl;
		}
	}
	else {
		throw exception("SoundFacade: cannot load effect");
	}
}

/// @brief 
/// Unloads the effect that belongs to the given identifier from the buffer
/// @param identifier 
/// The sound identifier saved when the file has been added
void SoundFacade::unloadEffect(const string& identifier) {
	if (loadedSoundEffects.find(identifier) == loadedSoundEffects.end()) {
		throw exception("SoundFacade: identifier does not exist");
	}
	stopLoopedEffect(identifier);
	loadedSoundEffects.erase(identifier);
	loopChannels.erase(identifier);
}

/// @brief 
/// Indefinitely plays a loaded effect that belongs to the given identifier
/// @param identifier 
/// The sound identifier saved when the file has been added
void SoundFacade::startLoopedEffect(const string& identifier, const int volume) {
	if (loadedSoundEffects.find(identifier) != loadedSoundEffects.end()) {
		int channel = Mix_PlayChannel(FIRST_AVAILABLE_CHANNEL, loadedSoundEffects[identifier], LOOP_INDEFINITELY);
		Mix_Volume(channel, volume);
		loopChannels.insert(pair<string, int>(identifier, channel));
	}
	else {
		throw exception("SoundFacade: identifier does not exist");
	}
}

/// @brief 
/// Stops a looped effect
/// @param identifier 
/// The sound identifier saved when the file has been added
void SoundFacade::stopLoopedEffect(const string& identifier) {
	if (loopChannels.find(identifier) != loopChannels.end()) {
		Mix_HaltChannel(loopChannels[identifier]);
		loopChannels.erase(identifier);
	}
	else {
		throw exception("SoundFacade: identifier does not exist");
	}
}

/// @brief 
/// Loads the music that belongs to the given identifier into the buffer
/// @param identifier 
/// The sound identifier saved when the file has been added
void SoundFacade::loadMusic(const string& identifier) {
	if (music) {
		Mix_FreeMusic(music);
	}

	/// TODO add fade between music
	if (soundPaths.find(identifier) != soundPaths.end())
	{
		music = Mix_LoadMUS(soundPaths[identifier].c_str());
		if (!music) {
			std::cerr << "Mix_LoadMUS Error: " << Mix_GetError() << std::endl;
		}
	}
	else {
		throw exception("SoundFacade: identifier does not exist");
	}
}

/// @brief 
/// Plays the currently loaded music at the given volume
/// @param volume 
/// The volume to play the music at. Ranges from 0 to 128. Defaults to 128 if not given
void SoundFacade::playMusic(const int volume = MIX_MAX_VOLUME) {
	if (music != NULL) {
		Mix_VolumeMusic(volume);
		Mix_PlayMusic(music, LOOP_INDEFINITELY);
	}
	else {
		throw exception("SoundFacade: identifier does not exist");
	}
}

/// @brief 
/// Loads and plays music that belongs to the given identifier at the given volume
/// @param identifier 
/// The sound identifier saved when the file has been added
/// @param volume
/// The volume to play the music at. Ranges from 0 to 128. Defaults to 128 if not given
void SoundFacade::playMusic(const string& identifier, const int volume = MIX_MAX_VOLUME) {
	if (soundPaths.find(identifier) != soundPaths.end()) {
		loadMusic(identifier);
		Mix_VolumeMusic(volume);
		Mix_PlayMusic(music, LOOP_INDEFINITELY);
	}
	else {
		throw exception("SoundFacade: identifier does not exist");
	}
}

/// @brief 
/// Stops the currently playing music and swaps it with the music that belongs to the given identifier
/// @param identifier 
/// The sound identifier saved when the file has been added
void SoundFacade::changeMusic(const string& identifier) {
	stopMusic();
	loadMusic(identifier);
}

/// @brief 
/// Fades out the currently playing music over the given time
/// @param fadeTime 
/// The amount of time it takes for the music to fade in ms
void SoundFacade::fadeOutMusic(const int fadeTime) {
	if (fadeTime < 0) {
		throw exception("SoundFacade: invalid fade time");
	}
	Mix_FadeOutMusic(fadeTime);
}

/// @brief 
/// Fades in the currently playing music over the given time
/// @param fadeTime 
/// The amount of time it takes for the music to fade in ms
void SoundFacade::fadeInMusic(const int fadeTime) {
	if (music == NULL) {
		throw exception("SoundFacade: sound does not exist");
	}
	if (fadeTime < 0) {
		throw exception("SoundFacade: invalid fade time");
	}
	rewindMusic();
	Mix_FadeInMusic(music, LOOP_INDEFINITELY, fadeTime);
}

/// @brief 
/// Fades in the music that belongs to the given identifier over [fadeTime]ms
/// @param identifier
/// The sound identifier saved when the file has been added
/// @param fadeTime 
/// The amount of time it takes for the music to fade in ms
void SoundFacade::fadeInMusic(const string& identifier, const int fadeTime) {
	if (music == NULL) {
		throw exception("SoundFacade: identifier does not exist");
	}
	if (fadeTime < 0) {
		throw exception("SoundFacade: Invalid fade time");
	}
	stopMusic();
	loadMusic(identifier);
	Mix_FadeInMusic(music, LOOP_INDEFINITELY, fadeTime);
}

/// @brief 
/// Rewinds the currently playing music
void SoundFacade::rewindMusic() {
	Mix_RewindMusic();
}

/// @brief 
/// Stops the currently playing music
void SoundFacade::stopMusic() {
	Mix_PauseMusic();
}

/// @brief 
/// Pauses the currently playing music
void SoundFacade::pauseMusic() {
	Mix_PauseMusic();
}

/// @brief 
/// Resumes the currently playing music
void SoundFacade::resumeMusic() {
	Mix_ResumeMusic();
}

/// @brief
/// Checks whether the given identifier exists in the list of sounds
/// @param identifier
/// The identifer to check for
bool SoundFacade::identifierExists(const string& identifier) {
	if (soundPaths.find(identifier) != soundPaths.end()) {
		return true;
	}
	throw exception("SoundFacade: identifier does not exist");
}

/// @brief
/// Checks whether the given identifier has a sound loaded in a stream
/// @param identifier
/// The identifier to check for
bool SoundFacade::identifierIsLoaded(const string& identifier) {
	return (loadedSoundEffects.find(identifier) != loadedSoundEffects.end());
}