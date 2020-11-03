#pragma once
#include <unordered_map>
#include "ISoundFacade.h"
#include "SceneManager/Object.h"

#define EXAMPLE_SOUND	"../Assets/Sound/b423b42.wav"
#define EXAMPLE_SPRITE  "../Assets/Sprites/simple.png"

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

	void SetFiles(unordered_map<string, string> files) override;
	void AddFile(const string& identifier, const string& file) override;
	void PlayEffect(const string& identifier, const int volume) override;
	void LoadEffect(const string& identifier) override;
	void UnloadEffect(const string& identifier) override;
	void StartLoopedEffect(const string& effect) override;
	void StopLoopedEffect(const string& identifier) override;
	void LoadMusic(const string& identifier) override;
	void PlayMusic(const int volume) override;
	void PlayMusic(const string& identifier, const int volume) override;
	void ChangeMusic(const string& identifier) override;
	void FadeOutMusic(const int fadeTime) override;
	void FadeInMusic(const int fadeTime) override;
	void FadeInMusic(const string& identifier, const int fadeTime) override;
	void RewindMusic() override;
	void StopMusic() override;
	void PauseMusic() override;
	void ResumeMusic() override;
	void Flush() override;
	bool IdentifierExists(const string& identifier) override;
	bool IdentifierIsLoaded(const string& identifier) override;
	unordered_map<string, int>& GetLoopchannels() override;
	unordered_map<string, string>& GetSoundPaths() override;
private:
	unordered_map<string, string> soundPaths;
	unordered_map<string, int> loopChannels;
	Mix_Music* music;
	map<std::string, Mix_Chunk*> loadedSoundEffects;

};
