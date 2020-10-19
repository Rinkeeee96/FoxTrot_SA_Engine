#pragma once
#include "../SceneManager/Object.h"

/// @brief
/// A struct containing data for showing messages on screen
#if(EXPORT)
class DLLEXPORT Message
#else
struct Message
#endif
{
	Message(const string& _text, int _r, int _g, int _b)
		: text{ _text }, r{ _r }, g{ _g }, b{ _b }{}
	const string& text;
	int r, g, b;
};

/// @brief
/// A struct containing data for 2d positions
#if(EXPORT)
class DLLEXPORT Position
#else
struct Position
#endif
{
	Position(int _x, int _y) : x{ _x }, y{ _y } {}
	int x, y;
};

/// @brief
/// A struct containing data for width and height
#if(EXPORT)
class DLLEXPORT Size
#else
struct Size
#endif
{
	Size(int _w, int _h) : w{ _w }, h{ _h } {}
	int w, h;
};

/// @brief Interface class for SDL2 facade
#if(EXPORT)
class DLLEXPORT ISVI
#else
class ISVI
#endif
{
public:
	ISVI() {};
	~ISVI() {};

	// Video Functions
	virtual void initSDL() = 0;

	virtual void clearScreen() = 0;
	virtual void drawScreen() = 0;
	virtual void loadImage(const int spriteID, const char* filename) = 0;

	//TODO delete this is only for POC
	virtual void renderCopy(const int spriteID, const int xPos, const int yPos, const int width, const int height, const int rotation) = 0;

	virtual void renderCopy(Object& object) = 0;

	virtual void drawMessageAt(const Message& message, const Position& pos) = 0;

	// Input Functions
	virtual void input() = 0;

	// Sound Functions
	virtual void SetFiles(std::map<std::string, std::string> files) = 0;
	virtual void AddFile(const std::string& identifier, const std::string& file) = 0;
	virtual void PlayEffect(const std::string& identifier, const int volume) = 0;
	virtual void LoadEffect(const std::string& identifier) = 0;
	virtual void UnloadEffect(const std::string& identifier) = 0;
	virtual void StartLoopedEffect(const std::string& effect) = 0;
	virtual void StopLoopedEffect(const std::string& identifier) = 0;
	virtual void LoadMusic(const std::string& identifier) = 0;
	virtual void PlayMusic(const int volume) = 0;
	virtual void PlayMusic(const std::string& identifier, const int volume) = 0;
	virtual void ChangeMusic(const std::string& identifier) = 0;
	virtual void FadeOutMusic(const int fadeTime) = 0;
	virtual void FadeInMusic(const int fadeTime) = 0;
	virtual void FadeInMusic(const std::string& identifier, const int fadeTime) = 0;
	virtual void RewindMusic() = 0;
	virtual void StopMusic() = 0;
	virtual void PauseMusic() = 0;
	virtual void ResumeMusic() = 0;
	virtual void Flush() = 0;

	virtual bool IdentifierExists(const std::string& identifier) = 0;
	virtual bool IdentifierIsLoaded(const std::string& identifier) = 0;

private:

};
