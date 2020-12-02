#pragma once
#include "SceneManager/Scene.h"
#include "SoundFacade.h"
#include "Events/Event.h"
#include "General/ISubsystem.h"

#define MAX_VOLUME 128

/// @brief 
/// SoundEngine is the Sound SDL2 wrapper
class API SoundEngine : public ISubsystem
{
public:
	SoundEngine();
	~SoundEngine();

	void start(EventDispatcher& dispatcher) override { 
		soundFacade = new SoundFacade;
	};

	void update() override { };

	void shutdown() override {
		delete soundFacade;
	};

	void setFiles(map<string, string> files);
	void addFile(const string& identifier, const string& file);
	void playEffect(const string& identifier, const int volume);
	void loadEffect(const string& identifier);
	void unloadEffect(const string& identifier);
	void startLoopedEffect(const string& effect, const int volume);
	void stopLoopedEffect(const string& identifier);
	void loadMusic(const string& identifier);
	void playMusic(const int volume);
	void playMusic(const string& identifier, const int volume);
	void changeMusic(const string& identifier);
	void fadeOutMusic(const int fadeTime);
	void fadeInMusic(const int fadeTime);
	void fadeInMusic(const string& identifier, const int fadeTime);
	void rewindMusic();
	void stopMusic();
	void pauseMusic();
	void resumeMusic();
	void flush();

	bool identifierExists(const string& identifier);
	bool identifierIsLoaded(const string& identifier);

	bool onPlayEffect(const string& identifier, int volume, bool shouldLoop);
	void onStopLoopedEffect(const string& identifier);

	void onStartBackgroundMusicEvent(const string& identifier);
	void onLoadBackgroundMusicEvent(const string& identifier, const string& fileName);

private:
	void onChangeBackgroundMusic(const string& identifier, const int volume);

	ISoundFacade* soundFacade = new SoundFacade;
};
