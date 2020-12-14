#pragma once
#include "SceneManager/Scene.h"
#include "SoundFacade.h"
#include "Events/Event.h"
#include "General/ISubsystem.h"

#define MAX_VOLUME 128

/// @brief 
/// SoundEngine is the Sound SDL2 wrapper
class  SoundEngine : public ISubsystem
{
public:
	SoundEngine();
	~SoundEngine();

	API void start(EventDispatcher& dispatcher) override { };
	API void update() override { };
	API void shutdown() override { };
	 
	API void setFiles(map<string, string> files);
	API void addFile(const string& identifier, const string& file);
	API void playEffect(const string& identifier, const int volume);
	API void loadEffect(const string& identifier);
	API void unloadEffect(const string& identifier);
	API void startLoopedEffect(const string& effect, const int volume);
	API void stopLoopedEffect(const string& identifier);
	API void loadMusic(const string& identifier);
	API void playMusic(const int volume);
	API void playMusic(const string& identifier, const int volume);
	API void changeMusic(const string& identifier);
	API void fadeOutMusic(const int fadeTime);
	API void fadeInMusic(const int fadeTime);
	API void fadeInMusic(const string& identifier, const int fadeTime);
	API void rewindMusic();
	API void stopMusic();
	API void pauseMusic();
	API void resumeMusic();
	API void flush();
	 
	API bool identifierExists(const string& identifier);
	API bool identifierIsLoaded(const string& identifier);
	
	API bool onPlayEffect(const string& identifier, int volume, bool shouldLoop);
	API void onStopLoopedEffect(const string& identifier);

private:
	void onChangeBackgroundMusic(const string& identifier, const int volume);


	// TODO clear on scene detach
	unique_ptr<ISoundFacade> soundFacade = unique_ptr<SoundFacade>(new SoundFacade);

};
