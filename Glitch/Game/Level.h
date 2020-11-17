#pragma once

/// @brief 
/// Level class. Level has all the information. 

#if(EXPORT)
class DLLEXPORT Level : public Scene
#else
class Level : public Scene
#endif
{
public:
	Level(const int id,const int _sceneHeight, const int _sceneWidth, map<string, string> sounds);
	virtual void OnAttach() override;
	virtual void Start() override;
	virtual void Pause();
	virtual void OnDetach() override;
	virtual void update() override;
private:
	map<string, string> sounds;
};