#pragma once
#include "SceneManager/Scene.h"

/// @brief 
/// Level class. Level has all the information. 

#if(EXPORT)
class DLLEXPORT Level : public Scene
#else
class Level : public Scene
#endif
{
public:
	Level(const int id, unordered_map<string, string> sounds);
	virtual void OnAttach() override;
	virtual void Start() override;
	virtual void Pause();
	virtual void OnDetach() override;
private:
	unordered_map<string, string> sounds;
};