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
class SoundFacade : public ISoundFacade
{
public:
	API SoundFacade();
	API ~SoundFacade();

	API bool isMix_PlayingMusic();

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
private:
	map<string, string> soundPaths;
	map<string, int> loopChannels;
	Mix_Music* music;
	// TODO clear on scene detach
	map<std::string, Mix_Chunk*> loadedSoundEffects;

};
