#include "stdafx.h"
#include "SoundEngine.h"

SoundEngine::SoundEngine() {}
SoundEngine::~SoundEngine(){}

/// @brief 
/// @param files 
void SoundEngine::SetFiles(map<string, string> files)
{
	soundFacade->SetFiles(files);
}
/// @brief 
/// @param identifier 
/// @param file 
void SoundEngine::AddFile(const string& identifier, const string& file)
{
	soundFacade->AddFile(identifier, file);
}
/// @brief 
/// @param effect 
/// @param volume 
void SoundEngine::PlayEffect(const string& effect, int volume = MAX_VOLUME)
{
	soundFacade->PlayEffect(effect, volume);
}
/// @brief 
/// @param identifier 
void SoundEngine::LoadEffect(const string& identifier)
{
	soundFacade->LoadEffect(identifier);
}
/// @brief 
/// @param identifier 
void SoundEngine::UnloadEffect(const string& identifier)
{
	soundFacade->UnloadEffect(identifier);
}
/// @brief 
/// @param effect 
void SoundEngine::StartLoopedEffect(const string& effect, int volume = MAX_VOLUME)
{
	soundFacade->StartLoopedEffect(effect, volume);
}
/// @brief 
/// @param identifier 
void SoundEngine::StopLoopedEffect(const string& identifier)
{
	soundFacade->StopLoopedEffect(identifier);
}
/// @brief 
/// @param identifier 
void SoundEngine::LoadMusic(const string& identifier)
{
	soundFacade->LoadMusic(identifier);
}
/// @brief 
/// @param volume 
void SoundEngine::PlayMusic(int volume = MAX_VOLUME)
{
	soundFacade->PlayMusic(volume);
}
/// @brief 
/// @param identifier 
/// @param volume 
void SoundEngine::PlayMusic(const string& identifier, int volume = MAX_VOLUME)
{
	soundFacade->PlayMusic(identifier, volume);
}
/// @brief 
/// @param identifier 
void SoundEngine::ChangeMusic(const string& identifier)
{
	soundFacade->ChangeMusic(identifier);
}
/// @brief 
/// @param fadeTime 
void SoundEngine::FadeOutMusic(int fadeTime)
{
	soundFacade->FadeOutMusic(fadeTime);
}
/// @brief 
/// @param fadeTime 
void SoundEngine::FadeInMusic(int fadeTime)
{
	soundFacade->FadeInMusic(fadeTime);
}
/// @brief 
/// @param identifier 
/// @param fadeTime 
void SoundEngine::FadeInMusic(const string& identifier, int fadeTime)
{
	soundFacade->FadeInMusic(identifier, fadeTime);
}
/// @brief 
void SoundEngine::RewindMusic()
{
	soundFacade->RewindMusic();
}
/// @brief 
void SoundEngine::StopMusic()
{
	soundFacade->StopMusic();
}
/// @brief 
void SoundEngine::PauseMusic()
{
	soundFacade->PauseMusic();
}
/// @brief 
void SoundEngine::ResumeMusic()
{
	soundFacade->ResumeMusic();
}
/// @brief 
void SoundEngine::Flush()
{
	soundFacade->Flush();
}



/// @brief
/// Event listener for when the music has to be changed
/// @param identifier
/// The identifier of the music to play
/// @param volume
/// The volume to play the music at. Ranges from 0 to 128
void SoundEngine::onChangeBackgroundMusic(const string& identifier, int volume = MAX_VOLUME) {
	if (IdentifierExists(identifier)) {
		if (soundFacade->isMix_PlayingMusic()) {
			ChangeMusic(identifier);
		}
		else {
			LoadMusic(identifier);
			PlayMusic(volume);
		}
	}
}

/// @brief
/// Event listener for stopping a looped effect
/// @param event
/// The event for the sound effect, contains everything for an effect to start
void SoundEngine::onStopLoopedEffect(const string& identifier) {
	StopLoopedEffect(identifier);
}

/// @brief
/// Event listener for when an effect has to be played
/// @param event
/// The event for the sound effect, contains everything for an effect to start
bool SoundEngine::onPlayEffect(const string& identifier, int volume, bool shouldLoop) {

	if (IdentifierExists(identifier)) {
		if (! IdentifierIsLoaded(identifier)) LoadEffect(identifier);
		
		(shouldLoop) ? StartLoopedEffect(identifier, volume) : PlayEffect(identifier, volume);

		return true;
	}
	return false;
}

/// @brief 
/// @param identifier 
/// @return 
bool SoundEngine::IdentifierExists(const string& identifier)
{
	return soundFacade->IdentifierExists(identifier);
}

/// @brief 
/// @param identifier 
/// @return 
bool SoundEngine::IdentifierIsLoaded(const string& identifier)
{
	return soundFacade->IdentifierIsLoaded(identifier);
}

void SoundEngine::onStartBackgroundMusicEvent(const string& identifier) {
	this->PlayMusic(identifier, 15);
}
void SoundEngine::onLoadBackgroundMusicEvent(const string& identifier, const string& fileName) {
	this->AddFile(identifier, fileName);
}