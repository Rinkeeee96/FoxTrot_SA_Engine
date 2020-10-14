#pragma once
#include <SDL_mixer.h>
#define FIRST_AVAILABLE_CHANNEL -1
#define DONT_LOOP 0
#define LOOP_INDEFINITELY -1

#define AUDIO_FREQUENCY 44100
#define AUDIO_CHANNEL_AMOUNT 2
#define AUDIO_CHUNK_SIZE 2048
namespace Glitch {
	class GLITCH_API SoundEngine
	{
	public:
		SoundEngine();
		~SoundEngine();
		void onChangeBackgroundMusic(const string& identifier, int volume);
		void onPlayEffect(const string& identifier, int volume);
		void SetFiles(map<string, string> files);
		void AddFile(const string& identifier, const string& file);
		void PlayEffect(const string& identifier, int volume);
		void LoadEffect(const string& identifier);
		void UnloadEffect(const string& identifier);
		void StartLoopedEffect(const string& effect);
		void StopLoopedEffect(const string& identifier);
		void LoadMusic(const string& identifier);
		void PlayMusic(int volume);
		void PlayMusic(const string& identifier, int volume);
		void ChangeMusic(const string& identifier);
		void FadeOutMusic(int fadeTime);
		void FadeInMusic(int fadeTime);
		void FadeInMusic(const string& identifier, int fadeTime);
		void RewindMusic();
		void StopMusic();
		void PauseMusic();
		void ResumeMusic();
		void Flush();
		bool IdentifierExists(const string& identifier);
		bool IdentifierIsLoaded(const string& identifier);
	private:
		map<string, string> soundPaths;
		map<string, int> loopChannels;
		Mix_Music* music;
		std::map<std::string, Mix_Chunk*> loadedSoundEffects;
	private:

	};

	SoundEngine::SoundEngine()
	{
	}

	SoundEngine::~SoundEngine()
	{
	}
}