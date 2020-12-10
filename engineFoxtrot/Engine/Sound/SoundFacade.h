#pragma once
#include "ISoundFacade.h"
#include "SceneManager/Objects/Object.h"

#define EXAMPLE_SOUND	"Assets/Sound/b423b42.wav"
#define EXAMPLE_SPRITE  "Assets/Sprites/simple.png"

#define FIRST_AVAILABLE_CHANNEL -1
#define DONT_LOOP 0
#define LOOP_INDEFINITELY -1

#define AUDIO_FREQUENCY 44100
#define AUDIO_CHANNEL_AMOUNT 2
#define AUDIO_CHUNK_SIZE 2048

struct Mix_Chunk;
struct _Mix_Music;
typedef struct _Mix_Music Mix_Music;

/// @brief 
/// SoundFacade is de Sound SDL2 facade
class API SoundFacade : public ISoundFacade
{
public:
	SoundFacade();
	~SoundFacade();

	bool isMix_PlayingMusic();

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
private:
	map<string, string> soundPaths;
	map<string, int> loopChannels;
	Mix_Music* music;
	// TODO clear on scene detach
	map<std::string, Mix_Chunk*> loadedSoundEffects;

};
