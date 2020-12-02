#pragma once

/// @brief Interface class for Sound facade
class ISoundFacade
{
public:
	ISoundFacade() {};
	~ISoundFacade() {};

	virtual bool isMix_PlayingMusic() = 0;
	virtual void setFiles(map<string, string> files) = 0;
	virtual void addFile(const string& identifier, const string& file) = 0;
	virtual void playEffect(const string& identifier, const int volume) = 0;
	virtual void loadEffect(const string& identifier) = 0;
	virtual void unloadEffect(const string& identifier) = 0;
	virtual void startLoopedEffect(const string& effect, const int volume) = 0;
	virtual void stopLoopedEffect(const string& identifier) = 0;
	virtual void loadMusic(const string& identifier) = 0;
	virtual void playMusic(const int volume) = 0;
	virtual void playMusic(const string& identifier, const int volume) = 0;
	virtual void changeMusic(const string& identifier) = 0;
	virtual void fadeOutMusic(const int fadeTime) = 0;
	virtual void fadeInMusic(const int fadeTime) = 0;
	virtual void fadeInMusic(const string& identifier, const int fadeTime) = 0;
	virtual void rewindMusic() = 0;
	virtual void stopMusic() = 0;
	virtual void pauseMusic() = 0;
	virtual void resumeMusic() = 0;
	virtual void flush() = 0;

	virtual bool identifierExists(const string& identifier) = 0;
	virtual bool identifierIsLoaded(const string& identifier) = 0;

private:

};
