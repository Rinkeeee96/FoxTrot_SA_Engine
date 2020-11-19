#pragma once
#include "SceneManager/SceneManager.h" //TODO check this
#include "SceneManager/Scene.h"
#include "SoundFacade.h"
#include "Events/Event.h"

/// @brief 
/// SoundEngine is the Sound SDL2 wrapper
class API SoundEngine
{
public:
	SoundEngine();
	~SoundEngine();

	void SetFiles(map<string, string> files);
	void AddFile(const string& identifier, const string& file);
	void PlayEffect(const string& identifier, const int volume);
	void LoadEffect(const string& identifier);
	void UnloadEffect(const string& identifier);
	void StartLoopedEffect(const string& effect, const int volume);
	void StopLoopedEffect(const string& identifier);
	void LoadMusic(const string& identifier);
	void PlayMusic(const int volume);
	void PlayMusic(const string& identifier, const int volume);
	void ChangeMusic(const string& identifier);
	void FadeOutMusic(const int fadeTime);
	void FadeInMusic(const int fadeTime);
	void FadeInMusic(const string& identifier, const int fadeTime);
	void RewindMusic();
	void StopMusic();
	void PauseMusic();
	void ResumeMusic();
	void Flush();

	bool IdentifierExists(const string& identifier);
	bool IdentifierIsLoaded(const string& identifier);
private:
	void onChangeBackgroundMusic(const string& identifier, const int volume);
	bool onPlayEffect(Event& event);
	bool onStopLoopedEffect(Event& event);

	bool onStartBackgroundMusicEvent(Event& event);
	bool onLoadBackgroundMusicEvent(Event& event);
	ISoundFacade* soundFacade = new SoundFacade;

};
