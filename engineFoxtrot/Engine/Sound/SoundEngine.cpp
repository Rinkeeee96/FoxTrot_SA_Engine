#include "stdafx.h"
#include "SoundEngine.h"

SoundEngine::SoundEngine() {}
SoundEngine::~SoundEngine(){}

/// @brief 
/// @param files 
void SoundEngine::setFiles(map<string, string> files)
{
	soundFacade->setFiles(files);
}
/// @brief 
/// @param identifier 
/// @param file 
void SoundEngine::addFile(const string& identifier, const string& file)
{
	soundFacade->addFile(identifier, file);
}
/// @brief 
/// @param effect 
/// @param volume 
void SoundEngine::playEffect(const string& effect, int volume = MAX_VOLUME)
{
	soundFacade->playEffect(effect, volume);
}
/// @brief 
/// @param identifier 
void SoundEngine::loadEffect(const string& identifier)
{
	soundFacade->loadEffect(identifier);
}
/// @brief 
/// @param identifier 
void SoundEngine::unloadEffect(const string& identifier)
{
	soundFacade->unloadEffect(identifier);
}
/// @brief 
/// @param effect 
void SoundEngine::startLoopedEffect(const string& effect, int volume = MAX_VOLUME)
{
	soundFacade->startLoopedEffect(effect, volume);
}
/// @brief 
/// @param identifier 
void SoundEngine::stopLoopedEffect(const string& identifier)
{
	soundFacade->stopLoopedEffect(identifier);
}
/// @brief 
/// @param identifier 
void SoundEngine::loadMusic(const string& identifier)
{
	soundFacade->loadMusic(identifier);
}
/// @brief 
/// @param volume 
void SoundEngine::playMusic(int volume = MAX_VOLUME)
{
	soundFacade->playMusic(volume);
}
/// @brief 
/// @param identifier 
/// @param volume 
void SoundEngine::playMusic(const string& identifier, int volume = MAX_VOLUME)
{
	soundFacade->playMusic(identifier, volume);
}
/// @brief 
/// @param identifier 
void SoundEngine::changeMusic(const string& identifier)
{
	soundFacade->changeMusic(identifier);
}
/// @brief 
/// @param fadeTime 
void SoundEngine::fadeOutMusic(int fadeTime)
{
	soundFacade->fadeOutMusic(fadeTime);
}
/// @brief 
/// @param fadeTime 
void SoundEngine::fadeInMusic(int fadeTime)
{
	soundFacade->fadeInMusic(fadeTime);
}
/// @brief 
/// @param identifier 
/// @param fadeTime 
void SoundEngine::fadeInMusic(const string& identifier, int fadeTime)
{
	soundFacade->fadeInMusic(identifier, fadeTime);
}
/// @brief 
void SoundEngine::rewindMusic()
{
	soundFacade->rewindMusic();
}
/// @brief 
void SoundEngine::stopMusic()
{
	soundFacade->stopMusic();
}
/// @brief 
void SoundEngine::pauseMusic()
{
	soundFacade->pauseMusic();
}
/// @brief 
void SoundEngine::resumeMusic()
{
	soundFacade->resumeMusic();
}
/// @brief 
void SoundEngine::flush()
{
	soundFacade->flush();
}

/// @brief
/// Event listener for when the music has to be changed
/// @param identifier
/// The identifier of the music to play
/// @param volume
/// The volume to play the music at. Ranges from 0 to 128
void SoundEngine::onChangeBackgroundMusic(const string& identifier, int volume = MAX_VOLUME) {
	if (identifierExists(identifier)) {
		if (soundFacade->isMix_PlayingMusic()) {
			changeMusic(identifier);
		}
		else {
			loadMusic(identifier);
			playMusic(volume);
		}
	}
}

/// @brief
/// Event listener for stopping a looped effect
/// @param event
/// The event for the sound effect, contains everything for an effect to start
void SoundEngine::onStopLoopedEffect(const string& identifier) {
	stopLoopedEffect(identifier);
}

/// @brief
/// Event listener for when an effect has to be played
/// @param event
/// The event for the sound effect, contains everything for an effect to start
bool SoundEngine::onPlayEffect(const string& identifier, int volume, bool shouldLoop) {

	if (identifierExists(identifier)) {
		if (! identifierIsLoaded(identifier)) loadEffect(identifier);
		
		(shouldLoop) ? startLoopedEffect(identifier, volume) : playEffect(identifier, volume);

		return true;
	}
	return false;
}

/// @brief 
/// @param identifier 
/// @return 
bool SoundEngine::identifierExists(const string& identifier)
{
	return soundFacade->identifierExists(identifier);
}

/// @brief 
/// @param identifier 
/// @return 
bool SoundEngine::identifierIsLoaded(const string& identifier)
{
	return soundFacade->identifierIsLoaded(identifier);
}